/********************************************************/
//
//  概要
//      メイン関数
//		
//		PROJECT NAME:SAKURA_PRPJECT MASTER	
//		version		:1.0
//
//		CPU TYPE    :SH7125 
//
// 		Iφ = 50MHz		内部クロック
//  	Bφ = 25MHz		バスクロック								      
//		Pφ = 25MHz		周辺クロック								    
//		MPφ= 25MHz		MTU2 クロック 
//
//  作成者
//		D.Yamamuro @ TUTrobo
//		S.Baba	   @ TUTrobo
//		K.Ishimori @ TUTrobo
//      K.Yamada   @ TUTrobo
//      IDO        @ TUTrobo
//
/********************************************************/

/********************************************************/
//
//  変更点
//			
//	問題点
//
//	持ち物
//		/* 制御・回路班リスト */
//
//		/* 機械班 */
//
/********************************************************/
                  
#include "setup.h"		// マイコンの設定
#include	<machine.h>



/*
void show_route(void)
{
	#if 1
	char zone=mode();
	int i;
	put_s("current = {\n\r{");
	
			for(i=0;i<4;i++)printf("%.2f, ",current.leaf_field[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot1[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot2[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot3[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.pass_field[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.get_sucker[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.V_GOAL[i].d);
			put_s(" }\n\r};");
			
			
	#endif
}
*/
int main()
{	
	/********************* main文タスク選択 ここから*********************/
//	#define CUSTOMIZE_DEBUG		// 色々、その時次第
//	#define GAME				// 試合	k
//	#define ENCODER_DEBUG		// ENCODERのデバック
//	#define ENC_CTRL_DEBUG		// エンコーダによるフィードバックのデバック
//	#define MOTOR_DEBUG 		// MOTORのデバック
//	#define OMUNI_DEBUG			// オムニのデバッグ(3つのduty)
//	#define PSCON_DEBUG			// PSこん
//	#define PSCON2_DEBUG
//	#define PSCON_HALF_DEBUG	// halfのデバッグ
//	#define R1350N_DEBUG		// ジャイロのデバッグ
//	#define GMA860COND_DEBUG	// ジャイロMAP状態のデバッグ
//	#define MACOND_DEBUG		// マシンコンディションのデバッグ
//	#define OMUNI_RES			// オムニの補正値だし
//	#define POSITION_DEBUG		// 自動化のための位置出し
//	#define CURRENT_DEBUG		// 相対位置
//	#define SPEED_CHECK			// 速さチェック
//	#define SUSPENTION_DEBUG	// 足回りのデバック
//	#define TOWER_DEBUG			// タワーのデバック
//	#define	SERVO_DEBUG			// サーボのデバッaク
//	#define SHOOTER_DEBUG       // 発射のデバック
//	#define RELOAD_DEBUG		// 装填のデバッグ
//	#define ARM_POSITION		// アーム系の位置確認
//	#define AD_0_3_DEBUG		// AD変換データのデバック(チャンネル0～チャンネル3)		
//	#define AD_4_7_DEBUG		// AD変換データのデバック(チャンネル4～チャンネル7)
	#define AD_0_7_DEBUG		// AD変換データのデバック(チャンネル4～チャンネル7)
//	#define BUZZER_DEBUG		// BUZZERのデバック
//	#define LED_DEBUG 			// LEDのデバック
//	#define LED_CTRL_DEBUG 		// LEDコントロールのデバック
//	#define AIR_DEBUG			// AIRのでバック
//	#define MODE_DEBUG			// モードのデバック
//	#define LIMIT_DEBUG			// リミットのデバック
//	#define WDT_DEBUG			// ウォッチドックタイマのデバック

	/********************* main文タスク選択 ここまで*********************/
	
	/********************** main文型名宣言 ここから**********************/
	
		
	/********************** main文型名宣言 ここから**********************/	
	
	/************** main文プログラムスタートアップ ここから**************/
	
	setup();					// マイコンの初期設定
	TASK_START();         		// カウントスタート 割り込みスタート
//	SENCE_START();         		// カウントスタート 割り込みスタート

	

//	COM0_START();				// 通信開始
	
	/*************** main文タスク選択より適用設定 ここから***************/
	#ifdef	MOTOR_DEBUG 		// MOTORのデバックのとき		
			motor_pwm_init();	// MOTOR_PWMの初期化
	#endif
			
	#ifdef	SUSPENTION_DEBUG	// 足回りのデバックのとき		
			motor_pwm_init();	// MOTOR_PWMの初期化
	#endif
	
	#ifdef	SERVO_DEBUG			// サーボのデバックのとき
		//	servo_pwm_init();	// SORVO_PWMの初期化
	#endif
	/*************** main文タスク選択より適用設定 ここまで***************/
	
	/*************** main文タスク選択より例外設定 ここから***************/	
	#ifdef	GAME 				// 試合のとき
	#define	EXCEPTION			// 例外
	#endif
			
	#ifdef	ENCODER_DEBUG 		// ENCODERのデバックのとき
	#define	EXCEPTION			// 例外
	#endif
			
	#ifdef	WDT_DEBUG			// ウォッチドックタ;イマのとき
	#define	EXCEPTION			// 例外
	#endif
	
//	#ifdef	comu0_slave_debug	// 石森通信のスレーブデバック
//	#define	EXCEPTION			// 例外
//	#endif
	
#ifndef EXCEPTION			// 例外でないとき
			wdt_stop();			// WDTを禁止
//			TASK_END();        	// タイマ割り込み禁止
//			SENCE_END();        // カウントスタート 割り込みスタート
#endif
	
	/************** main文タスク選択より例外設定 ここから****************/
	
	/************** main文プログラムスタートアップ ここまで**************/
//	comm_action('I',1);
	
//	fcu_eraze_db(TOP_ADDR_DB01);
	while(1)
	{
		debug();
	}
			
	return 0;
}		
void debug(){


#ifdef	CUSTOMIZE_DEBUG
{

	printf("%.1f\t,%.1f\t,%.1f\t,%.1f\t,%.1f\t,%.1f\t\r\n",KUMA_THETA_L.duty,KUMA_R_L.duty,KUMA_Z_L.duty,KUMA_THETA_R.duty,KUMA_R_R.duty,KUMA_Z_R.duty);
//	printf("%.1f\t,%.1f\t,%.1f\t,%.1f\t\n",DEBUG[0],DEBUG[1],DEBUG[2],DEBUG[3]);	
	//printf("%d\t,%.1f\t,%d\t,%.1f\r\n",AD_DATA[0],KUMA_THETA_L.pos,AD_DATA[3],KUMA_THETA_R.pos);
<<<<<<< HEAD
	//printf("%d,%d,%d,%d\n",SERVO_L,(int)DEBUG[0],SERVO_R,(int)DEBUG[1]);
=======
	printf("%d,%d,%.1f\n",(int)DEBUG[0],(int)DEBUG[1],YOSHI.duty);
>>>>>>> parent of 0ea2d61... 蟾ｦ荳九し繝ｼ繝懷柑縺九↑縺�縺ｮ蟇ｾ蜃ｦ縺励◆
}
#endif

#ifdef CURRENT_DEBUG
	int i;
	put_s("current = {{ \n\r");
	
			for(i=0;i<4;i++)printf("%.2f, ",current.leaf_field[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot1[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot2[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.spot3[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.pass_field[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.get_sucker[i].d);
			put_s(" },\n\r{ ");
			for(i=0;i<4;i++)printf("%.2f, ",current.V_GOAL[i].d);
			put_s(" }};\n\r");

#endif

#ifdef OMUNI_RES
{		
		printf("%d\t\n", macond.renc.l);		// xのエンコーダカウント
		printf("%d\t\n", macond.renc.r);		// yのエンコーダカウント
		printf("%f\t\n", macond.t_theta);	// マシン角度
		printf("%f\t\n" , macond.pos.x);	// x座標
		printf("%f\t\n" , macond.pos.y);	// x座標
		

		printf("\n");
}
#endif

		//////////////////////////////////////////////////////////////////	
#ifdef	ENCODER_DEBUG
		/****************** エンコーダデータのデバック ******************/

		//	show_macond();
		printf("%d, %d, %d, %d\n",MTU1.TCNT,MTU2.TCNT,MTU7.TCNT,MTU8.TCNT);	
/*
		printf("%4d,%4d,%4d,%4d,%4d\n"	,com0_tx[0][0]	
										,com0_tx[0][1]	
										,com0_tx[0][2]	
										,com0_tx[0][3]
										,com0_tx[0][4]	);	
*/		
		/****************** エンコーダデータのデバック ******************/
#endif	// encoder_debug 
		//////////////////////////////////////////////////////////////////
#ifdef	ENC_CTRL_DEBUG
{
	int res=0;
		/*************** エンコーダコントロールのデバック ***************/
//					 distEnd,	 ch,		num,	duty
//		enc_ctrl(recv0[0][1],     0,		  0,   &duty);
		
/*		for(loop = 0;loop <= 1000;loop = loop+200)
		{
//						 distEnd,	 ch,		num,	duty
			enc_ctrl(		loop,     0,		  0,   &duty);
			tower_motor_l(duty);
			tower_motor_r(duty);			
		}
*/		
		do
		{
//								distEnd,	 ch,		num,	duty
			res = 	enc_ctrl(	   loop,      0,		  0,   &duty);
			
			tower_motor_l(duty);
			tower_motor_r(duty);
			
			printf("%5.1f\t",duty);
//			printf("pwm_l = %4d\t",MTU24.TGRC);
//			printf("pwm_r = %4d\n",MTU24.TGRA);
		}
		while(res == 0);
		
//		tower_motor_l(duty);
//		tower_motor_r(duty);
		
		if(loop < -1000)	loop = 0;
		else				loop = loop-200;
					
//		for(delay_count1 = 0; delay_count1 < 65536; delay_count1 ++)	// delaytime
//		for(delay_count2 = 0; delay_count2 <   100; delay_count2 ++)
		for(delay_count1 = 0; delay_count1 <   100; delay_count1 ++)	// delaytime
		{
			printf("%5.1f\t",duty);
			printf("pwm_l = %4d\t",MTU24.TGRC);
			printf("pwm_r = %4d\n",MTU24.TGRA);
		}
		/*************** エンコーダコントロールのデバック ***************/
}
#endif//enc_ctrl_debug
		//////////////////////////////////////////////////////////////////		
#ifdef	MOTOR_DEBUG
{
	double pwm_loop;			// PWMのデバックのため for文ループ用
	
		/********************** モーターのデバック **********************/
		
		for(pwm_loop = -100.0; pwm_loop <=  100.0; pwm_loop = pwm_loop + 0.1)
		{
			pwm = anti_lock_pwm(pwm_loop);
			MTU0.TGRA = pwm;
			MTU0.TGRB = pwm;
			MTU0.TGRC = pwm;
			MTU0.TGRD = pwm;
			MTU4.TGRA = pwm;
			MTU4.TGRC = pwm;
			
			printf("pwm = %4d\t,R = %4d\t,C = %4d\n",pwm,MTU4.TGRA,MTU4.TGRB);
		}
		for(pwm_loop =  100.0; pwm_loop >= -100.0; pwm_loop = pwm_loop - 0.1)
		{
			pwm = anti_lock_pwm(pwm_loop);

			MTU0.TGRA = pwm;
			MTU0.TGRB = pwm;
			MTU0.TGRC = pwm;
			MTU0.TGRD = pwm;
			MTU4.TGRA = pwm;
			MTU4.TGRC = pwm;
				
			printf("pwm = %4d\t,R = %4d\t,C = %4d\n",pwm,MTU4.TGRA,MTU4.TGRB);
		}

/*		pwm = anti_lock_pwm(50.0);
		
		MTU20.TGRA = pwm;
		MTU20.TGRB = pwm;
		MTU20.TGRC = pwm;
		MTU23.TGRA = pwm;
		MTU23.TGRC = pwm;
		MTU24.TGRA = pwm;
		MTU24.TGRC = pwm;
*/		
}	
		/********************** モーターのデバック **********************/
#endif

#ifdef SPEED_CHECK
{
	/********************** 速度のデバック **********************/
	printf("%.2f,",macond.pos.x);
	printf("%.3f,",max_speed);
	printf("%.2f,",(double)speed_timer/100.0);
	printf("%.3f\n",macond.v);
	/********************* 速度のデバック **********************/
}
#endif

#ifdef OMUNI_DEBUG
{
	/********************** オムニのデバック **********************/
	printf("o=%.3f,l=%.3f,r=%.3f\t",motor_debug[0],motor_debug[1],motor_debug[2]);
	/********************* オムニのデバック **********************/
}
#endif

#ifdef R1350N_DEBUG
{
	/********************** ジャイロのデバック **********************/
		printf("m_angle=%.2f\t",(double)m_angle/100.0);
		printf("x=%d\t",accX);
		printf("y=%d\t",accY);
		printf("z=%d\n",accZ);
	/********************* ジャイロのデバック **********************/
}
#endif

#ifdef ARM_POSITION
{
	/********************** アームの位置表示 **********************/
		printf("fish_ad=%d\t",ad_data[2]);
		printf("fish_pos=%.2f\t",fishing_rod_position);
		printf("l_arm_ad=%d\t",ad_data[1]);
		printf("l_arm_pos=%.2f\n",l_arm_position);
	/********************* アームの位置表示 **********************/
}
#endif

#ifdef GMACND_DEBUG
{
	/********************** gmacondのデバック **********************/
		printf("ax=%.2f\t",gcond.ax);
		printf("ay=%.2f\t",gcond.ay);
		printf("m_ax=%.2f\t",gcond.m_ax);
		printf("m_ay=%.2f\t",gcond.m_ay);
		printf("dir=%.2f\t",gcond.a_rad*180.0/PI);
		printf("angle=%.2f\n",(double)m_angle/100.0);

	/********************* gmacondのデバック **********************/
}
#endif

#ifdef MACOND_DEBUG
{
	
	/********************** マシン状態のデバック **********************/
	//	printf("t_theta=%.2f\t",macond.t_theta);
	//	printf("v=%.2f\tv_rad=%.2f\t",macond.v,macond.v_rad);
	//	printf("x=%.2f\ty=%.2f\n",macond.pos.x,macond.pos.y);
	printf("L:%.1f\t,%.1f\t,%.1f\t,%d\r\n",KUMA_THETA_L.pos,KUMA_R_L.pos,KUMA_Z_L.pos,SERVO_L);
	printf("R:%.1f\t,%.1f\t,%.1f\t,%d\r\n",KUMA_THETA_R.pos,KUMA_R_R.pos,KUMA_Z_R.pos,SERVO_R);
	printf("UO=%.1f\t,YOSHI=%.1f\r\n",UO.pos,YOSHI.pos);
	printf("LX=%.1f\t,LY=%.1f\t,RX=%.1f\t,RY=%.1f\r\n",KUMA_POS_LX,KUMA_POS_LY,KUMA_POS_RX,KUMA_POS_RY);
	
	/********************* マシン状態のデバック **********************/

}
#endif

#ifdef POSITION_DEBUG
{
	/********************** gmacondのデバック **********************/
		printf("t_theta=%.2f\t",macond.t_theta);
		printf("x=%.2f\t",macond.pos.x);
		printf("y=%.2f\t",macond.pos.y);
		printf("rod=%.2f\n",fishing_rod_position);

	/********************* gmacondのデバック **********************/
}
#endif

#ifdef PSCON_HALF_DEBUG
{
	/********************** halfのデバッグ **********************/
		printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
		PS_BTN(RIGHT)	,PS_BTN(LEFT)	,PS_BTN(UP)		,PS_BTN(DOWN),
		PS_BTN(START)	,PS_BTN(R3)		,PS_BTN(L3)		,PS_BTN(SELECT),
		PS_BTN(SHIKAKU)	,PS_BTN(BATSU)	,PS_BTN(MARU)	,PS_BTN(SANKAKU),
		PS_BTN(R1)		,PS_BTN(L1)		,PS_BTN(R2)		,PS_BTN(L2)
		);
	/********************* halfのデバック **********************/
}
#endif
		//////////////////////////////////////////////////////////////////	
#ifdef	SUSPENSION_DEBUG
{
		/*********************** 足回りのデバック ***********************/
/*		
		for(pwm_loop = -100.0; pwm_loop <=  100.0; pwm_loop = pwm_loop + 0.1)
		{
			pwm_set_ctrl(pwm_loop, pwm_loop);
			
			printf("duty = %5.1f\n",pwm_loop);
		}
		for(pwm_loop =  100.0; pwm_loop >= -100.0; pwm_loop = pwm_loop - 0.1)
		{
			pwm_set_ctrl(pwm_loop, pwm_loop);
			
			printf("duty = %5.1f\n",pwm_loop);
		}
*/

//		pwm_set_ctrl(    0.0,   50.0);
		pwm_set_ctrl(   50.0,    0.0);	
//		pwm_set_ctrl(   50.0,   50.0);	
//		pwm_set_ctrl(  100.0,  100.0);
//		pwm_set_ctrl( -100.0, -100.0);

/*		ad_load_4_7(ad_data);
		
		printf("%4d \t pwn = %5.1f\n",ad_data[6-4],(double)(ad_data[6-4])*100.0/1023.0);
		
		if(ad_data[6-4] >= 511)
		{
			pwm_set_ctrl((double)(ad_data[6-4]-511)*100.0/512,(double)(ad_data[6-4]-511)*100.0/512);
		}
		else
		{
			pwm_set_ctrl(-(double)(511-ad_data[6-4])*100.0/512,-(double)(511-ad_data[6-4])*100.0/512);
		}
*/		
		/*********************** 足回りのデバック ***********************/
}
#endif
		//////////////////////////////////////////////////////////////////			
#ifdef	TOWER_DEBUG
{
		/*********************** タワーのデバック ***********************/		
/*		for(pwm_loop = -100.0; pwm_loop <=  100.0; pwm_loop = pwm_loop + 1.0)
		{
			tower_motor_l(pwm_loop);
			tower_motor_r(pwm_loop);
			printf("duty = %5.1f\n",pwm_loop);
		}
		for(pwm_loop =  100.0; pwm_loop >= -100.0; pwm_loop = pwm_loop - 1.0)
		{
			tower_motor_l(pwm_loop);
			tower_motor_r(pwm_loop);
			printf("duty = %5.1f\n",pwm_loop);
		}
*/
		tower_motor_l(50.0);
		tower_motor_r(50.0);
		/*********************** タワーのデバック ***********************/
}
#endif
		//////////////////////////////////////////////////////////////////	
#ifdef	SERVO_DEBUG
{
	int pwm;
		/********************** サーボのデバック **********************/
		TASK_END();         		// カウントスタート 割り込みスタート

		ad_load_0_3(ad_data);
		pwm = (ad_data[2])*SERVO_CYCLE/1023;
		printf("%4d \t pwn = %d\n",ad_data[2],pwm);
		SERVO_B_PWM = pwm;
		SERVO_T_PWM = pwm;						
		/********************** モーターのデバック **********************/
}
#endif
		//////////////////////////////////////////////////////////////////
#ifdef	AD_0_3_DEBUG
{
		int loop;
		int ad_data[4];
		/******* AD変換データのデバック(チャンネル0～チャンネル3) *******/
		
		ad_load_0_3(ad_data);
		
		for(loop = 0;loop <= 3;loop++)
			printf("ad_data[%d] = %4d\t",loop,ad_data[loop]);
		put_s("\n\r");
		
		/******* AD変換データのデバック(チャンネル0～チャンネル3) *******/
}
#endif	
		//////////////////////////////////////////////////////////////////
#ifdef	AD_4_7_DEBUG
{
		int loop;
		int ad_data[4];
		/******* AD変換データのデバック(チャンネル4～チャンネル7) *******/
		
		
		for(loop = 4;loop <= 7;loop++)
			printf("ad_data[%d] = %d\t",loop,ad_data[loop-4]);
		put_s("\n\r");
		
		/******* AD変換データのデバック(チャンネル4～チャンネル7) *******/
}
#endif
		//////////////////////////////////////////////////////////////////
#ifdef	AD_0_7_DEBUG
{
		int loop;
		int ad_data[8];
		/******* AD変換データのデバック(チャンネル0～チャンネル3) *******/
		
		ad_load_0_7(ad_data);
		
		for(loop = 0;loop <= 7;loop++)
			printf("[%d]:%4d\t",loop,ad_data[loop]);
		put_s("\n\r");
		
		/******* AD変換データのデバック(チャンネル0～チャンネル3) *******/
}

#endif

#ifdef SHOOTER_DEBUG
{
	char for_n;
	
	if(tera==1){
		if(print_g){
			for(for_n=0; for_n<20; for_n++){
				printf("%d, %d, %.1f, %.1f, %d\n",for_n,(int)print_data[3][for_n],print_data[0][for_n],print_data[1][for_n],(int)print_data[2][for_n]);
			}
			printf("\n");
			print_g=0;
		}
	}else{
		if(print_data[DEBUG_NUM][0] != -1.0){
			directions(&com[1],(int)(print_data[DEBUG_NUM][0]),6);
			transmission(&com[1]);
			//printf("%.1f",print_data[DEBUG_NUM][0]);
			print_data[DEBUG_NUM][0] = -1.0;
		}
	}
		//printf("%d, %d\n",ENC1_TCNT,ENC2_TCNT);
		/********************** 発射のデバック **********************/
	//printf("TGT:%.1f, C0:%.1f, C1:%.1f, C2:%.1f, D0:%.1f, D1:%.1f, D2:%.1f, E2:%d \n",psta[0].target[0],psta[0].current[0],psta[1].current[0],psta[2].current[0],psta[0].duty,psta[1].duty,psta[2].duty,psta[2].end);
}		
		/********************** 発射のデバック **********************/
#endif

#ifdef RELOAD_DEBUG
printf("TGT:%.1f, C0:%.1f, C1:%.1f, C2:%.1f, D0:%.1f, D1:%.1f, D2:%.1f, E2:%d \n",psta[0].target[0],psta[0].current[0],psta[1].current[0],psta[2].current[0],psta[0].duty,psta[1].duty,psta[2].duty,psta[2].end);




#endif
		//////////////////////////////////////////////////////////////////
#ifdef	AIR_DEBUG
{
		#if 0
			AIR_RIGHT_HAND 		=0;
			AIR_LEFT_HAND 		=0;	
			AIR_RIGHT_HAND_WIDE	=0;
			AIR_LEFT_TOWER 		=0;
			AIR_RIGHT_TOWER_UP   =   0;
			POWER_OUT			=0;
			AIR_LEFT_HAND_WIDE	=0;
			BUZZER_OUT			=0;
		#endif

		/****************** AIRコントロールのデバック *******************/
		
		leaf_collect_hand(OPEN);
		leaf_esta_hand   (OPEN);
		
		for(delay_count1 = 0; delay_count1 < 65536; delay_count1 ++)	// delaytime
		for(delay_count2 = 0; delay_count2 <    30; delay_count2 ++);
		
		leaf_collect_hand(CLOSE);
		leaf_esta_hand   (CLOSE);
		
		for(delay_count1 = 0; delay_count1 < 65536; delay_count1 ++)	// delaytime
		for(delay_count2 = 0; delay_count2 <    30; delay_count2 ++);
		
		/****************** AIRコントロールのデバック *******************/
}
#endif		
		//////////////////////////////////////////////////////////////////
#ifdef	MODE_DEBUG
{
		/*********************** モードのデバック ***********************/
		send_buff = mode();
		put_c(send_buff);
		put_s("\n\r");
		/*********************** モードのデバック ***********************/
}
#endif	
		//////////////////////////////////////////////////////////////////
	
		//////////////////////////////////////////////////////////////////
#ifdef	LIMIT_DEBUG
{
		/********************** リミットのデバック **********************/
		
		if(LIMIT_L==0)printf("LIMIT_L\t");
		if(LIMIT_R==0)printf("LIMIT_R\t");
		if(LIMIT_U==0)printf("LIMIT_U\t");
		if(TOGGLE==0)printf("TOGGLE\t");
		printf("\n");

		/********************** リミットのデバック **********************/
}
#endif			
#ifdef	WDT_DEBUG	
{
		/**************** ウォッチドッグタイマのデバック ****************/
		int wdt_count;				// ウォッチドッグタイマのデバックのため
		wdt_count = WDT.READ.WTCNT;
		printf("wdt_count = %d\n",wdt_count);	
		
		/**************** ウォッチドッグタイマのデバック ****************/
}
#endif

#ifdef PSCON_DEBUG//PSこん
{		
	pscon_debug();
}
#endif	
#ifdef PSCON2_DEBUG//PSこん
{		
	pscon2_debug();
}
#endif	


}


