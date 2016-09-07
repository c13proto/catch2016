/********************************************************/
//
//  �T�v
//      PWM�ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
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
	int dummy;					// �_�~�[�ǂݎ��̂���
		
	/*********�`�����l��0 pwm���[�h2�ݒ�J�n (�����)**********/

	MTU20.TCR.BIT.TPSC = 0;     //�N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRD�R���y�A�}�b�`��TCNT�N���A
	
	MTU2.TSYR.BYTE = 0;         // �Ɨ�����
		
	MTU20.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	
	MTU20.TGRA = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRB = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRC = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRD = CYCLE;	// �����ݒ�
			
	MTU20.TMDR.BIT.MD = 3;      // PWM���[�h2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// �|�[�gE0��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B0    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE1MD = 1;	// �|�[�gE1��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B1    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE2MD = 1;	// �|�[�gE2��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B2    = 1;  	// �o�̓|�[�g�ɐݒ�
		
	MTU2.TSTR.BIT.CST0 = 1;     // MU20�J�E���g�X�^�[�g
	
	/*********�`�����l��0 pwm���[�h2�ݒ�I�� (�����)**********/

	/*****�`�����l��3 pwm���[�h1�ݒ�J�n (���[�^�Q�A�[��)******/

	MTU2.TSTR.BIT.CST3 = 1; 	// MTU23�J�E���g��~
	
	MTU23.TCR.BIT.CCLR = 2; 	// TGRB�ŃJ�E���g�N���A;
	
	MTU23.TCR.BIT.TPSC = 0; 	// �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	// �����オ��G�b�W�ŃJ�E���g
	
	MTU23.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOB = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU23.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOD = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU23.TGRA = THRESHOLD;		// TIOC3A�R���y�A�}�b�`
	MTU23.TGRB = CYCLE;			// TIOC3B�R���y�A�}�b�`
	MTU23.TGRC = THRESHOLD;		// TIOC3C�R���y�A�}�b�`
	MTU23.TGRD = CYCLE;			// TIOC3D�R���y�A�}�b�`
	
	MTU23.TMDR.BIT.MD = 2;		// PWM1���[�h
	
	PFC.PECRL3.BIT.PE8MD = 1;	// �|�[�gE8��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B8    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL3.BIT.PE10MD= 1;	// �|�[�gE10��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B10   = 1;  	// �o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST3 = 1;     // MU23�J�E���g�X�^�[�g
	
	/*****�`�����l��3 pwm���[�h1�ݒ芮�� (���[�^�Q�����)******/

	/*************�`�����l��4 PWM���[�h1�ݒ�J�n(�T�[�{)***************/

	MTU2.TSTR.BIT.CST4 = 1; 	//MTU24�J�E���g��~
	
	MTU24.TCR.BIT.CCLR = 2; 	//TGRB�ŃJ�E���g�N���A;
	
	MTU24.TCR.BIT.TPSC = 2; 	//�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	//�����オ��G�b�W�ŃJ�E���g
	
	MTU24.TIOR.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOB = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU24.TIOR.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOD = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU24.TGRA = SERVO_TH;		//TIOC4A�R���y�A�}�b�`
	MTU24.TGRB = SERVO_CYCLE;	//TIOC4B�R���y�A�}�b�`
	MTU24.TGRC = SERVO_TH;		//TIOC4C�R���y�A�}�b�`
	MTU24.TGRD = SERVO_CYCLE;	//TIOC4D�R���y�A�}�b�`
	
	MTU24.TMDR.BIT.MD = 2;		//PWM1���[�h
	
	MTU2.TOER.BIT.OE4A = 1; 	//ch4�����K�{!�I�I
	MTU2.TOER.BIT.OE4B = 1;
	MTU2.TOER.BIT.OE4C = 1;
	MTU2.TOER.BIT.OE4D = 1;
	
								// �����ݒ�ł�POE���[�h�ɂȂ��Ă��邽��
								// PB16�ɂȂɂ���ڑ������PWM�g�`���łȂ��Ȃ�B
	PFC.PBIORH.BIT.B16    = 1;  // ���o�̓|�[�g�ɐݒ�
								// IO�̏����ݒ��������POE�t���O�������Ă��܂�����
								// �N���A���Ȃ���΂Ȃ�Ȃ�	
	dummy = POE.ICSR1.BIT.POE3F;// �_�~�[�ǂݎ��
	POE.ICSR1.BIT.POE3F = 0; 	// �t���O�N���A
	
	PFC.PECRL4.BIT.PE12MD = 1;	//�|�[�gE12��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B12    = 1;  //�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL4.BIT.PE14MD= 1;	//�|�[�gE14��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B14   = 1;  	//�o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST4 = 1;     //MU24�J�E���g�X�^�[�g
	
	/*************�`�����l��4 PWM���[�h1�ݒ�I��***************/
}

#if 0
/********************************************************/
//  ���O      
//		motor_pwm_init
//  �T�v
// 		PWM�֐�
//  �@�\����
//		MOTOR_PWM�̏�����
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
void motor_pwm_init(void)
{
	int dummy;					// �_�~�[�ǂݎ��̂���
	
	/*************�`�����l��0 pwm���[�h2�ݒ�J�n***************/
	
	MTU20.TCR.BIT.TPSC = 0;     // �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRD�R���y�A�}�b�`��TCNT�N���A
	
	MTU2.TSYR.BYTE = 0;         // �Ɨ�����
	
	MTU20.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	
	MTU20.TGRA = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRB = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRC = THRESHOLD;		// �f���[�e�B�ݒ�
	MTU20.TGRD = CYCLE;			// �����ݒ�
	
	MTU20.TMDR.BIT.MD = 3;      // PWM���[�h2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// �|�[�gE0��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B0    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE1MD = 1;	// �|�[�gE1��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B1    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE2MD = 1;	// �|�[�gE2��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B2    = 1;  	// �o�̓|�[�g�ɐݒ�
		
	MTU2.TSTR.BIT.CST0 = 1;     // MU20�J�E���g�X�^�[�g
	
	/*************�`�����l��0 pwm���[�h2�ݒ�I��*************/

	/*************�`�����l��3 PWM���[�h1�ݒ�J�n***************/

	MTU2.TSTR.BIT.CST3 = 1; 	// MTU23�J�E���g��~
	
	MTU23.TCR.BIT.CCLR = 2; 	// TGRB�ŃJ�E���g�N���A;
	
	MTU23.TCR.BIT.TPSC = 0; 	// �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	// �����オ��G�b�W�ŃJ�E���g
	
	MTU23.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOB = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU23.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOD = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU23.TGRA = THRESHOLD;		// TIOC3A�R���y�A�}�b�`
	MTU23.TGRB = CYCLE;			// TIOC3B�R���y�A�}�b�`
	MTU23.TGRC = THRESHOLD;		// TIOC3C�R���y�A�}�b�`
	MTU23.TGRD = CYCLE;			// TIOC3D�R���y�A�}�b�`
	
	MTU23.TMDR.BIT.MD = 2;		// PWM1���[�h
	
	PFC.PECRL3.BIT.PE8MD = 1;	// �|�[�gE8��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B8    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL3.BIT.PE10MD= 1;	// �|�[�gE10��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B10   = 1;  	// �o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST3 = 1;     // MU23�J�E���g�X�^�[�g
	
	/*************�`�����l��3 PWM���[�h1�ݒ�I��***************/

	/*************�`�����l��4 PWM���[�h1�ݒ�J�n***************/

	MTU2.TSTR.BIT.CST4 = 1; 	// MTU24�J�E���g��~
	
	MTU24.TCR.BIT.CCLR = 2; 	// TGRB�ŃJ�E���g�N���A;
	
	MTU24.TCR.BIT.TPSC = 0; 	// �N���b�N���g����/1 (MTU�̃N���b�N��25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	// �����オ��G�b�W�ŃJ�E���g
	
	MTU24.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOB = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU24.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOD = 1;     // ������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU24.TGRA = THRESHOLD;		// TIOC4A�R���y�A�}�b�`
	MTU24.TGRB = CYCLE;			// TIOC4B�R���y�A�}�b�`
	MTU24.TGRC = THRESHOLD;		// TIOC4C�R���y�A�}�b�`
	MTU24.TGRD = CYCLE;			// TIOC4D�R���y�A�}�b�`
	
	MTU24.TMDR.BIT.MD = 2;		// PWM1���[�h
	
								// ch4�����K�{!�I�I 
	MTU2.TOER.BIT.OE4A = 1; 	// FTIO4A��MTU2���������
	MTU2.TOER.BIT.OE4B = 1;		// FTIO4B��MTU2���������
	MTU2.TOER.BIT.OE4C = 1;		// FTIO4C��MTU2���������
	MTU2.TOER.BIT.OE4D = 1;		// FTIO4D��MTU2���������
	
								// �����ݒ�ł�POE���[�h�ɂȂ��Ă��邽��
								// PB16�ɂȂɂ���ڑ������PWM�g�`���łȂ��Ȃ�B
	PFC.PBIORH.BIT.B16    = 1;  // ���o�̓|�[�g�ɐݒ�
								// IO�̏����ݒ��������POE�t���O�������Ă��܂�����
								// �N���A���Ȃ���΂Ȃ�Ȃ�	
	dummy = POE.ICSR1.BIT.POE3F;// �_�~�[�ǂݎ��
	POE.ICSR1.BIT.POE3F = 0; 	// �t���O�N���A
	
	PFC.PECRL4.BIT.PE12MD = 1;	// �|�[�gE12��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B12    = 1;  // �o�̓|�[�g�ɐݒ�
	PE.DRL.BIT.B12 = 1;
	
	PFC.PECRL4.BIT.PE14MD= 1;	// �|�[�gE14��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B14   = 1;  	// �o�̓|�[�g�ɐݒ�
	PE.DRL.BIT.B14 = 1;
	
	MTU2.TSTR.BIT.CST4 = 1;     // MU24�J�E���g�X�^�[�g
	
	/*************�`�����l��4 PWM���[�h1�ݒ�I��***************/

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
	int dummy;					// �_�~�[�ǂݎ��̂���
			
	/*************�`�����l��0 pwm���[�h2�ݒ�J�n***************/
	
	MTU20.TCR.BIT.TPSC = 2;     //�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU20.TCR.BIT.CCLR = 6;     // TGRD�R���y�A�}�b�`��TCNT�N���A
	
	MTU2.TSYR.BYTE = 0;         // �Ɨ�����
		
	MTU20.TIOR.BIT.IOA = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOB = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU20.TIOR.BIT.IOC = 2;     // ������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	
	MTU20.TGRA = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRB = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRC = SERVO_TH;		// �f���[�e�B�ݒ�
	MTU20.TGRD = SERVO_CYCLE;	// �����ݒ�
			
	MTU20.TMDR.BIT.MD = 3;      // PWM���[�h2
	
	PFC.PECRL1.BIT.PE0MD = 1;	// �|�[�gE0��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B0    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE1MD = 1;	// �|�[�gE1��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B1    = 1;  	// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL1.BIT.PE2MD = 1;	// �|�[�gE2��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B2    = 1;  	// �o�̓|�[�g�ɐݒ�
		
/*	PFC.PECRL1.BIT.PE3MD = 1;	// �|�[�gE3��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B3    = 1;  	// �o�̓|�[�g�ɐݒ�

	PFC.PECRL1.BIT.PE4MD = 1;	// �|�[�gE4��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B4    = 1;  	// �o�̓|�[�g�ɐݒ�

	PFC.PECRL1.BIT.PE5MD = 1;	// �|�[�gE5��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B5    = 1;  	// �o�̓|�[�g�ɐݒ�

	PFC.PECRL1.BIT.PE6MD = 1;	// �|�[�gE6��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B6    = 1;  	// �o�̓|�[�g�ɐݒ�

	PFC.PECRL1.BIT.PE7MD = 1;	// �|�[�gE7��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B7    = 1;  	// �o�̓|�[�g�ɐݒ�
*/
	MTU2.TSTR.BIT.CST0 = 1;     // MU20�J�E���g�X�^�[�g
	
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

	/*************�`�����l��3 PWM���[�h1�ݒ�J�n***************/

	MTU2.TSTR.BIT.CST3 = 1; 	//MTU23�J�E���g��~
	
	MTU23.TCR.BIT.CCLR = 2; 	//TGRB�ŃJ�E���g�N���A;
	
	MTU23.TCR.BIT.TPSC = 2; 	//�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU23.TCR.BIT.CKEG = 0; 	//�����オ��G�b�W�ŃJ�E���g
	
	MTU23.TIOR.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOB = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU23.TIOR.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU23.TIOR.BIT.IOD = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU23.TGRA = SERVO_TH;		//TIOC3A�R���y�A�}�b�`
	MTU23.TGRB = SERVO_CYCLE;	//TIOC3B�R���y�A�}�b�`
	MTU23.TGRC = SERVO_TH;		//TIOC3C�R���y�A�}�b�`
	MTU23.TGRD = SERVO_CYCLE;	//TIOC3D�R���y�A�}�b�`
	
	MTU23.TMDR.BIT.MD = 2;		//PWM1���[�h
	
	PFC.PECRL3.BIT.PE8MD = 1;	//�|�[�gE8��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B8    = 1;  	//�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL3.BIT.PE10MD= 1;	//�|�[�gE10��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B10   = 1;  	//�o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST3 = 1;     //MU23�J�E���g�X�^�[�g
	
	/*************�`�����l��3 PWM���[�h1�ݒ�I��***************/

	/*************�`�����l��4 PWM���[�h1�ݒ�J�n***************/

	MTU2.TSTR.BIT.CST4 = 1; 	//MTU24�J�E���g��~
	
	MTU24.TCR.BIT.CCLR = 2; 	//TGRB�ŃJ�E���g�N���A;
	
	MTU24.TCR.BIT.TPSC = 2; 	//�N���b�N���g����/16 (MTU�̃N���b�N��25Mhz)
	
	MTU24.TCR.BIT.CKEG = 0; 	//�����オ��G�b�W�ŃJ�E���g
	
	MTU24.TIOR.BIT.IOA = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOB = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	MTU24.TIOR.BIT.IOC = 2;     //������Ԃ�0�o�� �R���y�A�}�b�`������1�o��
	MTU24.TIOR.BIT.IOD = 1;     //������Ԃ�0�o�� �R���y�A�}�b�`������0�o��
	
	MTU24.TGRA = SERVO_TH;		//TIOC4A�R���y�A�}�b�`
	MTU24.TGRB = SERVO_CYCLE;	//TIOC4B�R���y�A�}�b�`
	MTU24.TGRC = SERVO_TH;		//TIOC4C�R���y�A�}�b�`
	MTU24.TGRD = SERVO_CYCLE;	//TIOC4D�R���y�A�}�b�`
	
	MTU24.TMDR.BIT.MD = 2;		//PWM1���[�h
	
	MTU2.TOER.BIT.OE4A = 1; 	//ch4�����K�{!�I�I
	MTU2.TOER.BIT.OE4B = 1;
	MTU2.TOER.BIT.OE4C = 1;
	MTU2.TOER.BIT.OE4D = 1;
	
								// �����ݒ�ł�POE���[�h�ɂȂ��Ă��邽��
								// PB16�ɂȂɂ���ڑ������PWM�g�`���łȂ��Ȃ�B
	PFC.PBIORH.BIT.B16    = 1;  // ���o�̓|�[�g�ɐݒ�
								// IO�̏����ݒ��������POE�t���O�������Ă��܂�����
								// �N���A���Ȃ���΂Ȃ�Ȃ�	
	dummy = POE.ICSR1.BIT.POE3F;// �_�~�[�ǂݎ��
	POE.ICSR1.BIT.POE3F = 0; 	// �t���O�N���A
	
	PFC.PECRL4.BIT.PE12MD = 1;	//�|�[�gE12��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B12    = 1;  //�o�̓|�[�g�ɐݒ�
	
	PFC.PECRL4.BIT.PE14MD= 1;	//�|�[�gE14��MTU2�ɐݒ�
	PFC.PEIORL.BIT.B14   = 1;  	//�o�̓|�[�g�ɐݒ�
	
	MTU2.TSTR.BIT.CST4 = 1;     //MU24�J�E���g�X�^�[�g
	
	/*************�`�����l��4 PWM���[�h1�ݒ�I��***************/
}
#endif
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
		pwm = THRESHOLD + ( (UP_LIMIT - THRESHOLD) * duty ) / 100; 		//duty�̐ݒ� PWM
		
		if(pwm >= UP_LIMIT){pwm = UP_LIMIT;}		//���ł�				
	}	
	else if(duty < 0.0)
	{
		pwm = THRESHOLD + ( (THRESHOLD - DOWN_LIMIT) * duty ) / 100;	//duty�̐ݒ� PWM
		
		if(pwm <= DOWN_LIMIT){pwm = DOWN_LIMIT;}	//���ł�
	}
	else 
	{		
		pwm = THRESHOLD;	
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

