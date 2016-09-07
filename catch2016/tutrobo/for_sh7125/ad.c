/********************************************************/
//
//  �T�v
//      A/D�ϊ��֘A
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�

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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_init()							//AD�ϊ��̏����ݒ�
{

	STB.CR4.BIT._AD0   = 0;				//�X�^���o�C����
	AD0.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD0.ADCSR.BIT.STC  = 0;				//AD�ϊ��̎��Ԑݒ�(50�X�e�[�g)
	AD0.ADCSR.BIT.CKSL = 3;				//AD�ϊ��̎��Ԑݒ�(P��/2)
	AD0.ADCSR.BIT.ADM  = 0;				//AD�ϊ��̃��[�h�ݒ�(�V���O�����[�h)
	AD0.ADCSR.BIT.CH   = 0;				//�`�����l���Z���N�g(�V���O�����[�h AN0) �g���̂�AN0�`3
	
	//���`�����l���Z���N�g�́Aint ad_load(int i)�ōs���B	
}

/********************************************************/
//  ���O      
//		ad_load
//  �T�v
// 		A/D�ϊ��֐�
//  �@�\����
//		A/D�ϊ��̃`�����l���ݒ�EA/D�ϊ��̒l�̓ǂݎ��
//  �p�����^����
//		ch			�`�����l���̒l
//		ad_result	A/D�ϊ��̒l������
//		ad[4]		���ꂼ���0�`3��A/D�ϊ��̒l������
//  �߂�l
//		A/D�ϊ��̒l
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int ad_load(int ch) 				//AD�ϊ��`�����l���ݒ�
{
	int ad_result;
	int ad[4];
	
	AD0.ADCSR.BIT.CH = ch;			//AD�ϊ�����`�����l����ݒ�(ADST=0�̎�)
	AD0.ADCR.BIT.ADST = 1; 			// AD�ϊ��J�n
	while(AD0.ADCSR.BIT.ADF == 0);  // AD�ϊ��I���҂�
	ad[0] = AD0.ADDR0 >> 6; 		// AN0 10bit�Ŏ擾
	ad[1] = AD0.ADDR1 >> 6; 		// AN1 10bit�Ŏ擾
	ad[2] = AD0.ADDR2 >> 6; 		// AN2 10bit�Ŏ擾
	ad[3] = AD0.ADDR3 >> 6;			// AN3 10bit�Ŏ擾
	
	ad_result = ad[ch];
	
	AD0.ADCSR.BIT.ADF = 0; 			// AD�����t���O�N���A
	
	return ad_result;
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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_init()							
{
/*���͉����{�^���ɂȂ��Ă�
	STB.CR4.BIT._AD0   = 0;				//�X�^���o�C����
	AD0.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD0.ADCSR.BIT.STC  = 0;				//AD�ϊ��̎��Ԑݒ�(50�X�e�[�g)
	AD0.ADCSR.BIT.CKSL = 3;				//AD�ϊ��̎��Ԑݒ�(P��)
	AD0.ADCSR.BIT.ADM  = 1;				//AD�ϊ��̃��[�h�ݒ�(4 �`���l���X�L�������[�h)
	AD0.ADCSR.BIT.ADCS = 0;				//AD�ϊ��A���X�L����
	AD0.ADCSR.BIT.CH   = 3;				//�A���X�L�������[�h	
*/	
	STB.CR4.BIT._AD1   = 0;				//�X�^���o�C����
	AD1.ADCSR.BIT.ADIE = 0;				//ADF�̂�銄�荞�݂��C�l�[�u���ɂ��Ȃ�
	AD1.ADCSR.BIT.TRGE = 0;				//MTU,ADTRG�g���K���ϊ��J�n�𖳌�
	AD1.ADCSR.BIT.STC  = 0;				//AD�ϊ��̎��Ԑݒ�(50�X�e�[�g)
	AD1.ADCSR.BIT.CKSL = 3;				//AD�ϊ��̎��Ԑݒ�(P��)
	AD1.ADCSR.BIT.ADM  = 1;				//AD�ϊ��̃��[�h�ݒ�(4 �`���l���X�L�������[�h)
	AD1.ADCSR.BIT.ADCS = 0;				//AD�ϊ��A���X�L����
	AD1.ADCSR.BIT.CH   = 3;				//�A���X�L�������[�h
	
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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_load_0_3(int *ad_data) 				
{
	
	AD0.ADCR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD0.ADCSR.BIT.ADF == 0);  // AD�ϊ��I���҂�
	
	ad_data[0] = AD0.ADDR0 >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[1] = AD0.ADDR1 >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[2] = AD0.ADDR2 >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[3] = AD0.ADDR3 >> 6;	// AN3 10bit�Ŏ擾
	
	AD0.ADCSR.BIT.ADF = 0; 			// AD�����t���O�N���A

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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_load_4_7(int *ad_data) 				
{
	
	AD1.ADCR.BIT.ADST = 1; 			// AD�ϊ��J�n
	
	while(AD1.ADCSR.BIT.ADF == 0);  // AD�ϊ��I���҂�
	
	ad_data[0] = AD1.ADDR4 >> 6; 	// AN0 10bit�Ŏ擾
	ad_data[1] = AD1.ADDR5 >> 6; 	// AN1 10bit�Ŏ擾
	ad_data[2] = AD1.ADDR6 >> 6; 	// AN2 10bit�Ŏ擾
	ad_data[3] = AD1.ADDR7 >> 6;	// AN3 10bit�Ŏ擾
	
	AD1.ADCSR.BIT.ADF = 0; 			// AD�����t���O�N���A

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