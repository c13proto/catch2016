/*
 Name:		Sketch2_Servo_I2C.ino
 Created:	2016/07/17 0:22:23
 Author:	kenta
*/
/***************************************************
This is an example for our Adafruit 16-channel PWM & Servo driver
Servo test - this will drive 16 servos, one after the other

Pick one up today in the adafruit shop!
------> http://www.adafruit.com/products/815

These displays use I2C to communicate, 2 pins are required to
interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
soshite
Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, all text above must be included in any redistribution
****************************************************/

#include <Wire.h>
#include <C:\Users\idry7lash629\Documents\GitHub\catch2016\arduino\Sketch2_Servo_I2C\Sketch2_Servo_I2C\Adafruit_PWMServoDriver.h>
// the setup function runs once when you press reset or power the board


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// called this way, it uses the default address 0x40

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;


// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
	double pulselength;

	pulselength = 1000000;   // 1,000,000 us per second
	pulselength /= 60;   // 60 Hz
	Serial.print(pulselength); Serial.println(" us per period");
	pulselength /= 4096;  // 12 bits of resolution
	Serial.print(pulselength); Serial.println(" us per bit");
	pulse *= 1000;
	pulse /= pulselength;
	Serial.println(pulse);
	pwm.setPWM(n, 0, pulse);
}



void setup() {
	Serial.begin(9600);
	Serial.println("16 channel Servo test!");

	pinMode(30, INPUT_PULLUP);
	pinMode(32, INPUT_PULLUP);
	pinMode(34, INPUT_PULLUP);
	pinMode(36, INPUT_PULLUP);
	pinMode(38, INPUT_PULLUP);
	
	pwm.begin();
	pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

	yield();
}
// the loop function runs over and over again until power down or reset
void loop() {
	// Drive each servo one at a time
	int servo_val = SERVOMIN + (double)(SERVOMAX - SERVOMIN)*analogRead(0) / 1023.0;
	
	Serial.print(digitalRead(30));
	Serial.print(digitalRead(32));
	Serial.print(digitalRead(34));
	Serial.print(digitalRead(36));
	Serial.print(digitalRead(38));
	
	Serial.print(":");
	Serial.print(servo_val);
	Serial.print(":");
	Serial.println(servonum);
	
	pwm.setPWM(servonum, 0, servo_val);
	delay(500);
	pwm.setPWM(servonum, 0, SERVOMIN);
	delay(500);

	servonum++;
	if (servonum > 7) servonum = 0;
}
