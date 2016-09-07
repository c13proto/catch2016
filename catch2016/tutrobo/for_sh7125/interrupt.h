/********************************************************/
//
//  概要
//      割り込み関数関連
//	更新日時
//		2013/02/02
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __INTPRG_H__
#define __INTPRG_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      割り込み関数関連 プロトタイプ宣言
/********************************************************/
void int_cmt_cmt0(void);	// タイマ割り込み関数
void int_cmt_cmt1(void);	// タイマ割り込み関数
void int_sci1_rxi1(void);	// 受信割り込み関数

void int_sci0_txi0(void);	// 送信割り込み関数
void int_sci0_tei0(void);	// 送信完了割り込み関数
void int_sci0_rxi0(void);	// 受信割り込み関数
void int_sci0_eri0(void);	// 受信エラー割り込み関数

void int_sci1_txi1(void);	// 送信割り込み関数
void int_sci1_tei1(void);	// 送信完了割り込み関数
void int_sci1_rxi1(void);	// 受信割り込み関数
void int_sci1_eri1(void);	// 受信エラー割り込み関数

void int_sci2_txi2(void);	// 送信割り込み関数
void int_sci2_tei2(void);	// 送信完了割り込み関数
void int_sci2_rxi2(void);	// 受信割り込み関数
void int_sci2_eri2(void);	// 受信エラー割り込み関数

void after_recieve(void);	// 受信したデータから各種プログラムを実行する
void automatic_mode(void);	// 受信したデータから自動走行するかしないかを判断
void R1350N(unsigned char c);			// ジャイロ

/********************************************************/
//  TUTrobo
//
//  概要
//      割り込み関連 マクロ定義
/********************************************************/
#define SENCE_START()	{CMT.CMSTR.BIT.STR0 = 1;}
#define SENCE_END()		{CMT.CMSTR.BIT.STR0 = 0;}
#define TASK_START()	{CMT.CMSTR.BIT.STR1 = 1;}
#define TASK_END()		{CMT.CMSTR.BIT.STR1 = 0;}

extern int angle,accX,accY,accZ;//ジャイロの情報。角度、加速度
extern int m_angle;//角度
extern int cmt1_counter;//タイマ割り込みに入った回数を数える

#endif	//__INTPRG_H__
