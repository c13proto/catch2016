/********************************************************/
//
//  �T�v
//      �}�C�R���̐ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
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

#include "ad.h"			//A/D�ϊ��ݒ�
//#include "../individual/yamamuro.h"  //�R���l�֐�
#include "../calc.h"		//�v�Z�֘A��`
#include "clock.h"		//CLOCK�ݒ�
#include "cmt.h"		//CMT�֘A
#include "../type.h"		//�v���O�����̌^���錾
#include "../common.h"		//���ʂ̐ݒ莖��
//#include "../comu.h"		//�ʐM�֘A��`
#include "../control.h"	//�}�V���ړ�����֘A
//#include "../controller.h"	//�R���g���[���[�֘A
#include "enc.h"		//�G���R�[�_�֘A
#include "../feedback.h"	//�t�B�[�h�o�b�N�֘A��`
#include "../interrupt.h"	//���荞�݊֘A��`
#include "io.h"			//�s���ݒ�
#include "../../iodefine.h"	//PINdefine
#include "../omuni.h"		//�I���j�֘A
#include "../macro.h"		//�v�Z�p�}�N����`
#include "../path.h"		// �p�X�i�R�}���h�j�ݒ�
#include "pwm.h"		//PWM�ݒ�
#include "sci.h"		//SCI�֘A�ݒ�
//#include "sence.h"		//�v���֘A��`
#include "../../typedefine.h"	//�^�̕ʖ��錾 
//#include "wdt.h"		//WDT�֘A��`
//#include "table.h"

extern volatile char *send_data;	// �o�͊֐��̂���(�f�[�^�{��)
extern volatile char send_data_cnt;	// �o�͊֐��̂���(�f�[�^��)

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