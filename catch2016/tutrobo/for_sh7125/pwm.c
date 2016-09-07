/********************************************************/
//
//  概要
//      PWM設定
//  作成者
//		K.ishimori @ TUTrobo
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
	int dummy;					// ダミー読み取りのため
		
	/*********チャンネル0 pwmモード2設定開始 (足回り)**********/

	MTU20.TCR.BIT.TPSC = 0;     //クロック周波数φ/1 (MTUのクロックは25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRDコンペアマッチでTCNTクリア
	
	MTU2.TSYR.BYTE = 0;         // 独立動作
		
	MTU20.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	
	MTU20.TGRA = THRESHOLD;		// デューティ設定
	MTU20.TGRB = THRESHOLD;		// デューティ設定
	MTU20.TGRC = THRESHOLD;		// デューティ設定
	MTU20.TGRD = CYCLE;	// 周期設定
			
	MTU20.TMDR.BIT.MD = 3;      // PWMモード2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// ポートE0をMTU2に設定
	PFC.PEIORL.BIT.B0    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE1MD = 1;	// ポートE1をMTU2に設定
	PFC.PEIORL.BIT.B1    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE2MD = 1;	// ポートE2をMTU2に設定
	PFC.PEIORL.BIT.B2    = 1;  	// 出力ポートに設定
		
	MTU2.TSTR.BIT.CST0 = 1;     // MU20カウントスタート
	
	/*********チャンネル0 pwmモード2設定終了 (足回り)**********/

	/*****チャンネル3 pwmモード1設定開始 (モータ＿アーム)******/

	MTU2.TSTR.BIT.CST3 = 1; 	// MTU23カウント停止
	
	MTU23.TCR.BIT.CCLR = 2; 	// TGRBでカウントクリア;
	
	MTU23.TCR.BIT.TPSC = 0; 	// クロック周波数φ/1 (MTUのクロックは25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	// 立ち上がりエッジでカウント
	
	MTU23.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOB = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU23.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOD = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	
	MTU23.TGRA = THRESHOLD;		// TIOC3Aコンペアマッチ
	MTU23.TGRB = CYCLE;			// TIOC3Bコンペアマッチ
	MTU23.TGRC = THRESHOLD;		// TIOC3Cコンペアマッチ
	MTU23.TGRD = CYCLE;			// TIOC3Dコンペアマッチ
	
	MTU23.TMDR.BIT.MD = 2;		// PWM1モード
	
	PFC.PECRL3.BIT.PE8MD = 1;	// ポートE8をMTU2に設定
	PFC.PEIORL.BIT.B8    = 1;  	// 出力ポートに設定
	
	PFC.PECRL3.BIT.PE10MD= 1;	// ポートE10をMTU2に設定
	PFC.PEIORL.BIT.B10   = 1;  	// 出力ポートに設定
	
	MTU2.TSTR.BIT.CST3 = 1;     // MU23カウントスタート
	
	/*****チャンネル3 pwmモード1設定完了 (モータ＿足回り)******/

	/*************チャンネル4 PWMモード1設定開始(サーボ)***************/

	MTU2.TSTR.BIT.CST4 = 1; 	//MTU24カウント停止
	
	MTU24.TCR.BIT.CCLR = 2; 	//TGRBでカウントクリア;
	
	MTU24.TCR.BIT.TPSC = 2; 	//クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	//立ち上がりエッジでカウント
	
	MTU24.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOB = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	MTU24.TIOR.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOD = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	
	MTU24.TGRA = SERVO_TH;		//TIOC4Aコンペアマッチ
	MTU24.TGRB = SERVO_CYCLE;	//TIOC4Bコンペアマッチ
	MTU24.TGRC = SERVO_TH;		//TIOC4Cコンペアマッチ
	MTU24.TGRD = SERVO_CYCLE;	//TIOC4Dコンペアマッチ
	
	MTU24.TMDR.BIT.MD = 2;		//PWM1モード
	
	MTU2.TOER.BIT.OE4A = 1; 	//ch4だけ必須!！！
	MTU2.TOER.BIT.OE4B = 1;
	MTU2.TOER.BIT.OE4C = 1;
	MTU2.TOER.BIT.OE4D = 1;
	
								// 初期設定ではPOEモードになっているため
								// PB16になにかを接続するとPWM波形がでなくなる。
	PFC.PBIORH.BIT.B16    = 1;  // 入出力ポートに設定
								// IOの初期設定よりも早くPOEフラグがたってしまうため
								// クリアしなければならない	
	dummy = POE.ICSR1.BIT.POE3F;// ダミー読み取り
	POE.ICSR1.BIT.POE3F = 0; 	// フラグクリア
	
	PFC.PECRL4.BIT.PE12MD = 1;	//ポートE12をMTU2に設定
	PFC.PEIORL.BIT.B12    = 1;  //出力ポートに設定
	
	PFC.PECRL4.BIT.PE14MD= 1;	//ポートE14をMTU2に設定
	PFC.PEIORL.BIT.B14   = 1;  	//出力ポートに設定
	
	MTU2.TSTR.BIT.CST4 = 1;     //MU24カウントスタート
	
	/*************チャンネル4 PWMモード1設定終了***************/
}

#if 0
/********************************************************/
//  名前      
//		motor_pwm_init
//  概要
// 		PWM関数
//  機能説明
//		MOTOR_PWMの初期化
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
void motor_pwm_init(void)
{
	int dummy;					// ダミー読み取りのため
	
	/*************チャンネル0 pwmモード2設定開始***************/
	
	MTU20.TCR.BIT.TPSC = 0;     // クロック周波数φ/1 (MTUのクロックは25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRDコンペアマッチでTCNTクリア
	
	MTU2.TSYR.BYTE = 0;         // 独立動作
	
	MTU20.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	
	MTU20.TGRA = THRESHOLD;		// デューティ設定
	MTU20.TGRB = THRESHOLD;		// デューティ設定
	MTU20.TGRC = THRESHOLD;		// デューティ設定
	MTU20.TGRD = CYCLE;			// 周期設定
	
	MTU20.TMDR.BIT.MD = 3;      // PWMモード2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// ポートE0をMTU2に設定
	PFC.PEIORL.BIT.B0    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE1MD = 1;	// ポートE1をMTU2に設定
	PFC.PEIORL.BIT.B1    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE2MD = 1;	// ポートE2をMTU2に設定
	PFC.PEIORL.BIT.B2    = 1;  	// 出力ポートに設定
		
	MTU2.TSTR.BIT.CST0 = 1;     // MU20カウントスタート
	
	/*************チャンネル0 pwmモード2設定終了*************/

	/*************チャンネル3 PWMモード1設定開始***************/

	MTU2.TSTR.BIT.CST3 = 1; 	// MTU23カウント停止
	
	MTU23.TCR.BIT.CCLR = 2; 	// TGRBでカウントクリア;
	
	MTU23.TCR.BIT.TPSC = 0; 	// クロック周波数φ/1 (MTUのクロックは25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	// 立ち上がりエッジでカウント
	
	MTU23.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOB = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU23.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOD = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	
	MTU23.TGRA = THRESHOLD;		// TIOC3Aコンペアマッチ
	MTU23.TGRB = CYCLE;			// TIOC3Bコンペアマッチ
	MTU23.TGRC = THRESHOLD;		// TIOC3Cコンペアマッチ
	MTU23.TGRD = CYCLE;			// TIOC3Dコンペアマッチ
	
	MTU23.TMDR.BIT.MD = 2;		// PWM1モード
	
	PFC.PECRL3.BIT.PE8MD = 1;	// ポートE8をMTU2に設定
	PFC.PEIORL.BIT.B8    = 1;  	// 出力ポートに設定
	
	PFC.PECRL3.BIT.PE10MD= 1;	// ポートE10をMTU2に設定
	PFC.PEIORL.BIT.B10   = 1;  	// 出力ポートに設定
	
	MTU2.TSTR.BIT.CST3 = 1;     // MU23カウントスタート
	
	/*************チャンネル3 PWMモード1設定終了***************/

	/*************チャンネル4 PWMモード1設定開始***************/

	MTU2.TSTR.BIT.CST4 = 1; 	// MTU24カウント停止
	
	MTU24.TCR.BIT.CCLR = 2; 	// TGRBでカウントクリア;
	
	MTU24.TCR.BIT.TPSC = 0; 	// クロック周波数φ/1 (MTUのクロックは25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	// 立ち上がりエッジでカウント
	
	MTU24.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOB = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	MTU24.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOD = 1;     // 初期状態で0出力 コンペアマッチしたら0出力
	
	MTU24.TGRA = THRESHOLD;		// TIOC4Aコンペアマッチ
	MTU24.TGRB = CYCLE;			// TIOC4Bコンペアマッチ
	MTU24.TGRC = THRESHOLD;		// TIOC4Cコンペアマッチ
	MTU24.TGRD = CYCLE;			// TIOC4Dコンペアマッチ
	
	MTU24.TMDR.BIT.MD = 2;		// PWM1モード
	
								// ch4だけ必須!！！ 
	MTU2.TOER.BIT.OE4A = 1; 	// FTIO4AのMTU2動作を許可
	MTU2.TOER.BIT.OE4B = 1;		// FTIO4BのMTU2動作を許可
	MTU2.TOER.BIT.OE4C = 1;		// FTIO4CのMTU2動作を許可
	MTU2.TOER.BIT.OE4D = 1;		// FTIO4DのMTU2動作を許可
	
								// 初期設定ではPOEモードになっているため
								// PB16になにかを接続するとPWM波形がでなくなる。
	PFC.PBIORH.BIT.B16    = 1;  // 入出力ポートに設定
								// IOの初期設定よりも早くPOEフラグがたってしまうため
								// クリアしなければならない	
	dummy = POE.ICSR1.BIT.POE3F;// ダミー読み取り
	POE.ICSR1.BIT.POE3F = 0; 	// フラグクリア
	
	PFC.PECRL4.BIT.PE12MD = 1;	// ポートE12をMTU2に設定
	PFC.PEIORL.BIT.B12    = 1;  // 出力ポートに設定
	PE.DRL.BIT.B12 = 1;
	
	PFC.PECRL4.BIT.PE14MD= 1;	// ポートE14をMTU2に設定
	PFC.PEIORL.BIT.B14   = 1;  	// 出力ポートに設定
	PE.DRL.BIT.B14 = 1;
	
	MTU2.TSTR.BIT.CST4 = 1;     // MU24カウントスタート
	
	/*************チャンネル4 PWMモード1設定終了***************/

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
	int dummy;					// ダミー読み取りのため
			
	/*************チャンネル0 pwmモード2設定開始***************/
	
	MTU20.TCR.BIT.TPSC = 2;     //クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRDコンペアマッチでTCNTクリア
	
	MTU2.TSYR.BYTE = 0;         // 独立動作
		
	MTU20.TIOR.BIT.IOA = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOB = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	MTU20.TIOR.BIT.IOC = 2;     // 初期状態で0出力 コンペアマッチしたら1出力
	
	MTU20.TGRA = SERVO_TH;		// デューティ設定
	MTU20.TGRB = SERVO_TH;		// デューティ設定
	MTU20.TGRC = SERVO_TH;		// デューティ設定
	MTU20.TGRD = SERVO_CYCLE;	// 周期設定
			
	MTU20.TMDR.BIT.MD = 3;      // PWMモード2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// ポートE0をMTU2に設定
	PFC.PEIORL.BIT.B0    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE1MD = 1;	// ポートE1をMTU2に設定
	PFC.PEIORL.BIT.B1    = 1;  	// 出力ポートに設定
	
	PFC.PECRL1.BIT.PE2MD = 1;	// ポートE2をMTU2に設定
	PFC.PEIORL.BIT.B2    = 1;  	// 出力ポートに設定
		
/*	PFC.PECRL1.BIT.PE3MD = 1;	// ポートE3をMTU2に設定
	PFC.PEIORL.BIT.B3    = 1;  	// 出力ポートに設定

	PFC.PECRL1.BIT.PE4MD = 1;	// ポートE4をMTU2に設定
	PFC.PEIORL.BIT.B4    = 1;  	// 出力ポートに設定

	PFC.PECRL1.BIT.PE5MD = 1;	// ポートE5をMTU2に設定
	PFC.PEIORL.BIT.B5    = 1;  	// 出力ポートに設定

	PFC.PECRL1.BIT.PE6MD = 1;	// ポートE6をMTU2に設定
	PFC.PEIORL.BIT.B6    = 1;  	// 出力ポートに設定

	PFC.PECRL1.BIT.PE7MD = 1;	// ポートE7をMTU2に設定
	PFC.PEIORL.BIT.B7    = 1;  	// 出力ポートに設定
*/
	MTU2.TSTR.BIT.CST0 = 1;     // MU20カウントスタート
	
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

	/*************チャンネル3 PWMモード1設定開始***************/

	MTU2.TSTR.BIT.CST3 = 1; 	//MTU23カウント停止
	
	MTU23.TCR.BIT.CCLR = 2; 	//TGRBでカウントクリア;
	
	MTU23.TCR.BIT.TPSC = 2; 	//クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	//立ち上がりエッジでカウント
	
	MTU23.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOB = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	MTU23.TIOR.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU23.TIOR.BIT.IOD = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	
	MTU23.TGRA = SERVO_TH;		//TIOC3Aコンペアマッチ
	MTU23.TGRB = SERVO_CYCLE;	//TIOC3Bコンペアマッチ
	MTU23.TGRC = SERVO_TH;		//TIOC3Cコンペアマッチ
	MTU23.TGRD = SERVO_CYCLE;	//TIOC3Dコンペアマッチ
	
	MTU23.TMDR.BIT.MD = 2;		//PWM1モード
	
	PFC.PECRL3.BIT.PE8MD = 1;	//ポートE8をMTU2に設定
	PFC.PEIORL.BIT.B8    = 1;  	//出力ポートに設定
	
	PFC.PECRL3.BIT.PE10MD= 1;	//ポートE10をMTU2に設定
	PFC.PEIORL.BIT.B10   = 1;  	//出力ポートに設定
	
	MTU2.TSTR.BIT.CST3 = 1;     //MU23カウントスタート
	
	/*************チャンネル3 PWMモード1設定終了***************/

	/*************チャンネル4 PWMモード1設定開始***************/

	MTU2.TSTR.BIT.CST4 = 1; 	//MTU24カウント停止
	
	MTU24.TCR.BIT.CCLR = 2; 	//TGRBでカウントクリア;
	
	MTU24.TCR.BIT.TPSC = 2; 	//クロック周波数φ/16 (MTUのクロックは25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	//立ち上がりエッジでカウント
	
	MTU24.TIOR.BIT.IOA = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOB = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	MTU24.TIOR.BIT.IOC = 2;     //初期状態で0出力 コンペアマッチしたら1出力
	MTU24.TIOR.BIT.IOD = 1;     //初期状態で0出力 コンペアマッチしたら0出力
	
	MTU24.TGRA = SERVO_TH;		//TIOC4Aコンペアマッチ
	MTU24.TGRB = SERVO_CYCLE;	//TIOC4Bコンペアマッチ
	MTU24.TGRC = SERVO_TH;		//TIOC4Cコンペアマッチ
	MTU24.TGRD = SERVO_CYCLE;	//TIOC4Dコンペアマッチ
	
	MTU24.TMDR.BIT.MD = 2;		//PWM1モード
	
	MTU2.TOER.BIT.OE4A = 1; 	//ch4だけ必須!！！
	MTU2.TOER.BIT.OE4B = 1;
	MTU2.TOER.BIT.OE4C = 1;
	MTU2.TOER.BIT.OE4D = 1;
	
								// 初期設定ではPOEモードになっているため
								// PB16になにかを接続するとPWM波形がでなくなる。
	PFC.PBIORH.BIT.B16    = 1;  // 入出力ポートに設定
								// IOの初期設定よりも早くPOEフラグがたってしまうため
								// クリアしなければならない	
	dummy = POE.ICSR1.BIT.POE3F;// ダミー読み取り
	POE.ICSR1.BIT.POE3F = 0; 	// フラグクリア
	
	PFC.PECRL4.BIT.PE12MD = 1;	//ポートE12をMTU2に設定
	PFC.PEIORL.BIT.B12    = 1;  //出力ポートに設定
	
	PFC.PECRL4.BIT.PE14MD= 1;	//ポートE14をMTU2に設定
	PFC.PEIORL.BIT.B14   = 1;  	//出力ポートに設定
	
	MTU2.TSTR.BIT.CST4 = 1;     //MU24カウントスタート
	
	/*************チャンネル4 PWMモード1設定終了***************/
}
#endif
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
		pwm = THRESHOLD + ( (UP_LIMIT - THRESHOLD) * duty ) / 100; 		//dutyの設定 PWM
		
		if(pwm >= UP_LIMIT){pwm = UP_LIMIT;}		//頭打ち				
	}	
	else if(duty < 0.0)
	{
		pwm = THRESHOLD + ( (THRESHOLD - DOWN_LIMIT) * duty ) / 100;	//dutyの設定 PWM
		
		if(pwm <= DOWN_LIMIT){pwm = DOWN_LIMIT;}	//頭打ち
	}
	else 
	{		
		pwm = THRESHOLD;	
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

