/********************************************************/
//
//  �T�v
//      �t�B�[�h�o�b�N�֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/


#ifndef __FEEDBACK_H__
#define __FEEDBACK_H__

#include "type.h"		//�v���O�����̌^���錾

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �t�B�[�h�o�b�N�֘A �v���g�^�C�v�錾
/********************************************************/
void feedback_drive(void);										//�t�B�[�h�o�b�N
double duty_to_speed(double duty);								//�}�V���̖ڕW�Ƃ��铮����duty���瑬�x�ɕύX
double speed_to_duty(double speed);								//�}�V���̖ڕW�Ƃ��铮���𑬓x����duty�ɕύX
void foot_set_aiming_motion(double v_ratio,double r0,double t);	//�}�V���̖ڕW�Ƃ��铮����ݒ�
void lr_duty_ceiling_shift(DOUBLE_LR* d,double max);			//����ɂ��킹�ăV�t�g
void lr_duty_diff_limit(DOUBLE_LR* d,double limit,double over_k);//��������
void lr_duty_lowpath(DOUBLE_LR* duty,double a_limit);			//���[�p�X(��������)

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �t�B�[�h�o�b�N�֘A �O���[�o���ϐ��錾
/********************************************************/
extern volatile double    aim_v;				//���x(���V�I)
extern volatile DOUBLE_LR aim_lr;				//�����䗦

#endif	//__FEEDBACK_H__�@
