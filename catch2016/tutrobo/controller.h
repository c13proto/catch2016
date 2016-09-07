/********************************************************/
//
//  概要
//      コントローラー設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef	__CONTLOLLER_H__
#define	__CONTLOLLER_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      コントローラー設定 プロトタイプ宣言
/********************************************************/
void set_duty(void);
void input_register_ctrl(void);
double average_4(int data,char ch);
double PSstick_to_duty(int val,int th);
void uo_v_ctrl(void);
void r1_ctrl(void);
void auto_ctrl(void);

void manual_ctrl(void);
void kuma_ctrl(void);//熊坂アームの制御
void toku_ctrl(void);//徳山アームの制御
void uo_ctrl(void);//魚谷
void yoshi_ctrl(void);//吉見
void shabaash_ctrl(void);//サバッシュ！




void stop_ctrl(void);
void kuma_stop(void);
void toku_stop(void);
void uo_stop(void);
void yoshi_stop(void);

void limit_ctrl(void);
void kuma_limit(void);
void toku_limit(void);
void uo_limit(void);
void yoshi_limit(void);
double duty_diff_limit(double now,double pre,double limit);
int servo_diff_limit(int now,int pre,int limit);
double duty_limit(double duty,double limit);

void arm_condition_update();
void kuma_condition_l(int theta,int r, int z);
void kuma_condition_r(int theta,int r, int z);
void toku_condition(int enc_l,int enc_r);
void uo_condition(int enc);
void yoshi_condition(int ad);

extern int AD_DATA[8];
extern char pscon_err_flag;
extern arm_condition 	TOKU_L,TOKU_R,
						KUMA_THETA_L,KUMA_THETA_R,
						KUMA_R_L,KUMA_R_R,
						KUMA_Z_L,KUMA_Z_R,
						UO,
						YOSHI;
extern double KUMA_POS_LX;//熊坂アームのxy座標系
extern double KUMA_POS_LY;
extern double KUMA_POS_RX;
extern double KUMA_POS_RY;
extern int SERVO_L;
extern int SERVO_R;
extern char B_L;//ブラシレス
extern char B_R;
extern char B_U;
extern char B_U2;
extern char SHABAASH;

extern double DEBUG[5];
						
#define PSCON_TH	35
#define OPEN 	(1)
#define CLOSE 	(-1*OPEN)
#define MANUAL_MODE 0
#define AUTO_MODE 1
#define STOP_MODE 2


#define THETA_L_INITIAL 0//初期角度[deg]
#define THETA_R_INITIAL 180.0//
#define R_L_INITIAL 110.0//初期位置[mm]
#define R_R_INITIAL 110.0
#define AD_THETA_L_INITIAL 470//ad初期値
#define AD_THETA_R_INITIAL 561//ad初期値
#define	AD_R_L_INITIAL 130//
#define	AD_R_R_INITIAL 899//
#define AD_Z_L_INITIAL 429
#define AD_Z_R_INITIAL 125

#define AD_YOSHI_INITIAL 540

#define SERVO_L_INITIAL 2940
#define SERVO_R_INITIAL 5140


#endif//__CONTLOLLER_H__