/********************************************************/
//
//  �T�v
//      ���荞�݊֘A
//	�X�V����
//		2013/02/02
//  �쐬��
//		K.ishimori @ TUTrobo
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
	
	SCI0.SCSCR.BIT.TIE = 1; 	// ���M���荞�ݗv��������
	SCI0.SCSCR.BIT.TEIE = 1;	// ���M�������荞�ݗv��������

	CMT0.CMCSR.BIT.CMF = 0;		// �t���O�N���A	
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
int cmt1_counter;
void int_cmt_cmt1(void)
{

	
//	map_update();						//�W���C����2�̃G���R�[�_��p���ă}�b�v�̍X�V(coordinate_omni)

	//�v���X�e�R������̎�M/////////////////////////////////////////////////////
	
	recieve_data_input();				//��M���荞�݂���󂯎�����l���i�[�i����duty���v�Z���Ă���j
	
	/////////////////////////////////////////////////////////////////////////////
	
	
	//�e�����n///////////////////////////////////////////////////////////////////
	
	
//	gyro_map();							//�W���C��MAP��Ԃ̍X�V
	
	////////////////////////////////////////////////////////////////////////////
	
	//�蓮����//////////////////////////////////////////////////////////////////
	input_register_ctrl();						//�蓮����(duty�����W�X�^�Ɋi�[)

	
	CMT1.CMCSR.BIT.CMF = 0;		// �t���O�N���A
	
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
	rx_storage_processing(COM1);
//	com1_rx[0][0] = rx_1();		// �f�[�^��M
//	SCI1.SCSSR.BIT.RDRF = 0;	// SCSSR��RDRF�t���O��0�ɃN���A
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
#ifdef	sci1_synchronous	
		sci1_synchronous_init();
		SCI1.SCSSR.BIT.ORER = 0;
#endif//sci1_synchronous

#ifdef	sci1_asynchronous	
		sci1_asynchronous_init();
		//SCI1.SCSSR.BIT.ORER = 0;

		if(SCI1.SCSSR.BIT.ORER==1){
			printf("\nCOM1_o\n");
			SCI1.SCSSR.BIT.ORER=0;
		}
		if(SCI1.SCSSR.BIT.FER==1){
			printf("\nCOM1_f\n");
			SCI1.SCSSR.BIT.FER=0;
		}
		if(SCI1.SCSSR.BIT.PER==1){
			printf("\nCOM1_p\n");
			SCI1.SCSSR.BIT.PER=0;
		}
	
		SCI1.SCSSR.BIT.ORER = 0;
		SCI1.SCSSR.BIT.PER = 0;
		SCI1.SCSSR.BIT.FER = 0;
#endif//sci1_asynchronous

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
	tx_0(tx_storage_processing(0,LOAD));// �f�[�^���M
	SCI0.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
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
	SCI0.SCSSR.BIT.TEND = 0;	// SCSSR��TDRE�t���O��0�ɃN���A
	SCI0.SCSCR.BIT.TEIE = 0;	// ���M�������荞�ݗv�����֎~	
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
//	rx_storage_processing(0);
	R1350N(rec_c());
//	put_c('R');
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
void int_sci0_eri0(void)
{
#ifdef	sci0_synchronous	
		sci0_synchronous_init();
		SCI0.SCSSR.BIT.ORER = 0;
#endif//sci0_synchronous

#ifdef	sci0_asynchronous	
		sci0_asynchronous_init();
		//SCI0.SCSSR.BIT.ORER = 0;

		if(SCI0.SCSSR.BIT.ORER==1){
//			put_c('o');
			printf("\no\n");
			SCI0.SCSSR.BIT.ORER=0;
		}
		if(SCI0.SCSSR.BIT.FER==1){
//			put_c('f');
			printf("\nf\n");
			SCI0.SCSSR.BIT.FER=0;
		}
		if(SCI0.SCSSR.BIT.PER==1){
//			put_c('p');
			printf("\np\n");
			SCI0.SCSSR.BIT.PER=0;
		}
	
		SCI0.SCSSR.BIT.ORER = 0;
		SCI0.SCSSR.BIT.PER = 0;
		SCI0.SCSSR.BIT.FER = 0;
#endif//sci0_asynchronous

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
	
//	put_c('R');
	
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
				int i,j;
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
//	receipt(&com0);
	
	if(angle-old_angle > 18000)angle_counter--;
	else if(angle-old_angle < -18000)angle_counter++;
	else angle_counter+=0;
	
	
	m_angle=-(angle_counter*36000+angle);


	old_angle=angle;


}

/********************************************************/
//  ���O      
//		after_recieve
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		��M�����f�[�^����e��v���O���������s����@
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void after_recieve(void)
{
	
}