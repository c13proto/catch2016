/********************************************************/
//
//  �T�v
//      �}�C�R���̐ݒ�
//  �쐬��
//		@ TUTrobo
//
/********************************************************/

#ifndef __SETUP_H__
#define __SETUP_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�C�R���̐ݒ� �ǂݍ��݃w�b�_�t�@�C���錾
/********************************************************/

#include <stdio.h>
#include <stdarg.h> 	//printf �֐��̂悤�ȉό̎������̑���Ɋւ���^�ƃ}�N���̒�`
#include <math.h>		//��ʓI�Ȑ��l���Z����ѕϊ����v�Z����֐��̃Z�b�g��錾

#include "type.h"		//�v���O�����̌^���錾
#include "table.h"
#include "../iodefine.h"	//PINdefine
#include "../typedefine.h"	//�^�̕ʖ��錾 
#include "auto.h"

#define CPU_RX621
//#define CPU_SH7125

//CPU�ʃC���N���[�h�t�@�C��
#ifdef CPU_SH7125
	#include "for_sh7125/ad.h"			//A/D�ϊ��ݒ�
	#include "for_sh7125/clock.h"		//CLOCK�ݒ�
	#include "for_sh7125/cmt.h"		//CMT�֘A
	#include "for_sh7125/io.h"			//�s���ݒ�
	#include "for_sh7125/enc.h"		//�G���R�[�_�֘A
	#include "for_sh7125/interrupt.h"	//���荞�݊֘A��`
	#include "for_sh7125/pwm.h"		//PWM�ݒ�
	#include "for_sh7125/sci.h"		//SCI�֘A�ݒ�
	#include "for_sh7125/wdt.h"		//WDT�֘A��`
#endif

#ifdef CPU_RX621
	#include "for_rx/ad.h"			//A/D�ϊ��ݒ�
	#include "for_rx/clock.h"		//CLOCK�ݒ�
	#include "for_rx/cmt.h"		//CMT�֘A
	#include "for_rx/io.h"			//�s���ݒ�
	#include "for_rx/enc.h"		//�G���R�[�_�֘A
	#include "for_rx/interrupt.h"	//���荞�݊֘A��`
	#include "for_rx/pwm.h"		//PWM�ݒ�
	#include "for_rx/sci.h"		//SCI�֘A�ݒ�
	#include "for_rx/fld.h"     //�f�[�^�t���b�V��
	#include "for_rx/wdt.h"		//WDT�֘A��`
#endif

//#include "calc.h"		//�v�Z�֘A��` �����Ɉړ��o�H�֘A
#include "macro.h"		//�v�Z�p�}�N����`

#include "common.h"		//���ʂ̐ݒ莖��
//#include "sence.h"		//�v���֘A��`�@io�̏�ʊ֐�

//#include "omuni.h"		//�I���j�֘A io�̏�ʊ֐�

#include "comu2.h"		//�ʐM�֘A��` sci�̏�ʊ֐�

//#include "control.h"	//�}�V���ړ�����֘A ����
#include "controller.h"	//�R���g���[���[�֘A �蓮�@omuni�̏�ʊ֐�

#include "cet.h"

//#include "feedback.h"	//�t�B�[�h�o�b�N�֘A��`
//#include "path.h"		// �p�X�i�R�}���h�j�ݒ�


#ifdef CPU_SH7125
/*******************************************************************/
//PIN CONFIG
/*******************************************************************/


//#define MODE_IN					INPUT_PIN(PORTE,0)
//#define L_HOLD_LIMIT 			INPUT_PIN(PORTA,1)
//#define L_UNHOLD_LIMIT 			INPUT_PIN(PORTA,0)

#define AIR_R_UNDER_LIMIT 		INPUT_PIN_PF(0)
#define AIR_R_UP_LIMIT   		INPUT_PIN_PF(1)
#define AIR_L_UNDER_LIMIT 		INPUT_PIN_PF(3)
#define AIR_L_UP_LIMIT   		INPUT_PIN_PF(2)

#define R_TOWER_UNDER_LIMIT 	INPUT_PIN(PB,1)//���[�t
#define L_TOWER_UNDER_LIMIT 	INPUT_PIN(PB,2)//���[�t
#define SERVO_LIMIT				INPUT_PIN(PB,3)

/*//�ȑO�̔z�u
#define FRONT_SIFT_PWM		    PWM_PIN(0,B)//MTU20.TGRB
#define L_ARM_PWM               PWM_PIN(0,C)//MTU20.TGRC
#define FISH_PWM				PWM_PIN(0,A)//MTU20.TGRA
#define O_PWM					PWM_PIN(3,A)//MTU23.TGRA
#define L_PWM					PWM_PIN(3,C)//MTU23.TGRC
#define R_PWM					PWM_PIN(4,A)//MTU24.TGRA
#define SERVO_PWM 				PWM_PIN(4,C)//MTU24.TGRC
*/

#define O_PWM					PWM_PIN(0,A)//MTU20.TGRA
#define L_PWM					PWM_PIN(0,B)//MTU20.TGRB
#define R_PWM					PWM_PIN(0,C)//MTU20.TGRC
//#define L_ARM_PWM             PWM_PIN(3,A)//MTU23.TGRA
//#define FISH_PWM				PWM_PIN(3,C)//MTU23.TGRC
#define SERVO_T_PWM				PWM_PIN(4,A)//MTU24.TGRA
#define SERVO_B_PWM 			PWM_PIN(4,C)//MTU24.TGRC

#endif

#ifdef CPU_RX621
/*******************************************************************/
//PIN CONFIG
/*******************************************************************/

//io_out
#define PSCON_SW 		OUTPUT_PIN(PORTA,7)
#define PIN_B_L 		OUTPUT_PIN(PORTA,6)
#define PIN_B_R			OUTPUT_PIN(PORTA,5)
#define PIN_B_U 		OUTPUT_PIN(PORTA,4)
#define PIN_B_U2      	OUTPUT_PIN(PORTD,2)
#define PIN_SHABAASH	OUTPUT_PIN(PORTD,3)
#define LED7		OUTPUT_PIN(PORTD,1)
#define LED8		OUTPUT_PIN(PORTD,0)

#define LED_RED		OUTPUT_PIN(PORTB,2)
#define LED_BLUE	OUTPUT_PIN(PORTB,3)

#define PE4			OUTPUT_PIN(PORTE,4)
#define PE5			OUTPUT_PIN(PORTE,5)
#define PE6			OUTPUT_PIN(PORTE,6)
#define PE7			OUTPUT_PIN(PORTE,7)

//io_in
#define LIMIT_L 		INPUT_PIN(PORTE,0)
#define LIMIT_R 		INPUT_PIN(PORTE,1)
#define LIMIT_U 		INPUT_PIN(PORTE,2)
#define TOGGLE		INPUT_PIN(PORTE,3)

//pwm(dc_motor)
#define KUMA_THETA_L_PWM	PWM_PIN(0,A)//MTU0.TGRA
#define KUMA_THETA_R_PWM	PWM_PIN(0,B)//MTU0.TGRB
#define KUMA_R_L_PWM		PWM_PIN(0,C)//MTU0.TGRC
#define KUMA_R_R_PWM 		PWM_PIN(0,D)//MTU0.TGRD
#define M5_PWM	PWM_PIN(4,A)//MTU3.TGRA
#define YOSHI_PWM	PWM_PIN(4,C)//MTU3.TGRC
#define TOKU_L_PWM	PWM_PIN(6,A)//MTU6.TGRA
#define TOKU_R_PWM	PWM_PIN(6,B)//MTU6.TGRB
#define UO_PWM		PWM_PIN(6,D)//MTU6.TGRD
#define KUMA_Z_L_PWM	 	PWM_PIN(9,A)//MTU9.TGRA
#define KUMA_Z_R_PWM		PWM_PIN(9,C)//MTU9.TGRC
//pwm(servo)
#define SERVO_L_PWM	PWM_PIN(10,A)//MTU24.TGRA
#define SERVO_R_PWM	PWM_PIN(10,C)//MTU24.TGRC

//�G���R�[�_
#define ENC_L	MTU1.TCNT 
#define ENC_R	MTU2.TCNT
#define ENC_U	MTU7.TCNT 
#define ENC4	MTU8.TCNT

#endif
/*******************************************************************/


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�C�R���̐ݒ� �v���g�^�C�v�錾
/********************************************************/
void MTU2_init(void);	//MTU2�̃X�^���o�C����
void setup(void); 		//�����ݒ�
void debug(void);
#endif // __SETUP_H__