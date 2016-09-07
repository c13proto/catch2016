/********************************************************/
//
//  �T�v
//      CET�֘A
//  �쐬��
//		IDO
//
/********************************************************/
#if 0
#include "setup.h"		//�}�C�R���̐ݒ�

#define CET_MIN_TIME 8	//�ŏ��T���v�����O�Ԋu[ms]
#define CET_TIMEOUT 20	//�Œ��ҋ@����[ms] (�o�߂���Ƒ��x��0�Ƃ݂Ȃ�)
#define CET_CLOCK_CYCLE 6000000 //�^�C�}�[��1�b�ԂɃJ�E���g����N���b�N��   PWM 48000000 CMT�Ȃ�48Mhz/8=6MHz
#define ENCODER_NUM  2	//�G���R�[�_�[�̐�(����cetda�̔z�񐔂ƍ��킹��)
#define TIMER_TCNT	CMT2.CMCNT	//���Ԍv���p�^�C�}�[�J�E���g���W�X�^
#define TIMER_CLEAR_COUNT	65535  //�^�C�}�[���N���A����鎞�̃J�E���g��(�I�[�o�[�t���[�ŃN���A�Ȃ̂�0xFFFF=65535)

struct cet_data cetda[ENCODER_NUM] =
{
//		�ŏ��̃A�h���X�̓G���R�[�_�[�p���X�J�E���g�̃��W�X�^�Ȃ̂ŉ�H�d�l�ɉ����ĕK���C�����邱��
		{&(ENC1_TCNT),&(CMT2.CMCNT),	0, -1, 0, 0},				// 0 MTU5V�ɑΉ�
		{&(ENC2_TCNT),&(CMT3.CMCNT),	0, -1, 0, 0},				// 1 MTU5W�ɑΉ�
};

/********************************************************/
//  ���O      
//		cet_set_timer
//  �T�v
// 		CET�֘A
//  �@�\����
//		�^�C�}�[�J�n/��~
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void cet_set_timer(char encnum, char onoff) 				
{
	switch(encnum){
		case 0: 
			CMT.CMSTR1.BIT.STR2 = onoff;
			break;
		
		case 1:
			CMT.CMSTR1.BIT.STR3 = onoff;
			break;
			
		default:
			break;
	}
}

/********************************************************/
//  ���O      
//		cet_get_timer
//  �T�v
// 		CET�֘A
//  �@�\����
//		�^�C�}�[��Ԃ̊m�F
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

char cet_get_timer(char encnum) 				
{
	switch(encnum){
		case 0: 
			return CMT.CMSTR1.BIT.STR2;
			break;
		
		case 1:
			return CMT.CMSTR1.BIT.STR3;
			break;
			
		default:
			return -1;
			break;
	}
}

/********************************************************/
//  ���O      
//		cet_init
//  �T�v
// 		�Z�b�g�A�b�v�֐�
//  �@�\����
//		SH7125�ɂ�����CET�̐ݒ���s��
//		MTU24�̓t���[�����j���O�J�E���^�AMTU25���C���v�b�g�L���v�`���ɗ��p
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/
void cet_init(void){
//	CMT.CMSTR1.BIT.STR2 = 1;				//�J�E���g�J�n
	MTU5.TCRV.BIT.TPSC = 3;     //�N���b�N���g����/64 (MTU�̃N���b�N��48Mhz)
	MTU5.TCRU.BIT.TPSC = 3;     //�N���b�N���g����/64 (MTU�̃N���b�N��48Mhz)
	MTU5.TIORV.BIT.IOC = 17;  // �����オ��G�b�W�ŃC���v�b�g�L���v�`��
	MTU5.TIORU.BIT.IOC = 17;  // �����オ��G�b�W�ŃC���v�b�g�L���v�`��
	MTU5.TSTR.BIT.CSTV5 = 1;     // MU25V�J�E���g�X�^�[�g
	MTU5.TSTR.BIT.CSTU5 = 1;     // MU25W�J�E���g�X�^�[�g
	
	IEN(MTU5,TGIV5) = 0;  //���荞�݋֎~
	IEN(MTU5,TGIU5) = 0;  //���荞�݋֎~
	IPR(MTU5,TGIV5) = 11; // ���荞�݃��x���ݒ�(CMT0)0�`15 0:�Œ� 15:�ō�
	IPR(MTU5,TGIU5) = 11; // ���荞�݃��x���ݒ�(CMT0)0�`15 0:�Œ� 15:�ō�
	MTU5.TIER.BIT.TGIE5V = 1;  // ���荞�݋���
	MTU5.TIER.BIT.TGIE5U = 1;  // ���荞�݋���
	IEN(MTU5,TGIV5) = 1;  //���荞�݋���
	IEN(MTU5,TGIU5) = 1;  //���荞�݋���


	
	/*SH
	MTU24.TCR.BIT.TPSC = 0;     // �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	MTU24.TIER.BIT.TCIEV = 1;	//�I�[�o�[�t���[���荞�݋���
	INTC.IPRF.BIT._MTU24C= 13;  // ���荞�݃��x���ݒ�(CMT1)0�`15 0:�Œ� 15:�ō�
	MTU2.TSTR.BIT.CST4 = 1;     // MTU24�J�E���g�X�^�[�g
	
	MTU25.TIORV.BIT.IOC = 17;  // �����オ��G�b�W�ŃC���v�b�g�L���v�`��
	MTU25.TIORW.BIT.IOC = 17;  // �����オ��G�b�W�ŃC���v�b�g�L���v�`��
	
	PFC.PBCRL1.BIT.PB1MD = 3;	// �|�[�gB1��MTU2�ɐݒ�
	PFC.PBIORL.BIT.B1    = 0;  	// ���̓|�[�g�ɐݒ�
	
	PFC.PBCRL1.BIT.PB3MD = 3;	// �|�[�gB3��MTU2�ɐݒ�
	PFC.PBIORL.BIT.B3    = 0;  	// ���̓|�[�g�ɐݒ�
	
	MTU25.TIER.BIT.TGIEV = 1; 	//���荞�݋���(TCLKA)	
	MTU25.TIER.BIT.TGIEW = 1;	//���荞�݋���(TCLKC)
	INTC.IPRF.BIT._MTU25= 12;
	*/
}	

/********************************************************/
//  ���O      
//		cet_edge_action
//  �T�v
// 		CET�֘A
//  �@�\����
//		�p���X�G�b�W�ł̓���
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void cet_edge_action(char encnum) 				
{
	double elapsed_clock;
	if(cet_get_timer(encnum) == 1){ //�J��オ��񐔂�-1(�������)�Ŗ���������A���Ԍv����
		elapsed_clock = *cetda[encnum].timer_tcnt; //�J�E���g�J�n����̌o�ߎ��Ԃ����߂� ���F(���݂̃^�C�}�[�J�E���g + �J��オ�肷�鐔*�J��オ���) - �J�E���g�J�n���̃^�C�}�[�J�E���g
		if(elapsed_clock >= (double)(CET_MIN_TIME * CET_CLOCK_CYCLE / 1000)){ //�o�ߎ��Ԃ��Œ�T���v�����O�Ԋu���傫�����`�F�b�N ���F�ŏ��T���v�����O�Ԋu[ms]*1ms������̃J�E���g��
			cetda[encnum].last_tcnt = *cetda[encnum].enc_tcnt; //���݂̃G���R�[�_�[�p���X�J�E���g���L��
			cetda[encnum].last_elapsed = elapsed_clock; //���݂̌o�ߎ��Ԃ��L��
			cet_set_timer(encnum, 0); //�J�E���g��~
			//put_s("checked");
		}
	}else{ //�J��オ��񐔂�������ԂȂ�A�J�E���g���J�n����
		*cetda[encnum].timer_tcnt = *cetda[encnum].enc_tcnt = 0; //�J��オ��񐔁A�G���R�[�_�[�p���X�J�E���g���[����
		cet_set_timer(encnum, 1); //�J�E���g�J�n
	}
//	put_s("DBG_EDGE");
}

/********************************************************/
//  ���O      
//		cet_clear_action
//  �T�v
// 		CET�֘A
//  �@�\����
//		���Ԍv���p�^�C�}�[�N���A���̓���
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void cet_clear_action(char encnum) 				
{
	cet_set_timer(encnum, 0); //�J�E���g��~
	cetda[encnum].last_tcnt = cetda[encnum].last_elapsed = 0; //���x��0�ɂ���
	//put_s("DBG_CMT2");
}

/********************************************************/
//  ���O      
//		cet_get_rpm
//  �T�v
// 		CET�֘A
//  �@�\����
//		�^����ꂽ�z��ɉ�]���x[RPM]����
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void cet_get_rpm(double rot_return[]) 				
{
	char i;
	double delta_t[ENCODER_NUM];
	for(i=0; i < ENCODER_NUM; i++){
		delta_t[i] = (double)cetda[i].last_elapsed / (double)CET_CLOCK_CYCLE; //�o�ߎ���[s]���v�Z ��:�o�߃J�E���g�� / 1�b������̃J�E���g��
		if(delta_t[i] != 0.0)
			rot_return[i] = ((double)((short)cetda[i].last_tcnt) / (double)RND_PLS)* 60.0 / delta_t[i]; //RPM��Ԃ� ��:(�G���R�[�_�[�p���X / ���]������̃p���X��)[��]] / �o�ߎ���[s] * 60[s] 
		else
			rot_return[i] = 0.0;
		//if(fabs(rot_old[i]-rot_return[i]) > 200.0 && tera==1) //�����O��Ƃ̍����傫��������f�o�b�O���e���v�����g
		//	printf("%d: %.2f,%.2f,%.1fms,%d\n",i,rot_old[i],rot_return[i],delta_t[i]*1000,cetda[i].cntup);
		//rot_old[i] = rot_return[i]; //�O��̒l���L��
	}
//	put_s("get");
}
#endif
