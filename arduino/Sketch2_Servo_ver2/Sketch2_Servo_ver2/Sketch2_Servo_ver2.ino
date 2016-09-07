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

#include <SPI.h>
#include <Wire.h>
#include <C:\Users\idry7lash629\Documents\GitHub\catch2016\arduino\Sketch2_Servo_ver2\Sketch2_Servo_ver2\Adafruit_PWMServoDriver.h>
#include <TimerOne.h>

// the setup function runs once when you press reset or power the board


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// called this way, it uses the default address 0x40

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
//#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  400 // this is the 'maximum' pulse length count (out of 4096)

#define AMP0_TARGET 400
#define AMP1_TARGET 400
#define AMP2_TARGET 400
#define AMP2_TARGET2 250
#define SHABAASH_OFF 160
#define SHABAASH_ON	350

int PIN_B_L = 30;
int PIN_B_R = 32;
int PIN_B_U = 34;
int PIN_B_U2 = 36;
int PIN_SHABAASH = 38;

// our servo # counter
uint8_t servonum = 0;

int target_pulse[3] = { SERVOMIN };
int current_pulse[3] = { SERVOMIN };
int shabaash_val = SHABAASH_OFF;

boolean flag_setting = false;

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
	
	

	Serial.begin(57600);
	//Serial.println("16 channel Servo test!");

	pwm.begin();

	//pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates


	Timer1.initialize(500); //マイクロ秒単位で設定//1000
	Timer1.attachInterrupt(flash);



	pinMode(PIN_B_L, INPUT);
	pinMode(PIN_B_R, INPUT);
	pinMode(PIN_B_U, INPUT);
	pinMode(PIN_B_U2, INPUT);
	pinMode(PIN_SHABAASH, INPUT);

	pwm.setPWM(0, 0, SERVOMIN);
	pwm.setPWM(4, 0, SERVOMIN);
	pwm.setPWM(8, 0, SERVOMIN);
	pwm.setPWM(12, 0, SERVOMIN);
	pwm.setPWM(15, 0, SERVOMIN);
	//yield();
	Serial.println("16 channel Servo test!");

}
// the loop function runs over and over again until power down or reset
void loop() {

	int inputchar;
	

	// シリアルポートより1文字読み込む
	inputchar = Serial.read();

	//Serial.println("16 channel Servo test!");

	if (inputchar != -1) {
		// 読み込んだデータが -1 以外の場合　以下の処理を行う

		switch (inputchar) {
		case 'u':
			if (flag_setting == true) {
				Serial.print("U\n\r");

				target_pulse[0] = SERVOMAX;
				target_pulse[1] = SERVOMAX;
				target_pulse[2] = SERVOMAX;
			}
			

			break;
		case 'd':
			if (flag_setting == true) {
				Serial.print("D\n\r");

				target_pulse[0] = SERVOMIN;
				target_pulse[1] = SERVOMIN;
				target_pulse[2] = SERVOMIN;
			}
			

			break;


		case 't':
			if (flag_setting == true) {
				Serial.print("T\n\r");

				target_pulse[0] = AMP0_TARGET;
				target_pulse[1] = AMP1_TARGET;
				target_pulse[2] = AMP2_TARGET;
			}
			

			break;

		case 's':

			Serial.print("Setting\n\r");
			flag_setting = true;
			

			break;

		case 'r':

			Serial.print("running\n\r");
			flag_setting = false;


			break;

		case '1':
			shabaash_val+= 10;
			Serial.print("shabaash_val=");
			Serial.println(shabaash_val);
			break;

		case '2':
			shabaash_val -= 10;
			Serial.print("shabaash_val=");
			Serial.println(shabaash_val);
			break;
		}
		
	}
	else {
		// 読み込むデータが無い場合は何もしない
	}


	if (flag_setting == false) {
		if (digitalRead(PIN_B_L)) {
			target_pulse[0] = AMP0_TARGET;
		}
		else {
			target_pulse[0] = SERVOMIN;
		}

		if (digitalRead(PIN_B_R)) {
			target_pulse[1] = AMP1_TARGET;
		}
		else {
			target_pulse[1] = SERVOMIN;
		}

		if (digitalRead(PIN_B_U2))
		{
			target_pulse[2] = AMP2_TARGET2;
		}
		else if (digitalRead(PIN_B_U)) {
			target_pulse[2] = AMP2_TARGET;
		}
		else {
			target_pulse[2] = SERVOMIN;
		}
		if (digitalRead(PIN_SHABAASH)) {
			shabaash_val = SHABAASH_ON;
		}
		else {
			shabaash_val = SHABAASH_OFF;
		}
	}
	

	pwm.setPWM(0, 0, current_pulse[0]);
	pwm.setPWM(4, 0, current_pulse[1]);
	pwm.setPWM(8, 0, current_pulse[2]);
	pwm.setPWM(12, 0, shabaash_val);
	pwm.setPWM(15, 0, shabaash_val);
}

// 割り込み時に処理される関数
void flash() {
	for (size_t i = 0; i < 3; i++)
	{

		if (current_pulse[i] != target_pulse[i]) {


			if (current_pulse[i] < target_pulse[i]) {
				current_pulse[i] += 10;//2
				if (current_pulse[i] >= SERVOMAX) current_pulse[i] = SERVOMAX;

			}
			if (current_pulse[i] > target_pulse[i]) {
				current_pulse[i] -= 10;
				if (current_pulse[i] <= SERVOMIN) current_pulse[i] = SERVOMIN;
			}
			/*
			else {

				current_pulse[i] = target_pulse[i];
			}*/

			
		}
		
		if (flag_setting) {
			//Serial.println(current_pulse[0]);
		}

	}
	//Serial.println("aaaaaaa");
	
}


