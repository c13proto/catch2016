/********************************************************/
//
//  概要
//      A/D変換設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __AD_H__
#define __AD_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      A/D変換設定 プロトタイプ宣言
/********************************************************/
void ad_init();		 			// AD変換の初期設定
void ad_load_0_3(int *ad_data);	// チャンネル0~3を一度に読み取る	
void ad_load_4_7(int *ad_data);	// チャンネル4~7を一度に読み取る
void ad_load_0_7(int *ad_data);	// チャンネル0~7を一度に読み取る
int PID_control(double mokuhyou,double position,int max_duty,double Kp,double Ki,double Kd,char num);
double PID_control_d(double mokuhyou,double position,double max_duty,double Kp,double Ki,double Kd,double I_reset_range,char num);
#endif // __AD_H__