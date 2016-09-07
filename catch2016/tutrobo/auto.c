#include "setup.h"		// マイコンの設定

//--------------------------------------
//自動
//-------------------------------------

void auto_ctrl(void)
{
	auto_p1_ctrl();
	auto_p2_ctrl();
}

void auto_p1_ctrl(void)
{
	static	int uo_flag=0;
	static	int uo_counter=0;

	int maru=PSCON_PRE_MARU,
		sankaku=PSCON_PRE_SANKAKU,
		shikaku=PSCON_PRE_SHIKAKU,
		batsu=PSCON_PRE_BATSU,
		L1=PSCON_PRE_L1;
		
	//山室
	if(L1!=0)
	{		
		auto_uo_ctrl(0,50.0,0.75);
		if(D_direction_R!=0)//最初の動き
		{
			const int wait_time=5;//[*10ms]
			const double bottom_pos=1450.0;//1460.0;
			const double box_pos=100.0;
			
			if(uo_flag==0)
			{
				B_U=ON;
				B_U2=OFF;//低速モードOFF
			}
			
			auto_yoshi_ctrl(353.77);//吉見機構落ちない位置まで移動
			if(LED_RED==ON)
			{
				auto_toku_l_ctrl(371.4);//徳山取る直前まで移動
				auto_toku_r_ctrl(371.4);//徳山取る直前まで移動
			}
						
			if(YOSHI.pos>65.0)
			{								
				if(uo_flag==0)
				{
					auto_uo_ctrl(bottom_pos,75.0,0.75);
					if(ABS(UO.pos-bottom_pos)<20)uo_counter++;
					if(uo_counter>wait_time)uo_flag=1;//下に到着
				}
				else if(uo_flag==1)
				{
					auto_uo_ctrl(box_pos,100.0,0.75);
					if(ABS(box_pos-UO.pos)<550)B_U=OFF;
					if(UO.pos<box_pos)uo_flag=2;
				}
				else if(uo_flag==2)
				{
					auto_uo_ctrl(box_pos+5,100.0,1.5);
					if(UO.pos>box_pos+10)uo_flag=3;
				}
				else UO.duty=0;
				
			}
		}
		else if(D_direction_L!=0)//安全版
		{
			const int wait_time=25;//[*10ms]
			const double bottom_pos=1450.0;//1460.0;
			const double box_pos=100.0;
			
			if(uo_flag==0)
			{
				B_U=ON;
				B_U2=OFF;//低速モードOFF
			}
			
			auto_yoshi_ctrl(353.77);//吉見機構落ちない位置まで移動
			if(LED_RED==ON)
			{
				auto_toku_l_ctrl(371.4);//徳山取る直前まで移動
				auto_toku_r_ctrl(371.4);//徳山取る直前まで移動
			}
						
			if(YOSHI.pos>65.0)
			{								
				if(uo_flag==0)
				{
					auto_uo_ctrl(bottom_pos,60.0,0.75);
					if(ABS(UO.pos-bottom_pos)<20)uo_counter++;
					if(uo_counter>wait_time)uo_flag=1;//下に到着
				}
				else if(uo_flag==1)
				{
					auto_uo_ctrl(box_pos,40.0,0.75);
					if(ABS(box_pos-UO.pos)<550)B_U=OFF;
					if(UO.pos<box_pos)uo_flag=2;
				}
				else if(uo_flag==2)
				{
					auto_uo_ctrl(box_pos+5,100.0,1.5);
					if(UO.pos>box_pos+10)uo_flag=3;
				}
				else UO.duty=0;
				
			}
		}
		else if(D_direction_U!=0)//上の経路
		{
			if(KUMA_Z_L.pos>=100.0)auto_kuma_l_ctrl(40.0  ,500.0  ,-30   ,SERVO_L_INITIAL);//下にいる時まずは安定位置に移動
			else if(maru==0 && sankaku==0 && shikaku==0 && batsu!=0)
			{
				auto_kuma_l_ctrl(-33.1,		412.6,		-30,		SERVO_L_INITIAL-1180);//↓BOX
				if(KUMA_THETA_L.pos>45 && KUMA_THETA_L.pos<90)
					KUMA_R_L.duty=PID_control_d(350,KUMA_R_L.pos,65.0,0.5,0,0,5,1);//コモンゾーンとの干渉回避
				if(KUMA_THETA_L.pos>0)SERVO_L=SERVO_L_INITIAL;
				
				KUMA_THETA_L.duty=duty_limit(KUMA_THETA_L.duty,70);
				KUMA_R_L.duty=duty_limit(KUMA_R_L.duty,30);
				KUMA_Z_L.duty=duty_limit(KUMA_Z_L.duty,30);
			}
			else if(maru==0 && sankaku==0 && shikaku!=0 && batsu==0)
			{
				auto_kuma_l_ctrl(111.8,		467.9,		-30 ,		SERVO_L_INITIAL+780);//←BOX
				if(KUMA_THETA_L.pos>45 && KUMA_THETA_L.pos<90)
					KUMA_R_L.duty=PID_control_d(350,KUMA_R_L.pos,65.0,0.5,0,0,5,1);//コモンゾーンとの干渉回避
				if(KUMA_THETA_L.pos<90)SERVO_L=SERVO_L_INITIAL;
				
				KUMA_THETA_L.duty=duty_limit(KUMA_THETA_L.duty,70);
				KUMA_R_L.duty=duty_limit(KUMA_R_L.duty,30);
				KUMA_Z_L.duty=duty_limit(KUMA_Z_L.duty,30);
			}
			else if(maru==0 && sankaku!=0 && shikaku!=0 && batsu==0)
			{	
				auto_kuma_l_ctrl(109.8 ,601.9  ,-30   ,SERVO_L_INITIAL+3620);//左フタ
				if(KUMA_THETA_L.pos<45)KUMA_R_L.duty=0;//吉見機構との干渉防止
			}
			else if(maru==0 && sankaku!=0 && shikaku==0 && batsu==0)
			{	
				auto_kuma_l_ctrl(55.9  ,660.0  ,-30  ,SERVO_L_INITIAL+1800);//左中フタ
				if(KUMA_THETA_L.pos<45)KUMA_R_L.duty=0;
			}
			else kuma_l_zero();
		
		}
		else if(D_direction_D!=0)//下の経路
		{
			static int safe_flag=0;
			
			if(KUMA_Z_L.pos<=250)
			{
				SERVO_L=SERVO_L_INITIAL;
				auto_kuma_l_ctrl(40.0  ,450.0  ,500.0	,SERVO_L_INITIAL);//まずは安定位置に移動
				if(ABS(KUMA_THETA_L.pos-40.0)>10.0 || ABS(KUMA_R_L.pos-450)>10 && safe_flag==0)
					KUMA_Z_L.duty=PID_control_d(0,KUMA_Z_L.pos,50.0,1.5,0,0,5,2);//高さ０でストップ
				else safe_flag=1;
				
				if(KUMA_THETA_L.pos>90)
					KUMA_R_L.duty=PID_control_d(350,KUMA_R_L.pos,50.0,0.5,0,0,5,1);//コモンゾーンとの干渉回避
			}
			else if(maru==0 && sankaku==0 && shikaku!=0 && batsu==0)//左
				auto_kuma_l_ctrl(63.8  ,382.2	,450.2  ,SERVO_L_INITIAL+1980);
			else if(maru==0 && sankaku!=0 && shikaku!=0 && batsu==0)//左中
				auto_kuma_l_ctrl(49.4  ,467.9  ,450.2  ,SERVO_L_INITIAL+1600);
			else if(maru!=0 && sankaku!=0 && shikaku==0 && batsu==0)//右中
				auto_kuma_l_ctrl(35.6  ,560.5  ,450.2  ,SERVO_L_INITIAL+1180);
			else if(maru!=0 && sankaku==0 && shikaku==0 && batsu==0)//右
				auto_kuma_l_ctrl(28.2  ,672.4  ,450.2  ,SERVO_L_INITIAL+360);
			else if(maru!=0 && sankaku==0 && shikaku==0 && batsu!=0)//右下
				auto_kuma_l_ctrl(14.8  ,449.9  ,450.2  ,SERVO_L_INITIAL+3540);
			else if(maru==0 && sankaku==0 && shikaku!=0 && batsu!=0)//左下
				auto_kuma_l_ctrl(47.5  ,304.8  ,450.2  ,SERVO_L_INITIAL-1653);
			else 
			{
				safe_flag=0;
				kuma_l_zero();
			}
		}
		else
		{	
			if(PS_BTN(R3)==0)
			{
				uo_flag=0;
				uo_counter=0;
			}
			kuma_l_zero();
			auto_uo_ctrl(0,50.0,0.75);
		}
	}
	else 
	{
	}
	
}

void auto_p2_ctrl(void)
{
	
	
	int maru=PSCON_PRE_MARU_,
		snkaku=PSCON_PRE_SANKAKU_,
		shikaku=PSCON_PRE_SHIKAKU_,
		batsu=PSCON_PRE_BATSU_,
		L1=PSCON_PRE_L1_;
	
	//徳山
	if(L1!=0)//L1押されてる時
	{
		
		static int start_flag=0;
		if(D_direction_R_!=0)//最初の動き
		{
			
			//auto_kuma_r_ctrl(160.3 ,440.2 ,0,SERVO_R_INITIAL-4080)
			if(start_flag==0)
			{
				auto_kuma_r_ctrl(250,0,0,SERVO_R_INITIAL);//
				if(KUMA_THETA_R.pos>225)start_flag=1;				
			}
			if(start_flag==1)
			{
				auto_kuma_r_ctrl(200,405.2,0,SERVO_R_INITIAL);//
				if(KUMA_R_R.pos>300)auto_kuma_r_ctrl(160.3 ,405.2 ,0,SERVO_R_INITIAL-4080);
				if(KUMA_THETA_R.pos<165)start_flag=2;
			}
			if(start_flag==2)
			{
				auto_kuma_r_ctrl(160.3 ,405.2 ,450.2,SERVO_R_INITIAL-4080);
				if(KUMA_Z_R.pos>200)auto_kuma_r_ctrl(160.3 ,440.2 ,450.2,SERVO_R_INITIAL-4080);
				if(KUMA_Z_R.pos>400)start_flag=3;
			}
			if(start_flag==3)
			{
				kuma_r_zero();
			}		
		}
		else if(D_direction_U_!=0)//上の経路
		{
			if(maru==0 && snkaku==0 && shikaku!=0 && batsu==0)
			{
				auto_kuma_r_ctrl(165.1 ,370.2,-30,SERVO_R_INITIAL-3600);//左下(リミットで干渉は避けてくれるはず)
				KUMA_THETA_R.duty=duty_limit(KUMA_THETA_R.duty,70);
				KUMA_R_R.duty=duty_limit(KUMA_R_R.duty,30);
				KUMA_Z_R.duty=duty_limit(KUMA_Z_R.duty,40);
			}
			else if(KUMA_Z_R.pos>=100)
			{
				auto_kuma_r_ctrl(140.0 ,500.0 ,-30  	,SERVO_R_INITIAL);//下にいる時はとりあえず安定位置へ
				KUMA_THETA_R.duty=duty_limit(KUMA_THETA_R.duty,70);
				KUMA_R_R.duty=duty_limit(KUMA_R_R.duty,30);
				KUMA_Z_R.duty=duty_limit(KUMA_Z_R.duty,40);
			}
			else if(maru!=0 && snkaku==0 && shikaku==0 && batsu==0)
			{
				auto_kuma_r_ctrl(66.6  ,456.8  ,-30	,SERVO_R_INITIAL-840);//→BOX
				if(KUMA_THETA_R.pos<135 && KUMA_THETA_R.pos>90)
					KUMA_R_R.duty=PID_control_d(350,KUMA_R_R.pos,65.0,0.5,0,0,5,4);//コモンゾーンとの干渉回避
				if(KUMA_THETA_R.pos>90)SERVO_R=SERVO_R_INITIAL;
				KUMA_THETA_R.duty=duty_limit(KUMA_THETA_R.duty,70);
				KUMA_R_R.duty=duty_limit(KUMA_R_R.duty,30);
				KUMA_Z_R.duty=duty_limit(KUMA_Z_R.duty,40);
			}
			else if(maru==0 && snkaku==0 && shikaku==0 && batsu!=0)
			{
				auto_kuma_r_ctrl(220.5 ,445.8,0   ,SERVO_R_INITIAL+1260);//↓BOX
				if(KUMA_THETA_R.pos<135 && KUMA_THETA_R.pos>90)
					KUMA_R_R.duty=PID_control_d(350,KUMA_R_R.pos,65.0,0.5,0,0,5,4);//コモンゾーンとの干渉回避
				if(KUMA_THETA_R.pos<180)SERVO_R=SERVO_R_INITIAL;
				
				KUMA_THETA_R.duty=duty_limit(KUMA_THETA_R.duty,70);
				KUMA_R_R.duty=duty_limit(KUMA_R_R.duty,30);
				KUMA_Z_R.duty=duty_limit(KUMA_Z_R.duty,40);
			}
			else if(maru!=0 && snkaku!=0 && shikaku==0 && batsu==0)
			{	
				auto_kuma_r_ctrl(71.6  ,601.9  ,-30   ,SERVO_R_INITIAL-3760);//コモン右
				if(KUMA_THETA_R.pos>135)KUMA_R_R.duty=0;
			}
			else if(maru==0 && snkaku!=0 && shikaku==0 && batsu==0)
			{	auto_kuma_r_ctrl(124.5 ,671.0  ,-30   ,SERVO_R_INITIAL-1900);//コモン右中
				if(KUMA_THETA_R.pos>135)KUMA_R_R.duty=0;
			}
			else kuma_r_zero();
			
		}
		else if(D_direction_D_!=0)//下の経路
		{
			static int safe_flag=0;
			
			if(KUMA_Z_R.pos<=250)
			{

				SERVO_R=SERVO_R_INITIAL;
				auto_kuma_r_ctrl(140.0  ,450.0  ,500.0	,SERVO_R_INITIAL);//まずは安定位置に移動
				if( ABS(KUMA_THETA_R.pos-140.0)>10.0 || ABS(KUMA_R_R.pos-450)>10 && safe_flag==0)
				{	
					KUMA_Z_R.duty=PID_control_d(0,KUMA_Z_R.pos,50.0,1.5,0,0,5,5);
					//R:140.9 ,425.0  ,4.1    ,5140
				}
				else safe_flag=1;			
				if(KUMA_THETA_R.pos<90)KUMA_R_R.duty=PID_control_d(350,KUMA_R_R.pos,50.0,0.5,0,0,5,4);//コモンゾーンとの干渉回避
				
			}
			else if(maru!=0 && snkaku==0 && shikaku==0 && batsu==0)
				auto_kuma_r_ctrl(115.6 ,367.0	,450.2  ,SERVO_R_INITIAL-2180);//右
			else if(maru!=0 && snkaku!=0 && shikaku==0 && batsu==0)
				auto_kuma_r_ctrl(132.9 ,443.0  ,450.2  ,SERVO_R_INITIAL-1520);//右中
			else if(maru==0 && snkaku!=0 && shikaku!=0 && batsu==0)
				auto_kuma_r_ctrl(142.3 ,559.1  ,450.2  ,SERVO_R_INITIAL-1240);//左中
			else if(maru==0 && snkaku==0 && shikaku!=0 && batsu==0)
				auto_kuma_r_ctrl(151.2 ,661.3  ,450.2  ,SERVO_R_INITIAL-900);//左
			else if(maru!=0 && snkaku==0 && shikaku==0 && batsu!=0)
				auto_kuma_r_ctrl(136.4 ,300.7  ,450.2  ,SERVO_R_INITIAL+1560);//右下
			else if(maru==0 && snkaku==0 && shikaku!=0 && batsu!=0)
				auto_kuma_r_ctrl(165.1 ,440.2  ,450.2  ,SERVO_R_INITIAL-3600);//左下
			else 
			{
				
				safe_flag=0;
				kuma_r_zero();
			}
		}
		else
		{
			start_flag=0;
			kuma_r_zero();
		}
	}
	else
	{
	}
}


void kuma_l_zero(void)
{
	KUMA_THETA_L.duty=0;
	KUMA_R_L.duty=0;
	KUMA_Z_L.duty=0;
	
	KUMA_THETA_L.mode=STOP_MODE;
	KUMA_R_L.mode=STOP_MODE;
	KUMA_Z_L.mode=STOP_MODE;
		
}
void kuma_r_zero(void)
{
	KUMA_THETA_R.duty=0;
	KUMA_R_R.duty=0;
	KUMA_Z_R.duty=0;
	
	KUMA_THETA_R.mode=STOP_MODE;
	KUMA_R_R.mode=STOP_MODE;
	KUMA_Z_R.mode=STOP_MODE;
}
void auto_kuma_l_ctrl(double theta,double r,double z,int servo)
{
	const double	//PID制御を止める範囲 
		diff_theta=1.0,
		diff_r=10.0,
		diff_z=10.0;
			
	KUMA_THETA_L.duty=PID_control_d(theta,KUMA_THETA_L.pos,100.0,5.0,0,0,0.5,0);
	KUMA_R_L.duty=PID_control_d(r,KUMA_R_L.pos,50.0,0.35,0,0,5,1);
	KUMA_Z_L.duty=PID_control_d(z,KUMA_Z_L.pos,50.0,0.75,0,0,5,2);
	SERVO_L=servo;
	
	//if(ABS(KUMA_THETA_L.pos-theta)<diff_theta)KUMA_THETA_L.duty=0;
	//if(ABS(KUMA_R_L.pos-r)<diff_r)KUMA_R_L.duty=0;
	//if(ABS(KUMA_Z_L.pos-z)<diff_z)KUMA_Z_L.duty=0;
			
	KUMA_THETA_L.mode=AUTO_MODE;
	KUMA_R_L.mode=AUTO_MODE;
	KUMA_Z_L.mode=AUTO_MODE;
}
void auto_kuma_r_ctrl(double theta,double r,double z,int servo)
{
	const double	//PID制御を止める範囲 
		diff_theta=1.0,
		diff_r=10.0,
		diff_z=10.0;
			
	KUMA_THETA_R.duty=PID_control_d(theta,KUMA_THETA_R.pos,100.0,5.0,0,0,0.5,3);
	KUMA_R_R.duty=PID_control_d(r,KUMA_R_R.pos,70.0,0.65,0,0,5,4);
	KUMA_Z_R.duty=PID_control_d(z,KUMA_Z_R.pos,50.0,1.25,0,0,5,5);
	SERVO_R=servo;
	
	//if(ABS(KUMA_THETA_R.pos-theta)<diff_theta)KUMA_THETA_R.duty=0;
	//if(ABS(KUMA_R_R.pos-r)<diff_r)KUMA_R_R.duty=0;
	//if(ABS(KUMA_Z_R.pos-z)<diff_z)KUMA_Z_R.duty=0;
			
	KUMA_THETA_R.mode=AUTO_MODE;
	KUMA_R_R.mode=AUTO_MODE;
	KUMA_Z_R.mode=AUTO_MODE;
}
void auto_toku_l_ctrl(double aim)
{
	const double stop_area=10.0;
	
	TOKU_L.duty=PID_control_d(aim,TOKU_L.pos,100.0,1.0,0,0,0.5,6);
	if(ABS(TOKU_L.pos-aim)<stop_area)TOKU_L.duty=0;
	
	TOKU_L.mode=AUTO_MODE;
}
void auto_toku_r_ctrl(double aim)
{
	const double stop_area=10.0;
	
	TOKU_R.duty=PID_control_d(aim,TOKU_R.pos,100.0,1.0,0,0,0.5,7);
	if(ABS(TOKU_R.pos-aim)<stop_area)TOKU_R.duty=0;
	
	TOKU_R.mode=AUTO_MODE;
}
void auto_uo_ctrl(double aim,double max_duty,double p_gain)
{
	const double stop_area=10.0;
	
	UO.duty=PID_control_d(aim,UO.pos,max_duty,p_gain,0,0,0.5,8);//1.0
	//if(ABS(UO.pos-aim)<stop_area)UO.duty=0;
	
	UO.mode=AUTO_MODE;
}
void auto_yoshi_ctrl(double aim)
{
	const double stop_area=15.0;
	
	YOSHI.duty=PID_control_d(aim,YOSHI.pos,100.0,1.0,0,0,0.5,9);
	//if(ABS(YOSHI.pos-aim)<stop_area)YOSHI.duty=0;
	
	YOSHI.mode=AUTO_MODE;
}
