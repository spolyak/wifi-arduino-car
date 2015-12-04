// motor shield

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
// You can also make another motor on port M2
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(4);
const int LEFT_MOTOR_PIN = 8;
const int RIGHT_MOTOR_PIN = 2;
const int BACK_PIN = 9;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  pinMode(LEFT_MOTOR_PIN, INPUT_PULLUP);
  pinMode(RIGHT_MOTOR_PIN, INPUT);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(100);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

  myOtherMotor->setSpeed(100);
  myOtherMotor->run(FORWARD);
  // turn on motor
  myOtherMotor->run(RELEASE);
}

int leftMotorPin = HIGH;
int rightMotorPin = HIGH;
int backPin = HIGH;

void loop() {
  uint8_t i;

  backPin = digitalRead(BACK_PIN);
  if(backPin == LOW) {
    myMotor->setSpeed(150);
    myMotor->run(BACKWARD);
    myOtherMotor->setSpeed(150);
    myOtherMotor->run(BACKWARD);
  } else {
  
  leftMotorPin = digitalRead(LEFT_MOTOR_PIN);
  if(leftMotorPin == HIGH) {
    myMotor->setSpeed(0);
  } else {
    myMotor->setSpeed(150);
    myMotor->run(FORWARD);
  }
  rightMotorPin = digitalRead(RIGHT_MOTOR_PIN);
  if(rightMotorPin == HIGH) {
    myOtherMotor->setSpeed(0);
  } else {
    myOtherMotor->setSpeed(150);
    myOtherMotor->run(FORWARD);
  }
  }
}
