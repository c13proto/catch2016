/********************************************************/
//
//  �T�v
//      �|�[�g�֘A
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�

/********************************************************/
//  ���O      
//		power_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�E�G�A�[�̓d�������p�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void power_init(void)
{
	
	PFC.PACRL3.BIT.PA11MD = 0; // ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B11 = 1;    // �o�̓|�[�g�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		buzzer_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		BUZZER�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_init(void)
{
	
	PFC.PECRL4.BIT.PE15MD = 0; // ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B15 = 1;    // �o�̓|�[�g�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		led_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		LED�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_init(void)
{
	
	PFC.PECRL1.BIT.PE3MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B3 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE4MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B4 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE5MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B5 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE6MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B6 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL2.BIT.PE7MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B7 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL3.BIT.PE9MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B9 = 1;		// �o�̓|�[�g�ɐݒ�
	
	PFC.PECRL3.BIT.PE11MD = 0;	// ���o�͂ɐݒ�
	PFC.PEIORL.BIT.B11 = 1;		// �o�̓|�[�g�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		mode_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�h�I���̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void mode_init(void)
{
	
	PFC.PBCRH1.BIT.PB16MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORH.BIT.B16 = 0;		// ���̓|�[�g�ɐݒ�	
		
}

/********************************************************/
//  ���O      
//		button_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		�{�^���̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void button_init(void)
{
	
	PFC.PACRL3.BIT.PA10MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B10 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PACRL3.BIT.PA11MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B11 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PACRL4.BIT.PA12MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B12 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PACRL4.BIT.PA13MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B13 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PACRL4.BIT.PA14MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B14 = 0;		// ���̓|�[�g�ɐݒ�	
}

/********************************************************/
//  ���O      
//		limit_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		LIMIT�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void limit_init(void)
{
	
	PFC.PACRL4.BIT.PA14MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B14 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PACRL4.BIT.PA15MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B15 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PBCRL1.BIT.PB1MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B1 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PBCRL1.BIT.PB2MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B2 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PBCRL1.BIT.PB3MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B3 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PBCRL2.BIT.PB5MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B5 = 0;		// ���̓|�[�g�ɐݒ�




/*	PFC.PACRL4.BIT.PA15MD = 0;	// ���o�͂ɐݒ�
	PFC.PAIORL.BIT.B15 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PBCRL1.BIT.PB1MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B1 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PBCRL1.BIT.PB2MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B2 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PBCRL1.BIT.PB3MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B3 = 0;		// ���̓|�[�g�ɐݒ�

	PFC.PBCRL2.BIT.PB5MD = 0;	// ���o�͂ɐݒ�
	PFC.PBIORL.BIT.B5 = 0;		// ���̓|�[�g�ɐݒ�
	
	PFC.PBIORH.BIT.B16 = 1;  	// ���o�̓|�[�g�ɐݒ�
	PFC.PBIORH.BIT.B16 = 0;		// ���̓|�[�g�ɐݒ�	
*/
}

/********************************************************/
//  ���O      
//		io_init
//  �T�v
// 		IO�֐�
//  �@�\����
//		PIN�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void io_init(void)
{
/***********************MTU2�֘A*************************/

	MTU2_init();		// MTU2�̃X�^���o�C����
	pwm_init();			// PWM�̏�����
//	motor_pwm_init();	// MOTOR_PWM�̏�����
//	servo_pwm_init();	// SORVO_PWM�̏�����
	enc_init();			// �G���R�[�_�̏����ݒ�

/********************************************************/

/*********************IO�|�[�g�o��***********************/	

//	power_init();		// ���[�^�E�G�A�[�̓d�������p�̏����ݒ�
//	buzzer_init();		// BUZZER�̏����ݒ�	
	led_init();			// LED�̏����ݒ�(�o�̓s�������˂�)
	
/********************************************************/
	
/*********************IO�|�[�g����***********************/
	
	mode_init();		// ���[�h�I���̏����ݒ�
//	button_init();		// �{�^���̏����ݒ�
	limit_init();		// LIMIT�̏����ݒ�
	
/********************************************************/
		
}

/********************************************************/
//  ���O      
//		led_on
//  �T�v
// 		IO�֐�
//  �@�\����
//		LED��ON�ɂ���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_on(void)
{
	
	PE.DRL.BIT.B3 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B4 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B5 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B6 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B7 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B9 = 1;		// 5V�ɐݒ�
	PE.DRL.BIT.B11 = 1;		// 5V�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		led_off
//  �T�v
// 		IO�֐�
//  �@�\����
//		LED��OFF�ɂ���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_off(void)
{
	
	PE.DRL.BIT.B3 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B4 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B5 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B6 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B7 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B9 = 0;		// 0V�ɐݒ�
	PE.DRL.BIT.B11 = 0;		// 0V�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		led_ctrl
//  �T�v
// 		IO�֐�
//  �@�\����
//		LED�̓_�������R���g���[������
//  �p�����^����
//		number			number�ɉ�����led�̌�������ς��
//						�u0�`31�v�܂őI����
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void led_ctrl(char number)
{
	char dec;		// 10�i���i�[�p
	char bin[5];	// 2�i���i�[�p
	char loop;		// for���̂��߂̌^
	
	dec = number;	// �������i�[	
	
	for(loop = 0; loop < 5; loop++)
	{
		bin[loop] = dec % 2;
		dec = dec / 2;
	}
		
	PE.DRL.BIT.B7 = bin[0];		// 1bit
	PE.DRL.BIT.B6 = bin[1];		// 2bit
	PE.DRL.BIT.B5 = bin[2];		// 3bit
	PE.DRL.BIT.B4 = bin[3];		// 4bit
	PE.DRL.BIT.B3 = bin[4];		// 5bit
		
}

/********************************************************/
//  ���O      
//		mode
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�h�I��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		flag		'B':�]�[��
//					'R':�ԃ]�[��
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char mode(void)
{
	char flag = 0;
	
	if(PB.DR.BIT.B16  == 0)
	{
		flag = 'B';
	}
	else if(PB.DR.BIT.B16 == 1)	
	{
		flag = 'R';
	}
	
	return flag;
}



/*------------------------------------------------------*/
// �I���W�i���֐�


/********************************************************/
//  ���O      
//		motor_o
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�֐�
//  �p�����^����
//		raw_duty	�f���e�B�[���͒l
//		duty		�f���e�B�[���������p
//		pwm			MTU2���W�X�^�Ɋi�[����l	
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		pwm�o�͂Ȃ̂ŁAio_init��motor_control_pwm_init�ōs�Ȃ��Ă���
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_o(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = -raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
//	MTU23.TGRA = pwm;		
	O_PWM =pwm;
}

/********************************************************/
//  ���O      
//		motor_l
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�֐�
//  �p�����^����
//		raw_duty	�f���e�B�[���͒l
//		duty		�f���e�B�[���������p
//		pwm			MTU2���W�X�^�Ɋi�[����l	
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		pwm�o�͂Ȃ̂ŁAio_init��motor_control_pwm_init�ōs�Ȃ��Ă���
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_l(double raw_duty)
{
	double duty;
	int pwm;
	
	duty = raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
//	MTU23.TGRC = pwm;		
	L_PWM = pwm;	
}

/********************************************************/
//  ���O      
//		motor_r
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�֐�
//  �p�����^����
//		raw_duty	�f���e�B�[���͒l
//		duty		�f���e�B�[���������p
//		pwm			MTU2���W�X�^�Ɋi�[����l	
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		pwm�o�͂Ȃ̂ŁAio_init��motor_control_pwm_init�ōs�Ȃ��Ă���
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_r(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = -raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
//	MTU24.TGRA = pwm;		
	R_PWM = pwm;	
}


/********************************************************/
//  ���O      
//		motor_fish
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�֐�(�ފƃn���h)
//  �p�����^����
//		raw_duty	�f���e�B�[���͒l
//		duty		�f���e�B�[���������p
//		pwm			MTU2���W�X�^�Ɋi�[����l	
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		pwm�o�͂Ȃ̂ŁAio_init��motor_control_pwm_init�ōs�Ȃ��Ă���
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_fish(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
	FISH_PWM = pwm;				//���W�X�^�ɒl���i�[(3C����o��)
}

/********************************************************/
//  ���O      
//		motor_L_arm
//  �T�v
// 		IO�֐�
//  �@�\����
//		���[�^�֐�(L�A�[��)
//  �p�����^����
//		raw_duty	�f���e�B�[���͒l
//		duty		�f���e�B�[���������p
//		pwm			MTU2���W�X�^�Ɋi�[����l	
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		pwm�o�͂Ȃ̂ŁAio_init��motor_control_pwm_init�ōs�Ȃ��Ă���
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void motor_L_arm(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
//	MTU20.TGRC = pwm;			//���W�X�^�ɒl���i�[(2B����o��)
	L_ARM_PWM = pwm;			//���W�X�^�ɒl���i�[(3A����o��)

}


//���g�p�֐�
#if 0 
/********************************************************/
//  ���O      
//		power_on
//  �T�v
// 		POWER�֐�
//  �@�\����
//		�d���������s��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void  power_on(void)
{	
	PE.DRL.BIT.B3 = 1;	 //5V�ɐݒ�		
}


/********************************************************/
//  ���O      
//		power_off
//  �T�v
// 		POWER�֐�
//  �@�\����
//		�d���������s��Ȃ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void power_off(void)
{	
	PE.DRL.BIT.B3 = 0;	 //0V�ɐݒ�		
}

/********************************************************/
//  ���O      
//		buzzer_on
//  �T�v
// 		BUZZER�֐�
//  �@�\����
//		BUZZER��ON�ɂ���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_on(void)
{
	
	PE.DRL.BIT.B15 = 1;	 // 5V�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		buzzer_off
//  �T�v
// 		BUZZER�֐�
//  �@�\����
//		BUZZER��OFF�ɂ���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void buzzer_off(void)
{
	
	PE.DRL.BIT.B15 = 0;	 // 0V�ɐݒ�
		
}

/********************************************************/
//  ���O      
//		button
//  �T�v
// 		IO�֐�
//  �@�\����
//		�{�^���F��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		flag		�E�̃{�^������2�i���ŕ\��
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char button(void)
{
	char flag = 0;
	
	if(PA.DRL.BIT.B10 == 1){flag += 1;}
	if(PA.DRL.BIT.B11 == 1){flag += 2;}
	if(PA.DRL.BIT.B12 == 1){flag += 4;}
	if(PA.DRL.BIT.B13 == 1){flag += 8;}
	if(PA.DRL.BIT.B14 == 1){flag += 16;}
	
	return flag;
}/********************************************************/
//  ���O      
//		limit
//  �T�v
// 		IO�֐�
//  �@�\����
//		���~�b�g�F��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		flag		�E�̃{�^������2�i���ŕ\��
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char limit(void)
{
	char flag = 0;
	
	if(PA.DRL.BIT.B15 == 1){flag += 1;}
	if(PB.DR.BIT.B1   == 1){flag += 2;}
	if(PB.DR.BIT.B2   == 1){flag += 4;}
	if(PB.DR.BIT.B3   == 1){flag += 8;}
	if(PB.DR.BIT.B5   == 1){flag += 16;}
	if(PB.DR.BIT.B16  == 1){flag += 32;}
	
	return flag;
}

/********************************************************/
//  ���O      
//		leaf_collect_hand
//  �T�v
// 		IO�֐�
//  �@�\����
//		AIR�֐�(���[�t����n���h)
//  �p�����^����
//		state		�G�A�[�̏��
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void leaf_collect_hand(char state)
{
	if(state == OPEN)	PE.DRL.BIT.B7 = 1;
	else				PE.DRL.BIT.B7 = 0;	
}

/********************************************************/
//  ���O      
//		leaf_esta_hand
//  �T�v
// 		IO�֐�
//  �@�\����
//		AIR�֐�(���[�t�ݒu�n���h)
//  �p�����^����
//		state		�G�A�[�̏��
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void leaf_esta_hand(char state)
{
	if(state == OPEN)	PE.DRL.BIT.B6 = 1;
	else				PE.DRL.BIT.B6 = 0;	
}
#endif