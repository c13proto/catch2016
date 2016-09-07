/********************************************************/
//
//  概要
//      ポート関連
//  注意
//		マイコン依存ファイル!!
//  作成者
//		K.yamada @ TUTrobo
//
/********************************************************/


#include "../setup.h"		//マイコンの設定


/********************************************************/
//  名前      
//		MTU2_init
//  概要
// 		SETUP関数
//  機能説明
//		MTU2のスタンバイ解除
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void MTU2_init(void)
{
	MSTP_MTUA=0; // mtu0~5
	MSTP_MTUB=0; // mtu6~11	//スタンバイ解除
}
/********************************************************/
//  名前      
//		io_init
//  概要
// 		IO関数
//  機能説明
//		PINの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void io_init(void)
{
	
/*********************IOポート出力***********************/	

	SET_OUTPUT_PIN(PORTA,7);//led1
	SET_OUTPUT_PIN(PORTA,6);//led2
	SET_OUTPUT_PIN(PORTA,5);//led3
	SET_OUTPUT_PIN(PORTA,4);//led4
	SET_OUTPUT_PIN(PORTD,2);//led5
	SET_OUTPUT_PIN(PORTD,3);//led6
	SET_OUTPUT_PIN(PORTD,1);//led7
	SET_OUTPUT_PIN(PORTD,0);//led8
	SET_OUTPUT_PIN(PORTB,2);//led_red
	SET_OUTPUT_PIN(PORTB,3);//led_blue
	
	SET_OUTPUT_PIN(PORTE,4);//2pin
	SET_OUTPUT_PIN(PORTE,5);//2pin
	SET_OUTPUT_PIN(PORTE,6);//2pin
	SET_OUTPUT_PIN(PORTE,7);//2pin
	
	
/********************************************************/
	
/*********************IOポート入力***********************/

	//内部プルアップあり
	SET_P_INPUT_PIN(PORTE,0);//limit
	SET_P_INPUT_PIN(PORTE,1);//limit
	SET_P_INPUT_PIN(PORTE,2);//limit
	SET_P_INPUT_PIN(PORTE,3);//トグル
	
	//内部プルアップなし
	SET_INPUT(PORTC);//エンコーダ
	SET_INPUT(PORT4);//AD変換
	
	
	//未使用PINを入力モード内部プルアップに設定
	SET_P_INPUT_PIN(PORTD,4);
	SET_P_INPUT_PIN(PORTD,5);
	SET_P_INPUT_PIN(PORTD,6);
	SET_P_INPUT_PIN(PORTD,7);
	SET_P_INPUT_PIN(PORTA,2);
	SET_P_INPUT_PIN(PORTB,7);
	SET_P_INPUT_PIN(PORTB,6);
	
/********************************************************/
		
/***********************MTU2関連*************************/
	MTU2_init();		// MTU2のスタンバイ解除
	
	pwm_init();			// PWMの初期化
	enc_init();			// エンコーダの初期設定

/********************************************************/

}


/********************************************************/
//  名前      
//		limit
//  概要
// 		IO関数
//  機能説明
//		リミット認識
//  パラメタ説明
//		なし
//  戻り値
//		flag		右のボタンから2進数で表現
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char limit(void){
	char flag = 0;	
	return flag;
}

/*------------------------------------------------------*/
// オリジナル関数

#if 0
/********************************************************/
//  名前      
//		motor_o
//  概要
// 		IO関数
//  機能説明
//		モータ関数
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_o(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = -raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
	O_PWM = pwm;		
}

/********************************************************/
//  名前      
//		motor_l
//  概要
// 		IO関数
//  機能説明
//		モータ関数
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_l(double raw_duty)
{
	double duty;
	int pwm;
	
	duty = -raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
	L_PWM = pwm;		
}

/********************************************************/
//  名前      
//		motor_r
//  概要
// 		IO関数
//  機能説明
//		モータ関数
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_r(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = -raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
	R_PWM = pwm;		
}

/********************************************************/
//  名前      
//		motor_r2
//  概要
// 		IO関数
//  機能説明
//		モータ関数
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_servo(int state)
{
	SERVO_T_PWM = state;		
}

/********************************************************/
//  名前      
//		motor_fish
//  概要
// 		IO関数
//  機能説明
//		モータ関数(釣竿ハンド)
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_fish(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = -raw_duty;			//正逆転判定
	
	//pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	pwm = sign_mag_pwm(duty);	//サインマグニチュード用pwmに変更
	
	FISH_PWM = pwm;			//レジスタに値を格納(2Bから出力)
}

/********************************************************/
//  名前      
//		motor_L_arm
//  概要
// 		IO関数
//  機能説明
//		モータ関数(Lアーム)
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_L_arm(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = raw_duty;			//正逆転判定
	
//	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	pwm = sign_mag_pwm(duty);	//サインマグニチュード用pwmに変更
	
	L_ARM_PWM = pwm;			//レジスタに値を格納(2Bから出力)
}

/********************************************************/
//  名前      
//		motor_L_arm
//  概要
// 		IO関数
//  機能説明
//		モータ関数(Lアーム)
//  パラメタ説明
//		raw_duty	デュティー入力値
//		duty		デュティー正負調整用
//		pwm			MTU2レジスタに格納する値	
//  戻り値
//		なし
//	注意事項
//		pwm出力なので、io_initはmotor_control_pwm_initで行なっている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_front_shift(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
	FRONT_SIFT_PWM = pwm;			//レジスタに値を格納(2Bから出力)
}
/********************************************************/
//  名前      
//		leaf_collect_hand
//  概要
// 		IO関数
//  機能説明
//		AIR関数(リーフ回収ハンド)
//  パラメタ説明
//		state		エアーの状態
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void leaf_collect_hand(char state)
{
	if(state == OPEN)	LEAF_COLLECT_HAND_PIN = 1;
	else				LEAF_COLLECT_HAND_PIN = 0;	
}

/********************************************************/
//  名前      
//		leaf_esta_hand
//  概要
// 		IO関数
//  機能説明
//		AIR関数(リーフ設置ハンド)
//  パラメタ説明
//		state		エアーの状態
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void leaf_esta_hand(char state)
{
	if(state == OPEN)	LEAF_ESTA_HAND_PIN = 1;
	else				LEAF_ESTA_HAND_PIN = 0;	
}
#endif