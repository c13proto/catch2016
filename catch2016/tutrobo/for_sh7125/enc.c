/********************************************************/
//
//  概要
//      エンコーダ関連設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定
#include "../enc_para.h"	//エンコーダゲイン設定

/********************************************************/
//  名前      
//		enc_init
//  概要
//      エンコーダ
//  機能説明
//		エンコーダの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		MTU2スタンバイモード解除はsetup.cにある
//		MTU2_initで行っている
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/
void enc_init(void) //位相計数モードの設定
{
	MTU2.TSTR.BIT.CST1 = 1;    			//MTU20カウント停止
	PFC.PACRL2.BIT.PA6MD = 1;			//PA6(TCLKA)の動作設定
	PFC.PACRL2.BIT.PA7MD = 1;			//PA7(TCLKB)の動作設定
	PFC.PACRL3.BIT.PA8MD = 1;			//PA8(TCLKC)の動作設定
	PFC.PACRL3.BIT.PA9MD = 1;			//PA9(TCLKD)の動作設定
	PFC.PAIORL.BIT.B6 = 0;				//PA6の入出力設定
	PFC.PAIORL.BIT.B7 = 0;				//PA7の入出力設定
	PFC.PAIORL.BIT.B8 = 0;				//PA8の入出力設定	
	PFC.PAIORL.BIT.B9 = 0;				//PA9の入出力設定
	
	MTU21.TMDR.BIT.MD = 0x0004;			//ch1を位相計数モード1に設定
	MTU22.TMDR.BIT.MD = 0x0004;			//ch2を位相計数モード1に設定
	MTU21.TCNT = 0x0000;				//チャンネル1, カウンタクリアしとく
	MTU22.TCNT = 0x0000;				//チャンネル2, カウンタクリアしとく
	MTU2.TSTR.BIT.CST1 = 1;				//カウント開始	
	MTU2.TSTR.BIT.CST2 = 1;				//カウント開始
	
}

/********************************************************/
//  TUTrobo
//
//  概要
//      AD変換関数 プロトタイプ宣言
/********************************************************/
struct enc_information ENCInfArray[][ENC_AIM_MAX];	//各制御に用いるゲインが入る
struct enc_condition enc_cond[ENC_NUM]; 			//各制御に用いるの変数を代入

/********************************************************/
//  名前      
//		enc_ctrl
//  概要
// 		エンコーダ関数
//  機能説明
//		エンコーダによるフィードバック
//  パラメタ説明
//		distEnd	目標地点
//		ch		エンコーダチャネル
//		num		ゲインの選択
//		duty	現在のduty比
//  戻り値
//		enc_res	終了時CMD_END   
//	注意事項
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int enc_ctrl(double distEnd,short ch,short num,double* duty)
{
	int res = 0;
	
	/* エンコーダ制御のゲイン関連 */
	struct enc_information enc_inf;
	
	/* ゲインの受け取り */
	enc_inf = ENCInfArray[ch][num];
	
	/* エンコーダのチャンネル選択 */
	switch(ch)
	{
		case 0:
		
			enc_cond[ch].cnt_now = MTU21.TCNT;
				enc_cond[ch].cnt_diff  = (short)( ((unsigned short)enc_cond[ch].cnt_now - (unsigned short)enc_cond[ch].cnt_old));			/* エンコーダの回転の向きをここで補正 */
			break;
			
		case 1:
		
			enc_cond[ch].cnt_now = MTU22.TCNT;
				enc_cond[ch].cnt_diff  = (short)( ((unsigned short)enc_cond[ch].cnt_now - (unsigned short)enc_cond[ch].cnt_old));			/* エンコーダの回転の向きをここで補正 */
			break;
		
	}
	
	/* エンコーダの距離を算出 */
	enc_cond[ch].cnt_old   = enc_cond[ch].cnt_now;									/* 過去のエンコーダカウントを保存 */
	enc_cond[ch].dist_now += enc_cond[ch].cnt_diff * enc_inf.THO / ENCODER_RES;		/* 移動距離 */
	
	/* PIDの成分を算出 */	
	enc_cond[ch].er   = distEnd - enc_cond[ch].dist_now;						/* 比例成分 */
	enc_cond[ch].d_er = enc_cond[ch].er - (distEnd - enc_cond[ch].dist_old);	/* 微分成分 */
	if(enc_cond[ch].er <100)													/* 積分成分 */
	{
		enc_cond[ch].i_er += enc_cond[ch].er;
	}	
	
	if(ABS(enc_cond[ch].i_er) > 10000.0)							/* 積分成分のオーバーフロー対策 */	
	{
		if(enc_cond[ch].i_er > 0.0)	{enc_cond[ch].i_er =  10000.0;}
		else						{enc_cond[ch].i_er = -10000.0;}
	}

	/* PID制御 */
	*duty = enc_inf.K  * enc_cond[ch].er 
		  + enc_inf.Kd * enc_cond[ch].d_er
		  + enc_inf.Ki * enc_cond[ch].i_er;

	/* dutyの最大値制限 */
	if(*duty >  enc_inf.ratio) *duty =  enc_inf.ratio;
	if(*duty < -enc_inf.ratio) *duty = -enc_inf.ratio;

	/* 過去の距離を保存 */
	enc_cond[ch].dist_old = enc_cond[ch].dist_now;
	
	if( (ABS(enc_cond[ch].er) < enc_inf.adm) )		//到達範囲以内の場合
	{ 				
	
		enc_cond[ch].i_er = 0.0;
		*duty = 0.0;
		res = 1;

	}
	
/*	if(PA.DRL.BIT.B12 == 0)
	{
		MTU21.TCNT = 0x0000;				//チャンネル1, カウンタクリアしとく
		dist = 0.0;
		dist_old = 0.0;
	}
*/		
	/////////////////////////////////////////////////////////////////
//	デバックするために各値をグローバル変数に格納
//	printf("%d\n",PA.DRL.BIT.B12);
	
//	printf("%3.1f\n",enc_cond[ch].dist_now);	

//	printf("%d\t",enc_cnt);
//	printf("%d\n",cnt_old);		
	
//	printf("%d\n",enc_cnt);

/*	printf("%d\t",enc_cond[ch].cnt_now);
	printf("%f\t",enc_cond[ch].dist_now);
	printf("%f\t",distEnd);
	printf("%3.1f\n",*duty);
*/

	return res;
	
}