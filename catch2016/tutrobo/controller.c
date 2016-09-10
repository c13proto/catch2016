/********************************************************/
//
//  概要
//      コントローラー設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "setup.h"		// マイコンの設定

char 	pscon_err_flag=0;
int AD_DATA[8];

//----------------------------------------------

arm_condition TOKU_L={
	0,		//renc:エンコーダの累積値
	0,		//pos:座標[mm]
	0,		//v:速度[mm/sec]
	
	500.0,	//max_v:最大速度[mm/sec]
	0,		//aim_v:目標速度[mm/sec]
	0,		//duty:現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition TOKU_R={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	500.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_THETA_L={
	0,		//エンコーダの累積値
	0,		//座標[degree]
	0,		//角速度[degree/sec]
	
	360.0,	//最大角速度[deg/sec]
	0,		//目標角速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_THETA_R={
	0,		//エンコーダの累積値
	0,		//座標[degree]
	0,		//角速度[degree/sec]
	
	360.0,	//最大角速度[deg/sec]
	0,		//目標角速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_R_L={
	0,		//エンコーダの累積値
	0,		//座標[degree]
	0,		//角速度[degree/sec]
	
	360.0,	//最大角速度[deg/sec]
	0,		//目標角速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_R_R={
	0,		//エンコーダの累積値
	0,		//座標[degree]
	0,		//角速度[degree/sec]
	
	360.0,	//最大角速度[deg/sec]
	0,		//目標角速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_Z_L={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	500.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition KUMA_Z_R={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	500.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition UO={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	4000.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0,		//現在かけているduty(-100~100)
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
arm_condition YOSHI={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	500.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0,		//現在かけているduty(-100~100)	
	MANUAL_MODE	//mode(manual=0,auto=1,stop=2)
};
//---------------------------------------------


double KUMA_POS_LX;//熊坂アームのxy座標系
double KUMA_POS_LY;
double KUMA_POS_RX;
double KUMA_POS_RY;


int SERVO_L = SERVO_L_INITIAL;
int SERVO_R = SERVO_R_INITIAL;

char B_R=OFF;
char B_L=OFF;
char B_U=OFF;
char B_U2=OFF;
char SHABAASH=OFF;

double DEBUG[5];
/********************************************************/
//  名前      
//		recieve_data_input
//	概要
//		データ受信関連
//	機能説明
//		プレステコンから受信
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void recieve_data_input(void)
{

	static char initial=0;

	controller_data();
	controller2_data();

	if(HALF_1!=0 && D_direction_R+D_direction_L < 500 //pscon1
		|| (HALF_1_!=0 && D_direction_R_+D_direction_L_ < 500)//pscon2
		)pscon_err_flag=0;//暴走防止
	else pscon_err_flag=1;
	
	if(PSCON_SW==OFF)//最初だけチェック
	{
		if(YOSHI.duty!=0)pscon_err_flag=1;
	}

	if(pscon_err_flag==0)
	{
		static int wait_counter=0;
		const int wait_time=20;//0.2sec待機(動作を安定させるため)
		
		if(wait_counter>wait_time)
		{
			PSCON_SW=ON;		
			set_duty();//	値をdutyに変換
		}
		
		if(wait_counter<wait_time+10)wait_counter++;
	}
	else
	{ 
		printf("PSCON_ERROR\r\n");
		PSCON_SW=OFF;
	}
}

/********************************************************/
//  名前      
//		set_duty
//	概要
//		データ受信関連
//	機能説明
//		プレステコンの値をdutyに変換。
//
//	操作方法
//		変数にdutyを代入
//
//	作成者
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void set_duty(void)
{
	
	manual_ctrl();//手動操作
	auto_ctrl();//自動操作(auto.cに記載)
	stop_ctrl();
	limit_ctrl();
	
//	if(PSCON_PRE_R1==0)duty_limit_ctrl();//R1押してない時リミットをかける
}

/********************************************************/
//  名前      input_PWM_ctrl
//  概要      dutyから各レジスタに対応した数値を格納
/********************************************************/
void input_register_ctrl(void)
{	
	static double theta_l_=0,theta_r_=0;
	static int servo_l_=SERVO_L_INITIAL,servo_r_=SERVO_R_INITIAL;
	
	
	//KUMA_THETA_L.duty=duty_diff_limit(KUMA_THETA_L.duty,theta_l_,5.0);//急停止防止
	//KUMA_THETA_R.duty=duty_diff_limit(KUMA_THETA_R.duty,theta_r_,5.0);//急停止防止
	theta_l_=KUMA_THETA_L.duty;
	theta_r_=KUMA_THETA_R.duty;

	SERVO_L=servo_diff_limit(SERVO_L,servo_l_,100);//値変化し過ぎると反応してくれへん
	SERVO_R=servo_diff_limit(SERVO_R,servo_r_,100);
	servo_l_=SERVO_L;
	servo_r_=SERVO_R;

	r1_ctrl();//duty低減モード
	
	uo_v_ctrl();//魚谷ハンド速度制御
	
	
	
	//ここで正転逆転
	KUMA_THETA_L_PWM=anti_lock_pwm(-KUMA_THETA_L.duty);//0A
	KUMA_THETA_R_PWM=anti_lock_pwm(-KUMA_THETA_R.duty);//0B
	KUMA_R_L_PWM	=anti_lock_pwm(-KUMA_R_L.duty);//0C
	KUMA_R_R_PWM 	=anti_lock_pwm(KUMA_R_R.duty);//0D	
	KUMA_Z_L_PWM	=anti_lock_pwm(-KUMA_Z_L.duty);//9A
	KUMA_Z_R_PWM	=anti_lock_pwm(KUMA_Z_R.duty);//9C
	
	M5_PWM=anti_lock_pwm(PSstick_to_duty(DUTY_LY,PSCON_TH));//4A
	
	YOSHI_PWM	=anti_lock_pwm(YOSHI.duty);//4C
	TOKU_L_PWM	=anti_lock_pwm(-TOKU_L.duty);//6A
	TOKU_R_PWM	=anti_lock_pwm(TOKU_R.duty);//6B
	UO_PWM		=anti_lock_pwm(-UO.duty);//6D
	
	SERVO_L_PWM=SERVO_L;//10A
	SERVO_R_PWM=SERVO_R;//10C
	
	if(B_L==ON)PIN_B_L=ON;else PIN_B_L=OFF;
	if(B_R==ON)PIN_B_R=ON;else PIN_B_R=OFF;
	if(B_U==ON)PIN_B_U=ON;else PIN_B_U=OFF;
	if(B_U2==ON)PIN_B_U2=ON;else PIN_B_U2=OFF;
	if(SHABAASH==ON)PIN_SHABAASH=ON;else PIN_SHABAASH=OFF;
	if(TOGGLE==0)
	{	
		LED_RED=ON;
		LED_BLUE=OFF;
	}
	else 
	{
		LED_RED=OFF;
		LED_BLUE=ON;
	}
	
	if(PS_BTN(SANKAKU)==0 || PS_BTN_(SANKAKU)==0)
	{
		LED7=0;
		LED8=0;

		PE4=0;
		PE5=0;
		PE6=0;
		PE7=0;
		
	}
	else 
	{
		int limit=0;
		if(LIMIT_U==0)limit++;
		
		if(limit>=1)
		{
			LED7=1;
			LED8=1;		

			PE4=1;
			PE5=1;
			PE6=1;
			PE7=1;
		}
	}
//	printf("%d,%d\n",duty_dc,duty_sr);


}
void uo_v_ctrl(void)
{
	double diff=0;
	//魚谷の速度制御 duty100でv=4000
	UO.aim_v=UO.duty*40.0;
	diff=UO.aim_v-UO.v;
	
	UO.duty=UO.duty+diff*0.025;
	if(UO.duty>100)UO.duty=100.0;
	if(UO.duty<-100)UO.duty=-100.0;
}
void r1_ctrl(void)
{
			//R1での速度変更
	if(PSCON_PRE_R1!=0)
	{
		if(PSCON_PRE_L1!=0)//autoの時
		{	
			if(KUMA_THETA_L.mode!=STOP_MODE)KUMA_THETA_L.duty/=2.0;
			if(KUMA_R_L.mode!=STOP_MODE)KUMA_R_L.duty/=2.0;
			if(KUMA_Z_L.mode!=STOP_MODE)KUMA_Z_L.duty/=2.0;
		}
		else
		{
			if(KUMA_THETA_L.mode!=STOP_MODE)KUMA_THETA_L.duty/=2.0;
			if(KUMA_R_L.mode!=STOP_MODE)KUMA_R_L.duty/=2.0;
			if(KUMA_Z_L.mode!=STOP_MODE)KUMA_Z_L.duty/=2.0;
		}
	}
	if(PSCON_PRE_R1_!=0)
	{
		if(PSCON_PRE_L1_!=0)
		{
			if(KUMA_THETA_R.mode!=STOP_MODE)KUMA_THETA_R.duty/=2.0;
			if(KUMA_R_R.mode!=STOP_MODE)KUMA_R_R.duty/=2.0;
			if(KUMA_Z_R.mode!=STOP_MODE)KUMA_Z_R.duty/=2.0;
		}
		else
		{
			if(KUMA_THETA_R.mode!=STOP_MODE)KUMA_THETA_R.duty/=2.0;
			if(KUMA_R_R.mode!=STOP_MODE)KUMA_R_R.duty/=2.0;
			if(KUMA_Z_R.mode!=STOP_MODE)KUMA_Z_R.duty/=2.0;
		}		
	}
}
//--------------------------------------
//手動
//-------------------------------------
void manual_ctrl(void)
{
	kuma_ctrl();//熊坂アームの制御
	toku_ctrl();//徳山アームの制御
	uo_ctrl();//魚谷
	yoshi_ctrl();//吉見
	shabaash_ctrl();//サバッシュ！！
}
void kuma_ctrl(void)
{
	static int p1_start_=1,p2_start_=1;
	int p1_start=PS_BTN(START),
		p2_start=PS_BTN_(START);
	
	//左側の制御
	if(PSCON_PRE_L2-PSCON_PRE_R2>0)KUMA_THETA_L.duty=50;//反時計回りが+
	else if(PSCON_PRE_L2-PSCON_PRE_R2<0)KUMA_THETA_L.duty=-50;
	else KUMA_THETA_L.duty=0;
	if(PSCON_PRE_L1==0)
	{
		KUMA_R_L.duty=PSstick_to_duty(DUTY_LX,PSCON_TH)*0.5;//→が+
		KUMA_Z_L.duty=PSstick_to_duty(DUTY_LY,PSCON_TH)*0.5;//↓が+
	}
	
	if(KUMA_THETA_L.duty==0)KUMA_THETA_L.mode=STOP_MODE;
	else KUMA_THETA_L.mode=MANUAL_MODE;
	if(KUMA_R_L.duty==0)KUMA_R_L.mode=STOP_MODE;
	else KUMA_R_L.mode=MANUAL_MODE;
	if(KUMA_Z_L.duty==0)KUMA_Z_L.mode=STOP_MODE;
	else KUMA_Z_L.mode=MANUAL_MODE;
	
	//右側の制御
	if(PSCON_PRE_L2_-PSCON_PRE_R2_>0)KUMA_THETA_R.duty=50;//反時計回りが+
	else if(PSCON_PRE_L2_-PSCON_PRE_R2_<0)KUMA_THETA_R.duty=-50;
	else KUMA_THETA_R.duty=0;	
	if(PSCON_PRE_L1_==0)
	{
		KUMA_R_R.duty=PSstick_to_duty(DUTY_LX_,PSCON_TH)*0.5;//→が+
		KUMA_Z_R.duty=PSstick_to_duty(DUTY_LY_,PSCON_TH)*0.5;//↓が+
	}
	
	if(KUMA_THETA_R.duty==0)KUMA_THETA_R.mode=STOP_MODE;
	else KUMA_THETA_R.mode=MANUAL_MODE;
	if(KUMA_R_R.duty==0)KUMA_R_R.mode=STOP_MODE;
	else KUMA_R_R.mode=MANUAL_MODE;
	if(KUMA_Z_R.duty==0)KUMA_Z_R.mode=STOP_MODE;
	else KUMA_Z_R.mode=MANUAL_MODE;

	
	//サーボ(□○)
	if(PSCON_PRE_MARU-PSCON_PRE_SHIKAKU>0 && PSCON_PRE_L1==0)
	{
		if(PSCON_PRE_R1==0)SERVO_L+=40;
		else SERVO_L+=20;
	}
	else if(PSCON_PRE_MARU-PSCON_PRE_SHIKAKU<0 && PSCON_PRE_L1==0)
	{
		if(PSCON_PRE_R1==0)SERVO_L-=40;
		else SERVO_L-=20;
	}
	if(SERVO_L>SERVO_UP)SERVO_L=SERVO_UP;
	if(SERVO_L<SERVO_DOWN)SERVO_L=SERVO_DOWN;
	
	if(PSCON_PRE_MARU_-PSCON_PRE_SHIKAKU_>0 && PSCON_PRE_L1_==0)
	{
		if(PSCON_PRE_R1_==0)SERVO_R+=40;
		else SERVO_R+=20;
	}
	else if(PSCON_PRE_MARU_-PSCON_PRE_SHIKAKU_<0 && PSCON_PRE_L1_==0)
	{
		if(PSCON_PRE_R1_==0)SERVO_R-=40;
		else SERVO_R-=20;
	}
	if(SERVO_R>SERVO_UP)SERVO_R=SERVO_UP;
	if(SERVO_R<SERVO_DOWN)SERVO_R=SERVO_DOWN;
	
	//ブラシレス:start押される度に切り替え
	if(p1_start_!=0 && p1_start==0)
	{		
		if(B_L==OFF)B_L=ON;
		else B_L=OFF;
	}
	if(p2_start_!=0 && p2_start==0 && PS_BTN_(SELECT)!=0)
	{
		if(B_R==OFF)B_R=ON;
		else B_R=OFF;
	}
		
	p1_start_=p1_start;
	p2_start_=p2_start;
	
}
void toku_ctrl(void)
{	
	//toku_l 1P(L1,LY)
	if(PSCON_PRE_L1!=0)TOKU_L.duty=-PSstick_to_duty(DUTY_LY,PSCON_TH);//↑が+
	if(TOKU_L.duty==0)TOKU_L.mode=STOP_MODE;
	else TOKU_L.mode=MANUAL_MODE;
	//toku_r 2P(RY)
	if(PSCON_PRE_L1_==0)TOKU_R.duty=-PSstick_to_duty(DUTY_RY_,PSCON_TH);//↑が+
	if(TOKU_R.duty==0)TOKU_R.mode=STOP_MODE;
	else TOKU_R.mode=MANUAL_MODE;
	
	
}
void uo_ctrl(void)
{	
	
	/*duty v
	75.0    ,3004.1
	100.0   ,4276.4
	*/
	static int select_=1;
	int select=PS_BTN(SELECT);
	
	//P1(RY)
	if(PSCON_PRE_L1==0)UO.duty=-PSstick_to_duty(DUTY_RY,PSCON_TH)*0.75;//↑が+	
	if(UO.duty==0)UO.mode=STOP_MODE;
	else UO.mode=MANUAL_MODE;	
	
	//ブラシレス:select押される度に切り替え
	if(select_!= 0 && select==0)
	{
		if(PS_BTN(L3)==0)
		{
			if(B_U2==ON)B_U2=OFF;
			else B_U2=ON;
		}
		else if(B_U==ON)B_U=OFF;
		else B_U=ON;
	}
	
	select_=select;
}
void yoshi_ctrl(void)
{
	double duty1=0,duty2=0;
	//1P(L1,RY) or 2P(L1,LY)
	if(PSCON_PRE_L1!=0)duty1=-PSstick_to_duty(DUTY_RY,PSCON_TH);//↑が+
	if(PSCON_PRE_L1_!=0)duty2=-PSstick_to_duty(DUTY_LY_,PSCON_TH);//↑が+
	
	if(PSCON_PRE_R1!=0)duty1/=2.0;
	if(PSCON_PRE_R1_!=0)duty2/=2.0;
	
	if(ABS(duty1)>=ABS(duty2))YOSHI.duty=duty1;
	else YOSHI.duty=duty2;
	
	if(YOSHI.duty==0)YOSHI.mode=STOP_MODE;
	else YOSHI.mode=MANUAL_MODE;
}
void shabaash_ctrl(void)
{
	//サバッシュ！p2(select,start)
	static int select_start_=0;
	int select_start=0;
	
	if(PS_BTN_(START)==0 && PS_BTN_(SELECT)==0)select_start=1;
	else select_start=0;
	
	if(select_start==1 && select_start_==0)
	{
		if(SHABAASH==ON)SHABAASH=OFF;
		else SHABAASH=ON;
	}
	
	select_start_=select_start;
}

//--------------------------------------
//ストップ
//-------------------------------------
void stop_ctrl(void)
{
	kuma_stop();
	toku_stop();
	uo_stop();
	yoshi_stop();
}

void kuma_stop(void)
{
	//制御信号(最終的に入れるdutyではない)
	int theta_l=KUMA_THETA_L.mode,
		r_l=KUMA_R_L.mode,
		z_l=KUMA_Z_L.mode,
		
		theta_r=KUMA_THETA_R.mode,
		r_r=KUMA_R_R.mode,
		z_r=KUMA_Z_R.mode;
		
	static int theta_l_,theta_r_,
					r_l_,r_r_,
					z_l_,z_r_;
					
	static double pos_theta_l=THETA_L_INITIAL,pos_theta_r=THETA_R_INITIAL,
					pos_r_l=R_L_INITIAL,pos_r_r=R_R_INITIAL,
					pos_z_l,pos_z_r;
					
	
	//固定したいポジションの格納
	if(theta_l_!=STOP_MODE && theta_l==STOP_MODE)pos_theta_l=KUMA_THETA_L.pos;
	if(theta_r_!=STOP_MODE && theta_r==STOP_MODE)pos_theta_r=KUMA_THETA_R.pos;
	if(r_l_!=STOP_MODE && r_l==STOP_MODE)pos_r_l=KUMA_R_L.pos;
	if(r_r_!=STOP_MODE && r_r==STOP_MODE)pos_r_r=KUMA_R_R.pos;
	if(z_l_!=STOP_MODE && z_l==STOP_MODE)pos_z_l=KUMA_Z_L.pos;
	if(z_r_!=STOP_MODE && z_r==STOP_MODE)pos_z_r=KUMA_Z_R.pos;	

	
	//制御信号0の時にストップかける
//	if(theta_l==STOP_MODE)	KUMA_THETA_L.duty=PID_control_d(pos_theta_l,KUMA_THETA_L.pos,30.0,0.25,0,0,0.5,0);
//	if(r_l==STOP_MODE)		KUMA_R_L.duty=PID_control_d(pos_r_l,KUMA_R_L.pos,50.0,0.05,0,0,5,1);
	if(z_l==STOP_MODE)		KUMA_Z_L.duty=PID_control_d(pos_z_l,KUMA_Z_L.pos,50.0,1.25,0.01,0,5,2);

		
//	if(theta_r==STOP_MODE)	KUMA_THETA_R.duty=PID_control_d(pos_theta_r,KUMA_THETA_R.pos,30.0,2.0,0.01,0,0.5,3);
//	if(r_r==STOP_MODE)		KUMA_R_R.duty=PID_control_d(pos_r_r,KUMA_R_R.pos,50.0,0.1,0,0,5,4);
	if(z_r==STOP_MODE)		KUMA_Z_R.duty=PID_control_d(pos_z_r,KUMA_Z_R.pos,50.0,1.25,0.01,0,5,5);
	
	
	theta_l_=theta_l;
	r_l_=r_l;
	z_l_=z_l;
	
	theta_r_=theta_r;	
	r_r_=r_r;
	z_r_=z_r;
	
}
void toku_stop(void)
{
	int l=TOKU_L.mode,r=TOKU_R.mode;
	static int l_,r_;
	static double pos_l,pos_r;
	
		//固定したいポジションの格納
	if(l_!=STOP_MODE && l==STOP_MODE)pos_l=TOKU_L.pos;
	if(r_!=STOP_MODE && r==STOP_MODE)pos_r=TOKU_R.pos;
	
//	if(l==STOP_MODE)TOKU_L.duty=PID_control_d(pos_l,TOKU_L.pos,50.0,0.5,0.01,0,5,6);
//	if(r==STOP_MODE)TOKU_R.duty=PID_control_d(pos_r,TOKU_R.pos,50.0,0.5,0.01,0,5,7);
	
	l_=l;
	r_=r;
	
}
void uo_stop(void)
{
	int mode=UO.mode;
	static int mode_;
	static double pos;
	
	if(mode_!=STOP_MODE && mode==STOP_MODE)pos=UO.pos;
	
//	if(mode==STOP_MODE)YOSHI.duty=PID_control_d(pos,UO.pos,50.0,0.5,0.01,0,5,8);
	
	mode_=mode;
}
void yoshi_stop(void)
{
	int mode=YOSHI.mode;
	static int mode_;
	static double pos;
	
	if(mode_!=STOP_MODE && mode==STOP_MODE)pos=YOSHI.pos;
	
	if(mode==STOP_MODE)YOSHI.duty=PID_control_d(pos,YOSHI.pos,50.0,0.25,0.01,0,5,9);
	
	mode_=mode;
}

//--------------------------------------
//リミット
//-------------------------------------
void limit_ctrl(void)
{
	kuma_limit();
	toku_limit();
	uo_limit();
	yoshi_limit();
	
}
void kuma_limit(void)
{
	//theta
	if(KUMA_THETA_L.pos<-42.5 && KUMA_THETA_L.duty<0)KUMA_THETA_L.duty=0;
	if(KUMA_THETA_L.pos>131.1 && KUMA_THETA_L.duty>0)KUMA_THETA_L.duty=0;
	if(KUMA_THETA_R.pos>226.5 && KUMA_THETA_R.duty>0)KUMA_THETA_R.duty=0;
	if(KUMA_THETA_R.pos<53.3 && KUMA_THETA_R.duty<0)KUMA_THETA_R.duty=0;
	
	//rの前後
	if(KUMA_R_L.pos<=R_L_INITIAL+2 && KUMA_R_L.duty<0)KUMA_R_L.duty=0;
	if(KUMA_R_R.pos<=R_R_INITIAL+2 && KUMA_R_R.duty<0)KUMA_R_R.duty=0;
	
	//X530 Y480
	if(KUMA_POS_LX>530)
	{
		if(KUMA_R_L.duty>0)KUMA_R_L.duty=0;
		if(KUMA_THETA_L.duty<0)KUMA_THETA_L.duty=0;
	}
	if(KUMA_POS_LY>480 && KUMA_Z_L.pos>100)
	{
		if(KUMA_R_L.duty>0)KUMA_R_L.duty=0;
		if(KUMA_THETA_L.duty>0)KUMA_THETA_L.duty=0;
	}
	
	if(KUMA_POS_RX<-530)
	{
		if(KUMA_R_R.duty>0)KUMA_R_R.duty=0;
		if(KUMA_THETA_R.duty>0)KUMA_THETA_R.duty=0;
	}
	if(KUMA_POS_RY>480 && KUMA_Z_R.pos>100)
	{
		if(KUMA_R_R.duty>0)KUMA_R_L.duty=0;
		if(KUMA_THETA_R.duty<0)KUMA_THETA_R.duty=0;
	}
	
	//zの上下
	if(KUMA_Z_L.pos<=0 && KUMA_Z_L.duty<0)KUMA_Z_L.duty=0;
	if(KUMA_Z_R.pos<=0 && KUMA_Z_R.duty<0)KUMA_Z_R.duty=0;
	if(KUMA_Z_L.pos>=520.0 && KUMA_Z_L.duty>0)KUMA_Z_L.duty=0;
	if(KUMA_Z_R.pos>=520.0 && KUMA_Z_R.duty>0)KUMA_Z_R.duty=0;

	if(KUMA_Z_L.pos<=70.0 && PSCON_PRE_R1==0)//zアーム縁と取付台干渉防止
	{
		if((KUMA_THETA_L.pos<10.0 || KUMA_THETA_L.pos>80.0)&&KUMA_Z_L.duty>0 )KUMA_Z_L.duty=0;
		if(KUMA_R_L.pos<390.9 && KUMA_Z_L.duty>0)KUMA_Z_L.duty=0;
		if(ABS(KUMA_POS_LX)<250 && ABS(KUMA_POS_LY)<300 && KUMA_Z_L.duty>0)KUMA_Z_L.duty=0;//y300,x250
		
	}
	if(KUMA_Z_R.pos<=70.0 && PSCON_PRE_R1_==0)
	{
		if((KUMA_THETA_R.pos<100.0 || KUMA_THETA_R.pos>170.0)&&KUMA_Z_R.duty>0 )KUMA_Z_R.duty=0;
		if(KUMA_R_R.pos<390.9 && KUMA_Z_R.duty>0)KUMA_Z_R.duty=0;
		if(ABS(KUMA_POS_RX)<250 && ABS(KUMA_POS_RY)<300 && KUMA_Z_R.duty>0)KUMA_Z_R.duty=0;//y300,x250
	}
	//コモンゾーン↑のやつとファンの干渉防止
	if(KUMA_POS_LY>480.0 && KUMA_Z_L.duty>0 && PSCON_PRE_R1==0)KUMA_Z_L.duty=0;
	if(KUMA_POS_RY>480.0 && KUMA_Z_R.duty>0 && PSCON_PRE_R1_==0)KUMA_Z_R.duty=0;
	
}
void	toku_limit(void)
{
	if(TOKU_L.pos<=2 && TOKU_L.duty<0)TOKU_L.duty=0;
	if(TOKU_R.pos<=2 && TOKU_R.duty<0)TOKU_R.duty=0;
	if(TOKU_L.pos>=736.5 && TOKU_L.duty>0)TOKU_L.duty=0;
	if(TOKU_R.pos>=736.5 && TOKU_R.duty>0)TOKU_R.duty=0;
}
void	uo_limit(void)
{
	if(UO.pos<=2 && UO.duty<0)UO.duty=0;
	if(UO.pos>=1471.1 && UO.duty>0)UO.duty=0;
}
void	yoshi_limit(void)
{
	static int invade_counter=0;
	
	if(YOSHI.pos<=2 && YOSHI.duty<0)YOSHI.duty=0;
	if(YOSHI.pos>=395.0)invade_counter++;
	if(invade_counter==1 && YOSHI.duty>=99)
	{
		auto_yoshi_ctrl(YOSHI_INVADE_POS);//414.2
		invade_counter=0;
	}
	
	if(YOSHI.pos>305 && YOSHI.duty>0 && invade_counter>0)YOSHI.duty=0;
}




/********************************************************/
//  名前      
//		arm_condition_update
//	概要
//		アーム状態の更新
//	作成者
//		やまむろ
/********************************************************/
void arm_condition_update()
{
	ad_load_0_7(AD_DATA);
	
	kuma_condition_l(average_4(AD_DATA[0],0),average_4(AD_DATA[1],1),average_4(AD_DATA[2],2));
	kuma_condition_r(average_4(AD_DATA[3],3),average_4(AD_DATA[4],4),average_4(AD_DATA[5],5));
	yoshi_condition(AD_DATA[6]);
	
	toku_condition(ENC_L,ENC_R);
	uo_condition(ENC_U);


	cmt1_counter=0;
}



void kuma_condition_l(int ad_theta,int ad_r,int ad_z)
{	
	const double circ=45.0*PI;//1回転辺りの距離
	const double circ_kuma=320.0*PI;
		
	KUMA_THETA_L.pos=THETA_L_INITIAL+(double)(ad_theta- AD_THETA_L_INITIAL)*360.0/102.3 * circ/circ_kuma;//ポテンショの角度*熊坂テーブルの割合
	KUMA_R_L.pos	=R_L_INITIAL+(double)(ad_r 	- AD_R_L_INITIAL)*circ/102.3;//10回転ポテンショなので1回転で102.3
	KUMA_Z_L.pos	=-(double)(ad_z	- AD_Z_L_INITIAL)*circ/102.3;//10回転ポテンショなので1回転で102.3
	
	KUMA_POS_LX=KUMA_R_L.pos*mycos(KUMA_THETA_L.pos*PI/180.0);
	KUMA_POS_LY=KUMA_R_L.pos*mysin(KUMA_THETA_L.pos*PI/180.0);
}
void kuma_condition_r(int ad_theta,int ad_r,int ad_z)
{	
	const double circ=45.0*PI;//1回転辺りの距離
	const double circ_kuma=320.0*PI;
	
	KUMA_THETA_R.pos=THETA_R_INITIAL+(double)(ad_theta- AD_THETA_R_INITIAL)*360.0/102.3 * circ/circ_kuma;//ポテンショの角度*熊坂テーブルの割合
	KUMA_R_R.pos	=R_R_INITIAL-(double)(ad_r 	- AD_R_R_INITIAL)*circ/102.3;//10回転ポテンショなので1回転で102.3
	KUMA_Z_R.pos	=(double)(ad_z	- AD_Z_R_INITIAL)*circ/102.3;//10回転ポテンショなので1回転で102.3
	
	KUMA_POS_RX=KUMA_R_R.pos*mycos(KUMA_THETA_R.pos*PI/180.0);
	KUMA_POS_RY=KUMA_R_R.pos*mysin(KUMA_THETA_R.pos*PI/180.0);
}
void toku_condition(int enc_l,int enc_r)
{
	const double circ=45.0*PI;	
	const int enc_pulse=800;		//1回転あたりのエンコーダパルス数	
	static int enc_l_,enc_r_;		//過去のエンコーダカウント
	
	int diff_l =  -(short)((unsigned short)enc_l - (unsigned short)enc_l_);		//エンコーダの回転の向きをここで補正する。
	int diff_r =  -(short)((unsigned short)enc_r - (unsigned short)enc_r_);		//エンコーダの回転の向きをここで補正する。
	
	TOKU_L.renc += diff_l;			//エンコーダカウントの累積値
	TOKU_R.renc += diff_r;
	
	if(LIMIT_L==0)TOKU_L.renc=0;
	if(LIMIT_R==0)TOKU_R.renc=0;
	
	TOKU_L.pos=TOKU_L.renc*circ/(double)enc_pulse;
	TOKU_R.pos=TOKU_R.renc*circ/(double)enc_pulse;
	
	TOKU_L.v=diff_l*(circ/(double)enc_pulse)/(cmt1_counter*0.01);//速度計算[mm/sec]
	TOKU_R.v=diff_r*(circ/(double)enc_pulse)/(cmt1_counter*0.01);//速度計算[mm/sec]
	
	enc_l_=enc_l;
	enc_r_=enc_r;
}
void uo_condition(int enc)
{
	const double circ=45.0*PI;	
	const int enc_pulse=800;		//1回転あたりのエンコーダパルス数	
	static int enc_;		//過去のエンコーダカウント
	int diff=  (short)((unsigned short)enc - (unsigned short)enc_);
	UO.renc+=diff;	
	if(LIMIT_U==0)UO.renc=0;
	UO.pos=UO.renc*circ/(double)enc_pulse;
	UO.v=diff*(circ/(double)enc_pulse)/(cmt1_counter*0.01);//速度計算[mm/sec]
	enc_=enc;
}
void yoshi_condition(int ad)
{
	const double circ=45.0*PI;//1回転辺りの距離
	YOSHI.pos	=(double)(ad	- AD_YOSHI_INITIAL)*circ/102.3;//10回転ポテンショなので1回転で102.3
}

/********************************************************/
//  名前      
//		PSstick_to_duty
//	概要
//		プレステコンのスティックの傾きをdutyに変換(thは中心からの+-閾値)
//	作成者
//		やまむろ
/********************************************************/
double PSstick_to_duty(int val,int th)
{
	double duty=0;
	
	if( (val>=127-th) && (val<=127+th) )duty=0.0;
	else if(val<127)duty=-100.0*(127.0-(th+val))/(double)(127-th);
	else if(val>127)duty= 100.0*(val-(127.0+th))/(double)(128-th);
	
	if(duty>100)duty=100;
	else if(duty<-100)duty=-100;

	return duty;
}


/********************************************************/
//  名前      
//		average_4
//	概要
//		4つの移動平均
//	作成者
//		やまむろ
/********************************************************/
double average_4(int data,char ch)
{
	static int stack[8][4];
	static double ave;
	char i;
	for(i=3;i>0;i--)
	{
		stack[ch][i]=stack[ch][i-1];
	}
	stack[ch][0]=data;
	ave=(double)(stack[ch][0]+stack[ch][1]+stack[ch][2]+stack[ch][3])/4.0;
	
	return ave;
}

//dutyの変化量制限
double duty_diff_limit(double now,double pre,double limit)
{
	double duty=now;
	if(ABS(now-pre)>limit)
	{
		if(now>pre)duty=pre+limit;
		else if(pre>=now)duty=pre-limit;
	}
	if(duty>100)duty=100.0;
	if(duty<-100)duty=-100.0;
	return duty;
}
int servo_diff_limit(int now,int pre,int limit)
{
	double duty=now;
	if(ABS(now-pre)>limit)
	{
		if(now>pre)duty=pre+limit;
		else if(pre>=now)duty=pre-limit;
	}
	if(duty>SERVO_UP)duty=SERVO_UP;
	if(duty<SERVO_DOWN)duty=SERVO_DOWN;
	return duty;
}
double duty_limit(double duty,double limit)
{
	double val=duty;
	if(duty>limit)val=limit;
	if(duty<-limit)val=-limit;
	return val;
}
