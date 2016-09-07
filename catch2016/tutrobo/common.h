/********************************************************/
//
//  概要
//      共通の設定事項
//  作成者
//		TUTrobo
//
/********************************************************/

/********************************************************/
//  TUTrobo
//
//  概要
//      共通の設定事項 マシン選択
/********************************************************/
#define MACHINE_NAME	HIMAWARI

/********************************************************/
//  TUTrobo
//
//  概要
//      共通の設定事項 マシンパラメータ
/********************************************************/
#if		MACHINE_NAME ==	HIMAWARI

/*マシンに合わせて設定こっから*/
#define	ENCODER_RC_L		macorrec.ENCODER_RC_L							// 左のエンコーダの補正値
#define ENCODER_RC_R		macorrec.ENCODER_RC_R							// 右のエンコーダの補正値
#define ENCODER_D			macorrec.ENCODER_D 								// エンコーダータイヤ直径
#define	ENCODER_D_L			macorrec.ENCODER_D_L							// 左エンコーダータイヤ直径
#define	ENCODER_D_R			macorrec.ENCODER_D_R							// 右エンコーダータイヤ直径
#define ENCODER_T			macorrec.ENCODER_T								// エンコーダートレッド
#define TMP					( (2.0 * ENCODER_T * ENCODER_RES) / ENCODER_D )	// 片方のエンコーダを中心にした時に一回転した時のエンコーダのパルス数

#define	ENCODER_D_X			omni_macorrec.ENCODER_D_X							// Xエンコーダータイヤ直径
#define	ENCODER_D_Y			omni_macorrec.ENCODER_D_Y							// Yエンコーダータイヤ直径



#define	TIRE_R_L			170.0 				// Aタイヤ直径
#define	TIRE_R_R			170.0 				// Bタイヤ直径
#define	TIRE_R				170.0				// タイヤ直径
#define	TIRE_T				632.0 				// タイヤトレッド

#define MAX_DUTY			100.0				// PWMのMAX値
#define MIN_DUTY			10.0				// PWMのMIN値

#define A_LIMIT				100.0				// 速度変化制限 [mm/(割り込み時間あたり)^2]

#define DIFF_LIMIT			50.0				// 左右duty差分制限

#define DIFF_OVER_K			0.1					// ???

#define MOTOR_rpm			300					// モータの定格回転数(r/min)(ギアヘッドを含む)
#define MOTOR_rating		24	  				// モータの定格電圧(V)
#define BATTERY_rating		7.7					// バッテリーの電圧
#define BATTERY				3					// 使用バッテリーの数

#define MAX_SPEED			2500.0				// 最高速度 [mm/s]
	
//#define ENCODER_RES			800					// 1回転あたりのエンコーダパルス数
//#define ENCODER_RES			3200			// 1回転あたりのエンコーダパルス数
#define ENCODER_RES			2000			// 1回転あたりのエンコーダパルス数
/*マシンに合わせて設定ここまで*/

#endif

#ifndef __COMMON_H__
#define __COMMON_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      共通の設定事項 スケジュール設定
/********************************************************/
#define FEEDBACK_INTERVAL		10				// フィードバックタイマ周期[ms]

/********************************************************/
//  TUTrobo
//
//  概要
//      共通の設定事項 	計算のときの近似値設定
/********************************************************/
#define LIMIT_ZERO				0.0000001		// 計算中の0判定
#define LIMIT_INF				1000000.0		// 計算中のInf判定
#define LIMIT_INF_OVER			1000001.0		// 計算中のInf判定代入数値

/********************************************************/
//  TUTrobo
//
//  概要
//      共通の設定事項 グローバル変数設定
/********************************************************/
extern struct machine_condition macond;			// マシンコンディション				
extern struct correction_value  macorrec;		// マシンの補正値
extern struct omni_correction_value omni_macorrec;//マシンの補正値(omni)
extern struct gyro_condition gcond;				// ジャイロのコンディション
/********************************************************/
//  TUTrobo
//
//  概要
//      割り込み関連 グローバル変数設定
/********************************************************/
extern volatile char automatic_mode_flag;		// 自動走行するか、しないか

#endif // __COMMON_H__