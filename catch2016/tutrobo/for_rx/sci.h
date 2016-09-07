/********************************************************/
//
//  �T�v
//  	SCI�֘A�ݒ�
//	�X�V����
//		2013/04/26
//  �쐬��
//		TUTrobo
//
/********************************************************/

#ifndef __SCI_H__
#define __SCI_H__

#define B_115200 25//12
#define B_76800	38//19	
// �{�[���[�g    38,400 �����������[�h			
#define B_38400	77//38					
// �r�b�g���[�g BRR = (48,000,000[Hz]/(32*38,400[bps]))-1 => 19	�{�[���[�g    19,200 �����������[�h
#define B_19200 155//77                 
// �{�[���[�g    9,600  �����������[�h
#define B_9600	311//155					

#define EVEN  0x10
#define ODD   0x11
#define NONE  0x00
#define ONE_STOPBIT  0x01
#define TWO_STOPBITS 0x10
#define SCI_ASYNC_INIT(ch,baudrate,parity,stop,priority) {\
	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/\
	MSTP_SCI##ch = 0;						/* SCI�X�^���o�C����*/\
	SCI##ch##.SCMR.BIT.SMIF=0;				/* �f�[�^�t�H�[�}�b�gLSB���*/\
    SCI##ch##.SCR.BYTE = 0x00;				/* SCSCR���W�X�^�N���A*/\
	SCI##ch##.SEMR.BIT.ABCS=1;				/*		*/\
	/*/////////////////// �N���b�N�\�[�X��I�� �������� ////////////////////*/\
	SCI##ch##.SCR.BIT.CKE = 0;				/*	�������������[�h */\
										/*	00�F�����N���b�N�^SCK �[�q�͓��͒[�q�i���͐M���͖����j*/\
										/*	01�F�����N���b�N�^SCK �[�q�̓N���b�N�o�� */\
										/*	10�F�O���N���b�N�^SCK �[�q�̓N���b�N���� */\
										/*	11�F�O���N���b�N�^SCK �[�q�̓N���b�N���� */\
	/*/////////////////// �N���b�N�\�[�X��I�� �����܂� ////////////////////*/	\
	/*/////////////////// �ʐM�t�H�[�}�b�g�ݒ� �������� ////////////////////*/	\
	/* �R�~���j�P�[�V�������[�h */								\
    SCI##ch##.SMR.BIT.CM = 0;				/*	0�F�������������[�h*/	\
										/*	1�F�N���b�N���������[�h*/\
	/* �L�����N�^�����O�X */									\
	SCI##ch##.SMR.BIT.CHR = 0;				/*	0�F8 �r�b�g�f�[�^*/\
										/*	1�F7 �r�b�g�f�[�^*/\
	/* �p���e�B�C�l�[�u�� */									\
	SCI##ch##.SMR.BIT.PE = (parity>1)?1:0;	/*	0�F�p���e�B�r�b�g�̕t���A����у`�F�b�N���֎~*/\
										/*	1�F�p���e�B�r�b�g�̕t���A����у`�F�b�N������*/\
	/* �p���e�B���[�h */									\
	SCI##ch##.SMR.BIT.PM = parity&0x1;				/*	0�F�����p���e�B*/\
										/*	1�F��p���e�B*/\
	/* �X�g�b�v�r�b�g�����O�X */									\
	SCI##ch##.SMR.BIT.STOP = (stop>>1)&0x1;				/*	0�F1 �X�g�b�v�r�b�g*1 */\
										/*	1�F2 �X�g�b�v�r�b�g*2 */\
	/* �}���`�v���Z�b�T���[�h */									\
	SCI##ch##.SMR.BIT.MP = 0;				/*	0�F�}���`�v���Z�b�T���[�h���֎~ */\
										/*	1�F�}���`�v���Z�b�T���[�h�����i�������������[�h�̂ݗL���j*/\
	/* �N���b�N�Z���N�g1�A0 */									\
	SCI##ch##.SMR.BIT.CKS = 0;				/*	00�FP�ӃN���b�N*/\
										/*	01�FP��/64 �N���b�N*/\
										/*	10�FP��/16 �N���b�N*/\
										/*	11�FP��/64 �N���b�N*/\
	/*/////////////////// �ʐM�t�H�[�}�b�g�ݒ� �����܂� ////////////////////*/\
	/* �r�b�g���[�g�ݒ�	��������*/\
	SCI##ch##.BRR = baudrate;	\
	{volatile int i;for(i=0;i<50;i++);}		/*1�r�b�g���ԑҋ@*/\
	/* �r�b�g���[�g�ݒ�	�����܂�*/			\
	/*//////////////////// SCSCR���W�X�^�ݒ� �������� //////////////////////*/\
	SCI##ch##_RX_ENABLE /*PORT3.ICR.BIT.B0 = 1; \//���̓o�b�t�@���g�p���適���ꂪ�Ȃ��Ǝ�M�ł��Ȃ�*/\
	SCI##ch##.SCR.BYTE |= 0x30;			/* ����M���������	*/\
	SCI##ch##.SCR.BIT.RIE = 1; 			/* ��M���荞�ݗv��������*/\
    SCI##ch##.SCR.BIT.TIE = 0; 			/* ���M���荞�ݗv�����֎~*/\
	/*//////////////////// SCSCR���W�X�^�ݒ� �����܂� //////////////////////*/\
	/*/////////////// SCI0�̊��荞�݃��x����ݒ� �������� ///////////////////*/\
	IEN(SCI##ch,RXI##ch) = 0;  /*���荞�݋֎~*/\
	IPR(SCI##ch,RXI##ch) = priority; /* ���荞�݃��x���ݒ�()0�`15 0:�Œ� 15:�ō�*/\
	IEN(SCI##ch,RXI##ch) = 1; /*���荞�݋���*/\
	IEN(SCI##ch,ERI##ch) = 0;  /*���荞�݋֎~*/\
	IPR(SCI##ch,ERI##ch) = priority; /* ���荞�݃��x���ݒ�()0�`15 0:�Œ� 15:�ō�*/\
	IEN(SCI##ch,ERI##ch) = 1; /*���荞�݋���*/\
	/*/////////////// SCI0�̊��荞�݃��x����ݒ� �����܂� //////////////////*/\
}

#define SCI0_RX_ENABLE {PORT2.ICR.BIT.B1 = 1;} 
#define SCI1_RX_ENABLE {PORT3.ICR.BIT.B0 = 1;} 
#define SCI2_RX_ENABLE {PORT5.ICR.BIT.B2 = 1;} 

#define SCI_PRIORITY_CHANGE(ch,priority){\
	IEN(SCI##ch,RXI##ch) = 0;  /*���荞�݋֎~*/\
	IPR(SCI##ch,RXI##ch) = priority; /* ���荞�݃��x���ݒ�()0�`15 0:�Œ� 15:�ō�*/\
	IEN(SCI##ch,RXI##ch) = 1; /*���荞�݋���*/\
	IEN(SCI##ch,ERI##ch) = 0;  /*���荞�݋֎~*/\
	IPR(SCI##ch,ERI##ch) = priority; /* ���荞�݃��x���ݒ�()0�`15 0:�Œ� 15:�ō�*/\
	IEN(SCI##ch,ERI##ch) = 1; /*���荞�݋���*/\
}

#define SCI_SEND(ch,c) {\
 	while (SCI##ch##.SSR.BIT.TDRE==0);\
    SCI##ch##.SSR.BIT.TDRE=0;	\
    SCI##ch##.TDR=c;					/*�V���A�����M����f�[�^���i�[*/\
}
#define SCI_RECV(ch) (SCI##ch##.RDR)


#define SCI_ERI(ch) {\
	if(SCI##ch##.SSR.BIT.ORER==1){\
	/*	put_c('o');*/\
	/*	put_c(ch+0x30);*/\
		SCI##ch##.SSR.BIT.ORER=0;\
	}\
	if(SCI##ch##.SSR.BIT.FER==1){\
		put_c('f');\
		SCI##ch##.SSR.BIT.FER=0;\
	}\
	if(SCI##ch##.SSR.BIT.PER==1){\
		put_c('p');\
		SCI##ch##.SSR.BIT.PER=0;\
}}
//SCI_SEND(1)

//	#define sci0_asynchronous					// SCI0������������[�h�ɐݒ�
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

void send_c(char c);			// SCI0���瑗�M
char rec_c(void);				// SCI0�����M
void send_c2(char c);			// SCI2���瑗�M
char rec_c2(void);				// SCI2�����M

void put_s(char *);				// SCI1���瑗�M
void put_c(char );				// SCI1���當���񑗐M
char get_c(void);				// SCI1�����M

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