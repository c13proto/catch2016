/********************************************************/
//
//  �T�v
//      ���ʂ̐ݒ莖��
//  �쐬��
//		TUTrobo
//
/********************************************************/

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���ʂ̐ݒ莖�� �}�V���I��
/********************************************************/
#define MACHINE_NAME	HIMAWARI

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���ʂ̐ݒ莖�� �}�V���p�����[�^
/********************************************************/
#if		MACHINE_NAME ==	HIMAWARI

/*�}�V���ɍ��킹�Đݒ肱������*/
#define	ENCODER_RC_L		macorrec.ENCODER_RC_L							// ���̃G���R�[�_�̕␳�l
#define ENCODER_RC_R		macorrec.ENCODER_RC_R							// �E�̃G���R�[�_�̕␳�l
#define ENCODER_D			macorrec.ENCODER_D 								// �G���R�[�_�[�^�C�����a
#define	ENCODER_D_L			macorrec.ENCODER_D_L							// ���G���R�[�_�[�^�C�����a
#define	ENCODER_D_R			macorrec.ENCODER_D_R							// �E�G���R�[�_�[�^�C�����a
#define ENCODER_T			macorrec.ENCODER_T								// �G���R�[�_�[�g���b�h
#define TMP					( (2.0 * ENCODER_T * ENCODER_RES) / ENCODER_D )	// �Е��̃G���R�[�_�𒆐S�ɂ������Ɉ��]�������̃G���R�[�_�̃p���X��

#define	ENCODER_D_X			omni_macorrec.ENCODER_D_X							// X�G���R�[�_�[�^�C�����a
#define	ENCODER_D_Y			omni_macorrec.ENCODER_D_Y							// Y�G���R�[�_�[�^�C�����a



#define	TIRE_R_L			170.0 				// A�^�C�����a
#define	TIRE_R_R			170.0 				// B�^�C�����a
#define	TIRE_R				170.0				// �^�C�����a
#define	TIRE_T				632.0 				// �^�C���g���b�h

#define MAX_DUTY			100.0				// PWM��MAX�l
#define MIN_DUTY			10.0				// PWM��MIN�l

#define A_LIMIT				100.0				// ���x�ω����� [mm/(���荞�ݎ��Ԃ�����)^2]

#define DIFF_LIMIT			50.0				// ���Eduty��������

#define DIFF_OVER_K			0.1					// ???

#define MOTOR_rpm			300					// ���[�^�̒�i��]��(r/min)(�M�A�w�b�h���܂�)
#define MOTOR_rating		24	  				// ���[�^�̒�i�d��(V)
#define BATTERY_rating		7.7					// �o�b�e���[�̓d��
#define BATTERY				3					// �g�p�o�b�e���[�̐�

#define MAX_SPEED			2500.0				// �ō����x [mm/s]
	
//#define ENCODER_RES			800					// 1��]������̃G���R�[�_�p���X��
//#define ENCODER_RES			3200			// 1��]������̃G���R�[�_�p���X��
#define ENCODER_RES			2000			// 1��]������̃G���R�[�_�p���X��
/*�}�V���ɍ��킹�Đݒ肱���܂�*/

#endif

#ifndef __COMMON_H__
#define __COMMON_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���ʂ̐ݒ莖�� �X�P�W���[���ݒ�
/********************************************************/
#define FEEDBACK_INTERVAL		10				// �t�B�[�h�o�b�N�^�C�}����[ms]

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���ʂ̐ݒ莖�� 	�v�Z�̂Ƃ��̋ߎ��l�ݒ�
/********************************************************/
#define LIMIT_ZERO				0.0000001		// �v�Z����0����
#define LIMIT_INF				1000000.0		// �v�Z����Inf����
#define LIMIT_INF_OVER			1000001.0		// �v�Z����Inf���������l

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���ʂ̐ݒ莖�� �O���[�o���ϐ��ݒ�
/********************************************************/
extern struct machine_condition macond;			// �}�V���R���f�B�V����				
extern struct correction_value  macorrec;		// �}�V���̕␳�l
extern struct omni_correction_value omni_macorrec;//�}�V���̕␳�l(omni)
extern struct gyro_condition gcond;				// �W���C���̃R���f�B�V����
/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���荞�݊֘A �O���[�o���ϐ��ݒ�
/********************************************************/
extern volatile char automatic_mode_flag;		// �������s���邩�A���Ȃ���

#endif // __COMMON_H__