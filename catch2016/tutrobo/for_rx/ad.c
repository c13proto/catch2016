/********************************************************/
//
//  �T�v
//      A/D�ϊ��֘A
//  ����
//		�}�C�R���ˑ��t�@�C��!!
//  �쐬��
//		K.yamada@ TUTrobo
//
/********************************************************/


#include "../setup.h"		//�}�C�R���̐ݒ�

//#define AD0_SINGLE_10
#define AD0_SCAN_10

//#define AD1_SINGLE_10
#define AD1_SCAN_10

//AD_SINGLE_12
//AD_SCAN_12

int ad[4];

#if 0
/////////////////////////////////////////////////////////

/*******AD�ϊ��V���O���X�L�������[�h�̃v���O����********/

/********************************************************/
//  ���O      
//		ad_init
//  �T�v
// 		A/D�ϊ��֐�
//  �@�\����
//		A/D�̏�����
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		@ TUTrobo
//
/********************************************************/
void ad_init()							//AD�ϊ��̏����ݒ�
{
//SH7125
#if 0
	STB.CR4.BIT._AD0   = 0;				//�X�^���o�C����
	AD0.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD0.ADCSR.BIT.STC  = 0;				//AD�ϊ��̎��Ԑݒ�(50�X�e�[�g)
	AD0.ADCSR.BIT.CKSL = 3;				//AD�ϊ��̎��Ԑݒ�(P��/2)
	AD0.ADCSR.BIT.ADM  = 0;				//AD�ϊ��̃��[�h�ݒ�(�V���O�����[�h)
	AD0.ADCSR.BIT.CH   = 0;				//�`�����l���Z���N�g(�V���O�����[�h AN0) �g���̂�AN0�`3
	
	//���`�����l���Z���N�g�́Aint ad_load(int i)�ōs���B	
#endif
}




/****AD�ϊ��V���O���X�L�������[�h�̃v���O���������܂�***/

/////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////

/*********AD�ϊ��A���X�L�������[�h�̃v���O����**********/

/********************************************************/
//  ���O      
//		ad_init(�A���X�L�������[�h)
//  �T�v
// 		A/D�ϊ��֐�
//  �@�\����
//		A/D�̏�����
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		 @ TUTrobo
//
/********************************************************/
void ad_init()							
{
	PORT4.ICR.BYTE = 0xFF;				// �|�[�g���͐ݒ�
#if defined(AD0_SINGLE_10) || defined(AD0_SCAN_10)	
	MSTP_AD0 = 0;						//�X���[�v�Έډ���
	AD0.ADCSR.BIT.ADST = 0; 			// AD�ϊ���~
	AD0.ADDPR.BIT.DPSEL = 1;			//�f�[�^��MSB�ɂ悹��
	AD0.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD0.ADCR.BIT.TRGS = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD0.ADSSTR= 75;						//0.52[us]+ADSSTR/48[Mhz]>=2[us]
	                                    //ADSSTR >= 71.04
	AD0.ADCR.BIT.CKS = 3;				//AD�ϊ��̎��Ԑݒ�(P��) 48Mhz
	AD0.ADCSR.BIT.CH  = 3;				//AD�ϊ��̃��[�h�ݒ�(4 �`���l���X�L�������[�h)
	#ifdef AD0_SCAN_10
		AD0.ADCR.BIT.MODE   = 3;				//�X�L�������[�h
	#endif
#endif

#if defined(AD1_SINGLE_10) || defined(AD1_SCAN_10)	
	MSTP_AD1 = 0;						//�X���[�v�Έډ���
	AD1.ADCSR.BIT.ADST = 0; 			// AD�ϊ���~
	AD1.ADDPR.BIT.DPSEL = 1;
	AD1.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD1.ADCR.BIT.TRGS = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD1.ADSSTR= 75;						//0.52[us]+ADSSTR/48[Mhz]>=2[us]
	                                    //ADSSTR >= 71.04
	AD1.ADCR.BIT.CKS = 3;				//AD�ϊ��̎��Ԑݒ�(P��) 48Mhz
	AD1.ADCSR.BIT.CH  = 3;				//AD�ϊ��̃��[�h�ݒ�(4 �`���l���X�L�������[�h)	
	#ifdef AD1_SCAN_10
		AD1.ADCR.BIT.MODE   = 3;				//�X�L�������[�h
	#endif
#endif
}

/********************************************************/
//  ���O      
//		ad_load(�A���X�L�������[�h)
//  �T�v
// 		A/D�ϊ��֐�
//  �@�\����
//		�`�����l��0~3����x�ɓǂݎ��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		 @ TUTrobo
//
/********************************************************/
void ad_load_0_3(int *ad_data) 				
{
	
	AD0.ADCSR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD0.ADCSR.BIT.ADST == 1);  // AD�ϊ��I���҂�
	
	ad_data[0] = AD0.ADDRA >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[1] = AD0.ADDRB >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[2] = AD0.ADDRC >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[3] = AD0.ADDRD >> 6;	// AN3 10bit�Ŏ擾
	
}

/********************************************************/
//  ���O      
//		ad_load(�A���X�L�������[�h)
//  �T�v
// 		A/D�ϊ��֐�
//  �@�\����
//		�`�����l��4~7����x�ɓǂݎ��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		@ TUTrobo
//
/********************************************************/
void ad_load_4_7(int *ad_data) 				
{
	
	AD1.ADCSR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD1.ADCSR.BIT.ADST == 1);  // AD�ϊ��I���҂�
	
	ad_data[0] = AD1.ADDRA >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[1] = AD1.ADDRB >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[2] = AD1.ADDRC >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[3] = AD1.ADDRD >> 6;	// AN3 10bit�Ŏ擾
	
}
void ad_load_0_7(int *ad_data) 				
{
	AD0.ADCSR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD0.ADCSR.BIT.ADST == 1);  // AD�ϊ��I���҂�
	
	ad_data[0] = AD0.ADDRA >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[1] = AD0.ADDRB >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[2] = AD0.ADDRC >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[3] = AD0.ADDRD >> 6;	// AN3 10bit�Ŏ擾
	
	AD1.ADCSR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD1.ADCSR.BIT.ADST == 1);  // AD�ϊ��I���҂�
	
	ad_data[4] = AD1.ADDRA >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[5] = AD1.ADDRB >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[6] = AD1.ADDRC >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[7] = AD1.ADDRD >> 6;	// AN3 10bit�Ŏ擾
	
}
/******AD�ϊ��A���X�L�������[�h�̃v���O���������܂�*****/

/////////////////////////////////////////////////////////

/********************************************************/
//  ���O      
//		PID_control
//  �T�v
// 		PID����
//  �@�\����
//		�ڕW���W�ƌ��݈ʒu����уQ�C���ݒ���󂯎��Aduty��Ԃ�
//  �p�����^����
//		mokuhyou:�ڕW���W
//		position:���ݍ��W
//		max_duty:�����Ă����ő��duty(0~100�Ŏ󂯎��)
//		Kp,Ki,Kd:���Q�C���A�����Q�C���A�ϕ��Q�C��
//		num		:0~3�܂ł̔ԍ�(char�^)�B�v���O�������œ����ɂ��̊֐����Ăяo���Ƃ���num�𕪂���
//  �߂�l
//		-100~100��duty(int�^)
//  �쐬��
//		�R��
//
/********************************************************/
int PID_control(double mokuhyou,double position,int max_duty,double Kp,double Ki,double Kd,char num)
{
	int duty[4];
	static double comp_P[4],comp_I[4],comp_D[4];//P,I,D����
	static double old_position[4],old_mokuhyou[4];//�ߋ��̍��W�A�ڕW���W
	
	if(old_mokuhyou[num] != mokuhyou)//�ڕW���W���ς������P,I,D������������
	{
		comp_P[num]=0.0;
		comp_I[num]=0.0;
		comp_D[num]=0.0;
		old_position[num]=0.0;
		old_mokuhyou[num]=0.0;
	}
	
	comp_P[num] = Kp*(mokuhyou - position);
	comp_I[num] +=Ki*comp_P[num];
	comp_D[num] = Kd*(position-old_position[num]);
	
	duty[num] = (int)(comp_P[num] + comp_I[num] + comp_D[num]+0.5);//int�^�Ɏ����Ƃ��Ɏl�̌ܓ��������̂�0.5�𑫂��Ă���
	
	if(duty[num]>max_duty)duty[num]=max_duty;//���ł�
	if(duty[num]<-max_duty)duty[num]=-max_duty;//��ł�
	
	old_position[num] = position;
	old_mokuhyou[num] = mokuhyou;
	
//	printf("%.1f\t%.1f\t%.1f\n",mokuhyou,position,comp_P[num]);
	
	return duty[num];
	
}
double PID_control_d(double mokuhyou,double position,double max_duty,double Kp,double Ki,double Kd,double I_reset_range,char num)
{
	double duty[10];
	static double comp_P[10],comp_I[10],comp_D[10];//P,I,D����
	static double old_position[10],old_mokuhyou[10];//�ߋ��̍��W�A�ڕW���W
	
	if(old_mokuhyou[num] != mokuhyou)//�ڕW���W���ς������P,I,D������������
	{
		comp_P[num]=0.0;
		comp_I[num]=0.0;
		comp_D[num]=0.0;
		old_position[num]=0.0;
		old_mokuhyou[num]=0.0;
	}
	
	comp_P[num] = Kp*(mokuhyou - position);
	comp_I[num] +=Ki*comp_P[num];
	comp_D[num] = Kd*(position-old_position[num]);
	
	if(ABS(mokuhyou-position)<=I_reset_range)comp_I[num]=0.0;//������x�߂Â�����I����������������i�قƂ�ǂ̑���͂��������ׂ��H�j
		
	duty[num] = comp_P[num] + comp_I[num] + comp_D[num];
	
	if(duty[num]>max_duty)duty[num]=max_duty;//���ł�
	if(duty[num]<-max_duty)duty[num]=-max_duty;//��ł�
	
	old_position[num] = position;
	old_mokuhyou[num] = mokuhyou;
	
//	printf("%.1f\t%.1f\t%.1f\n",mokuhyou,position,comp_P[num]);
	
	return duty[num];
	
}