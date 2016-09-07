/********************************************************/
//
//  �T�v
//      �v�Z�֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/

#ifndef __CALC_H__
#define __CALC_H__

#include "type.h"		//�v���O�����̌^���錾

/********************************************************/
//  TUTrobo
//
//  �T�v
//      A/D�ϊ��ݒ� �v���g�^�C�v�錾
/********************************************************/
DOUBLE_XY get_ctrl_point(DOUBLE_XY,double,double);				// ����_�v�Z
DOUBLE_XY get_intersection(DOUBLE_XY,double,DOUBLE_XY,double);	// 2�����̌�_���Z�o(����_�v�Z�p)
void get_bisector(DOUBLE_XY, DOUBLE_XY, double*, double*);		// ����2�������̎Z�o
DOUBLE_XY get_center(double, double, double, double);			// �����̌�_���Z�o
double get_direction(DOUBLE_XY, DOUBLE_XY, DOUBLE_XY);			// ��]�̒��S�̍��E�𔻒�

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �x�W�F�Ȑ��|�C���g�v�Z(3��)
/********************************************************/
#define get_bezier3_point(p0,p1,p2,p3,t) (POW3(1-(t))*p0 + 3*POW2(1-(t))*(t)*(p1) + 3*(1-(t))*POW2(t)*(p2) + POW3(t)*(p3))


#endif // __CALC_H__