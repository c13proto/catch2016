/********************************************************/
//
//  概要
//      オムニ関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/
#if 0
#include "setup.h"
double motor_debug[4];
double custom_debug[5];
/********************************************************/
//  名前      
//		pwm_set_omni_ctrl
//  概要
// 		IO関数
//  機能説明
//		モータ関数(オムニ仕様)　
//  パラメタ説明
//		duty_l1,duty_l2	Lデュティー
//		duty_r1,duty_r2	Rデュティー	
//  戻り値
//		なし
//  作成者
//		S.Baba @ TUTrobo
//
/********************************************************/
void pwm_set_omni_ctrl(OMNI_DUTY omni)	
{
	if(ABS(omni.o)>100.0 || ABS(omni.l)>100.0 || ABS(omni.r)>100.0)omni.o=omni.l=omni.r=0.0;//変なduty来たら全部止める		
	
	motor_o(omni.o);
	motor_l(omni.l);
	motor_r(omni.r);
	
	
//	printf("%.2f\t%.2f\t%.2f\t%.2f\n",omni.l1,omni.l2,omni.r2,omni.r1);
	
/*
    l1    r1
	-------
	|	  |
	| ↑  |
	-------
	l2    r2
*/
}

/********************************************************/
//	名前
//		omni_moters_duty3
//	概要
//		オムニ3輪制御関連
//	機能説明
//	    3つのモーターに出力するトルク(duty)の計算
//    	軸方向不動型
//
//	パラメータ説明
//		現在のマシン角度					theta(radian)
//		マシン中心の移動に使うトルクの割合	v_ratio(0~100)
//		目標速度							duty(0~100)
//		目標方向							theta_direction(radian)
//		目標回転速度						kaiten(-100~100)
//
//	戻り値	
//		各モータ出力duty(-100~100)
// 注意点
//		回転するために与えられるトルクの最大値は (100-v_ratio)/100
//		よって、v_ratioを100で動かすとマシンは回転できない
//
//		常にマシン初期状態での正面をx軸、左側をy軸ととっている。
//		→マシン角度によらず軸は一定
// 作成者
//		やまむろ @ TUTrobo	
/********************************************************/
OMNI_DUTY omni_moters_duty3(double theta,double v_ratio,double duty,double theta_direction,double kaiten)
{

	double x,y;

	const double Kp_direction = 0.4, Ki_direction = 0.04, Kd_direction = -0.0,K=15000.0,//(1.0,0.01,0.3おもりなし),(1.2,0.04,0.4ビデオ１次審査)
					Kp_kaiten=1.0, Ki_kaiten=0.035,Kd_kaiten=0.0,K_kaiten=6000.0;//回転のゲイン設定(マシン重量によらず一定角速度での回転を目指す)
					
	static double P_direction=0.0,I_direction=0.0,D_direction=0.0,
						P_kaiten=0.0,I_kaiten=0.0,D_kaiten=0.0,
					old_P_direction=0.0,old_P_kaiten=0.0,old_theta=0.0;
					
	double PID_direction=0.0,PID_kaiten=0.0;
	double senkai_seibun;//３つのモータに出力する旋回性分duty
	
	static double old_kaiten,old_duty;//加速度制限のため
	static int back_count_R,back_count_L;
		
	OMNI_DUTY omni;

//----------------フィードバック	
	kaiten=diff_limit(old_kaiten,kaiten,3.5);//旋回の変化量制限
	speed_control(&duty,&theta_direction,&kaiten);//ブレーキと速度制御
	res_direction(&theta_direction,0.7,0.0,0.0);//方向補正フィードバック
//---------------------------
	x=mycos(theta_direction);
	y=mysin(theta_direction);
	//Kで旋回フィードバックの強さを指定			//マシンが理想状態の時　K_kaiten(theta-old_theta)=kaiten　が成り立つようにするのが理想
	P_direction=K*(old_theta-theta);			P_kaiten=kaiten-K_kaiten*(theta-old_theta);//回転のフィードバックは、目標値(kaiten)にゲインを足している
	I_direction+=P_direction;					I_kaiten+=P_kaiten;
	D_direction=P_direction-old_P_direction;	D_kaiten=P_kaiten-old_P_kaiten;
	
	custom_debug[0]=P_kaiten;//デバッグのため
//	custom_debug[1]=P_kaiten;
//printf("P_direction=%.3f\n",P_direction);
	
	if(old_kaiten!=kaiten){I_direction=0;D_direction=0;I_kaiten=0.0;D_kaiten=0.0;}//目標値が変わったのでdirectionゲインのリセット

	if(kaiten==0.0)//旋回を手動で指定していないとき、外乱で旋回しないようにフィードバックする
	{
		PID_direction=(Kp_direction*P_direction+Ki_direction*I_direction+Kd_direction*D_direction);//フィードバックの正負判定
		PID_kaiten=0.0;
	}
	else//旋回を手動で指定している時、等角速度で旋回するようにする
	{
		PID_direction=0.0;//-kaiten;//回転の正負判定
		PID_kaiten=(kaiten+Kp_kaiten*P_kaiten+Ki_kaiten*I_kaiten+Kd_kaiten*D_kaiten);//フィードバックの正負判定
	}
	
	if(PID_direction>100)PID_direction=100;		if(PID_kaiten>100)PID_kaiten=100;
	if(PID_direction<-100)PID_direction=-100;	if(PID_kaiten<-100)PID_kaiten=-100;
	
	
	
	if(HALF_1==251){I_direction=0;D_direction=0;PID_direction=0;I_kaiten=0.0,D_kaiten=0.0;}//右スティックボタンでゲインリセット
	
//	printf("kaiten=%.2f\tPID=%.2f\t\n",kaiten,(PID_direction+PID_kaiten));
	
	senkai_seibun=(PID_direction+PID_kaiten)*(100.000-v_ratio)/100.000;//旋回成分を格納

	omni.o = (v_ratio*duty/100.000) * (x*mycos(theta+1.0/2.0*PI) + y*mysin(theta+1.0/2.0*PI));//直進成分のみをとりあえず格納
	omni.l = (v_ratio*duty/100.000) * (x*mycos(theta+7.0/6.0*PI) + y*mysin(theta+7.0/6.0*PI));	
	omni.r = (v_ratio*duty/100.000) * (x*mycos(theta+11.0/6.0*PI) + y*mysin(theta+11.0/6.0*PI));

	
	if(senkai_stop_flag==1)senkai_seibun=0.0;//旋回フィードバックを切る
	if(duty!=0.0)convert_omni_duty(&omni,duty,senkai_seibun);//duty比を維持したまま目標dutyへ最大限活かせるように変換する（OMNI_DUTY omni達を書き換える）
	else//進行させたくないときは旋回成分だけ代入
	{
		omni.o = senkai_seibun;
		omni.l = senkai_seibun;
		omni.r = senkai_seibun;	
	}

//custom_debug[0]=senkai_seibun;
/*	
//--------------------ちょっとバックする(リーフを上げる際60ms下がる)------------	
	if(hand_R_status==air_UP && hand_R_position!=air_UP)
	{
		if(back_count_R<500)back_count_R++;
		if(back_count_R<10)omni.r=-40.0;//ちょっと右タイヤを後ろに動かす
	}else back_count_R=0;

	if(hand_L_status==air_UP && hand_L_position!=air_UP)
	{
		if(back_count_L<500)back_count_L++;
		if(back_count_L<10)omni.l= 40.0;//ちょっと左タイヤを後ろに動かす
	}else back_count_L=0;
//-----------------------------------------------------------------------------
*/

//	printf("%.1f\t%.1f\t%.1f\t%.1f\t\n",omni.l1,omni.l2,omni.r1,omni.r2);
		

//	old_duty=duty;			
	old_kaiten=kaiten;
						
	old_P_direction=P_direction;	old_P_kaiten=P_kaiten;
	old_theta=theta;
	
//	printf("%.1f\t%.1f\n",kaiten,old_kaiten);
	
	return omni;

}


/********************************************************/
//  名前      
//		reset
//  概要
// 		IO関数
//  機能説明
//		リセット関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		S.Baba @ TUTrobo
//
/********************************************************/
void reset(void)
{
	pwm_set_omni(0.0,0.0,0.0,0.0);
	
	macond.renc.l = 0.0; macond.renc.r = 0.0;	macond.renc.o = 0.0;
	macond.enc.l = 0.0;	macond.enc.r = 0.0;		macond.enc.o = 0.0;
	macond.v_enc.l = 0.0; macond.v_enc.r = 0.0;	macond.v_enc.o = 0.0;

	macond.theta     = 0.0;
	macond.t_theta   = 0.0;
	macond.v		 = 0.0; 
	macond.pos.x = 0.0;	macond.pos.y = 0.0;
	
}

/********************************************************/
//  名前      
//		convert_omni_duty
//  概要
// 		IO関数
//  機能説明
//		dutyの最適化
//  パラメタ説明
//		max_duty		// 出力の最大値
//  戻り値
//		なし
//  作成者
//		Yamamuro
//
/********************************************************/
void convert_omni_duty(OMNI_DUTY *omni,double max_duty,double senkai_duty)
{
	double abs_max;//一番高いdutyの絶対値
	double max_direction=100.0-ABS(senkai_duty);//進行方向成分にあげられる最大のdutyを格納
	double max_or_min;//絶対値の一番大きい奴
	double max,min;//最大値と最小値


	if(max_duty*max_direction/100.0 < max_direction)max_direction*=max_duty/100.0;//進行方向成分にかけていい最大値
	
	max_or_min=omni->o;//絶対値が大きいものを選ぶ
	if(ABS(max_or_min)<ABS(omni->l))max_or_min=omni->l;
	if(ABS(max_or_min)<ABS(omni->r))max_or_min=omni->r;
	
	min=omni->o;//小さものを選ぶ
	if(min>ABS(omni->l))min=omni->l;
	if(min>ABS(omni->r))min=omni->r;
	
	max=omni->o;//大きいものを選ぶ
	if(max<ABS(omni->l))min=omni->l;
	if(max<ABS(omni->r))min=omni->r;	
	

	if(senkai_duty>0.0)//旋回成分が正の時
	{
		if(max_or_min>0.0)//絶対値の最大が正の時
		{
			omni->o*=max_direction/ABS(max_or_min);
			omni->l*=max_direction/ABS(max_or_min);
			omni->r*=max_direction/ABS(max_or_min);
		}
		else//絶対値の大きいやつが負だった時
		{
			omni->o*=(max_direction-senkai_duty)/ABS(max_or_min);//とりあえずそいつが目標dutyになるようにする(回転を足して-100.0)まで
			omni->l*=(max_direction-senkai_duty)/ABS(max_or_min);
			omni->r*=(max_direction-senkai_duty)/ABS(max_or_min);
			
			if((omni->o+senkai_duty)>100.0 || (omni->l+senkai_duty)>100.0 || (omni->r+senkai_duty)>100.0)//旋回成分を足した後どれかが100を超えていたら正の方向をあわせる
			{
				omni->o*=max_direction/max;//正方向で最大のものが旋回を足して100を超えないようにする
				omni->l*=max_direction/max;
				omni->r*=max_direction/max;
			}
		}
	}
	else//旋回が負の時
	{
		if(max_or_min>0.0)//絶対値の大きい奴が正だった時
		{
			omni->o*=(max_direction+senkai_duty)/ABS(max_or_min);//とりあえずそいつが目標dutyになるようにする(-100.0)まで
			omni->l*=(max_direction+senkai_duty)/ABS(max_or_min);
			omni->r*=(max_direction+senkai_duty)/ABS(max_or_min);
			
			if((omni->o+senkai_duty) < -100.0 || (omni->l+senkai_duty) < -100.0 || (omni->r+senkai_duty) < -100.0)//どれかが-100を下回っていたら正の方向をあわせる
			{
				omni->o*=max_direction/(-min);//-100を下回らないようにする
				omni->l*=max_direction/(-min);
				omni->r*=max_direction/(-min);			
			}
			
		}
		else
		{
			omni->o*=max_direction/ABS(max_or_min);
			omni->l*=max_direction/ABS(max_or_min);
			omni->r*=max_direction/ABS(max_or_min);
		}
	}
	
	omni->o+=senkai_duty;
	omni->l+=senkai_duty;
	omni->r+=senkai_duty;

	if(omni->o>100.0)omni->o=100.0;
	if(omni->o<-100.0)omni->o=-100.0;
	if(omni->l>100.0)omni->l=100.0;
	if(omni->l<-100.0)omni->l=-100.0;	
	if(omni->r>100.0)omni->r=100.0;
	if(omni->r<-100.0)omni->r=-100.0;

}
/********************************************************/
//  名前      
//		diff_limit
//  概要
// 		IO関数
//  機能説明
//		dutyの最適化
//  パラメタ説明
//		old:	過去の値
//		new:	現在の値
//		limit:	許容する変化量(絶対値)
//  戻り値
//		変化量を抑えた値(double型)
//  作成者
//		Yamamuro
//
/********************************************************/
double diff_limit(double old,double new,double limit)
{
	double after;
	double diff;
	
	diff=ABS(old-new);
	
	if(diff>limit)//変化量の絶対値がリミットより多い時
	{
			if(old<new)	after=old+limit;//増やしたい時
			if(old>=new)after=old-limit;//減らしたい時

	}
	else after=new;
	
//	printf("%.1f,%.1f,%.1f\n",old,new,after);
	
	return after;

}

/********************************************************/
//  名前      
//		inertia_stop
//  概要
// 		
//  機能説明
//		慣性を止める。（動いた方向の逆にdutyをかけるだけ）
//
//  パラメタ説明
//		duty:ブレーキをかけるduty
//		theta_direction:ブレーキをかける方向
//		K:ブレーキの強さ（MAXの時）
//
//  戻り値
//		なし
//  作成者
//		Yamamuro
//
/********************************************************/
void speed_control(double *duty,double *theta_direction,double *kaiten)
{
	double pre_duty,K_stopper=0.15;
	static double old_duty,old_theta_direction;
//	if(old_theta_direction!=*theta_direction)*duty=0;
	
//	printf("%.2f\t",*kaiten);
	
	if(direction_duty==0.0)//(*duty==0 && *kaiten==0)//ブレーキをかけたい時の制御
	{
		pre_duty=macond.v*K_stopper;
		if(pre_duty>100.0)pre_duty=100.0;
	
		*theta_direction=macond.v_rad-choose_degree*PI/18000.0+PI;//速度方向の逆をdutyのかける方向に指定
		while(*theta_direction<0.0)*theta_direction+=2.0*PI;//theta_directionを0~2Piにする
		while(*theta_direction>2.0*PI)*theta_direction-=2.0*PI;
	
		*duty=diff_limit(old_duty,pre_duty,1.2);//ちょっとづつブレーキをかけていく。ここの引数を変えることで急停止になったりする
	
	}
	else
	{		
		//dutyが100のときにv=2300[mm/s]として2つ目の引数を決めている
		pre_duty=*duty+(double)PID_control(*duty,macond.v*100.0/2300.0,100,1.5,0.015,0.1,3);
//		if(pre_duty>old_duty && macond.v<500.0)pre_duty=diff_limit(old_duty,pre_duty,2.0);//加速の場合加速度制限。（スタート時のスリップ防止の為）
		
		if(pre_duty<0.0)pre_duty=0.0;
		else if(pre_duty>100.0)pre_duty=100.0;
		*duty=pre_duty;
	}
	

	
	old_theta_direction=*theta_direction;
	old_duty=*duty;
	
//	printf("%.2f\n",*kaiten);
	
}

/********************************************************/
//  名前      
//		res_direction
//  概要
// 		
//  機能説明
//		方向補正
//  パラメタ説明
//		mokuhyou_direction:目標方向(絶対座標の方向(choose_degree)が変わっている時がちょっと複雑)
//		Kp,Ki,Kd:ゲイン(PID制御として扱っていいのか不明。方向の補正の仕方として成り立つかしら)
//
//  戻り値
//		res_direction:補正後の方向。 (double型の値[rad])
//  作成者
//		Yamamuro
//
/********************************************************/
void res_direction(double *mokuhyou_direction,double Kp,double Ki,double Kd)
{
	double res_direction;
	static double old_mokuhyou_direction;
	static double res_P,res_I,res_D,old_P;
	double offset=choose_degree*PI/18000.0;
	double final_mokuhyou;//最終的に向いてほしい目標方向（絶対角度[rad]
	
	while(offset<0)offset+=2.0*PI;//オフセットを0~2PIにする
	while(offset>2.0*PI)offset-=2.0*PI;
	
	final_mokuhyou = *mokuhyou_direction + offset;
	
	
	if(final_mokuhyou>2.0*PI)final_mokuhyou-=2.0*PI;//final_mokuhyouを0~2PIにする
	
	if(old_mokuhyou_direction!= *mokuhyou_direction)//目標方向が変わったのでゲインのリセット
	{
		res_P=0.0;res_I=0.0;res_D=0.0,old_P=0.0;
	}
	

	if(macond.v==0.0)res_direction = *mokuhyou_direction;//速度が少なかったら目標方向の補正はしない
	else
	{
		if(final_mokuhyou>(3.0/2.0*PI) && macond.v_rad< PI/2.0)//目標値が右前にあり、現在方向が左前にあるとき
		{
			res_P=final_mokuhyou-(macond.v_rad+2.0*PI);
		}
		else if(final_mokuhyou<(PI/2.0)  &&  macond.v_rad>(3.0/2.0*PI))//目標が左前にあり、現在方向が右前にあるとき
		{
			res_P=final_mokuhyou-(macond.v_rad-2.0*PI);
		}
		else res_P=(final_mokuhyou-macond.v_rad);//目標方向と現在方向の差を出す。現在方向のほうが大きければ負、逆なら正の値を出す
		
		res_I+=res_P;
		res_D=res_P-old_P;
		
		if(ABS(res_P)>(PI/2.0))res_direction=*mokuhyou_direction;//目標方向と進んだ方向が大きかったら補正しない
		else res_direction=*mokuhyou_direction+Kp*res_P+Ki*res_I+Kd*res_D;
		
	
		
	}	
	
	old_mokuhyou_direction = *mokuhyou_direction;
	old_P=res_P;
	
	*mokuhyou_direction = res_direction;//あえて目標値は変更前のを使用（i成分のため）

}
#endif