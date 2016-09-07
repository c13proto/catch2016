/********************************************************/
//
//  概要
//      PWM設定
//  注意
//		マイコン依存ファイル!!
//  作成者
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

/********************************************************/
//  TUTrobo
//
//  概要
//      PWM設定 プロトタイプ宣言
/********************************************************/
void motor_pwm_init(void);		// PWMの初期化
int anti_lock_pwm(double duty);	// モータのアンチロックのPWMをコントロールする

/********************************************************/
//  名前      
//		pwm_init
//  概要
// 		PWM関数
//  機能説明
//		PWMの初期化
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		MTU2スタンバイモード解除,カウント停止は
//		setup.cにあるMTU2_initで行っている
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/
void pwm_init(void)
{
	volatile int dummy;					// ダミー読み取りのため
		
	MTUA.TSTR.BIT.CST0 = 0;     // MTU0カウントストップ	
	MTUA.TSTR.BIT.CST4 = 0; 	// MTU4カウントストップ
	MTUB.TSTR.BIT.CST0 = 0;     // MTU6カウントストップ
	MTUB.TSTR.BIT.CST3 = 0; 	// MTU9カウントストップ
	MTUB.TSTR.BIT.CST4 = 0; 	// MTU10カウントストップ

/*********チャンネル0 pwmモード2設定開始 (DCモータ)**********/
//0A~0DまでPINあり
	
	MTU0.TCR.BIT.TPSC = 0;     //クロック周波数φ/1 (MTUのクロックは48Mhz)	
	MTU0.TCR.BIT.CCLR = 3;     // 同期動作2の時はここの値を3にする
//	MTU0.TCR.BIT.CCLR = 2;     // TGRBで同期クリア
	MTU0.TMDR.BIT.MD = 3;      // PWMモード2
	MTUA.TSYR.BYTE = 0x81;      //0と4の同期動作
//	MTUA.TSYR.BYTE = 0;         //独立動作
	MTU0.TIORH.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU0.TIORH.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU0.TIORL.BIT.IOD = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU0.TIORL.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力	
	MTU0.TGRA = ANTI_THRESHOLD;	// デューティ設定
	MTU0.TGRB = ANTI_THRESHOLD;	// デューティ設定
	MTU0.TGRC = ANTI_THRESHOLD;	// デューティ設定
	MTU0.TGRD = ANTI_THRESHOLD;	// デューティ設定
			
/*****チャンネル4 pwmモード1設定開始 (DCモータ)******/
//4A,4CのPINあり

	MTU4.TCR.BIT.TPSC = 0; 	// クロック周波数φ/1 (MTUのクロックは25Mhz)
	MTU4.TCR.BIT.CKEG = 0; 	// 立ち上がりエッジでカウント
	MTU4.TCR.BIT.CCLR = 2; 	// TGRBでカウントクリア;
	MTU4.TMDR.BIT.MD = 2;		// PWMモード1
	MTU4.TIORH.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU4.TIORH.BIT.IOB = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU4.TIORL.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU4.TIORL.BIT.IOD = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU4.TGRA = ANTI_THRESHOLD;		// TIOC4Aコンペアマッチ
	MTU4.TGRB = ANTI_CYCLE;			// TIOC4Bコンペアマッチ
	MTU4.TGRC = ANTI_THRESHOLD;		// TIOC4Cコンペアマッチ
	MTU4.TGRD = ANTI_CYCLE;			// TIOC4Dコンペアマッチ
	// ch4だけ必須!！！ 
	MTUA.TOER.BIT.OE4A = 1; 	// FTIO4AのMTU2動作を許可
	MTUA.TOER.BIT.OE4B = 1;		// FTIO4BのMTU2動作を許可
	MTUA.TOER.BIT.OE4C = 1;		// FTIO4CのMTU2動作を許可
	MTUA.TOER.BIT.OE4D = 1;		// FTIO4DのMTU2動作を許可

	IOPORT.PFCMTU.BIT.MTUS4 = 0; 		// 0：P24をMTIOC4A-A端子として選択 P25をMTIOC4C-A端子として選択
										// 1：P82をMTIOC4A-B端子として選択 P83をMTIOC4C-B端子として選択
	//IOPORT.PFCMTU.BIT.MTUS5 = 0;		// 0：P30をMTIOC4B-A端子として選択 P31をMTIOC4D-A端子として選択
										// 1：P54をMTIOC4B-B端子として選択 P55をMTIOC4D-B端子として選択
					

/*********チャンネル6 pwmモード2設定開始 (DCモータ)**********/
//6A,6B,6DにPINあり

	MTU6.TCR.BIT.TPSC =0;     //クロック周波数φ/16 (MTUのクロックは48Mhz)	
//	MTU6.TCR.BIT.CCLR = 2;//    // TGRBでカウントクリア
	MTU6.TCR.BIT.CCLR = 3;//    // 同期動作の時はここの値を3にする	
	MTU6.TMDR.BIT.MD = 3;       // PWMモード2
	MTUB.TSYR.BYTE = 0x41;      //6と9の同期動作
//	MTUB.TSYR.BYTE = 0;         //独立動作			
	MTU6.TIORH.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU6.TIORH.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU6.TIORL.BIT.IOD = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU6.TIORL.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力	
	MTU6.TGRA = ANTI_THRESHOLD;	// デューティ設定
	MTU6.TGRB = ANTI_THRESHOLD;	// デューティ設定
	MTU6.TGRC = ANTI_THRESHOLD;	// デューティ設定(PINが無いので便宜上)
	MTU6.TGRD = ANTI_THRESHOLD;	// デューティ設定	

/*****チャンネル9 pwmモード1設定開始 (DCモータ)******/

	MTU9.TCR.BIT.TPSC = 0; 		//クロック周波数φ/16 (MTUのクロックは48Mhz)
	MTU9.TCR.BIT.CKEG = 0; 		// 立ち上がりエッジでカウント
	MTU9.TCR.BIT.CCLR = 2; 		// TGRBでカウントクリア;
	MTU9.TMDR.BIT.MD = 2;		// PWM1モード	
	MTU9.TIORH.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU9.TIORH.BIT.IOB = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU9.TIORL.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU9.TIORL.BIT.IOD = 1;     // 初期状態で0出力 コンペアマッチしたら0出力	
	MTU9.TGRA = ANTI_THRESHOLD;	// TIOC4Aコンペアマッチ
	MTU9.TGRB = ANTI_CYCLE;		// TIOC4Bコンペアマッチ
	MTU9.TGRC = ANTI_THRESHOLD;	// TIOC4Cコンペアマッチ
	MTU9.TGRD = ANTI_CYCLE;		// TIOC4Dコンペアマッチ	

/*************チャンネル10 PWMモード1設定開始（サーボ）***************/

	MTU10.TCR.BIT.TPSC = 2; 	//クロック周波数φ/16 (MTUのクロックは48Mhz)	
	MTU10.TCR.BIT.CKEG = 0; 	//立ち上がりエッジでカウント
	MTU10.TCR.BIT.CCLR = 2; 	//TGRBでカウントクリア;
	MTU10.TMDR.BIT.MD = 2;		//PWM1モード		
	MTU10.TIORH.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力(逆は５)
	MTU10.TIORH.BIT.IOB = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	MTU10.TIORL.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU10.TIORL.BIT.IOD = 1;     //初期状態で0出力 コンペアマッチしたら0出力	
	MTU10.TGRA = SERVO_TH;		//TIOC4Aコンペアマッチ
	MTU10.TGRB = SERVO_CYCLE;	//周期設定
	MTU10.TGRC = SERVO_TH;		//TIOC4Cコンペアマッチ
	MTU10.TGRD = SERVO_CYCLE;	//周期設定	
	// ch4だけ必須!！！ 
	MTUB.TOER.BIT.OE4A = 1; 	// FTIO4AのMTU2動作を許可
	MTUB.TOER.BIT.OE4B = 1;		// FTIO4BのMTU2動作を許可
	MTUB.TOER.BIT.OE4C = 1;		// FTIO4CのMTU2動作を許可
	MTUB.TOER.BIT.OE4D = 1;		// FTIO4DのMTU2動作を許可
	
/*************チャンネル10 PWMモード1設定終了***************/


	MTUA.TSTR.BIT.CST0 = 1;     // MTU0カウントスタート
	MTUA.TSTR.BIT.CST4 = 1;     // MTU4カウントスタート
	MTUB.TSTR.BIT.CST0 = 1;     // MTU6カウントスタート
	MTUB.TSTR.BIT.CST3 = 1;     // MTU9カウントスタート
	MTUB.TSTR.BIT.CST4 = 1;     // MTU10カウントスタート

}



/********************************************************/
//  名前      
//		servo_pwm_init
//  概要
// 		PWM関数
//  機能説明
//		SORVO_PWMの初期化
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		MTU2スタンバイモード解除,カウント停止は
//		setup.cにあるMTU2_initで行っている
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/
void servo_pwm_init(void)
{
	volatile int dummy;					// ダミー読み取りのため
			
	/*************チャンネル0 pwmモード2設定開始***************/
	
	MTU0.TCR.BIT.TPSC = 2;     //クロック周波数φ/16 (MTUのクロックは48Mhz)
	
	MTU0.TCR.BIT.CCLR = 6;     // TGRDコンペアマッチでTCNTクリア
	
	MTUA.TSYR.BYTE = 0;         // 独立動作
		
	MTU0.TIORH.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU0.TIORH.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU0.TIORL.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	
	MTU0.TGRA = SERVO_TH;		// デューティ設定
	MTU0.TGRB = SERVO_TH;		// デューティ設定
	MTU0.TGRC = SERVO_TH;		// デューティ設定
	MTU0.TGRD = SERVO_CYCLE;	// 周期設定
			
	MTU0.TMDR.BIT.MD = 3;      // PWMモード2
	

	MTUA.TSTR.BIT.CST0 = 1;     // MU20カウントスタート
	
	/*************チャンネル0 pwmモード2設定終了***************/

	/*************チャンネル0,2同期モード設定開始**************/
/*	
	MTU2.TSTR.BIT.CST0 = 1;    	//MTU20カウント停止
	MTU2.TSTR.BIT.CST2 = 1; 	//MTU22カウント停止
	
	MTU20.TCR.BIT.TPSC = 2;     //クロック周波数φ/16 (MTUのクロックは25Mhz)
	MTU22.TCR.BIT.TPSC = 2;     //クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU20.TCR.BIT.CCLR = 3;     //同期クリア
	MTU22.TCR.BIT.CCLR = 2;     //TGRBコンペアマッチでTCNTクリア
	
	MTU2.TSYR.BYTE = 5;         //チャネル0,2同期動作
	
	MTU20.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOB = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOD = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU22.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力

	MTU20.TGRA = SERVO_TH;		// デューティ設定
	MTU20.TGRB = SERVO_TH;		// デューティ設定
	MTU20.TGRC = SERVO_TH;		// デューティ設定
	MTU20.TGRD = SERVO_TH;		// デューティ設定
	MTU22.TGRA = SERVO_TH;		// デューティ設定
	MTU22.TGRB = SERVO_CYCLE;	// 周期設定
	
	MTU20.TMDR.BIT.MD = 3;      //PWMモード2
	MTU22.TMDR.BIT.MD = 3;      //PWMモード2
	
	PFC.PECRL1.BIT.PE0MD = 1;	//ポートE0をMTU2に設定
	PFC.PEIORL.BIT.B0    = 1;  	//出力ポートに設定
	
	PFC.PECRL1.BIT.PE1MD = 1;	//ポートE1をMTU2に設定
	PFC.PEIORL.BIT.B1    = 1;  	//出力ポートに設定
	
	PFC.PECRL1.BIT.PE2MD = 1;  	//ポートE2をMTU2に設定
	PFC.PEIORL.BIT.B2    = 1;  	//出力ポートに設定	
	
	PFC.PECRL1.BIT.PE3MD = 1;  	//ポートE3をMTU2に設定
	PFC.PEIORL.BIT.B3    = 1;  	//出力ポートに設定
	
	PFC.PECRL2.BIT.PE6MD = 1;  	//ポートE6をMTU2に設定
	PFC.PEIORL.BIT.B6    = 1;  	//出力ポートに設定
	
	PFC.PECRL2.BIT.PE7MD = 1;  	//ポートE7をMTU2に設定
	PFC.PEIORL.BIT.B7    = 1;  	//出力ポートに設定
	
	MTU2.TSTR.BIT.CST0 = 1;     //MU20カウントスタート
	MTU2.TSTR.BIT.CST2 = 1;		//MU22カウントスタート
*/	
	/*************チャンネル0,2同期モード設定終了**************/


	/*************チャンネル4 PWMモード1設定開始***************/

	MTUA.TSTR.BIT.CST4 = 1; 	//MTU24カウント停止
	
	MTU4.TCR.BIT.CCLR = 2; 	//TGRBでカウントクリア;
	
	MTU4.TCR.BIT.TPSC = 2; 	//クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU4.TCR.BIT.CKEG = 0; 	//立ち上がりエッジでカウント
	
	MTU4.TIORH.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU4.TIORH.BIT.IOB = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	MTU4.TIORL.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU4.TIORL.BIT.IOD = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	
	MTU4.TGRA = SERVO_TH;		//TIOC4Aコンペアマッチ
	MTU4.TGRB = SERVO_CYCLE;	//TIOC4Bコンペアマッチ
	MTU4.TGRC = SERVO_TH;		//TIOC4Cコンペアマッチ
	MTU4.TGRD = SERVO_CYCLE;	//TIOC4Dコンペアマッチ
	
	MTU4.TMDR.BIT.MD = 2;		//PWM1モード
/*	
	MTU.TOER.BIT.OE4A = 1; 	//ch4だけ必須!！！
	MTU.TOER.BIT.OE4B = 1;
	MTU.TOER.BIT.OE4C = 1;
	MTU.TOER.BIT.OE4D = 1;
*/	
								// 初期設定ではPOEモードになっているため
								// PB16になにかを接続するとPWM波形がでなくなる。
//	PFC.PBIORH.BIT.B16    = 1;  // 入出力ポートに設定
								// IOの初期設定よりも早くPOEフラグがたってしまうため
								// クリアしなければならない	
	dummy = POE.ICSR1.BIT.POE3F;// ダミー読み取り
	POE.ICSR1.BIT.POE3F = 0; 	// フラグクリア

	
	IOPORT.PFCMTU.BIT.MTUS4 = 0; 		// 0：P24をMTIOC4A-A端子として選択 P25をMTIOC4C-A端子として選択
										// 1：P82をMTIOC4A-B端子として選択 P83をMTIOC4C-B端子として選択
	IOPORT.PFCMTU.BIT.MTUS5 = 1;		// 0：P30をMTIOC4B-A端子として選択 P31をMTIOC4D-A端子として選択
										// 1：P54をMTIOC4B-B端子として選択 P55をMTIOC4D-B端子として選択
	
/*	
	PFC.PECRL4.BIT.PE12MD = 1;	//ポートE12をMTU2に設定
	PFC.PEIORL.BIT.B12    = 1;  //出力ポートに設定
	
	PFC.PECRL4.BIT.PE14MD= 1;	//ポートE14をMTU2に設定
	PFC.PEIORL.BIT.B14   = 1;  	//出力ポートに設定
*/	
	MTUA.TSTR.BIT.CST4 = 1;     //MTU4カウントスタート
	
	/*************チャンネル4 PWMモード1設定終了***************/
}

/********************************************************/
//  名前      
//		anti_lock_pwm
//  概要
// 		MOTOR関数
//  機能説明
//		モータのアンチロックのPWMをコントロールする
//  パラメタ説明
//		なし
//	注意事項
//		THRESHOLD/UP_LIMIT/DOWN_LIMITの確認
//		THRESHOLD/UP_LIMIT/DOWN_LIMITはpwm.hで設定している
//  戻り値
//		pwm		MTU2レジスタに格納する値
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int anti_lock_pwm(double duty)
{	
	int pwm;	
		
	if(duty > 0.0)
	{
		pwm = ANTI_THRESHOLD + ( (ANTI_UP_LIMIT - ANTI_THRESHOLD) * duty ) / 100; 		//dutyの設定 PWM
		
		if(pwm >= ANTI_UP_LIMIT){pwm = ANTI_UP_LIMIT;}		//頭打ち				
	}	
	else if(duty < 0.0)
	{
		pwm = ANTI_THRESHOLD + ( (ANTI_THRESHOLD - ANTI_DOWN_LIMIT) * duty ) / 100;	//dutyの設定 PWM
		
		if(pwm <= ANTI_DOWN_LIMIT){pwm = ANTI_DOWN_LIMIT;}	//頭打ち
	}
	else 
	{		
		pwm = ANTI_THRESHOLD;	
	}
	
	return pwm;
		
}

/********************************************************/
//  名前      
//		anti_lock_pwm
//  概要
// 		MOTOR関数
//  機能説明
//		モータのアンチロックのPWMをコントロールする
//  パラメタ説明
//		なし
//	注意事項
//		THRESHOLD/UP_LIMIT/DOWN_LIMITの確認
//		THRESHOLD/UP_LIMIT/DOWN_LIMITはpwm.hで設定している
//  戻り値
//		pwm		MTU2レジスタに格納する値
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int sign_mag_pwm(double duty)
{	
	int pwm;	
		
	if(duty > 0.0)
	{
		pwm = SIGN_THRESHOLD + ( (SIGN_UP_LIMIT - SIGN_THRESHOLD) * duty ) / 100; 		//dutyの設定 PWM
		
		if(pwm >= SIGN_UP_LIMIT){pwm = SIGN_UP_LIMIT;}		//頭打ち				
	}	
	else if(duty < 0.0)
	{
		pwm = SIGN_THRESHOLD + ( (SIGN_THRESHOLD - SIGN_DOWN_LIMIT) * duty ) / 100;	//dutyの設定 PWM
		
		if(pwm <= SIGN_DOWN_LIMIT){pwm = SIGN_DOWN_LIMIT;}	//頭打ち
	}
	else 
	{		
		pwm = SIGN_THRESHOLD;	
	}
	
	return pwm;
		
}

/********************************************************/
//  名前      
//		servo_pwm
//  概要
// 		SERVO関数
//  機能説明
//		サーボモータのPWMをコントロールする
//  パラメタ説明
//		なし
//	注意事項
//		SERVO_TH/SERVO_UP/SERVO_DOWNの確認
//		SERVO_TH/SERVO_UP/SERVO_DOWNはpwm.hで設定している
//  戻り値
//		pwm		MTU2レジスタに格納する値
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int servo_pwm(double range)
{	
	int pwm;	
		
	if(range > 0.0)
	{
		pwm = SERVO_TH + ( (SERVO_UP - SERVO_TH) * range ) / 100; 		//dutyの設定 PWM
		
		if(pwm >= SERVO_UP){pwm = SERVO_UP;}		//頭打ち				
	}	
	else if(range < 0.0)
	{
		pwm = SERVO_TH + ( (SERVO_TH - SERVO_DOWN) * range ) / 100;		//dutyの設定 PWM
		
		if(pwm <= SERVO_DOWN){pwm =SERVO_DOWN;}	//頭打ち
	}
	else 
	{		
		pwm = SERVO_TH;	
	}
	
	return pwm;
		
}

