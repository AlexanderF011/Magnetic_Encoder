## Magnetic_Encoder
Includes test code for the AEAT-6600-T16 magnetic encoder. Written with the intention of using the encoder for a Surveyor's Wheel.

The microcontroller of choice for this project was the Arduino UNO R3. Maybe be modified in the future to work with the TM4C123G launchpad.

References two GitHub repositories created by Andrew Becker(4nswer) and GitHub user i-make-robots, as well as code from a public forum that Becker linked.

# Parts Links:
https://www.mouser.com/ProductDetail/Broadcom-Avago/AEAT-6600-T16?qs=8n%2FQlCIuKOdOdhSdcPVfJA%3D%3D
This encoder has TSSOP-16 layout
- In order to get data from this, due to the close proximity of the pins, it is necessary to use https://www.mouser.com/ProductDetail/535-LCQT-TSSOP16
- Halfway through the project, we also purchased https://www.mouser.com/ProductDetail/652-PEC11H4215FS0024 because of complications with the original encoder.
The rest of the parts are simply hardware or came with the pre-existing box, save the Arduino Uno.

# Reference Code:
- https://github.com/4nswer/AEAT-6600-T16
- https://github.com/MarginallyClever/aeat6600-t16-sensor-test
- https://forum.arduino.cc/t/absolute-rotary-encoder-ssi-spi-how/153103
Full credit for the initial C++ code goes to them.
