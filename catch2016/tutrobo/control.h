/********************************************************/
//
//  概要
//      マシン移動制御関連
//  作成者
//		TUTrobo
//
/********************************************************/

#ifndef __CONTROL_H__
#define __CONTROL_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 プロトタイプ宣言
/********************************************************/
void cmd_init(void);			// コマンドの初期設定
char mode_control(void);		// モードの選択
void task_control(void);		// 場合わけをしてpathの動きを行う


/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 コマンド状態
/********************************************************/
#define CMD_HOLD			0				// 継続
#define CMD_END				1				// 終了
#define CMD_END_ALL			2				// 全て終了(タスク停止)

/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 指定サイクル待ち(wait_cycle)用
/********************************************************/
#define WAIT_CNT_FINISH		0				// カウント終了
#define WAIT_CNT_CONTINUE	1				// カウント継続

/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 PATH関連
/********************************************************/
extern unsigned short task_number;
extern struct comand_information cmd_inf;	// comArrayの値を受け取る型

/********************************************************/
//  TUTrobo
//
//  概要
//      マシン移動制御関連 プロトタイプ宣言
/********************************************************/
void enc_getrot(double *rot);
void pcon_update(char num, double current);
void pcon_setting(char num, double lim, double tlrnce);
void pcon_gain(char num, double gain_P, double gain_I, double gain_D);
void pcon_motor(char num, double duty, char sign);
double pcon_pid(char num,double target);
double pcon_manual(char num,double duty);
int comm_action(char cmd,int data);
char shoot_seq(char flag,double *rot);
char reload_seq(char flag,int ad[4],int ad_old[4]);
int terminal_control(char c);
void shooter_control(void);
/********************************************************/
//  TUTrobo
//
//  概要
//      エンコーダ関連パラメータ
/********************************************************/
//0～1の値を指定すること。現在位置が0，終点が1
#define ENC_D	40	//エンコーダーホイール直径 (歯車の場合、モジュール1*歯数40で求まる)
#define	RND_PLS	800		//一回転のパルス数
//#define PI		3.1416  //円周率
/********************************************************/
//  TUTrobo
//
//  概要
//      制御関連パラメータ
/********************************************************/
#define	MM_PER_ROT	2.0		//#エンコーダー一回転で変化する位置[mm]
#define	CENTER_MM	55.5	//#0度の時のモーター位置[mm] 49-43 OLD:57.5
#define	ROT_RADIUS	150.0	//#旋回機構の回転半径[mm] 207.5
#define DEBUG_NUM	2	//tera=0時に現在値のグラフ出力をするPCON番号

/********************************************************/
//  TUTrobo
//
//  概要
//      IDO関連 グローバル変数設定
/********************************************************/
extern char c_dbg[10];
extern char cnt_dbg;
extern int recv_cnt;
extern char print_g;
extern double print_data[4][21];

extern int send_flg;

extern struct command_parameters cmdp;
extern struct pid_config pcon[];
extern struct pid_status psta[];

extern int ad_debug_g[4],tera;
extern char encd_g,enc_reset_g;
extern double rot_cnt_g[2],pid_duty_g[2],p1_g,i1_g,p2_g,i2_g,p3_g,i3_g;



#endif // __CONTROL_H__