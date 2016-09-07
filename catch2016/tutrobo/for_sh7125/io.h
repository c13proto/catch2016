/********************************************************/
//
//  概要
//      ポート関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __IO_H__
#define __IO_H__


#define INPUT_PIN(port,pin) (port##.DR.BIT.B##pin)
#define INPUT_PIN_PF(pin) (PF.DRL.BIT.B##pin)
#define OUTPUT_PIN(port,pin) (port##.DRL.BIT.B##pin)

#define PWM_PIN(ch,port) (MTU2##ch##.TGR##port)


#define ON 1
#define OFF 0


/********************************************************/
//  TUTrobo
//
//  概要
//      ポート関連 プロトタイプ宣言
/********************************************************/
void power_init(void);							// モータ・エアーの電源供給用の初期設定
void buzzer_init(void);							// BUZZERの初期設定
void led_init(void);							// LEDの初期設定
void mode_init(void);							// モード選択の初期設定
void button_init(void);							// ボタンの初期設定
void limit_init(void);							// LIMITの初期設定

void front_limit_init(void);					// マシンの前のリミットの初期設定
void back_limit_init(void);						// マシンの後のリミットの初期設定

void io_init(void);		 						// PINの初期設定

//void buzzer_on(void);							// BUZZERをONにする
//void buzzer_off(void);							// BUZZERをOFFにする

//void power_on(void);							// 電源供給を行う
//void power_off(void);							// 電源供給を行わない

void led_on(void);								// LEDをONにする
void led_off(void);								// LEDをOFFにする
void led_ctrl(char number);						// LEDの点き方をコントロールする

char mode(void);								// モード選択

char button(void);								// ボタン認識

char limit(void);								// リミット認識

/********************************************************/
//  TUTrobo
//
//  概要
//      ポート関連 定数定義
/********************************************************/
#define OPEN	1
#define CLOSE	0

/*----------------------------------------------*/
void motor_o(double raw_duty);					// MOTOR_oの設定
void motor_l(double raw_duty);					// MOTOR_lの設定
void motor_r(double raw_duty);					// MOTOR_rの設定
void leaf_collect_hand(char state);				// AIR関数(リーフ回収ハンド)
void leaf_esta_hand(char state);				// AIR関数(リーフ設置ハンド)
void motor_L_arm(double raw_duty);				//Lアーム
void motor_fish(double raw_duty);				//釣竿
#endif // __IO_H__