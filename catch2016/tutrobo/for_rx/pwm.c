/********************************************************/
//
//  �T�v
//      PWM�ݒ�
//  ����
//		�}�C�R���ˑ��t�@�C��!!
//  �쐬��
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�

/********************************************************/
//  TUTrobo
//
//  �T�v
//      PWM�ݒ� �v���g�^�C�v�錾
/********************************************************/
void motor_pwm_init(void);		// PWM�̏�����
int anti_lock_pwm(double duty);	// ���[�^�̃A���`���b�N��PWM���R���g���[������

/********************************************************/
//  ���O      
//		pwm_init
//  �T�v
// 		PWM�֐�
//  �@�\����
//		PWM�̏�����
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		MTU2�X�^���o�C���[�h����,�J�E���g��~��
//		setup.c�ɂ���MTU2_init�ōs���Ă���
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/
void pwm_init(void)
{
	volatile int dummy;					// �_�~�[�ǂݎ��̂���
		
	MTUA.TSTR.BIT.CST0 = 0;     // MTU0�J�E���g�X�g�b�v	
	MTUA.TSTR.BIT.CST4 = 0; 	// MTU4�J�E���g�X�g�b�v
	MTUB.TSTR.BIT.CST0 = 0;     // MTU6�J�E���g�X�g�b�v
	MTUB.TSTR.BIT.CST3 = 0; 	// MTU9�J�E���g�X�g�b�v
	MTUB.TSTR.BIT.CST4 = 0; 	// MTU10�J�E���g�X�g�b�v

/*********�`�����l��0 pwm���[�h2�ݒ�J�n (DC���[�^)**********/
//0A~0D�܂�PIN����
	
	MTU0.TCR.BIT.TPSC = 0;     //�N���b�N���g����/1 (MTU�̃N���b�N��48Mhz)	
	MTU0.TCR.BIT.CCLR = 3;     // ��������2�̎��͂����̒l��3�ɂ���
//	MTU0.TCR.BIT.CCLR = 2;     // TGRB�œ����N���A
	MTU0.TMDR.BIT.MD = 3;      // PWM���[�h2
	MTUA.TSYR.BYTE = 0x81;      //0��4�̓�������
//	MTUA.TSYR.BYTE = 0;         //�Ɨ�����
	MTU0.TIORH.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU0.TIORH.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU0.TIORL.BIT.IOD = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU0.TIORL.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��	
	MTU0.TGRA = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
	MTU0.TGRB = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
	MTU0.TGRC = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
	MTU0.TGRD = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
			
/*****�`�����l��4 pwm���[�h1�ݒ�J�n (DC���[�^)******/
//4A,4C��PIN����

	MTU4.TCR.BIT.TPSC = 0; 	// �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	MTU4.TCR.BIT.CKEG = 0; 	// �����オ��G�b�W�ŃJ�E���g
	MTU4.TCR.BIT.CCLR = 2; 	// TGRB�ŃJ�E���g�N���A;
	MTU4.TMDR.BIT.MD = 2;		// PWM���[�h1
	MTU4.TIORH.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU4.TIORH.BIT.IOB = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU4.TIORL.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU4.TIORL.BIT.IOD = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU4.TGRA = ANTI_THRESHOLD;		// TIOC4A�R���y�A�}�b�`
	MTU4.TGRB = ANTI_CYCLE;			// TIOC4B�R���y�A�}�b�`
	MTU4.TGRC = ANTI_THRESHOLD;		// TIOC4C�R���y�A�}�b�`
	MTU4.TGRD = ANTI_CYCLE;			// TIOC4D�R���y�A�}�b�`
	// ch4�����K�{!�I�I 
	MTUA.TOER.BIT.OE4A = 1; 	// FTIO4A��MTU2���������
	MTUA.TOER.BIT.OE4B = 1;		// FTIO4B��MTU2���������
	MTUA.TOER.BIT.OE4C = 1;		// FTIO4C��MTU2���������
	MTUA.TOER.BIT.OE4D = 1;		// FTIO4D��MTU2���������

	IOPORT.PFCMTU.BIT.MTUS4 = 0; 		// 0�FP24��MTIOC4A-A�[�q�Ƃ��đI�� P25��MTIOC4C-A�[�q�Ƃ��đI��
										// 1�FP82��MTIOC4A-B�[�q�Ƃ��đI�� P83��MTIOC4C-B�[�q�Ƃ��đI��
	//IOPORT.PFCMTU.BIT.MTUS5 = 0;		// 0�FP30��MTIOC4B-A�[�q�Ƃ��đI�� P31��MTIOC4D-A�[�q�Ƃ��đI��
										// 1�FP54��MTIOC4B-B�[�q�Ƃ��đI�� P55��MTIOC4D-B�[�q�Ƃ��đI��
					

/*********�`�����l��6 pwm���[�h2�ݒ�J�n (DC���[�^)**********/
//6A,6B,6D��PIN����

	MTU6.TCR.BIT.TPSC =0;     //�N���b�N���g����/16 (MTU�̃N���b�N��48Mhz)	
//	MTU6.TCR.BIT.CCLR = 2;//    // TGRB�ŃJ�E���g�N���A
	MTU6.TCR.BIT.CCLR = 3;//    // ��������̎��͂����̒l��3�ɂ���	
	MTU6.TMDR.BIT.MD = 3;       // PWM���[�h2
	MTUB.TSYR.BYTE = 0x41;      //6��9�̓�������
//	MTUB.TSYR.BYTE = 0;         //�Ɨ�����			
	MTU6.TIORH.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU6.TIORH.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU6.TIORL.BIT.IOD = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU6.TIORL.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��	
	MTU6.TGRA = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
	MTU6.TGRB = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�
	MTU6.TGRC = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�(PIN�������̂ŕ֋X��)
	MTU6.TGRD = ANTI_THRESHOLD;	// �f���[�e�B�ݒ�	

/*****�`�����l��9 pwm���[�h1�ݒ�J�n (DC���[�^)******/

	MTU9.TCR.BIT.TPSC = 0; 		//�N���b�N���g����/16 (MTU�̃N���b�N��48Mhz)
	MTU9.TCR.BIT.CKEG = 0; 		// �����オ��G�b�W�ŃJ�E���g
	MTU9.TCR.BIT.CCLR = 2; 		// TGRB�ŃJ�E���g�N���A;
	MTU9.TMDR.BIT.MD = 2;		// PWM1���[�h	
	MTU9.TIORH.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU9.TIORH.BIT.IOB = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU9.TIORL.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU9.TIORL.BIT.IOD = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��	
	MTU9.TGRA = ANTI_THRESHOLD;	// TIOC4A�R���y�A�}�b�`
	MTU9.TGRB = ANTI_CYCLE;		// TIOC4B�R���y�A�}�b�`
	MTU9.TGRC = ANTI_THRESHOLD;	// TIOC4C�R���y�A�}�b�`
	MTU9.TGRD = ANTI_CYCLE;		// TIOC4D�R���y�A�}�b�`	

/*************�`�����l��10 PWM���[�h1�ݒ�J�n�i�T�[�{�j***************/

	MTU10.TCR.BIT.TPSC = 2; 	//�N���b�N���g����/16 (MTU�̃N���b�N��48Mhz)	
	MTU10.TCR.BIT.CKEG = 0; 	//�����オ��G�b�W�ŃJ�E���g
	MTU10.TCR.BIT.CCLR = 2; 	//TGRB�ŃJ�E���g�N���A;
	MTU10.TMDR.BIT.MD = 2;		//PWM1���[�h		
	MTU10.TIORH.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��(�t�͂T)
	MTU10.TIORH.BIT.IOB = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU10.TIORL.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU10.TIORL.BIT.IOD = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��	
	MTU10.TGRA = SERVO_TH;		//TIOC4A�R���y�A�}�b�`
	MTU10.TGRB = SERVO_CYCLE;	//�����ݒ�
	MTU10.TGRC = SERVO_TH;		//TIOC4C�R���y�A�}�b�`
	MTU10.TGRD = SERVO_CYCLE;	//�����ݒ�	
	// ch4�����K�{!�I�I 
	MTUB.TOER.BIT.OE4A = 1; 	// FTIO4A��MTU2���������
	MTUB.TOER.BIT.OE4B = 1;		// FTIO4B��MTU2���������
	MTUB.TOER.BIT.OE4C = 1;		// FTIO4C��MTU2���������
	MTUB.TOER.BIT.OE4D = 1;		// FTIO4D��MTU2���������
	
/*************�`�����l��10 PWM���[�h1�ݒ�I��***************/


	MTUA.TSTR.BIT.CST0 = 1;     // MTU0�J�E���g�X�^�[�g
	MTUA.TSTR.BIT.CST4 = 1;     // MTU4�J�E���g�X�^�[�g
	MTUB.TSTR.BIT.CST0 = 1;     // MTU6�J�E���g�X�^�[�g
	MTUB.TSTR.BIT.CST3 = 1;     // MTU9�J�E���g�X�^�[�g
	MTUB.TSTR.BIT.CST4 = 1;     // MTU10�J�E���g�X�^�[�g

}



/********************************************************/
//  ���O      
//		servo_pwm_init
//  �T�v
// 		PWM�֐�
//  �@�\����
//		SORVO_PWM�̏�����
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		MTU2�X�^���o�C���[�h����,�J�E���g��~��
//		setup.c�ɂ���MTU2_init�ōs���Ă���
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/
void servo_pwm_init(void)
{
	volatile int dummy;					// �_�~�[�ǂݎ��̂���
			
	/*************�`�����l��0 pwm���[�h2�ݒ�J�n***************/
	
	MTU0.TCR.BIT.TPSC = 2;     //�N���b�N���g����/16 (MTU�̃N���b�N��48Mhz)
	
	MTU0.TCR.BIT.CCLR = 6;     // TGRD�R���y�A�}�b�`��TCNT�N���A
	
	MTUA.TSYR.BYTE = 0;         // �Ɨ�����
		
	MTU0.TIORH.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU0.TIORH.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU0.TIORL.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	
	MTU0.TGRA = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU0.TGRB = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU0.TGRC = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU0.TGRD = SERVO_CYCLE;	// �����ݒ�
			
	MTU0.TMDR.BIT.MD = 3;      // PWM���[�h2
	

	MTUA.TSTR.BIT.CST0 = 1;     // MU20�J�E���g�X�^�[�g
	
	/*************�`�����l��0 pwm���[�h2�ݒ�I��***************/

	/*************�`�����l��0,2�������[�h�ݒ�J�n**************/
/*	
	MTU2.TSTR.BIT.CST0 = 1;    	//MTU20�J�E���g��~
	MTU2.TSTR.BIT.CST2 = 1; 	//MTU22�J�E���g��~
	
	MTU20.TCR.BIT.TPSC = 2;     //�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	MTU22.TCR.BIT.TPSC = 2;     //�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU20.TCR.BIT.CCLR = 3;     //�����N���A
	MTU22.TCR.BIT.CCLR = 2;     //TGRB�R���y�A�}�b�`��TCNT�N���A
	
	MTU2.TSYR.BYTE = 5;         //�`���l��0,2��������
	
	MTU20.TIOR.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOB = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOD = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU22.TIOR.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��

	MTU20.TGRA = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRB = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRC = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRD = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU22.TGRA = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU22.TGRB = SERVO_CYCLE;	// �����ݒ�
	
	MTU20.TMDR.BIT.MD = 3;      //PWM���[�h2
	MTU22.TMDR.BIT.MD = 3;      //PWM���[�h2
	
	PFC.PECRL1.BIT.PE0MD = 1;	//�|�[�gE0��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B0    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE1MD = 1;	//�|�[�gE1��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B1    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE2MD = 1;  	//�|�[�gE2��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B2    = 1;  	//�o�̓|�[�g�ɐݒ�	
	
	PFC.PECRL1.BIT.PE3MD = 1;  	//�|�[�gE3��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B3    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE6MD = 1;  	//�|�[�gE6��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B6    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE7MD = 1;  	//�|�[�gE7��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B7    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST0 = 1;     //MU20�J�E���g�X�^�[�g
	MTU2.TSTR.BIT.CST2 = 1;		//MU22�J�E���g�X�^�[�g
*/	
	/*************�`�����l��0,2�������[�h�ݒ�I��**************/


	/*************�`�����l��4 PWM���[�h1�ݒ�J�n***************/

	MTUA.TSTR.BIT.CST4 = 1; 	//MTU24�J�E���g��~
	
	MTU4.TCR.BIT.CCLR = 2; 	//TGRB�ŃJ�E���g�N���A;
	
	MTU4.TCR.BIT.TPSC = 2; 	//�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU4.TCR.BIT.CKEG = 0; 	//�����オ��G�b�W�ŃJ�E���g
	
	MTU4.TIORH.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU4.TIORH.BIT.IOB = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU4.TIORL.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU4.TIORL.BIT.IOD = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU4.TGRA = SERVO_TH;		//TIOC4A�R���y�A�}�b�`
	MTU4.TGRB = SERVO_CYCLE;	//TIOC4B�R���y�A�}�b�`
	MTU4.TGRC = SERVO_TH;		//TIOC4C�R���y�A�}�b�`
	MTU4.TGRD = SERVO_CYCLE;	//TIOC4D�R���y�A�}�b�`
	
	MTU4.TMDR.BIT.MD = 2;		//PWM1���[�h
/*	
	MTU.TOER.BIT.OE4A = 1; 	//ch4�����K�{!�I�I
	MTU.TOER.BIT.OE4B = 1;
	MTU.TOER.BIT.OE4C = 1;
	MTU.TOER.BIT.OE4D = 1;
*/	
								// �����ݒ�ł�POE���[�h�ɂȂ��Ă��邽��
								// PB16�ɂȂɂ���ڑ������PWM�g�`���łȂ��Ȃ�B
//	PFC.PBIORH.BIT.B16    = 1;  // ���o�̓|�[�g�ɐݒ�
								// IO�̏����ݒ��������POE�t���O�������Ă��܂�����
								// �N���A���Ȃ���΂Ȃ�Ȃ�	
	dummy = POE.ICSR1.BIT.POE3F;// �_�~�[�ǂݎ��
	POE.ICSR1.BIT.POE3F = 0; 	// �t���O�N���A

	
	IOPORT.PFCMTU.BIT.MTUS4 = 0; 		// 0�FP24��MTIOC4A-A�[�q�Ƃ��đI�� P25��MTIOC4C-A�[�q�Ƃ��đI��
										// 1�FP82��MTIOC4A-B�[�q�Ƃ��đI�� P83��MTIOC4C-B�[�q�Ƃ��đI��
	IOPORT.PFCMTU.BIT.MTUS5 = 1;		// 0�FP30��MTIOC4B-A�[�q�Ƃ��đI�� P31��MTIOC4D-A�[�q�Ƃ��đI��
										// 1�FP54��MTIOC4B-B�[�q�Ƃ��đI�� P55��MTIOC4D-B�[�q�Ƃ��đI��
	
/*	
	PFC.PECRL4.BIT.PE12MD = 1;	//�|�[�gE12��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B12    = 1;  //�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL4.BIT.PE14MD= 1;	//�|�[�gE14��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B14   = 1;  	//�o�̓|�[�g�ɐݒ�
*/	
	MTUA.TSTR.BIT.CST4 = 1;     //MTU4�J�E���g�X�^�[�g
	
	/*************�`�����l��4 PWM���[�h1�ݒ�I��***************/
}

/********************************************************/
//  ���O      
//		anti_lock_pwm
//  �T�v
// 		MOTOR�֐�
//  �@�\����
//		���[�^�̃A���`���b�N��PWM���R���g���[������
//  �p�����^����
//		�Ȃ�
//	���ӎ���
//		THRESHOLD/UP_LIMIT/DOWN_LIMIT�̊m�F
//		THRESHOLD/UP_LIMIT/DOWN_LIMIT��pwm.h�Őݒ肵�Ă���
//  �߂�l
//		pwm		MTU2���W�X�^�Ɋi�[����l
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int anti_lock_pwm(double duty)
{	
	int pwm;	
		
	if(duty > 0.0)
	{
		pwm = ANTI_THRESHOLD + ( (ANTI_UP_LIMIT - ANTI_THRESHOLD) * duty ) / 100; 		//duty�̐ݒ� PWM
		
		if(pwm >= ANTI_UP_LIMIT){pwm = ANTI_UP_LIMIT;}		//���ł�				
	}	
	else if(duty < 0.0)
	{
		pwm = ANTI_THRESHOLD + ( (ANTI_THRESHOLD - ANTI_DOWN_LIMIT) * duty ) / 100;	//duty�̐ݒ� PWM
		
		if(pwm <= ANTI_DOWN_LIMIT){pwm = ANTI_DOWN_LIMIT;}	//���ł�
	}
	else 
	{		
		pwm = ANTI_THRESHOLD;	
	}
	
	return pwm;
		
}

/********************************************************/
//  ���O      
//		anti_lock_pwm
//  �T�v
// 		MOTOR�֐�
//  �@�\����
//		���[�^�̃A���`���b�N��PWM���R���g���[������
//  �p�����^����
//		�Ȃ�
//	���ӎ���
//		THRESHOLD/UP_LIMIT/DOWN_LIMIT�̊m�F
//		THRESHOLD/UP_LIMIT/DOWN_LIMIT��pwm.h�Őݒ肵�Ă���
//  �߂�l
//		pwm		MTU2���W�X�^�Ɋi�[����l
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int sign_mag_pwm(double duty)
{	
	int pwm;	
		
	if(duty > 0.0)
	{
		pwm = SIGN_THRESHOLD + ( (SIGN_UP_LIMIT - SIGN_THRESHOLD) * duty ) / 100; 		//duty�̐ݒ� PWM
		
		if(pwm >= SIGN_UP_LIMIT){pwm = SIGN_UP_LIMIT;}		//���ł�				
	}	
	else if(duty < 0.0)
	{
		pwm = SIGN_THRESHOLD + ( (SIGN_THRESHOLD - SIGN_DOWN_LIMIT) * duty ) / 100;	//duty�̐ݒ� PWM
		
		if(pwm <= SIGN_DOWN_LIMIT){pwm = SIGN_DOWN_LIMIT;}	//���ł�
	}
	else 
	{		
		pwm = SIGN_THRESHOLD;	
	}
	
	return pwm;
		
}

/********************************************************/
//  ���O      
//		servo_pwm
//  �T�v
// 		SERVO�֐�
//  �@�\����
//		�T�[�{���[�^��PWM���R���g���[������
//  �p�����^����
//		�Ȃ�
//	���ӎ���
//		SERVO_TH/SERVO_UP/SERVO_DOWN�̊m�F
//		SERVO_TH/SERVO_UP/SERVO_DOWN��pwm.h�Őݒ肵�Ă���
//  �߂�l
//		pwm		MTU2���W�X�^�Ɋi�[����l
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int servo_pwm(double range)
{	
	int pwm;	
		
	if(range > 0.0)
	{
		pwm = SERVO_TH + ( (SERVO_UP - SERVO_TH) * range ) / 100; 		//duty�̐ݒ� PWM
		
		if(pwm >= SERVO_UP){pwm = SERVO_UP;}		//���ł�				
	}	
	else if(range < 0.0)
	{
		pwm = SERVO_TH + ( (SERVO_TH - SERVO_DOWN) * range ) / 100;		//duty�̐ݒ� PWM
		
		if(pwm <= SERVO_DOWN){pwm =SERVO_DOWN;}	//���ł�
	}
	else 
	{		
		pwm = SERVO_TH;	
	}
	
	return pwm;
		
}

