# WiFi Robot Car

This Arduino robot car implementation was originally based on this project [implementation](https://github.com/spolyak/wifi-arduino-car/blob/master/wifi-controlled-mobile-robot.pdf). After I bought the WiFi shield and Motor shield though I realized that I had a pin conflict so I decided to try the build using two Arduino boards instead. This buildout achieves the same result using two boards.

# The Parts

* 2 Arduino Uno boards
* 1 2WD Motor Smart Robot Car Chassis Kit Speed Encoder Battery Box for Arduino
* 1 DFRobot 7.4V LiPo 2200mAh Battery (Arduino Power Jack)
* 1 6 x AA battery holder with 5.5mm/2.1mm plug
* 2 arduino breadboards
* HC - SR04 Ultrasonic Distance Measuring Sensor Module for Arduino / NewPing Library
* Solder iron, solder
* LED, resistor (purple, black, red, gold)
* Breadboard jumper cables
* Adafruit Motor/Stepper/Servo Shield for Arduino v2 Kit - v2.3
* Adafruit HUZZAH CC3000 WiFi Shield with Onboard Antenna
* Set of stackable headers

# The Car

The robot car can be controlled via WiFi using a webpage that issues REST server commands to the car. The car built looks like this:

![r1](https://raw.githubusercontent.com/spolyak/wifi-arduino-car/master/img/r1.JPG)
![r2](https://raw.githubusercontent.com/spolyak/wifi-arduino-car/master/img/r2.JPG)

The wiring is summarized as follows:
![r3](https://raw.githubusercontent.com/spolyak/wifi-arduino-car/master/img/r3.JPG)

# The Robot Software

Software artifacts for an arduino wifi car

Need libraries:
* Adafruit CC3000 library (http://adafru.it/cFn) 
* aREST (http://adafru.it/dis) library. To install the library, simply clone the Git repository or extract the files in your Arduino /libraries folder.
* [New ping library](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home#!newping-arduino-library-for-arduino)

See the src folder for code for the code. The robot code goes to the wifi/uno shield and the robot motor software goes to the motor/uno shield.

# The website software

See the interface folder using node.js

