/********************************************************/
//
//  �T�v
//      �|�[�g�֘A
//  ����
//		�}�C�R���ˑ��t�@�C��!!
//  �쐬��
//		K.yamada @ TUTrobo
//
/********************************************************/


#include "../setup.h"		//�}�C�R���̐ݒ�


/********************************************************/
//  ���O      
//		MTU2_init
//  �T�v
// 		SETUP�֐�
//  �@�\����
//		MTU2�̃X�^���o�C����
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void MTU2_init(void)
{
	MSTP_MTUA=0; // mtu0~5
	MSTP_MTUB=0; // mtu6~11	//�X�^���o�C����
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
	
/*********************IO�|�[�g�o��***********************/	

	SET_OUTPUT_PIN(PORTA,7);//led1
	SET_OUTPUT_PIN(PORTA,6);//led2
	SET_OUTPUT_PIN(PORTA,5);//led3
	SET_OUTPUT_PIN(PORTA,4);//led4
	SET_OUTPUT_PIN(PORTD,2);//led5
	SET_OUTPUT_PIN(PORTD,3);//led6
	SET_OUTPUT_PIN(PORTD,1);//led7
	SET_OUTPUT_PIN(PORTD,0);//led8
	SET_OUTPUT_PIN(PORTB,2);//led_red
	SET_OUTPUT_PIN(PORTB,3);//led_blue
	
	SET_OUTPUT_PIN(PORTE,4);//2pin
	SET_OUTPUT_PIN(PORTE,5);//2pin
	SET_OUTPUT_PIN(PORTE,6);//2pin
	SET_OUTPUT_PIN(PORTE,7);//2pin
	
	
/********************************************************/
	
/*********************IO�|�[�g����***********************/

	//�����v���A�b�v����
	SET_P_INPUT_PIN(PORTE,0);//limit
	SET_P_INPUT_PIN(PORTE,1);//limit
	SET_P_INPUT_PIN(PORTE,2);//limit
	SET_P_INPUT_PIN(PORTE,3);//�g�O��
	
	//�����v���A�b�v�Ȃ�
	SET_INPUT(PORTC);//�G���R�[�_
	SET_INPUT(PORT4);//AD�ϊ�
	
	
	//���g�pPIN����̓��[�h�����v���A�b�v�ɐݒ�
	SET_P_INPUT_PIN(PORTD,4);
	SET_P_INPUT_PIN(PORTD,5);
	SET_P_INPUT_PIN(PORTD,6);
	SET_P_INPUT_PIN(PORTD,7);
	SET_P_INPUT_PIN(PORTA,2);
	SET_P_INPUT_PIN(PORTB,7);
	SET_P_INPUT_PIN(PORTB,6);
	
/********************************************************/
		
/***********************MTU2�֘A*************************/
	MTU2_init();		// MTU2�̃X�^���o�C����
	
	pwm_init();			// PWM�̏�����
	enc_init();			// �G���R�[�_�̏����ݒ�

/********************************************************/

}


/********************************************************/
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
char limit(void){
	char flag = 0;	
	return flag;
}

/*------------------------------------------------------*/
// �I���W�i���֐�

#if 0
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
	
	O_PWM = pwm;		
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
	
	duty = -raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
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
	
	R_PWM = pwm;		
}

/********************************************************/
//  ���O      
//		motor_r2
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
void motor_servo(int state)
{
	SERVO_T_PWM = state;		
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
	
	duty = -raw_duty;			//���t�]����
	
	//pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	pwm = sign_mag_pwm(duty);	//�T�C���}�O�j�`���[�h�ppwm�ɕύX
	
	FISH_PWM = pwm;			//���W�X�^�ɒl���i�[(2B����o��)
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
	
//	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	pwm = sign_mag_pwm(duty);	//�T�C���}�O�j�`���[�h�ppwm�ɕύX
	
	L_ARM_PWM = pwm;			//���W�X�^�ɒl���i�[(2B����o��)
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
void motor_front_shift(double raw_duty)
{
	double	duty;
	int pwm;
	
	duty = raw_duty;			//���t�]����
	
	pwm = anti_lock_pwm(duty);	//�A���`���b�N�V�X�e���ppwm�ɕύX
	
	FRONT_SIFT_PWM = pwm;			//���W�X�^�ɒl���i�[(2B����o��)
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
	if(state == OPEN)	LEAF_COLLECT_HAND_PIN = 1;
	else				LEAF_COLLECT_HAND_PIN = 0;	
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
	if(state == OPEN)	LEAF_ESTA_HAND_PIN = 1;
	else				LEAF_ESTA_HAND_PIN = 0;	
}
#endif