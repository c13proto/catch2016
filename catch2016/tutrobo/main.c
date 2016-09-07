/********************************************************/
//
//  �T�v
//      ���C���֐�
//		
//		PROJECT NAME:SAKURA_PRPJECT MASTER	
//		version		:1.0
//
//		CPU TYPE    :SH7125 
//
// 		I�� = 50MHz		�����N���b�N
//  	B�� = 25MHz		�o�X�N���b�N								      
//		P�� = 25MHz		���ӃN���b�N								    
//		MP��= 25MHz		MTU2 �N���b�N 
//
//  �쐬��
//		D.Yamamuro @ TUTrobo
//		S.Baba	   @ TUTrobo
//		K.Ishimori @ TUTrobo
//      K.Yamada   @ TUTrobo
//      IDO        @ TUTrobo
//
/********************************************************/

/********************************************************/
//
//  �ύX�_
//			
//	���_
//
//	������
//		/* ����E��H�ǃ��X�g */
//
//		/* �@�B�� */
//
/********************************************************/
                  
#include "setup.h"		// �}�C�R���̐ݒ�
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
	/********************* main���^�X�N�I�� ��������*********************/
//	#define CUSTOMIZE_DEBUG		// �F�X�A���̎�����
//	#define GAME				// ����	k
//	#define ENCODER_DEBUG		// ENCODER�̃f�o�b�N
//	#define ENC_CTRL_DEBUG		// �G���R�[�_�ɂ��t�B�[�h�o�b�N�̃f�o�b�N
//	#define MOTOR_DEBUG 		// MOTOR�̃f�o�b�N
//	#define OMUNI_DEBUG			// �I���j�̃f�o�b�O(3��duty)
//	#define PSCON_DEBUG			// PS����
//	#define PSCON2_DEBUG
//	#define PSCON_HALF_DEBUG	// half�̃f�o�b�O
//	#define R1350N_DEBUG		// �W���C���̃f�o�b�O
//	#define GMA860COND_DEBUG	// �W���C��MAP��Ԃ̃f�o�b�O
	#define MACOND_DEBUG		// �}�V���R���f�B�V�����̃f�o�b�O
//	#define OMUNI_RES			// �I���j�̕␳�l����
//	#define POSITION_DEBUG		// �������̂��߂̈ʒu�o��
//	#define CURRENT_DEBUG		// ���Έʒu
//	#define SPEED_CHECK			// �����`�F�b�N
//	#define SUSPENTION_DEBUG	// �����̃f�o�b�N
//	#define TOWER_DEBUG			// �^���[�̃f�o�b�N
//	#define	SERVO_DEBUG			// �T�[�{�̃f�o�ba�N
//	#define SHOOTER_DEBUG       // ���˂̃f�o�b�N
//	#define RELOAD_DEBUG		// ���U�̃f�o�b�O
//	#define ARM_POSITION		// �A�[���n�̈ʒu�m�F
//	#define AD_0_3_DEBUG		// AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��0�`�`�����l��3)		
//	#define AD_4_7_DEBUG		// AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��4�`�`�����l��7)
//	#define AD_0_7_DEBUG		// AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��4�`�`�����l��7)
//	#define BUZZER_DEBUG		// BUZZER�̃f�o�b�N
//	#define LED_DEBUG 			// LED�̃f�o�b�N
//	#define LED_CTRL_DEBUG 		// LED�R���g���[���̃f�o�b�N
//	#define AIR_DEBUG			// AIR�̂Ńo�b�N
//	#define MODE_DEBUG			// ���[�h�̃f�o�b�N
//	#define LIMIT_DEBUG			// ���~�b�g�̃f�o�b�N
//	#define WDT_DEBUG			// �E�H�b�`�h�b�N�^�C�}�̃f�o�b�N

	/********************* main���^�X�N�I�� �����܂�*********************/
	
	/********************** main���^���錾 ��������**********************/
	
		
	/********************** main���^���錾 ��������**********************/	
	
	/************** main���v���O�����X�^�[�g�A�b�v ��������**************/
	
	setup();					// �}�C�R���̏����ݒ�
	TASK_START();         		// �J�E���g�X�^�[�g ���荞�݃X�^�[�g
//	SENCE_START();         		// �J�E���g�X�^�[�g ���荞�݃X�^�[�g

	

//	COM0_START();				// �ʐM�J�n
	
	/*************** main���^�X�N�I�����K�p�ݒ� ��������***************/
	#ifdef	MOTOR_DEBUG 		// MOTOR�̃f�o�b�N�̂Ƃ�		
			motor_pwm_init();	// MOTOR_PWM�̏�����
	#endif
			
	#ifdef	SUSPENTION_DEBUG	// �����̃f�o�b�N�̂Ƃ�		
			motor_pwm_init();	// MOTOR_PWM�̏�����
	#endif
	
	#ifdef	SERVO_DEBUG			// �T�[�{�̃f�o�b�N�̂Ƃ�
		//	servo_pwm_init();	// SORVO_PWM�̏�����
	#endif
	/*************** main���^�X�N�I�����K�p�ݒ� �����܂�***************/
	
	/*************** main���^�X�N�I������O�ݒ� ��������***************/	
	#ifdef	GAME 				// �����̂Ƃ�
	#define	EXCEPTION			// ��O
	#endif
			
	#ifdef	ENCODER_DEBUG 		// ENCODER�̃f�o�b�N�̂Ƃ�
	#define	EXCEPTION			// ��O
	#endif
			
	#ifdef	WDT_DEBUG			// �E�H�b�`�h�b�N�^;�C�}�̂Ƃ�
	#define	EXCEPTION			// ��O
	#endif
	
//	#ifdef	comu0_slave_debug	// �ΐX�ʐM�̃X���[�u�f�o�b�N
//	#define	EXCEPTION			// ��O
//	#endif
	
#ifndef EXCEPTION			// ��O�łȂ��Ƃ�
			wdt_stop();			// WDT���֎~
//			TASK_END();        	// �^�C�}���荞�݋֎~
//			SENCE_END();        // �J�E���g�X�^�[�g ���荞�݃X�^�[�g
#endif
	
	/************** main���^�X�N�I������O�ݒ� ��������****************/
	
	/************** main���v���O�����X�^�[�g�A�b�v �����܂�**************/
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

//	printf("%.1f\t,%.1f\t,%.1f\t,%.1f\t,%.1f\t,%.1f\t\r\n",KUMA_THETA_L.duty,KUMA_R_L.duty,KUMA_Z_L.duty,KUMA_THETA_R.duty,KUMA_R_R.duty,KUMA_Z_R.duty);
//	printf("%.1f\t,%.1f\t,%.1f\t,%.1f\t\n",DEBUG[0],DEBUG[1],DEBUG[2],DEBUG[3]);	
	//printf("%d\t,%.1f\t,%d\t,%.1f\r\n",AD_DATA[0],KUMA_THETA_L.pos,AD_DATA[3],KUMA_THETA_R.pos);

//	printf("%d,%d,%d,%d,%.1,%.1f\n",(int)DEBUG[0],(int)DEBUG[1],(int)DEBUG[2],(int)DEBUG[3],ABS(KUMA_THETA_R.pos-140.0),ABS(KUMA_R_R.pos-450));
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
		printf("%d\t\n", macond.renc.l);		// x�̃G���R�[�_�J�E���g
		printf("%d\t\n", macond.renc.r);		// y�̃G���R�[�_�J�E���g
		printf("%f\t\n", macond.t_theta);	// �}�V���p�x
		printf("%f\t\n" , macond.pos.x);	// x���W
		printf("%f\t\n" , macond.pos.y);	// x���W
		

		printf("\n");
}
#endif

		//////////////////////////////////////////////////////////////////	
#ifdef	ENCODER_DEBUG
		/****************** �G���R�[�_�f�[�^�̃f�o�b�N ******************/

		//	show_macond();
		printf("%d, %d, %d, %d\n",MTU1.TCNT,MTU2.TCNT,MTU7.TCNT,MTU8.TCNT);	
/*
		printf("%4d,%4d,%4d,%4d,%4d\n"	,com0_tx[0][0]	
										,com0_tx[0][1]	
										,com0_tx[0][2]	
										,com0_tx[0][3]
										,com0_tx[0][4]	);	
*/		
		/****************** �G���R�[�_�f�[�^�̃f�o�b�N ******************/
#endif	// encoder_debug 
		//////////////////////////////////////////////////////////////////
#ifdef	ENC_CTRL_DEBUG
{
	int res=0;
		/*************** �G���R�[�_�R���g���[���̃f�o�b�N ***************/
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
		/*************** �G���R�[�_�R���g���[���̃f�o�b�N ***************/
}
#endif//enc_ctrl_debug
		//////////////////////////////////////////////////////////////////		
#ifdef	MOTOR_DEBUG
{
	double pwm_loop;			// PWM�̃f�o�b�N�̂��� for�����[�v�p
	
		/********************** ���[�^�[�̃f�o�b�N **********************/
		
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
		/********************** ���[�^�[�̃f�o�b�N **********************/
#endif

#ifdef SPEED_CHECK
{
	/********************** ���x�̃f�o�b�N **********************/
	printf("%.2f,",macond.pos.x);
	printf("%.3f,",max_speed);
	printf("%.2f,",(double)speed_timer/100.0);
	printf("%.3f\n",macond.v);
	/********************* ���x�̃f�o�b�N **********************/
}
#endif

#ifdef OMUNI_DEBUG
{
	/********************** �I���j�̃f�o�b�N **********************/
	printf("o=%.3f,l=%.3f,r=%.3f\t",motor_debug[0],motor_debug[1],motor_debug[2]);
	/********************* �I���j�̃f�o�b�N **********************/
}
#endif

#ifdef R1350N_DEBUG
{
	/********************** �W���C���̃f�o�b�N **********************/
		printf("m_angle=%.2f\t",(double)m_angle/100.0);
		printf("x=%d\t",accX);
		printf("y=%d\t",accY);
		printf("z=%d\n",accZ);
	/********************* �W���C���̃f�o�b�N **********************/
}
#endif

#ifdef ARM_POSITION
{
	/********************** �A�[���̈ʒu�\�� **********************/
		printf("fish_ad=%d\t",ad_data[2]);
		printf("fish_pos=%.2f\t",fishing_rod_position);
		printf("l_arm_ad=%d\t",ad_data[1]);
		printf("l_arm_pos=%.2f\n",l_arm_position);
	/********************* �A�[���̈ʒu�\�� **********************/
}
#endif

#ifdef GMACND_DEBUG
{
	/********************** gmacond�̃f�o�b�N **********************/
		printf("ax=%.2f\t",gcond.ax);
		printf("ay=%.2f\t",gcond.ay);
		printf("m_ax=%.2f\t",gcond.m_ax);
		printf("m_ay=%.2f\t",gcond.m_ay);
		printf("dir=%.2f\t",gcond.a_rad*180.0/PI);
		printf("angle=%.2f\n",(double)m_angle/100.0);

	/********************* gmacond�̃f�o�b�N **********************/
}
#endif

#ifdef MACOND_DEBUG
{
	
	/********************** �}�V����Ԃ̃f�o�b�N **********************/
	//	printf("t_theta=%.2f\t",macond.t_theta);
	//	printf("v=%.2f\tv_rad=%.2f\t",macond.v,macond.v_rad);
	//	printf("x=%.2f\ty=%.2f\n",macond.pos.x,macond.pos.y);
	printf("L:%.1f\t,%.1f\t,%.1f\t,%d\r\n",KUMA_THETA_L.pos,KUMA_R_L.pos,KUMA_Z_L.pos,SERVO_L);
	printf("R:%.1f\t,%.1f\t,%.1f\t,%d\r\n",KUMA_THETA_R.pos,KUMA_R_R.pos,KUMA_Z_R.pos,SERVO_R);
	printf("UO=%.1f\t,YOSHI=%.1f\r\n",UO.pos,YOSHI.pos);
	printf("LX=%.1f\t,LY=%.1f\t,RX=%.1f\t,RY=%.1f\r\n",KUMA_POS_LX,KUMA_POS_LY,KUMA_POS_RX,KUMA_POS_RY);
	
	/********************* �}�V����Ԃ̃f�o�b�N **********************/

}
#endif

#ifdef POSITION_DEBUG
{
	/********************** gmacond�̃f�o�b�N **********************/
		printf("t_theta=%.2f\t",macond.t_theta);
		printf("x=%.2f\t",macond.pos.x);
		printf("y=%.2f\t",macond.pos.y);
		printf("rod=%.2f\n",fishing_rod_position);

	/********************* gmacond�̃f�o�b�N **********************/
}
#endif

#ifdef PSCON_HALF_DEBUG
{
	/********************** half�̃f�o�b�O **********************/
		printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
		PS_BTN(RIGHT)	,PS_BTN(LEFT)	,PS_BTN(UP)		,PS_BTN(DOWN),
		PS_BTN(START)	,PS_BTN(R3)		,PS_BTN(L3)		,PS_BTN(SELECT),
		PS_BTN(SHIKAKU)	,PS_BTN(BATSU)	,PS_BTN(MARU)	,PS_BTN(SANKAKU),
		PS_BTN(R1)		,PS_BTN(L1)		,PS_BTN(R2)		,PS_BTN(L2)
		);
	/********************* half�̃f�o�b�N **********************/
}
#endif
		//////////////////////////////////////////////////////////////////	
#ifdef	SUSPENSION_DEBUG
{
		/*********************** �����̃f�o�b�N ***********************/
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
		/*********************** �����̃f�o�b�N ***********************/
}
#endif
		//////////////////////////////////////////////////////////////////			
#ifdef	TOWER_DEBUG
{
		/*********************** �^���[�̃f�o�b�N ***********************/		
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
		/*********************** �^���[�̃f�o�b�N ***********************/
}
#endif
		//////////////////////////////////////////////////////////////////	
#ifdef	SERVO_DEBUG
{
	int pwm;
		/********************** �T�[�{�̃f�o�b�N **********************/
		TASK_END();         		// �J�E���g�X�^�[�g ���荞�݃X�^�[�g

		ad_load_0_3(ad_data);
		pwm = (ad_data[2])*SERVO_CYCLE/1023;
		printf("%4d \t pwn = %d\n",ad_data[2],pwm);
		SERVO_B_PWM = pwm;
		SERVO_T_PWM = pwm;						
		/********************** ���[�^�[�̃f�o�b�N **********************/
}
#endif
		//////////////////////////////////////////////////////////////////
#ifdef	AD_0_3_DEBUG
{
		int loop;
		int ad_data[4];
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��0�`�`�����l��3) *******/
		
		ad_load_0_3(ad_data);
		
		for(loop = 0;loop <= 3;loop++)
			printf("ad_data[%d] = %4d\t",loop,ad_data[loop]);
		put_s("\n\r");
		
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��0�`�`�����l��3) *******/
}
#endif	
		//////////////////////////////////////////////////////////////////
#ifdef	AD_4_7_DEBUG
{
		int loop;
		int ad_data[4];
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��4�`�`�����l��7) *******/
		
		
		for(loop = 4;loop <= 7;loop++)
			printf("ad_data[%d] = %d\t",loop,ad_data[loop-4]);
		put_s("\n\r");
		
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��4�`�`�����l��7) *******/
}
#endif
		//////////////////////////////////////////////////////////////////
#ifdef	AD_0_7_DEBUG
{
		int loop;
		int ad_data[8];
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��0�`�`�����l��3) *******/
		
		ad_load_0_7(ad_data);
		
		for(loop = 0;loop <= 7;loop++)
			printf("[%d]:%4d\t",loop,ad_data[loop]);
		put_s("\n\r");
		
		/******* AD�ϊ��f�[�^�̃f�o�b�N(�`�����l��0�`�`�����l��3) *******/
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
		/********************** ���˂̃f�o�b�N **********************/
	//printf("TGT:%.1f, C0:%.1f, C1:%.1f, C2:%.1f, D0:%.1f, D1:%.1f, D2:%.1f, E2:%d \n",psta[0].target[0],psta[0].current[0],psta[1].current[0],psta[2].current[0],psta[0].duty,psta[1].duty,psta[2].duty,psta[2].end);
}		
		/********************** ���˂̃f�o�b�N **********************/
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

		/****************** AIR�R���g���[���̃f�o�b�N *******************/
		
		leaf_collect_hand(OPEN);
		leaf_esta_hand   (OPEN);
		
		for(delay_count1 = 0; delay_count1 < 65536; delay_count1 ++)	// delaytime
		for(delay_count2 = 0; delay_count2 <    30; delay_count2 ++);
		
		leaf_collect_hand(CLOSE);
		leaf_esta_hand   (CLOSE);
		
		for(delay_count1 = 0; delay_count1 < 65536; delay_count1 ++)	// delaytime
		for(delay_count2 = 0; delay_count2 <    30; delay_count2 ++);
		
		/****************** AIR�R���g���[���̃f�o�b�N *******************/
}
#endif		
		//////////////////////////////////////////////////////////////////
#ifdef	MODE_DEBUG
{
		/*********************** ���[�h�̃f�o�b�N ***********************/
		send_buff = mode();
		put_c(send_buff);
		put_s("\n\r");
		/*********************** ���[�h�̃f�o�b�N ***********************/
}
#endif	
		//////////////////////////////////////////////////////////////////
	
		//////////////////////////////////////////////////////////////////
#ifdef	LIMIT_DEBUG
{
		/********************** ���~�b�g�̃f�o�b�N **********************/
		
		if(LIMIT_L==0)printf("LIMIT_L\t");
		if(LIMIT_R==0)printf("LIMIT_R\t");
		if(LIMIT_U==0)printf("LIMIT_U\t");
		if(TOGGLE==0)printf("TOGGLE\t");
		printf("\n");

		/********************** ���~�b�g�̃f�o�b�N **********************/
}
#endif			
#ifdef	WDT_DEBUG	
{
		/**************** �E�H�b�`�h�b�O�^�C�}�̃f�o�b�N ****************/
		int wdt_count;				// �E�H�b�`�h�b�O�^�C�}�̃f�o�b�N�̂���
		wdt_count = WDT.READ.WTCNT;
		printf("wdt_count = %d\n",wdt_count);	
		
		/**************** �E�H�b�`�h�b�O�^�C�}�̃f�o�b�N ****************/
}
#endif

#ifdef PSCON_DEBUG//PS����
{		
	pscon_debug();
}
#endif	
#ifdef PSCON2_DEBUG//PS����
{		
	pscon2_debug();
}
#endif	


}


