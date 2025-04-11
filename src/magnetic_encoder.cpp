#include <Arduino.h>
#include "magnetic_encoder.h"

/*  Magnetic Encoder Code for the AEAT-6600-T16 (C++ Version)
*   Written by: Alexander Fried
*
*   Intended to be used with the Arduino UNO R3. Most of the code is derived from Dan Royer's(GitHub: i-make-robots)
*   "aeat6600-t16-sensor-test" repository. The sensor should be setup to match the schematic from an unnamed user's
*   (GitHub: 4answer) "AEAT-6600-T16" repository.
*
*   Created for data collection with a surveyor's wheel. You must record your specific wheel's radius under 
*   "WHEEL_RAD" in the variable defintions section below.
*
*   This code was written using the following sources as references:
*   https://github.com/4nswer/AEAT-6600-T16
*   https://github.com/MarginallyClever/aeat6600-t16-sensor-test
*   https://forum.arduino.cc/t/absolute-rotary-encoder-ssi-spi-how/153103
*/

// Pin Definitions:
#define MAG_HI      3
#define MAG_LO      2
#define ALIGN_PIN   4
#define PWM_PIN     7
#define PWR_DWN     5
#define PROG_PIN    9
#define NCS_PIN     10
#define CLK_PIN     11
#define DATA_PIN    12

// Variable Definitions:
#define ANGLE_BITS      (10)
#define BIT_COUNT       (10)
#define ANGLE_PER_BIT   (360.0/(float)((long)1<<ANGLE_BITS))
#define WHEEL_RAD       (0.25)               // Radius of wheel in meters 
#define PI              3.1415926
#define DIST_PER_ANGLE  ((WHEEL_RAD * 2 * PI)/360.0)
#define DIST_PER_BIT    ((DIST_PER_ANGLE)/(ANGLE_PER_BIT))
double totalDistance = 0;
double pastPosition = 0;

void magneticEncoder::setup() {
  pinMode(MAG_HI, INPUT);                   // Outputs HIGH when magnetic field is too strong
  pinMode(MAG_LO, INPUT);                   // Outputs HIGH when magnetic field is too weak
  pinMode(ALIGN_PIN,OUTPUT);                // Set LOW for normal operation, set HIGH for alignment mode
  pinMode(PWR_DWN,OUTPUT);                  // Set HIGH to begin powering-off the device 
  pinMode(PROG_PIN,OUTPUT);                 // Set LOW for normal operation, set HIGH for OTP programming (pull-down)
  pinMode(NCS_PIN,OUTPUT);                  // Set HIGH for internal pull-up
  pinMode(DATA_PIN, INPUT);                 // Outputs sensor readings
  pinMode(CLK_PIN, OUTPUT);                 // Set HIGH to begin the clock
  //digitalWrite(NCS_PIN, HIGH);
  digitalWrite(CLK_PIN, HIGH);
  Serial.begin(57600);                      // Sets the data rate to the specified bits-per-second
  Serial.println("Surveyor's Wheel Distance Calculations: ");
}

void magneticEncoder::loop() {
  //digitalWrite(NCS_PIN, LOW);
  delay(3000);
  double distTraveled = getDistTraveled();
  totalDistance += distTraveled;
  Serial.print("Current Distance from Start: ");
  Serial.print(totalDistance);
  Serial.println("m");
  Serial.print("Distance since last Reading: ");
  Serial.print(distTraveled);
  Serial.print("m");
}

// Function Definitions:
double magneticEncoder::getDistTraveled() {
  double currPosition = (readPosition() * DIST_PER_BIT);
  double distTraveled = currPosition - pastPosition;
  pastPosition = currPosition;
  return distTraveled;
}

uint32_t magneticEncoder::readPosition() {
  uint32_t data = 0;
  uint8_t instream = 0;

  digitalWrite(NCS_PIN, LOW);
  delayMicroseconds(1);
  digitalWrite(CLK_PIN, LOW);
  delayMicroseconds(1);

  for(int i = 0; i < BIT_COUNT; i++) {
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(1);
    instream = digitalRead(DATA_PIN);
    data = (data << 1) | instream;
  }

  digitalWrite(NCS_PIN, HIGH);
  digitalWrite(CLK_PIN, HIGH);

  return data;
}