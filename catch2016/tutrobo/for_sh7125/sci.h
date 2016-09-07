/********************************************************/
//
//  �T�v
//  	SCI�֘A�ݒ�
//	�X�V����
//		2013/02/02 
//  �쐬��
//		TUTrobo
//
/********************************************************/

#ifndef __SCI_H__
#define __SCI_H__
	
	#define sci0_asynchronous					// SCI0������������[�h�ɐݒ�
//	#define sci0_synchronous					// SCI0���N���b�N���������[�h�ɐݒ�

	#define sci1_asynchronous					// SCI0������������[�h�ɐݒ�
	
//	#define sci2_asynchronous					// SCI0������������[�h�ɐݒ�

/********************************************************/
//  TUTrobo
//
//  �T�v
//      SCI�֘A�ݒ� �Ē�`
/********************************************************/
#undef puts
#undef putc
#undef getc

#define puts	put_s
#define putc	put_c
#define getc	get_c

/********************************************************/
//  TUTrobo
//
//  �T�v
//      SCI�֘A�ݒ� printf�p�^���錾
/********************************************************/
typedef struct{
	int z[2],n,l,m;
	unsigned long var,base;
}p_table;

/********************************************************/
//  TUTrobo
//
//  �T�v
//      SCI�֘A�ݒ� �v���g�^�C�v�錾
/********************************************************/
void sci_init(); 				// SCI�̏����ݒ�
void sci0_asynchronous_init();	// SCI0�����������̏����ݒ�
void sci0_synchronous_init();	// SCI0�N���b�N�������̏����ݒ�
void sci1_asynchronous_init();	// SCI1�����������̏����ݒ�
void sci2_asynchronous_init();	// SCI2�����������̏����ݒ�

void send_c(char c);			// SCI0���瑗�M
char rec_c(void);				// SCI0�����M
void tx_0(char send);			// SCI0���瑗�M(���荞�ݎg�p��)
char rx_0(void);				// SCI0�����M(���荞�ݎg�p��)
char txrx_0(char send);			// SCI0���瑗��M(���荞�ݎg�p��)

void put_s(char *);				// SCI1���瑗�M
void put_c(char );				// SCI1���當���񑗐M
char get_c(void);				// SCI1�����M
void tx_1(char send);			// SCI1���瑗�M(���荞�ݎg�p��)
char rx_1(void);				// SCI1�����M(���荞�ݎg�p��)
char txrx_1(char send);			// SCI1���瑗��M(���荞�ݎg�p��)

void transmit_c(char c);		// SCI2���瑗�M
char accept_c(void);			// SCI2�����M
void tx_2(char send);			// SCI2���瑗�M(���荞�ݎg�p��)
char rx_2(void);				// SCI2�����M(���荞�ݎg�p��)
char txrx_2(char send);			// SCI2���瑗��M(���荞�ݎg�p��)


int printf(const char *, ...);	// ���������͂���convert�ɂ킽���B
p_table clear(p_table);			// p_table������
void convert(p_table table);	// printf�����������������\��
void itoa(int value,char buff[],int radix);	//int��char�ϊ�

/********************************************************/
//  TUTrobo
//
//  �T�v
//      SCI�֘A�ݒ� ���荞�݃t���O�֘A
/********************************************************/
#define COM0_START()	{SCI0.SCSCR.BIT.TIE = 1;}
#define COM0_END()		{SCI0.SCSCR.BIT.TIE = 0;}

#endif // __SCI_H__