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



/********************************************************/
//ポートの役割 たんぽぽ
//	CN1									CN2			
//	1	PD0		POWER					1	PA0		PWM6A　同期モード20kHz	
//	2	PD1		BUZZER 					2	PA1		PWM6B　同期モード20kHz	
//	3	PD2		AIR						3	PA2		PWM6C　同期モード20kHz	
//	4	PD3		AIR						4	PA3		PWM6D　同期モード20kHz	
//	5	PD4		AIR						5	PA4		laser
//	6	PD5		cet						6	PA5		AIR
//	7	PD6		cet						7	PA6		AIR	
//	8	PD7								8	PA7		AIR
//	9	PE0		LIMIT_SW0 				9	PB0		PWM9A　同期モード20kHz		
//	10	PE1		LIMIT_SW1				10	PB1		PWM9C　同期モード20kHz		
//	11	PE2		LIMIT_SW2				11	PB2		mode	
//	12	PE3		LIMIT_SW3				12	PB3	    mode
//	13	PE4		LIMIT_SW4				13	PB4		PWM10A	
//	14	PE5		LIMIT_SW5				14	PB5		PWM10C	
//	15	PE6		LIMIT_SW6				15	PB6			
//	16	PE7		LIMIT_SW7				16	PB7			
//	17	P40		AN0						17	PC0		MTCLKG-A	
//	18	P41		AN1						18	PC1		MTCLKH-A	
//	19	P42		AN2						19	PC2     MTCLKE-A	
//	20	P43		AN3						20	PC3		MTCLKF-A	
//	21	P44		AN4						21	PC4		MTCLKC-B	
//	22	P45		AN5						22	PC5		MTCLKD-B	
//	23	P46		AN6						23	PC6		MTCLKA-B	
//	24	P47		AN7						24	PC7		MTCLKB-B
//	25	P30		RxD1	PC				25	P20		TxD0 	コントローラ
//	26	P31								26	P21		RxD0 	コントローラ
//	27	P32		PWM0C　同期モード20kHz	27	P22		SCK0
//	28	P33		PWM0D　同期モード20kHz	28	P23		
//	29	P34		PWM0A　同期モード20kHz	29	P24		PWM4A　同期モード20kHz
//	30	P35								30	P25		PWM4C　同期モード20kHz
//	31	P05								31	P26		TxD1 	PC
//	32	P07								32	P27		SCK1
//	33	AVCC							33	P50		TxD2-B  ジャイロ
//	34	EMLE							34	P51		SCK2
//	35	MD1								35	P52		RxD2-B ジャイロ
//	36	RES								36	P53		
//	37	VCC								37	P54			
//	38	GND								38	P55			
//	39	VCC								39	P12		
//	40	GND								40	P13		PWM0B　同期モード20kHz

/********************************************************/
#define SET_P_INPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =0; port##.PCR.BIT.B##pin =1; port##.ICR.BIT.B##pin  =1;}
//ex)SET_PULL_INPUT(PORTE,7); // プルアップ付入力設定
#define SET_OUTPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =1;}
#define SET_P_INPUT(port) { port##.DDR.BYTE =0x00; port##.PCR.BYTE =0xFF; port##.ICR.BYTE  =0xFF;}
#define SET_INPUT(port) { port##.DDR.BYTE =0x00; port##.ICR.BYTE  =0xFF;}
#define SET_INPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =0; port##.ICR.BIT.B##pin  =1;}
#define SET_OUTPUT(port) { port##.DDR.BYTE =0xFF;}
#define INPUT_PIN(port,pin) (port##.PORT.BIT.B##pin)
#define OUTPUT_PIN(port,pin) (port##.DR.BIT.B##pin)
#define PWM_PIN(ch,port) (MTU##ch##.TGR##port)

/********************************************************/
//  TUTrobo
//
//  概要
//      ポート関連 プロトタイプ宣言
/********************************************************/
//void power_init(void);							// モータ・エアーの電源供給用の初期設定
//void buzzer_init(void);							// BUZZERの初期設定
//void led_init(void);							// LEDの初期設定
//void mode_init(void);							// モード選択の初期設定
//void button_init(void);							// ボタンの初期設定
//void limit_init(void);							// LIMITの初期設定

//void front_limit_init(void);					// マシンの前のリミットの初期設定
//void back_limit_init(void);						// マシンの後のリミットの初期設定

void io_init(void);		 						// PINの初期設定

//void buzzer_on(void);							// BUZZERをONにする
//void buzzer_off(void);							// BUZZERをOFFにする

//void power_on(void);							// 電源供給を行う
//void power_off(void);							// 電源供給を行わない

//void led_on(void);								// LEDをONにする
//void led_off(void);								// LEDをOFFにする
//void led_ctrl(char number);						// LEDの点き方をコントロールする

//char mode(void);								// モード選択

//char button(void);								// ボタン認識

//char limit(void);								// リミット認識

/********************************************************/
//  TUTrobo
//
//  概要
//      ポート関連 定数定義
/********************************************************/
#define OPEN	1
#define CLOSE	0
#define ON	1
#define OFF	0


/*----------------------------------------------*/
void motor_o(double raw_duty);					// MOTOR_oの設定
void motor_l(double raw_duty);					// MOTOR_lの設定
void motor_r(double raw_duty);					// MOTOR_rの設定
void motor_servo(int state);					// SERVOの設定
void leaf_collect_hand(char state);				// AIR関数(リーフ回収ハンド)
void leaf_esta_hand(char state);				// AIR関数(リーフ設置ハンド)
void motor_L_arm(double raw_duty);				//Lアーム
void motor_fish(double raw_duty);				//釣竿
//void motor_tower_L_stopper(double raw_duty);	//Lタワーストッパー
//void motor_front_shift(double raw_duty);		//全体を前に出すやつ
#endif // __IO_H__