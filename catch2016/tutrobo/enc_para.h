/********************************************************/
//
//  �T�v
//      �G���R�[�_�Q�C���ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __ENC_PARA_H__
#define __ENC_PARA_H__

#include "macro.h"		//�v�Z�p�萔�E�}�N���S��`

extern struct enc_information ENCInfArray[][ENC_AIM_MAX] =
{
		 {/* �^���[�̃G���R�[�_ */
//			{���x��,���B�덷, ���]�Ői�ދ���, ���Q�C��, �����Q�C��, �ϕ��Q�C��}
			{100.0,      5.0,       (28.65*PI), 	   3.5, 	  10.0, 	   0.0},
		 },
};

#endif // __ENC_PARA_H__