/********************************************************/
//
//  �T�v
//      �v�Z�p�萔�E�}�N���S 
//  �쐬��
//		TUTrobo
//
/********************************************************/

#ifndef __MACRO_H__
#define __MACRO_H__

//�~����
/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v�Z�p�萔�E�}�N���S 
/********************************************************/
#define PI					3.1415926535							//�~����
#define ABS(x) 				(((x) > 0) ? (x) : -(x))				//��Βl
#define DEG2RAD(x)			((x)/180.0*PI)							//�p�x�����W�A���ɕύX
#define RAD2DEG(x)			((x)/PI * 180.0)						//���W�A�����p�x�ɕύX
#define POW2(x)				((x)*(x))								//���
#define POW3(x)				((x)*(x)*(x))							//�O��
#define DIST(a,b,c,d)		(sqrt(POW2((c)-(a)) + POW2((d)-(b))))	//(a,b)->(c,d)�̒���

#endif // __MACRO_H__