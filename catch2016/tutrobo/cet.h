/********************************************************/
//
//  概要
//      CET関連
//  作成者
//		Ido
//
/********************************************************/

#ifndef __CET_H__
#define __CET_H__

#define USE_CET			//CET使用
#define TIMER_START(ch) (CMT.CMSTR1.BIT.STR##ch)
/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 プロトタイプ宣言
/********************************************************/
void cet_set_timer(char encnum, char onoff);
char cet_get_timer(char encnum);
void cet_init(void);
unsigned short* get_enc_tcnt(char num);
void cet_edge_action(char encnum);
void cet_clear_action(char encnum);
void cet_get_rpm(double rot_return[]);

/*
unsigned int g_cet_start_clock[ENCODER_NUM];
int g_cet_cntup[ENCODER_NUM],g_cet_tcnt[ENCODER_NUM],g_cet_elapsed[ENCODER_NUM];

unsigned short* g_enc_tcnt[ENCODER_NUM]
*/

struct cet_data{
	unsigned short* enc_tcnt;	//エンコーダーカウントレジスタへのアドレス
	unsigned short* timer_tcnt;	//タイマーカウントレジスタへのアドレス
	unsigned int start_clock;	//カウント開始時のタイマークロック
	int cntup;					//繰り上がり回数
	int last_tcnt;				//最後に記録されたエンコーダカウント
	int last_elapsed;			//最後に記録されたカウント時間
};

#endif // __CET_H__