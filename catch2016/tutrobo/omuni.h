/********************************************************/
//
//  概要
//      オムニ関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/
#if 0
#ifndef __OMUNI_H__
#define __OMUNI_H__
/********************************************************/
//  TUTrobo
//
//  概要
//      オムニ関連	 型名宣言
/********************************************************/
typedef struct omuni_duty
{
	double 	o,l,r;	
}
OMNI_DUTY;
#define SIGN(a) ((a>0) ? 1 : -1)
#define atan3(y,x) ( (((y)==0)&& ((x)==0)) ? 0 : atan2((y),(x))) 
/********************************************************/
//  TUTrobo
//
//  概要
//      オムニ関連	 プロトタイプ宣言
/********************************************************/
void pwm_set_omni_ctrl(OMNI_DUTY omni);		//MOTOR_CONTROL(オムニ仕様)関数 
OMNI_DUTY omni_moters_duty3(double theta,double v_ratio,double duty,double theta_direction,double kaiten);
void reset(void);
void convert_omni_duty(OMNI_DUTY *omni,double max_duty,double senkai_duty);
double diff_limit(double old,double new,double limit);
void speed_control(double *duty,double *theta_direction,double *kaiten);//ブレーキと速度制御
void res_direction(double *mokuhyou_direction,double Kp,double Ki,double Kd);//方向補正

extern double motor_debug[4];
extern double custom_debug[5]; 

#endif//__OMUNI_H__