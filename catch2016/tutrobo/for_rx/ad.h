/********************************************************/
//
//  �T�v
//      A/D�ϊ��ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __AD_H__
#define __AD_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      A/D�ϊ��ݒ� �v���g�^�C�v�錾
/********************************************************/
void ad_init();		 			// AD�ϊ��̏����ݒ�
void ad_load_0_3(int *ad_data);	// �`�����l��0~3����x�ɓǂݎ��	
void ad_load_4_7(int *ad_data);	// �`�����l��4~7����x�ɓǂݎ��
void ad_load_0_7(int *ad_data);	// �`�����l��0~7����x�ɓǂݎ��
int PID_control(double mokuhyou,double position,int max_duty,double Kp,double Ki,double Kd,char num);
double PID_control_d(double mokuhyou,double position,double max_duty,double Kp,double Ki,double Kd,double I_reset_range,char num);
#endif // __AD_H__