/********************************************************/
//
//  �T�v
//      �|�[�g�֘A
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __IO_H__
#define __IO_H__


#define INPUT_PIN(port,pin) (port##.DR.BIT.B##pin)
#define INPUT_PIN_PF(pin) (PF.DRL.BIT.B##pin)
#define OUTPUT_PIN(port,pin) (port##.DRL.BIT.B##pin)

#define PWM_PIN(ch,port) (MTU2##ch##.TGR##port)


#define ON 1
#define OFF 0


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �|�[�g�֘A �v���g�^�C�v�錾
/********************************************************/
void power_init(void);							// ���[�^�E�G�A�[�̓d�������p�̏����ݒ�
void buzzer_init(void);							// BUZZER�̏����ݒ�
void led_init(void);							// LED�̏����ݒ�
void mode_init(void);							// ���[�h�I���̏����ݒ�
void button_init(void);							// �{�^���̏����ݒ�
void limit_init(void);							// LIMIT�̏����ݒ�

void front_limit_init(void);					// �}�V���̑O�̃��~�b�g�̏����ݒ�
void back_limit_init(void);						// �}�V���̌�̃��~�b�g�̏����ݒ�

void io_init(void);		 						// PIN�̏����ݒ�

//void buzzer_on(void);							// BUZZER��ON�ɂ���
//void buzzer_off(void);							// BUZZER��OFF�ɂ���

//void power_on(void);							// �d���������s��
//void power_off(void);							// �d���������s��Ȃ�

void led_on(void);								// LED��ON�ɂ���
void led_off(void);								// LED��OFF�ɂ���
void led_ctrl(char number);						// LED�̓_�������R���g���[������

char mode(void);								// ���[�h�I��

char button(void);								// �{�^���F��

char limit(void);								// ���~�b�g�F��

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �|�[�g�֘A �萔��`
/********************************************************/
#define OPEN	1
#define CLOSE	0

/*----------------------------------------------*/
void motor_o(double raw_duty);					// MOTOR_o�̐ݒ�
void motor_l(double raw_duty);					// MOTOR_l�̐ݒ�
void motor_r(double raw_duty);					// MOTOR_r�̐ݒ�
void leaf_collect_hand(char state);				// AIR�֐�(���[�t����n���h)
void leaf_esta_hand(char state);				// AIR�֐�(���[�t�ݒu�n���h)
void motor_L_arm(double raw_duty);				//L�A�[��
void motor_fish(double raw_duty);				//�ފ�
#endif // __IO_H__