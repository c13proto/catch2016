/********************************************************/
//
//  概要
//      PWM設定
//  作成者
//		@ TUTrobo
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
void motor_pwm_init(void);		// MOTOR_PWMの初期化
void servo_pwm_init(void);		// SORVO_PWMの初期化
int anti_lock_pwm(double duty);	// モータのアンチロックのPWMをコントロールする
int servo_pwm(double range);	// サーボのPWMをコントロールする

/********************************************************/
//  TUTrobo
//
//  概要
//      PWM設定 PWM値定義
/********************************************************/

/************** PWM設定 PWM値定義 ここから***************/
/************** PWM設定 PWM値定義 ここから***************/

	/******周期 60[kHz]  MAXduty 100[%] の設定開始*******/
		
	#define ANTI_CYCLE		2400//800		// 周期設定  cycle=48000k/60k
	#define ANTI_UP_LIMIT 	2399//799		// MAXカウント値 	周期より1小さいのはPWMMAX値は1249だから
	#define ANTI_DOWN_LIMIT	1			// MINカウント値	
	#define ANTI_THRESHOLD 	1200//400			// THRESHOLDカウント値
	
	/******周期 60[kHz]  MAXduty 100[%] の設定終了*******/

	/******周期 20[kHz]  MAXduty 100[%] の設定開始*******/
	
	#define SIGN_CYCLE		2400		// 周期設定  cycle=48000k/20k
	#define SIGN_UP_LIMIT 	2399		// MAXカウント値 	周期より1小さいのはPWMMAX値は1249だから
	#define SIGN_DOWN_LIMIT	1			// MINカウント値	
	#define SIGN_THRESHOLD 	1200			// THRESHOLDカウント値
	
	/******周期 20[kHz]  MAXduty 100[%] の設定終了*******/
	//////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////
	/********周期 50[Hz]  サーボPWM の設定開始*********/
	#define SERVO_CYCLE	60000//31250		// 周期設定			
	#define SERVO_UP 	7000//3340		// MAXカウント値 	
	#define SERVO_DOWN	500//1200		// MINカウント値	
	#define SERVO_TH 	3250//2270		// THRESHOLDカウント値
	/********周期 50[Hz]  サーボPWM の設定終了*********/

#endif // __PWM_H__