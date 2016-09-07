/********************************************************/
//
//  �T�v
//      PWM�ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __PWM_H__
#define __PWM_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      PWM�ݒ� �v���g�^�C�v�錾
/********************************************************/
void pwm_init(void);			// PWM�̏�����
int anti_lock_pwm(double duty);	// ���[�^�̃A���`���b�N��PWM���R���g���[������
int servo_pwm(double range);	// �T�[�{��PWM���R���g���[������

/********************************************************/
//  TUTrobo
//
//  �T�v
//      PWM�ݒ� PWM�l��`
/********************************************************/

/************** PWM�ݒ� PWM�l��` ��������***************/
	#define MOTOR_DUTY_100		// ���[�^�[MAXduty = 100
//	#define MOTOR_DUTY_90		// ���[�^�[MAXduty = 90
/************** PWM�ݒ� PWM�l��` ��������***************/

	//////////////////////////////////////////////////////	
#ifdef	MOTOR_DUTY_100
	/******���� 20[kHz]  MAXduty 100[%] �̐ݒ�J�n*******/
	
	#define CYCLE		1250		// �����ݒ�
	#define UP_LIMIT 	1249		// MAX�J�E���g�l 	�������1�������̂�PWMMAX�l��1249������
	#define DOWN_LIMIT	1			// MIN�J�E���g�l	
	#define THRESHOLD 	625			// THRESHOLD�J�E���g�l
	
	/******���� 20[kHz]  MAXduty 100[%] �̐ݒ�I��*******/
#endif
	//////////////////////////////////////////////////////
#ifdef	MOTOR_DUTY_90	
	/******���� 20[kHz]  MAXduty 90[%] �̐ݒ�J�n*******/
	
	#define CYCLE		1250		// �����ݒ�
	#define UP_LIMIT 	1125		// MAX�J�E���g�l 	�������1�������̂�PWMMAX�l��1249������
	#define DOWN_LIMIT	125			// MIN�J�E���g�l	
	#define THRESHOLD 	625			// THRESHOLD�J�E���g�l
	
	/********���� 20[kHz]  MAXduty 90[%] �̐ݒ�I��*********/
#endif
	//////////////////////////////////////////////////////
	/********���� 50[Hz]  �T�[�{PWM �̐ݒ�J�n*********/
	#define SERVO_CYCLE	31250		// �����ݒ�			
	#define SERVO_UP 	3340		// MAX�J�E���g�l 	
	#define SERVO_DOWN	1200		// MIN�J�E���g�l	
	#define SERVO_TH 	2270		// THRESHOLD�J�E���g�l
	/********���� 50[Hz]  �T�[�{PWM �̐ݒ�I��*********/

#endif // __PWM_H__