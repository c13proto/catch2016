/********************************************************/
//
//  �T�v
//      ���荞�݊֘A
//	�X�V����
//		
//  �쐬��
//		@ TUTrobo
//
/********************************************************/
//���荞�݂�����ɂ�                 
//resetprg.c��
//#define SR_Init    0x00000000
//�ɂ���

#include <machine.h>
#include "../../vect.h"

#include "../setup.h"		//�}�C�R���̐ݒ�
	
/********************************************************/
//  ���O      
//		int_cmt_cmt0
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		�^�C�}���荞�݊֐�
//	���ӎ���
//		intprg.c�Œ�`���Ă���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_cmt_cmt0(void)
{

}

/********************************************************/
//  ���O      
//		int_cmt_cmt1
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		�^�C�}���荞�݊֐�
//	���ӎ���
//		intprg.c�Œ�`���Ă���
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int cmt1_counter=0;
void int_cmt_cmt1(void)
{
	cmt1_counter++;//10ms���Ƃɓ����Ă���
	
	arm_condition_update();
		
	//�v���X�e�R������̎�M/////////////////////////////////////////////////////	
	recieve_data_input();				//��M���荞�݂���󂯎�����l���i�[�i����duty���v�Z���Ă���j

	
	input_register_ctrl();						//duty�����W�X�^�Ɋi�[
	

	cmt1_counter=0;
}

/********************************************************/
//  ���O      
//		int_sci1_rxi1
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci1_rxi1(void)	
{
	receipt(&com[1]); 
}

/********************************************************/
//  ���O      
//		int_sci1_eri1
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M�G���[���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci1_eri1(void)
{
		SCI_ERI(1);
}

/********************************************************/
//  ���O      
//		int_sci0_txi0
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		���M���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_txi0(void)
{	
}

/********************************************************/
//  ���O      
//		int_sci0_tei0
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		���M�������荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_tei0(void)
{
}

/********************************************************/
//  ���O      
//		int_sci0_rxi0
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_rxi0(void)
{
	receipt(&com[0]);
	
	//���荞�ݗD��x�ύX
//	SCI_PRIORITY_CHANGE(0,12);
//	SCI_PRIORITY_CHANGE(2,13);
}

/********************************************************/
//  ���O      
//		int_sci0_eri0
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M�G���[���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_eri0(void){
	SCI_ERI(0);	
}

/********************************************************/
//  ���O      
//		int_sci2_rxi2
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
void int_sci2_rxi2(void){
	receipt(&com[2]);
	//���荞�ݗD��x�ύX
//	SCI_PRIORITY_CHANGE(0,13);
//	SCI_PRIORITY_CHANGE(2,12);
//	R1350N(SCI_RECV(2));
}
/********************************************************/
//  ���O      
//		int_sci2_eri2
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M�G���[���荞�݊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci2_eri2(void){
	SCI_ERI(2);
}
/********************************************************/
//  ���O      
//		R1350N
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M���荞�݊֐� master��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		
//  �쐬��
//		Ido @ TUT
//
/********************************************************/
int angle,accX,accY,accZ;
int m_angle;

void R1350N(unsigned char c)	
{
	static unsigned char j_buffer[15],j_data;
	static int j_state,j_counter;
	static int angle_counter=0;
	static int old_angle;
	
	j_data=c;
		
	switch(j_state){
		case 0:
			//put_c('0');
			if(j_data==0xAA){j_state++;}break;
		
		case 1:
			//put_c('1');
			if(j_data==0x00){j_state++;}
			else{j_counter=0;j_state=0;}break;
		
		case 2:
			//put_c('2');
			j_buffer[j_counter] = j_data;
			j_counter++;
			
			if(j_counter>=13)
			{
				int sum=0;
				int i;
				for(i=0;i<11;i++)sum += j_buffer[i];
				if((sum & 0xff) == j_buffer[12])
				{
					angle	= ((j_buffer[2] << 8) | j_buffer[1]);
					if(angle&0x8000){
						angle^=0xFFFF;
						angle+=1;
						angle*=-1;
					}
					
					accX	= ((j_buffer[6] << 8) | j_buffer[5]);
					if(accX&0x8000){
						accX^=0xFFFF;
						accX+=1;
						accX*=-1;
					}					
					
					accY	= ((j_buffer[8] << 8) | j_buffer[7]);
					if(accY&0x8000){
						accY^=0xFFFF;
						accY+=1;
						accY*=-1;
					}
										
					accZ	= ((j_buffer[10] << 8) | j_buffer[9]);
					if(accZ&0x8000){
						accZ^=0xFFFF;
						accZ+=1;
						accZ*=-1;
					}
				//	put_c('3');
				//	for(j=0;j<100;j++);//delay
					
				}
				j_state=0;
				j_counter=0;
			}break;
	}
	
	if(angle-old_angle > 18000)angle_counter--;
	else if(angle-old_angle < -18000)angle_counter++;
	else angle_counter+=0;
	
	
	m_angle=-(angle_counter*36000+angle);
	old_angle=angle;
}

