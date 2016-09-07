/********************************************************/
//
//  概要
//      フィードバック関連
//  作成者
//		TUTrobo
//
/********************************************************/


#ifndef __FEEDBACK_H__
#define __FEEDBACK_H__

#include "type.h"		//プログラムの型名宣言

/********************************************************/
//  TUTrobo
//
//  概要
//      フィードバック関連 プロトタイプ宣言
/********************************************************/
void feedback_drive(void);										//フィードバック
double duty_to_speed(double duty);								//マシンの目標とする動きをdutyから速度に変更
double speed_to_duty(double speed);								//マシンの目標とする動きを速度からdutyに変更
void foot_set_aiming_motion(double v_ratio,double r0,double t);	//マシンの目標とする動きを設定
void lr_duty_ceiling_shift(DOUBLE_LR* d,double max);			//上限にあわせてシフト
void lr_duty_diff_limit(DOUBLE_LR* d,double limit,double over_k);//差動制限
void lr_duty_lowpath(DOUBLE_LR* duty,double a_limit);			//ローパス(加速制限)

/********************************************************/
//  TUTrobo
//
//  概要
//      フィードバック関連 グローバル変数宣言
/********************************************************/
extern volatile double    aim_v;				//速度(レシオ)
extern volatile DOUBLE_LR aim_lr;				//差動比率

#endif	//__FEEDBACK_H__　
