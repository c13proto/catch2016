/********************************************************/
//
//  �T�v
//      �G���R�[�_�֘A�ݒ�
//  ����
//		�}�C�R���ˑ��t�@�C��!!
//  �쐬��
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�
#include "../enc_para.h"	//�G���R�[�_�Q�C���ݒ�

/********************************************************/
//  ���O      
//		enc_init
//  �T�v
//      �G���R�[�_
//  �@�\����
//		�G���R�[�_�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		MTU2�X�^���o�C���[�h������setup.c�ɂ���
//		MTU2_init�ōs���Ă���
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/
void enc_init(void) //�ʑ��v�����[�h�̐ݒ�
{
	MTUA.TSTR.BIT.CST1 = 0;    			//MTU20�J�E���g��~
	MTUA.TSTR.BIT.CST2 = 0;    			//MTU20�J�E���g��~
	MTUB.TSTR.BIT.CST1 = 0;    			//MTU20�J�E���g��~
	MTUB.TSTR.BIT.CST2 = 0;    			//MTU20�J�E���g��~

	PORTC.ICR.BYTE=0xFF;
	IOPORT.PFCMTU.BIT.TCLKS = 1; 		// 0�F�I��
										// 1�FPORTC�I��
	IOPORT.PFDMTU.BIT.TCLKS = 0; 		// 0�FPORTC�I��
									
	
	
	/*���
	
	PFC.PACRL2.BIT.PA6MD = 1;			//PA6(TCLKA)�̓���ݒ�
	PFC.PACRL2.BIT.PA7MD = 1;			//PA7(TCLKB)�̓���ݒ�
	PFC.PACRL3.BIT.PA8MD = 1;			//PA8(TCLKC)�̓���ݒ�
	PFC.PACRL3.BIT.PA9MD = 1;			//PA9(TCLKD)�̓���ݒ�
	PFC.PAIORL.BIT.B6 = 0;				//PA6�̓��o�͐ݒ�
	PFC.PAIORL.BIT.B7 = 0;				//PA7�̓��o�͐ݒ�
	PFC.PAIORL.BIT.B8 = 0;				//PA8�̓��o�͐ݒ�	
	PFC.PAIORL.BIT.B9 = 0;				//PA9�̓��o�͐ݒ�
	
	*/
	MTU1.TMDR.BIT.MD = 0x0004;			//ch1���ʑ��v�����[�h1�ɐݒ�
	MTU2.TMDR.BIT.MD = 0x0004;			//ch2���ʑ��v�����[�h1�ɐݒ�
	MTU1.TCNT = 0x0000;				//�`�����l��1, �J�E���^�N���A���Ƃ�
	MTU2.TCNT = 0x0000;				//�`�����l��2, �J�E���^�N���A���Ƃ�
	MTUA.TSTR.BIT.CST1 = 1;				//�J�E���g�J�n	
	MTUA.TSTR.BIT.CST2 = 1;				//�J�E���g�J�n
	
	
	
	MTU7.TMDR.BIT.MD = 0x0004;			//ch1���ʑ��v�����[�h1�ɐݒ�
	MTU8.TMDR.BIT.MD = 0x0004;			//ch2���ʑ��v�����[�h1�ɐݒ�
	MTU7.TCNT = 0x0000;				//�`�����l��1, �J�E���^�N���A���Ƃ�
	MTU8.TCNT = 0x0000;				//�`�����l��2, �J�E���^�N���A���Ƃ�
	MTUB.TSTR.BIT.CST1 = 1;				//�J�E���g�J�n	
	MTUB.TSTR.BIT.CST2 = 1;				//�J�E���g�J�n
	
}

/********************************************************/
//  TUTrobo
//
//  �T�v
//      AD�ϊ��֐� �v���g�^�C�v�錾
/********************************************************/
struct enc_information ENCInfArray[][ENC_AIM_MAX];	//�e����ɗp����Q�C��������
struct enc_condition enc_cond[ENC_NUM]; 			//�e����ɗp����̕ϐ�����

/********************************************************/
//  ���O      
//		enc_ctrl
//  �T�v
// 		�G���R�[�_�֐�
//  �@�\����
//		�G���R�[�_�ɂ��t�B�[�h�o�b�N
//  �p�����^����
//		distEnd	�ڕW�n�_
//		ch		�G���R�[�_�`���l��
//		num		�Q�C���̑I��
//		duty	���݂�duty��
//  �߂�l
//		enc_res	�I����CMD_END   
//	���ӎ���
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int enc_ctrl(double distEnd,short ch,short num,double* duty)
{
	int res = 0;
	
	/* �G���R�[�_����̃Q�C���֘A */
	struct enc_information enc_inf;
	
	/* �Q�C���̎󂯎�� */
	enc_inf = ENCInfArray[ch][num];
	
	/* �G���R�[�_�̃`�����l���I�� */
	switch(ch)
	{
		case 0:
		
			enc_cond[ch].cnt_now = MTU1.TCNT;
				enc_cond[ch].cnt_diff  = (short)( ((unsigned short)enc_cond[ch].cnt_now - (unsigned short)enc_cond[ch].cnt_old));			/* �G���R�[�_�̉�]�̌����������ŕ␳ */
			break;
			
		case 1:
		
			enc_cond[ch].cnt_now = MTU2.TCNT;
				enc_cond[ch].cnt_diff  = (short)( ((unsigned short)enc_cond[ch].cnt_now - (unsigned short)enc_cond[ch].cnt_old));			/* �G���R�[�_�̉�]�̌����������ŕ␳ */
			break;
		
	}
	
	/* �G���R�[�_�̋������Z�o */
	enc_cond[ch].cnt_old   = enc_cond[ch].cnt_now;									/* �ߋ��̃G���R�[�_�J�E���g��ۑ� */
	enc_cond[ch].dist_now += enc_cond[ch].cnt_diff * enc_inf.THO / ENCODER_RES;		/* �ړ����� */
	
	/* PID�̐������Z�o */	
	enc_cond[ch].er   = distEnd - enc_cond[ch].dist_now;						/* ��ᐬ�� */
	enc_cond[ch].d_er = enc_cond[ch].er - (distEnd - enc_cond[ch].dist_old);	/* �������� */
	if(enc_cond[ch].er <100)													/* �ϕ����� */
	{
		enc_cond[ch].i_er += enc_cond[ch].er;
	}	
	
	if(ABS(enc_cond[ch].i_er) > 10000.0)							/* �ϕ������̃I�[�o�[�t���[�΍� */	
	{
		if(enc_cond[ch].i_er > 0.0)	{enc_cond[ch].i_er =  10000.0;}
		else						{enc_cond[ch].i_er = -10000.0;}
	}

	/* PID���� */
	*duty = enc_inf.K  * enc_cond[ch].er 
		  + enc_inf.Kd * enc_cond[ch].d_er
		  + enc_inf.Ki * enc_cond[ch].i_er;

	/* duty�̍ő�l���� */
	if(*duty >  enc_inf.ratio) *duty =  enc_inf.ratio;
	if(*duty < -enc_inf.ratio) *duty = -enc_inf.ratio;

	/* �ߋ��̋�����ۑ� */
	enc_cond[ch].dist_old = enc_cond[ch].dist_now;
	
	if( (ABS(enc_cond[ch].er) < enc_inf.adm) )		//���B�͈͈ȓ��̏ꍇ
	{ 				
	
		enc_cond[ch].i_er = 0.0;
		*duty = 0.0;
		res = 1;

	}
	
/*	if(PA.DRL.BIT.B12 == 0)
	{
		MTU21.TCNT = 0x0000;				//�`�����l��1, �J�E���^�N���A���Ƃ�
		dist = 0.0;
		dist_old = 0.0;
	}
*/		
	/////////////////////////////////////////////////////////////////
//	�f�o�b�N���邽�߂Ɋe�l���O���[�o���ϐ��Ɋi�[
//	printf("%d\n",PA.DRL.BIT.B12);
	
//	printf("%3.1f\n",enc_cond[ch].dist_now);	

//	printf("%d\t",enc_cnt);
//	printf("%d\n",cnt_old);		
	
//	printf("%d\n",enc_cnt);

/*	printf("%d\t",enc_cond[ch].cnt_now);
	printf("%f\t",enc_cond[ch].dist_now);
	printf("%f\t",distEnd);
	printf("%3.1f\n",*duty);
*/

	return res;
	
}