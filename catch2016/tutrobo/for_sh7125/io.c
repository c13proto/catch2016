/********************************************************/
//
//  概要
//      ポート関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

/********************************************************/
//  名前      
//		power_init
//  概要
// 		IO関数
//  機能説明
//		モータ・エアーの電源供給用の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void power_init(void)
{
	
	PFC.PACRL3.BIT.PA11MD = 0; // 入出力に設定
	PFC.PAIORL.BIT.B11 = 1;    // 出力ポートに設定
		
}

/********************************************************/
//  名前      
//		buzzer_init
//  概要
// 		IO関数
//  機能説明
//		BUZZERの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_init(void)
{
	
	PFC.PECRL4.BIT.PE15MD = 0; // 入出力に設定
	PFC.PEIORL.BIT.B15 = 1;    // 出力ポートに設定
		
}

/********************************************************/
//  名前      
//		led_init
//  概要
// 		IO関数
//  機能説明
//		LEDの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_init(void)
{
	
	PFC.PECRL1.BIT.PE3MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B3 = 1;		// 出力ポートに設定
	
	PFC.PECRL2.BIT.PE4MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B4 = 1;		// 出力ポートに設定
	
	PFC.PECRL2.BIT.PE5MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B5 = 1;		// 出力ポートに設定
	
	PFC.PECRL2.BIT.PE6MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B6 = 1;		// 出力ポートに設定
	
	PFC.PECRL2.BIT.PE7MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B7 = 1;		// 出力ポートに設定
	
	PFC.PECRL3.BIT.PE9MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B9 = 1;		// 出力ポートに設定
	
	PFC.PECRL3.BIT.PE11MD = 0;	// 入出力に設定
	PFC.PEIORL.BIT.B11 = 1;		// 出力ポートに設定
		
}

/********************************************************/
//  名前      
//		mode_init
//  概要
// 		IO関数
//  機能説明
//		モード選択の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void mode_init(void)
{
	
	PFC.PBCRH1.BIT.PB16MD = 0;	// 入出力に設定
	PFC.PBIORH.BIT.B16 = 0;		// 入力ポートに設定	
		
}

/********************************************************/
//  名前      
//		button_init
//  概要
// 		IO関数
//  機能説明
//		ボタンの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void button_init(void)
{
	
	PFC.PACRL3.BIT.PA10MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B10 = 0;		// 入力ポートに設定
	
	PFC.PACRL3.BIT.PA11MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B11 = 0;		// 入力ポートに設定
	
	PFC.PACRL4.BIT.PA12MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B12 = 0;		// 入力ポートに設定
	
	PFC.PACRL4.BIT.PA13MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B13 = 0;		// 入力ポートに設定
	
	PFC.PACRL4.BIT.PA14MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B14 = 0;		// 入力ポートに設定	
}

/********************************************************/
//  名前      
//		limit_init
//  概要
// 		IO関数
//  機能説明
//		LIMITの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void limit_init(void)
{
	
	PFC.PACRL4.BIT.PA14MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B14 = 0;		// 入力ポートに設定

	PFC.PACRL4.BIT.PA15MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B15 = 0;		// 入力ポートに設定

	PFC.PBCRL1.BIT.PB1MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B1 = 0;		// 入力ポートに設定

	PFC.PBCRL1.BIT.PB2MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B2 = 0;		// 入力ポートに設定
	
	PFC.PBCRL1.BIT.PB3MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B3 = 0;		// 入力ポートに設定

	PFC.PBCRL2.BIT.PB5MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B5 = 0;		// 入力ポートに設定




/*	PFC.PACRL4.BIT.PA15MD = 0;	// 入出力に設定
	PFC.PAIORL.BIT.B15 = 0;		// 入力ポートに設定
	
	PFC.PBCRL1.BIT.PB1MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B1 = 0;		// 入力ポートに設定

	PFC.PBCRL1.BIT.PB2MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B2 = 0;		// 入力ポートに設定
	
	PFC.PBCRL1.BIT.PB3MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B3 = 0;		// 入力ポートに設定

	PFC.PBCRL2.BIT.PB5MD = 0;	// 入出力に設定
	PFC.PBIORL.BIT.B5 = 0;		// 入力ポートに設定
	
	PFC.PBIORH.BIT.B16 = 1;  	// 入出力ポートに設定
	PFC.PBIORH.BIT.B16 = 0;		// 入力ポートに設定	
*/
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
/***********************MTU2関連*************************/

	MTU2_init();		// MTU2のスタンバイ解除
	pwm_init();			// PWMの初期化
//	motor_pwm_init();	// MOTOR_PWMの初期化
//	servo_pwm_init();	// SORVO_PWMの初期化
	enc_init();			// エンコーダの初期設定

/********************************************************/

/*********************IOポート出力***********************/	

//	power_init();		// モータ・エアーの電源供給用の初期設定
//	buzzer_init();		// BUZZERの初期設定	
	led_init();			// LEDの初期設定(出力ピンも兼ねる)
	
/********************************************************/
	
/*********************IOポート入力***********************/
	
	mode_init();		// モード選択の初期設定
//	button_init();		// ボタンの初期設定
	limit_init();		// LIMITの初期設定
	
/********************************************************/
		
}

/********************************************************/
//  名前      
//		led_on
//  概要
// 		IO関数
//  機能説明
//		LEDをONにする
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_on(void)
{
	
	PE.DRL.BIT.B3 = 1;		// 5Vに設定
	PE.DRL.BIT.B4 = 1;		// 5Vに設定
	PE.DRL.BIT.B5 = 1;		// 5Vに設定
	PE.DRL.BIT.B6 = 1;		// 5Vに設定
	PE.DRL.BIT.B7 = 1;		// 5Vに設定
	PE.DRL.BIT.B9 = 1;		// 5Vに設定
	PE.DRL.BIT.B11 = 1;		// 5Vに設定
		
}

/********************************************************/
//  名前      
//		led_off
//  概要
// 		IO関数
//  機能説明
//		LEDをOFFにする
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_off(void)
{
	
	PE.DRL.BIT.B3 = 0;		// 0Vに設定
	PE.DRL.BIT.B4 = 0;		// 0Vに設定
	PE.DRL.BIT.B5 = 0;		// 0Vに設定
	PE.DRL.BIT.B6 = 0;		// 0Vに設定
	PE.DRL.BIT.B7 = 0;		// 0Vに設定
	PE.DRL.BIT.B9 = 0;		// 0Vに設定
	PE.DRL.BIT.B11 = 0;		// 0Vに設定
		
}

/********************************************************/
//  名前      
//		led_ctrl
//  概要
// 		IO関数
//  機能説明
//		LEDの点き方をコントロールする
//  パラメタ説明
//		number			numberに応じてledの光り方が変わる
//						「0～31」まで選択可
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_ctrl(char number)
{
	char dec;		// 10進数格納用
	char bin[5];	// 2進数格納用
	char loop;		// for文のための型
	
	dec = number;	// 引数を格納	
	
	for(loop = 0; loop < 5; loop++)
	{
		bin[loop] = dec % 2;
		dec = dec / 2;
	}
		
	PE.DRL.BIT.B7 = bin[0];		// 1bit
	PE.DRL.BIT.B6 = bin[1];		// 2bit
	PE.DRL.BIT.B5 = bin[2];		// 3bit
	PE.DRL.BIT.B4 = bin[3];		// 4bit
	PE.DRL.BIT.B3 = bin[4];		// 5bit
		
}

/********************************************************/
//  名前      
//		mode
//  概要
// 		IO関数
//  機能説明
//		モード選択
//  パラメタ説明
//		なし
//  戻り値
//		flag		'B':青ゾーン
//					'R':赤ゾーン
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char mode(void)
{
	char flag = 0;
	
	if(PB.DR.BIT.B16  == 0)
	{
		flag = 'B';
	}
	else if(PB.DR.BIT.B16 == 1)	
	{
		flag = 'R';
	}
	
	return flag;
}



/*------------------------------------------------------*/
// オリジナル関数


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
	
//	MTU23.TGRA = pwm;		
	O_PWM =pwm;
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
	
	duty = raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
//	MTU23.TGRC = pwm;		
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
	
//	MTU24.TGRA = pwm;		
	R_PWM = pwm;	
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
	
	duty = raw_duty;			//正逆転判定
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
	FISH_PWM = pwm;				//レジスタに値を格納(3Cから出力)
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
	
	pwm = anti_lock_pwm(duty);	//アンチロックシステム用pwmに変更
	
//	MTU20.TGRC = pwm;			//レジスタに値を格納(2Bから出力)
	L_ARM_PWM = pwm;			//レジスタに値を格納(3Aから出力)

}


//未使用関数
#if 0 
/********************************************************/
//  名前      
//		power_on
//  概要
// 		POWER関数
//  機能説明
//		電源供給を行う
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void  power_on(void)
{	
	PE.DRL.BIT.B3 = 1;	 //5Vに設定		
}


/********************************************************/
//  名前      
//		power_off
//  概要
// 		POWER関数
//  機能説明
//		電源供給を行わない
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void power_off(void)
{	
	PE.DRL.BIT.B3 = 0;	 //0Vに設定		
}

/********************************************************/
//  名前      
//		buzzer_on
//  概要
// 		BUZZER関数
//  機能説明
//		BUZZERをONにする
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_on(void)
{
	
	PE.DRL.BIT.B15 = 1;	 // 5Vに設定
		
}

/********************************************************/
//  名前      
//		buzzer_off
//  概要
// 		BUZZER関数
//  機能説明
//		BUZZERをOFFにする
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_off(void)
{
	
	PE.DRL.BIT.B15 = 0;	 // 0Vに設定
		
}

/********************************************************/
//  名前      
//		button
//  概要
// 		IO関数
//  機能説明
//		ボタン認識
//  パラメタ説明
//		なし
//  戻り値
//		flag		右のボタンから2進数で表現
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char button(void)
{
	char flag = 0;
	
	if(PA.DRL.BIT.B10 == 1){flag += 1;}
	if(PA.DRL.BIT.B11 == 1){flag += 2;}
	if(PA.DRL.BIT.B12 == 1){flag += 4;}
	if(PA.DRL.BIT.B13 == 1){flag += 8;}
	if(PA.DRL.BIT.B14 == 1){flag += 16;}
	
	return flag;
}/********************************************************/
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
char limit(void)
{
	char flag = 0;
	
	if(PA.DRL.BIT.B15 == 1){flag += 1;}
	if(PB.DR.BIT.B1   == 1){flag += 2;}
	if(PB.DR.BIT.B2   == 1){flag += 4;}
	if(PB.DR.BIT.B3   == 1){flag += 8;}
	if(PB.DR.BIT.B5   == 1){flag += 16;}
	if(PB.DR.BIT.B16  == 1){flag += 32;}
	
	return flag;
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
	if(state == OPEN)	PE.DRL.BIT.B7 = 1;
	else				PE.DRL.BIT.B7 = 0;	
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
	if(state == OPEN)	PE.DRL.BIT.B6 = 1;
	else				PE.DRL.BIT.B6 = 0;	
}
#endif