/********************************************************/
//
//  概要
//      PWM設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __PWM_H__
#define __PWM_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      PWM設定 プロトタイプ宣言
/********************************************************/
void pwm_init(void);			// PWMの初期化
int anti_lock_pwm(double duty);	// モータのアンチロックのPWMをコントロールする
int servo_pwm(double range);	// サーボのPWMをコントロールする

/********************************************************/
//  TUTrobo
//
//  概要
//      PWM設定 PWM値定義
/********************************************************/

/************** PWM設定 PWM値定義 ここから***************/
	#define MOTOR_DUTY_100		// モーターMAXduty = 100
//	#define MOTOR_DUTY_90		// モーターMAXduty = 90
/************** PWM設定 PWM値定義 ここから***************/

	//////////////////////////////////////////////////////	
#ifdef	MOTOR_DUTY_100
	/******周期 20[kHz]  MAXduty 100[%] の設定開始*******/
	
	#define CYCLE		1250		// 周期設定
	#define UP_LIMIT 	1249		// MAXカウント値 	周期より1小さいのはPWMMAX値は1249だから
	#define DOWN_LIMIT	1			// MINカウント値	
	#define THRESHOLD 	625			// THRESHOLDカウント値
	
	/******周期 20[kHz]  MAXduty 100[%] の設定終了*******/
#endif
	//////////////////////////////////////////////////////
#ifdef	MOTOR_DUTY_90	
	/******周期 20[kHz]  MAXduty 90[%] の設定開始*******/
	
	#define CYCLE		1250		// 周期設定
	#define UP_LIMIT 	1125		// MAXカウント値 	周期より1小さいのはPWMMAX値は1249だから
	#define DOWN_LIMIT	125			// MINカウント値	
	#define THRESHOLD 	625			// THRESHOLDカウント値
	
	/********周期 20[kHz]  MAXduty 90[%] の設定終了*********/
#endif
	//////////////////////////////////////////////////////
	/********周期 50[Hz]  サーボPWM の設定開始*********/
	#define SERVO_CYCLE	31250		// 周期設定			
	#define SERVO_UP 	3340		// MAXカウント値 	
	#define SERVO_DOWN	1200		// MINカウント値	
	#define SERVO_TH 	2270		// THRESHOLDカウント値
	/********周期 50[Hz]  サーボPWM の設定終了*********/

#endif // __PWM_H__