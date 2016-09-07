/********************************************************/
//
//  概要
//      CET関連
//  作成者
//		IDO
//
/********************************************************/
#if 0
#include "setup.h"		//マイコンの設定

#define CET_MIN_TIME 8	//最小サンプリング間隔[ms]
#define CET_TIMEOUT 20	//最長待機時間[ms] (経過すると速度を0とみなす)
#define CET_CLOCK_CYCLE 6000000 //タイマーが1秒間にカウントするクロック数   PWM 48000000 CMTなら48Mhz/8=6MHz
#define ENCODER_NUM  2	//エンコーダーの数(下のcetdaの配列数と合わせる)
#define TIMER_TCNT	CMT2.CMCNT	//時間計測用タイマーカウントレジスタ
#define TIMER_CLEAR_COUNT	65535  //タイマーがクリアされる時のカウント数(オーバーフローでクリアなので0xFFFF=65535)

struct cet_data cetda[ENCODER_NUM] =
{
//		最初のアドレスはエンコーダーパルスカウントのレジスタなので回路仕様に応じて必ず修正すること
		{&(ENC1_TCNT),&(CMT2.CMCNT),	0, -1, 0, 0},				// 0 MTU5Vに対応
		{&(ENC2_TCNT),&(CMT3.CMCNT),	0, -1, 0, 0},				// 1 MTU5Wに対応
};

/********************************************************/
//  名前      
//		cet_set_timer
//  概要
// 		CET関連
//  機能説明
//		タイマー開始/停止
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

void cet_set_timer(char encnum, char onoff) 				
{
	switch(encnum){
		case 0: 
			CMT.CMSTR1.BIT.STR2 = onoff;
			break;
		
		case 1:
			CMT.CMSTR1.BIT.STR3 = onoff;
			break;
			
		default:
			break;
	}
}

/********************************************************/
//  名前      
//		cet_get_timer
//  概要
// 		CET関連
//  機能説明
//		タイマー状態の確認
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

char cet_get_timer(char encnum) 				
{
	switch(encnum){
		case 0: 
			return CMT.CMSTR1.BIT.STR2;
			break;
		
		case 1:
			return CMT.CMSTR1.BIT.STR3;
			break;
			
		default:
			return -1;
			break;
	}
}

/********************************************************/
//  名前      
//		cet_init
//  概要
// 		セットアップ関数
//  機能説明
//		SH7125におけるCETの設定を行う
//		MTU24はフリーランニングカウンタ、MTU25をインプットキャプチャに利用
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/
void cet_init(void){
//	CMT.CMSTR1.BIT.STR2 = 1;				//カウント開始
	MTU5.TCRV.BIT.TPSC = 3;     //クロック周波数φ/64 (MTUのクロックは48Mhz)
	MTU5.TCRU.BIT.TPSC = 3;     //クロック周波数φ/64 (MTUのクロックは48Mhz)
	MTU5.TIORV.BIT.IOC = 17;  // 立ち上がりエッジでインプットキャプチャ
	MTU5.TIORU.BIT.IOC = 17;  // 立ち上がりエッジでインプットキャプチャ
	MTU5.TSTR.BIT.CSTV5 = 1;     // MU25Vカウントスタート
	MTU5.TSTR.BIT.CSTU5 = 1;     // MU25Wカウントスタート
	
	IEN(MTU5,TGIV5) = 0;  //割り込み禁止
	IEN(MTU5,TGIU5) = 0;  //割り込み禁止
	IPR(MTU5,TGIV5) = 11; // 割り込みレベル設定(CMT0)0～15 0:最低 15:最高
	IPR(MTU5,TGIU5) = 11; // 割り込みレベル設定(CMT0)0～15 0:最低 15:最高
	MTU5.TIER.BIT.TGIE5V = 1;  // 割り込み許可
	MTU5.TIER.BIT.TGIE5U = 1;  // 割り込み許可
	IEN(MTU5,TGIV5) = 1;  //割り込み許可
	IEN(MTU5,TGIU5) = 1;  //割り込み許可


	
	/*SH
	MTU24.TCR.BIT.TPSC = 0;     // クロック周波数φ/1 (MTUのクロックは25Mhz)
	MTU24.TIER.BIT.TCIEV = 1;	//オーバーフロー割り込み許可
	INTC.IPRF.BIT._MTU24C= 13;  // 割り込みレベル設定(CMT1)0～15 0:最低 15:最高
	MTU2.TSTR.BIT.CST4 = 1;     // MTU24カウントスタート
	
	MTU25.TIORV.BIT.IOC = 17;  // 立ち上がりエッジでインプットキャプチャ
	MTU25.TIORW.BIT.IOC = 17;  // 立ち上がりエッジでインプットキャプチャ
	
	PFC.PBCRL1.BIT.PB1MD = 3;	// ポートB1をMTU2に設定
	PFC.PBIORL.BIT.B1    = 0;  	// 入力ポートに設定
	
	PFC.PBCRL1.BIT.PB3MD = 3;	// ポートB3をMTU2に設定
	PFC.PBIORL.BIT.B3    = 0;  	// 入力ポートに設定
	
	MTU25.TIER.BIT.TGIEV = 1; 	//割り込み許可(TCLKA)	
	MTU25.TIER.BIT.TGIEW = 1;	//割り込み許可(TCLKC)
	INTC.IPRF.BIT._MTU25= 12;
	*/
}	

/********************************************************/
//  名前      
//		cet_edge_action
//  概要
// 		CET関連
//  機能説明
//		パルスエッジでの動作
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

void cet_edge_action(char encnum) 				
{
	double elapsed_clock;
	if(cet_get_timer(encnum) == 1){ //繰り上がり回数が-1(初期状態)で無かったら、時間計測中
		elapsed_clock = *cetda[encnum].timer_tcnt; //カウント開始からの経過時間を求める 式：(現在のタイマーカウント + 繰り上がりする数*繰り上がり回数) - カウント開始時のタイマーカウント
		if(elapsed_clock >= (double)(CET_MIN_TIME * CET_CLOCK_CYCLE / 1000)){ //経過時間が最低サンプリング間隔より大きいかチェック 式：最小サンプリング間隔[ms]*1msあたりのカウント数
			cetda[encnum].last_tcnt = *cetda[encnum].enc_tcnt; //現在のエンコーダーパルスカウントを記憶
			cetda[encnum].last_elapsed = elapsed_clock; //現在の経過時間を記憶
			cet_set_timer(encnum, 0); //カウント停止
			//put_s("checked");
		}
	}else{ //繰り上がり回数が初期状態なら、カウントを開始する
		*cetda[encnum].timer_tcnt = *cetda[encnum].enc_tcnt = 0; //繰り上がり回数、エンコーダーパルスカウントをゼロに
		cet_set_timer(encnum, 1); //カウント開始
	}
//	put_s("DBG_EDGE");
}

/********************************************************/
//  名前      
//		cet_clear_action
//  概要
// 		CET関連
//  機能説明
//		時間計測用タイマークリア時の動作
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

void cet_clear_action(char encnum) 				
{
	cet_set_timer(encnum, 0); //カウント停止
	cetda[encnum].last_tcnt = cetda[encnum].last_elapsed = 0; //速度を0にする
	//put_s("DBG_CMT2");
}

/********************************************************/
//  名前      
//		cet_get_rpm
//  概要
// 		CET関連
//  機能説明
//		与えられた配列に回転速度[RPM]を代入
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

void cet_get_rpm(double rot_return[]) 				
{
	char i;
	double delta_t[ENCODER_NUM];
	for(i=0; i < ENCODER_NUM; i++){
		delta_t[i] = (double)cetda[i].last_elapsed / (double)CET_CLOCK_CYCLE; //経過時間[s]を計算 式:経過カウント数 / 1秒あたりのカウント数
		if(delta_t[i] != 0.0)
			rot_return[i] = ((double)((short)cetda[i].last_tcnt) / (double)RND_PLS)* 60.0 / delta_t[i]; //RPMを返す 式:(エンコーダーパルス / 一回転あたりのパルス数)[回転] / 経過時間[s] * 60[s] 
		else
			rot_return[i] = 0.0;
		//if(fabs(rot_old[i]-rot_return[i]) > 200.0 && tera==1) //もし前回との差が大きすぎたらデバッグ内容をプリント
		//	printf("%d: %.2f,%.2f,%.1fms,%d\n",i,rot_old[i],rot_return[i],delta_t[i]*1000,cetda[i].cntup);
		//rot_old[i] = rot_return[i]; //前回の値を記憶
	}
//	put_s("get");
}
#endif
