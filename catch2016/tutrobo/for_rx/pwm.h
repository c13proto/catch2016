/********************************************************/
//
//  �T�v
//      PWM�ݒ�
//  �쐬��
//		@ TUTrobo
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
void motor_pwm_init(void);		// MOTOR_PWM�̏�����
void servo_pwm_init(void);		// SORVO_PWM�̏�����
int anti_lock_pwm(double duty);	// ���[�^�̃A���`���b�N��PWM���R���g���[������
int servo_pwm(double range);	// �T�[�{��PWM���R���g���[������

/********************************************************/
//  TUTrobo
//
//  �T�v
//      PWM�ݒ� PWM�l��`
/********************************************************/

/************** PWM�ݒ� PWM�l��` ��������***************/
/************** PWM�ݒ� PWM�l��` ��������***************/

	/******���� 60[kHz]  MAXduty 100[%] �̐ݒ�J�n*******/
		
	#define ANTI_CYCLE		2400//800		// �����ݒ�  cycle=48000k/60k
	#define ANTI_UP_LIMIT 	2399//799		// MAX�J�E���g�l 	�������1�������̂�PWMMAX�l��1249������
	#define ANTI_DOWN_LIMIT	1			// MIN�J�E���g�l	
	#define ANTI_THRESHOLD 	1200//400			// THRESHOLD�J�E���g�l
	
	/******���� 60[kHz]  MAXduty 100[%] �̐ݒ�I��*******/

	/******���� 20[kHz]  MAXduty 100[%] �̐ݒ�J�n*******/
	
	#define SIGN_CYCLE		2400		// �����ݒ�  cycle=48000k/20k
	#define SIGN_UP_LIMIT 	2399		// MAX�J�E���g�l 	�������1�������̂�PWMMAX�l��1249������
	#define SIGN_DOWN_LIMIT	1			// MIN�J�E���g�l	
	#define SIGN_THRESHOLD 	1200			// THRESHOLD�J�E���g�l
	
	/******���� 20[kHz]  MAXduty 100[%] �̐ݒ�I��*******/
	//////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////
	/********���� 50[Hz]  �T�[�{PWM �̐ݒ�J�n*********/
	#define SERVO_CYCLE	60000//31250		// �����ݒ�			
	#define SERVO_UP 	7000//3340		// MAX�J�E���g�l 	
	#define SERVO_DOWN	500//1200		// MIN�J�E���g�l	
	#define SERVO_TH 	3250//2270		// THRESHOLD�J�E���g�l
	/********���� 50[Hz]  �T�[�{PWM �̐ݒ�I��*********/

#endif // __PWM_H__