/********************************************************/
//
//  概要
//      CMT関連
//  注意
//		マイコン依存ファイル!!
//  作成者
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

/********************************************************/
//  名前      
//		cmt_init
//  概要
// 		CMT関数
//  機能説明
//		CMTの初期設定　(クロック設定が25MHzにしてある)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		タイマカウントは
//		TASK_START()およびTASK_END()でコントロールしている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void cmt_init(void) 
{
	
	MSTP_CMT0 = 0;						//スリープ偏移解除
	CMT.CMSTR0.BIT.STR0 = 0;				//カウント停止
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT0.CMCR.BIT.CMIE= 1;				//割込許可
	CMT0.CMCR.BIT.CKS = 1;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	#ifdef USE_CET
	CMT0.CMCOR = 5969;						//コンペアマッチコンスタント設定(4ms) 0.67 *10^(-3) * n=2  n=5970.15
	#else
	CMT0.CMCOR = 14925;						//コンペアマッチコンスタント設定(10ms) 0.67 *10^(-3) * n=10  n=14925.37 
	#endif
	CMT0.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR0.BIT.STR0 = 0;				//カウント停止
	
	IEN(CMT0,CMI0) = 0;  //割り込み禁止
	IPR(CMT0,CMI0) = 9; // 割り込みレベル設定(CMT0)0〜15 0:最低 15:最高
	IEN(CMT0,CMI0) = 1;  //割り込み許可

	MSTP_CMT1 = 0;						//スリープ偏移解除
	CMT.CMSTR0.BIT.STR1 = 0;				//カウント停止
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT1.CMCR.BIT.CMIE= 1;				//割込許可
	CMT1.CMCR.BIT.CKS = 1;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	CMT1.CMCOR = 14925;						//コンペアマッチコンスタント設定(10ms) 0.67 *10^(-3) * n=10  n=14925.37 
	CMT1.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR0.BIT.STR1 = 0;				//カウント停止
	
	IEN(CMT1,CMI1) = 0;  //割り込み禁止
	IPR(CMT1,CMI1) = 10; // 割り込みレベル設定(CMT0)0〜15 0:最低 15:最高
	IEN(CMT1,CMI1) = 1;  //割り込み許可
	
	MSTP_CMT2 = 0;						//スリープ偏移解除
	CMT.CMSTR1.BIT.STR2 = 0;				//カウント停止
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT2.CMCR.BIT.CMIE= 1;				//割込許可
	CMT2.CMCR.BIT.CKS = 0;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	CMT2.CMCOR = 65535;						//コンペアマッチコンスタント設定(10ms) 0.67 *10^(-3) * n=10  n=14925.37 
	CMT2.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR1.BIT.STR2 = 0;				//カウント停止
	
	IEN(CMT2,CMI2) = 0;  //割り込み禁止
	IPR(CMT2,CMI2) = 12; // 割り込みレベル設定(CMT0)0〜15 0:最低 15:最高
	IEN(CMT2,CMI2) = 1;  //割り込み許可	
	
	MSTP_CMT3 = 0;						//スリープ偏移解除
	CMT.CMSTR1.BIT.STR3 = 0;				//カウント停止
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT3.CMCR.BIT.CMIE= 1;				//割込許可
	CMT3.CMCR.BIT.CKS = 0;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	CMT3.CMCOR = 65535;						//コンペアマッチコンスタント設定(10ms) 0.67 *10^(-3) * n=10  n=14925.37 
	CMT3.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR1.BIT.STR3 = 0;				//カウント停止
	
	IEN(CMT3,CMI3) = 0;  //割り込み禁止
	IPR(CMT3,CMI3) = 12; // 割り込みレベル設定(CMT0)0〜15 0:最低 15:最高
	IEN(CMT3,CMI3) = 1;  //割り込み許可	
}
