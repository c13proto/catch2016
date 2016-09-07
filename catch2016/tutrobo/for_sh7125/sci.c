/********************************************************/
//
//  �T�v
//      SCI�֘A
//	�X�V����
//		2013/02/02
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�

/********************************************************/
//  ���O      
//		sci_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci_init() 
{
	/********************* SCI0�̏����� (SH/AVR�ƒʐM�p) *********************/
#ifdef	sci0_synchronous
	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
	sci0_synchronous_init();
	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
#endif//sci0_synchronous

#ifdef	sci0_asynchronous
	/*************** SCI0 �����������[�h�ݒ� (SH/AVR�ƒʐM�p) ****************/
	sci0_asynchronous_init();
	/*************** SCI0 �����������[�h�ݒ� (SH/AVR�ƒʐM�p) ****************/
#endif//sci0_asynchronous	
	/********************* SCI0�̏����� (SH/AVR�ƒʐM�p) *********************/	

	//-----------------------------------------------------------------------//	
	
	/*********************** SCI1�̏����� (PC�ƒʐM�p) ***********************/
#ifdef	sci1_asynchronous
	/***************** SCI1 �����������[�h�ݒ� (PC�ƒʐM�p) ******************/
	sci1_asynchronous_init();
	/***************** SCI1 �����������[�h�ݒ� (PC�ƒʐM�p) ******************/
#endif//sci1_asynchronous	
	/*********************** SCI1�̏����� (PC�ƒʐM�p) ***********************/	

	//-----------------------------------------------------------------------//

	/********************* SCI2�̏����� (SH/AVR�ƒʐM�p) *********************/
#ifdef	sci2_asynchronous
	/*************** SCI2 �����������[�h�ݒ� (SH/AVR�ƒʐM�p) ****************/
	sci2_asynchronous_init();
	/*************** SCI2 �����������[�h�ݒ� (SH/AVR�ƒʐM�p) ****************/
#endif//sci2_asynchronous	
	/********************* SCI2�̏����� (SH/AVR�ƒʐM�p) *********************/	
	
}

/********************************************************/
//  ���O      
//		sci0_asynchronous_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0�����������̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci0_asynchronous_init() 
{	
	////////////////////////// ���[�h��I�� �������� //////////////////////////
	#define asynchro_115200						// �{�[���[�g   115,200 �����������[�h	
//	#define asynchro_38400						// �{�[���[�g    38,400 �����������[�h
//	#define asynchro_19200						// �{�[���[�g    19,200 �����������[�h
//	#define asynchro_9600						// �{�[���[�g    9,600  �����������[�h

//	#define sci0_asynchro_tx					// ���M�ɐݒ�
	#define sci0_asynchro_rx					// ��M�ɐݒ�
//	#define sci0_asynchro_txrx					// ����M�ɐݒ�
	////////////////////////// ���[�h��I�� �����܂� //////////////////////////
	
	int cnt1,cnt2;		// delay_time�p

	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
	STB.CR3.BIT._SCI0=0;				// SCI�X�^���o�C����
	
    SCI0.SCSCR.BYTE = 0x00;				// SCSCR���W�X�^�N���A
	
	///////////////////// �N���b�N�\�[�X��I�� �������� //////////////////////			
	SCI0.SCSCR.BIT.CKE = 0;				/*	�������������[�h */
										//	00�F�����N���b�N�^SCK �[�q�͓��͒[�q�i���͐M���͖����j
										//	01�F�����N���b�N�^SCK �[�q�̓N���b�N�o��
										//	10�F�O���N���b�N�^SCK �[�q�̓N���b�N����
										//	11�F�O���N���b�N�^SCK �[�q�̓N���b�N����										
	///////////////////// �N���b�N�\�[�X��I�� �����܂� //////////////////////
	
	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �������� //////////////////////									
	/* �R�~���j�P�[�V�������[�h */								
    SCI0.SCSMR.BIT.CA = 0;				//	0�F�������������[�h
										//	1�F�N���b�N���������[�h
	/* �L�����N�^�����O�X */									
	SCI0.SCSMR.BIT.CHR = 0;				//	0�F8 �r�b�g�f�[�^
										//	1�F7 �r�b�g�f�[�^
	/* �p���e�B�C�l�[�u�� */									
	SCI0.SCSMR.BIT._PE = 0;				//	0�F�p���e�B�r�b�g�̕t���A����у`�F�b�N���֎~
										//	1�F�p���e�B�r�b�g�̕t���A����у`�F�b�N������*
	/* �p���e�B���[�h */									
	SCI0.SCSMR.BIT.OE = 0;				//	0�F�����p���e�B
										//	1�F��p���e�B
	/* �X�g�b�v�r�b�g�����O�X */									
	SCI0.SCSMR.BIT.STOP = 0;			//	0�F1 �X�g�b�v�r�b�g*1
										//	1�F2 �X�g�b�v�r�b�g*2
	/* �}���`�v���Z�b�T���[�h */									
	SCI0.SCSMR.BIT.MP = 0;				//	0�F�}���`�v���Z�b�T���[�h���֎~
										//	1�F�}���`�v���Z�b�T���[�h�����i�������������[�h�̂ݗL���j
	/* �N���b�N�Z���N�g1�A0 */									
	SCI0.SCSMR.BIT.CKS = 0;				//	00�FP�ӃN���b�N
										//	01�FP��/4 �N���b�N
										//	10�FP��/16 �N���b�N
										//	11�FP��/64 �N���b�N

	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �����܂� //////////////////////
	
	////////////////////// �r�b�g���[�g�ݒ�	�������� /////////////////////////
#ifdef	asynchro_115200		
		SCI0.SCBRR = 6;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*115,200[bps]))-1 => 6	
#endif
#ifdef	asynchro_19200		
		SCI0.SCBRR = 40;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI0.SCBRR = 80;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// �r�b�g���[�g�ݒ�	�����܂� /////////////////////////						

	///////////////// �g�p����O���[�q��PFC�̐ݒ� �������� ///////////////////	
	PFC.PACRL1.BIT.PA0MD = 1;			// PA0�̓��o�͐ݒ�(����)	***RXD0_SCI_0***
	PFC.PACRL1.BIT.PA1MD = 1;			// PA1�̓��o�͐ݒ�(�o��)	***TXD0_SCI_0***
//	PFC.PACRL1.BIT.PA2MD = 1;			// SCK0 ���o�͐ݒ�(���o�́j	***SCK0_SCI_0***
	///////////////// �g�p����O���[�q��PFC�̐ݒ� �����܂� ///////////////////
	
	////////////////////// SCSCR���W�X�^�ݒ� �������� ////////////////////////
#ifdef	sci0_asynchro_tx			
	SCI0.SCSCR.BIT.TE=1;  				// �g�����X�~�b�g�C�l�[�u��:���M���������
	SCI0.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
	SCI0.SCSCR.BIT.TEIE = 0;			// ���M�������荞�ݗv�����֎~
#endif//sci0_asynchro_tx	

#ifdef	sci0_asynchro_rx	
    SCI0.SCSCR.BIT.RE=1;  				// ���V�[�u�C�l�[�u��:��M���������	
    SCI0.SCSCR.BIT.RIE=1; 				// ��M���荞�ݗv��������
    SCI0.SCSCR.BIT.TIE=0; 				// ���M���荞�ݗv�����֎~
#endif//sci0_asynchro_rx

#ifdef	sci0_asynchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* ���ӃN���b�N�S�N���b�N�ȏ�ҋ@ */	
	SCI0.SCSCR.BYTE |= 0x30;			// ����M���������	
	SCI0.SCSCR.BIT.RIE = 1; 			// ��M���荞�ݗv��������
	SCI0.SCSCR.BIT.TIE = 1; 			// ���M���荞�ݗv��������
#endif//sci0_asynchro_txrx
	////////////////////// SCSCR���W�X�^�ݒ� �����܂� ////////////////////////

	///////////////// SCI0�̊��荞�݃��x����ݒ� �������� ////////////////////
#ifdef	sci0_asynchro_tx
	INTC.IPRL.BIT._SCI0 = 15;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_asynchro_tx
#ifdef	sci0_asynchro_rx
	INTC.IPRL.BIT._SCI0 = 15;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_asynchro_rx
#ifdef	sci0_asynchro_txrx
	INTC.IPRL.BIT._SCI0 = 15;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_asynchro_txrx
	///////////////// SCI0�̊��荞�݃��x����ݒ� �����܂� ////////////////////
	
	//////////////////////// #define ������ �������� /////////////////////////
	#undef asynchro_38400						// �{�[���[�g    38,400 �����������[�h
	#undef asynchro_19200						// �{�[���[�g    19,200 �����������[�h
	#undef asynchro_9600						// �{�[���[�g    9,600  �����������[�h
	#undef sci0_asynchro_tx						// ���M�ɐݒ�
	#undef sci0_asynchro_rx						// ��M�ɐݒ�
	#undef sci0_asynchro_txrx					// ����M�ɐݒ�
	//////////////////////// #define ������ �����܂� /////////////////////////
}

/********************************************************/
//  ���O      
//		sci0_synchronous_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0�N���b�N�������̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci0_synchronous_init() 
{
	////////////////////////// ���[�h��I�� �������� //////////////////////////
//	#define sci0_synchro_master					// �}�X�^�[�ɐݒ�
//	#define synchro_3125000						// �{�[���[�g 3,125,000 �N���b�N���������[�h
//	#define synchro_1000000						// �{�[���[�g 1,000,000 �N���b�N���������[�h
//	#define synchro_500000						// �{�[���[�g   500,000 �N���b�N���������[�h
//	#define synchro_38400						// �{�[���[�g    38,400 �N���b�N���������[�h
	
	#define sci0_synchro_slave					// �X���[�u�ɐݒ�

//	#define sci0_synchro_tx						// ���M�ɐݒ�
	#define sci0_synchro_rx						// ��M�ɐݒ�
//	#define sci0_synchro_txrx					// ����M�ɐݒ�
	////////////////////////// ���[�h��I�� �����܂� //////////////////////////
	
	int cnt1,cnt2;		// delay_time�p

	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
	STB.CR3.BIT._SCI0=0;				// SCI�X�^���o�C����
	
    SCI0.SCSCR.BYTE = 0x00;				// SCSCR���W�X�^�N���A
	
	///////////////////// �N���b�N�\�[�X��I�� �������� //////////////////////
#ifdef	sci0_synchro_master				/* �}�X�^�[�ɐݒ� */				
	SCI0.SCSCR.BIT.CKE = 0;				/*	�N���b�N���������[�h */
										//	00�F�����N���b�N�^SCK �[�q�͓����N���b�N�o��
										//	01�F�����N���b�N�^SCK �[�q�͓����N���b�N�o��
										//	10�F�O���N���b�N�^SCK �[�q�͓����N���b�N����
										//	11�F�O���N���b�N�^SCK �[�q�͓����N���b�N����
#endif	// sci0_synchro_master

#ifdef	sci0_synchro_slave				/* �X���[�u�ɐݒ� */									
	SCI0.SCSCR.BIT.CKE = 3;				/*	�N���b�N���������[�h */
										//	00�F�����N���b�N�^SCK �[�q�͓����N���b�N�o��
										//	01�F�����N���b�N�^SCK �[�q�͓����N���b�N�o��
										//	10�F�O���N���b�N�^SCK �[�q�͓����N���b�N����
										//	11�F�O���N���b�N�^SCK �[�q�͓����N���b�N����
#endif	// sci0_synchro_slave										
	///////////////////// �N���b�N�\�[�X��I�� �����܂� //////////////////////
	
	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �������� //////////////////////									
	/* �R�~���j�P�[�V�������[�h */								
    SCI0.SCSMR.BIT.CA = 1;				//	0�F�������������[�h
										//	1�F�N���b�N���������[�h
	/* �L�����N�^�����O�X */									
	SCI0.SCSMR.BIT.CHR = 0;				//	0�F8 �r�b�g�f�[�^
										//	1�F7 �r�b�g�f�[�^
	/* �p���e�B�C�l�[�u�� */									
	SCI0.SCSMR.BIT._PE = 1;				//	0�F�p���e�B�r�b�g�̕t���A����у`�F�b�N���֎~
										//	1�F�p���e�B�r�b�g�̕t���A����у`�F�b�N������*
	/* �p���e�B���[�h */									
	SCI0.SCSMR.BIT.OE = 1;				//	0�F�����p���e�B
										//	1�F��p���e�B
	/* �X�g�b�v�r�b�g�����O�X */									
	SCI0.SCSMR.BIT.STOP = 1;			//	0�F1 �X�g�b�v�r�b�g*1
										//	1�F2 �X�g�b�v�r�b�g*2
	/* �}���`�v���Z�b�T���[�h */									
	SCI0.SCSMR.BIT.MP = 0;				//	0�F�}���`�v���Z�b�T���[�h���֎~
										//	1�F�}���`�v���Z�b�T���[�h�����i�������������[�h�̂ݗL���j
	/* �N���b�N�Z���N�g1�A0 */									
	SCI0.SCSMR.BIT.CKS = 0;				//	00�FP�ӃN���b�N
										//	01�FP��/4 �N���b�N
										//	10�FP��/16 �N���b�N
										//	11�FP��/64 �N���b�N
	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �����܂� //////////////////////
	
	////////////////////// �r�b�g���[�g�ݒ�	�������� /////////////////////////
#ifdef	synchro_3125000		
		SCI0.SCBRR = 1;					// �r�b�g���[�g BRR = (25,000,000/(8*(1/2)*3,125,000))-1 => 1	
#endif		
#ifdef	synchro_1000000		
		SCI0.SCBRR = 5;					// �r�b�g���[�g BRR = (25,000,000/(8*(1/2)*1,000,000))-1 => 5
#endif	
#ifdef	synchro_500000					
		SCI0.SCBRR = 12;				// �r�b�g���[�g BRR = (25,000,000/(8*(1/2)*500,000))-1 => 12	
#endif	
#ifdef	synchro_38400		
		SCI0.SCBRR = 162;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(8*(1/2)*38,400[bps]))-1 => 162	
#endif	
	////////////////////// �r�b�g���[�g�ݒ�	�����܂� /////////////////////////						

	///////////////// �g�p����O���[�q��PFC�̐ݒ� �������� ///////////////////	
	PFC.PACRL1.BIT.PA0MD = 1;			// PA0�̓��o�͐ݒ�(����)	***RXD0_SCI_0***
	PFC.PACRL1.BIT.PA1MD = 1;			// PA1�̓��o�͐ݒ�(�o��)	***TXD0_SCI_0***
	PFC.PACRL1.BIT.PA2MD = 1;			// SCK0 ���o�͐ݒ�(���o�́j	***SCK0_SCI_0***
	///////////////// �g�p����O���[�q��PFC�̐ݒ� �����܂� ///////////////////
	
	////////////////////// SCSCR���W�X�^�ݒ� �������� ////////////////////////
#ifdef	sci0_synchro_tx			
	SCI0.SCSCR.BIT.TE=1;  				// �g�����X�~�b�g�C�l�[�u��:���M���������
	SCI0.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
	SCI0.SCSCR.BIT.TEIE = 1;			// ���M�������荞�ݗv�����֎~
#endif//sci0_synchro_tx	

#ifdef	sci0_synchro_rx	
    SCI0.SCSCR.BIT.RE=1;  				// ���V�[�u�C�l�[�u��:��M���������	
    SCI0.SCSCR.BIT.RIE=1; 				// ��M���荞�ݗv��������
    SCI0.SCSCR.BIT.TIE=0; 				// ���M���荞�ݗv�����֎~
#endif//sci0_synchro_rx

#ifdef	sci0_synchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* ���ӃN���b�N�S�N���b�N�ȏ�ҋ@ */	
	SCI0.SCSCR.BYTE |= 0x30;			// ����M���������	
	SCI0.SCSCR.BIT.RIE = 1; 			// ��M���荞�ݗv��������
	SCI0.SCSCR.BIT.TIE = 1; 			// ���M���荞�ݗv��������
#endif//sci0_synchro_txrx
	////////////////////// SCSCR���W�X�^�ݒ� �����܂� ////////////////////////

	///////////////// SCI0�̊��荞�݃��x����ݒ� �������� ////////////////////
#ifdef	sci0_synchro_tx
	INTC.IPRL.BIT._SCI0 = 13;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_synchro_tx
#ifdef	sci0_synchro_rx
	INTC.IPRL.BIT._SCI0 = 13;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_synchro_rx
#ifdef	sci0_synchro_txrx
	INTC.IPRL.BIT._SCI0 = 13;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci0_synchro_txrx
	///////////////// SCI0�̊��荞�݃��x����ݒ� �����܂� ////////////////////
	
	//////////////////////// #define ������ �������� /////////////////////////
	#undef sci0_synchro_master					// �}�X�^�[�ɐݒ�
	#undef synchro_3125000						// �{�[���[�g 3,125,000 �N���b�N���������[�h
	#undef synchro_1000000						// �{�[���[�g 1,000,000 �N���b�N���������[�h
	#undef synchro_500000						// �{�[���[�g   500,000 �N���b�N���������[�h
	#undef synchro_38400						// �{�[���[�g    38,400 �N���b�N���������[�h	
	#undef sci0_synchro_slave					// �X���[�u�ɐݒ�
	#undef sci0_synchro_tx						// ���M�ɐݒ�
	#undef sci0_synchro_rx						// ��M�ɐݒ�
	#undef sci0_synchro_txrx					// ����M�ɐݒ�
	//////////////////////// #define ������ �����܂� /////////////////////////
}

/********************************************************/
//  ���O      
//		sci1_asynchronous_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1�����������̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci1_asynchronous_init() 
{	
	////////////////////////// ���[�h��I�� �������� //////////////////////////
//	#define asynchro_38400						// �{�[���[�g    38,400 �����������[�h
	#define asynchro_19200						// �{�[���[�g    19,200 �����������[�h
//	#define asynchro_9600						// �{�[���[�g    9,600  �����������[�h

//	#define sci1_asynchro_tx					// ���M�ɐݒ�
//	#define sci1_asynchro_rx					// ��M�ɐݒ�
	#define sci1_asynchro_txrx					// ����M�ɐݒ�
	////////////////////////// ���[�h��I�� �����܂� //////////////////////////

	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
	STB.CR3.BIT._SCI1 = 0;				// SCI�X�^���o�C����
	
    SCI1.SCSCR.BYTE = 0x00;				// SCSCR���W�X�^�N���A
	
	///////////////////// �N���b�N�\�[�X��I�� �������� //////////////////////			
	SCI1.SCSCR.BIT.CKE = 0;				/*	�������������[�h */
										//	00�F�����N���b�N�^SCK �[�q�͓��͒[�q�i���͐M���͖����j
										//	01�F�����N���b�N�^SCK �[�q�̓N���b�N�o��
										//	10�F�O���N���b�N�^SCK �[�q�̓N���b�N����
										//	11�F�O���N���b�N�^SCK �[�q�̓N���b�N����										
	///////////////////// �N���b�N�\�[�X��I�� �����܂� //////////////////////
	
	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �������� //////////////////////									
	/* �R�~���j�P�[�V�������[�h */								
    SCI1.SCSMR.BIT.CA = 0;				//	0�F�������������[�h
										//	1�F�N���b�N���������[�h
	/* �L�����N�^�����O�X */									
	SCI1.SCSMR.BIT.CHR = 0;				//	0�F8 �r�b�g�f�[�^
										//	1�F7 �r�b�g�f�[�^
	/* �p���e�B�C�l�[�u�� */									
	SCI1.SCSMR.BIT._PE = 0;				//	0�F�p���e�B�r�b�g�̕t���A����у`�F�b�N���֎~
										//	1�F�p���e�B�r�b�g�̕t���A����у`�F�b�N������*
	/* �p���e�B���[�h */									
	SCI1.SCSMR.BIT.OE = 0;				//	0�F�����p���e�B
										//	1�F��p���e�B
	/* �X�g�b�v�r�b�g�����O�X */									
	SCI1.SCSMR.BIT.STOP = 0;			//	0�F1 �X�g�b�v�r�b�g*1
										//	1�F2 �X�g�b�v�r�b�g*2
	/* �}���`�v���Z�b�T���[�h */									
	SCI1.SCSMR.BIT.MP = 0;				//	0�F�}���`�v���Z�b�T���[�h���֎~
										//	1�F�}���`�v���Z�b�T���[�h�����i�������������[�h�̂ݗL���j
	/* �N���b�N�Z���N�g1�A0 */									
	SCI1.SCSMR.BIT.CKS = 0;				//	00�FP�ӃN���b�N
										//	01�FP��/4 �N���b�N
										//	10�FP��/16 �N���b�N
										//	11�FP��/64 �N���b�N

	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �����܂� //////////////////////
	
	////////////////////// �r�b�g���[�g�ݒ�	�������� /////////////////////////
#ifdef	asynchro_38400		
		SCI1.SCBRR = 19;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 19	
#endif
#ifdef	asynchro_19200		
		SCI1.SCBRR = 40;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI1.SCBRR = 80;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// �r�b�g���[�g�ݒ�	�����܂� /////////////////////////						

	///////////////// �g�p����O���[�q��PFC�̐ݒ� �������� ///////////////////	
	PFC.PACRL1.BIT.PA3MD = 1;			// PA3�̓��o�͐ݒ�(����)	***RXD1_SCI_0***
	PFC.PACRL2.BIT.PA4MD = 1;			// PA4�̓��o�͐ݒ�(�o��)	***TXD1_SCI_0***
//	PFC.PACRL2.BIT.PA5MD = 1;			// SCK1 ���o�͐ݒ�(���o�́j	***SCK1_SCI_0***
	///////////////// �g�p����O���[�q��PFC�̐ݒ� �����܂� ///////////////////
	
	////////////////////// SCSCR���W�X�^�ݒ� �������� ////////////////////////
#ifdef	sci1_asynchro_tx			
	SCI1.SCSCR.BIT.TE   = 1;  			// �g�����X�~�b�g�C�l�[�u��:���M���������
	SCI1.SCSCR.BIT.TIE  = 0; 			// ���M���荞�ݗv�����֎~
	SCI1.SCSCR.BIT.TEIE = 0;			// ���M�������荞�ݗv�����֎~
#endif//sci0_asynchro_tx	

#ifdef	sci1_asynchro_rx	
    SCI1.SCSCR.BIT.RE  = 1;  			// ���V�[�u�C�l�[�u��:��M���������
//	SCI1.SCSCR.BIT.TE  = 1;  			// �g�����X�~�b�g�C�l�[�u��:���M���������
	SCI1.SCSCR.BIT.RIE = 1; 			// ��M���荞�ݗv��������
    SCI1.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
#endif//sci0_asynchro_rx

#ifdef	sci1_asynchro_txrx
	SCI1.SCSCR.BYTE |= 0x30;			// ����M���������	
	SCI1.SCSCR.BIT.RIE = 1; 			// ��M���荞�ݗv��������
    SCI1.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
#endif//sci0_asynchro_txrx
	////////////////////// SCSCR���W�X�^�ݒ� �����܂� ////////////////////////

	///////////////// SCI0�̊��荞�݃��x����ݒ� �������� ////////////////////
#ifdef	sci1_asynchro_tx
	INTC.IPRL.BIT._SCI1 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci1_asynchro_tx
#ifdef	sci1_asynchro_rx
	INTC.IPRL.BIT._SCI1 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci1_asynchro_rx
#ifdef	sci1_asynchro_txrx
	INTC.IPRL.BIT._SCI1 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci1_asynchro_txrx
	///////////////// SCI0�̊��荞�݃��x����ݒ� �����܂� ////////////////////
	
	//////////////////////// #define ������ �������� /////////////////////////
	#undef asynchro_38400						// �{�[���[�g    38,400 �����������[�h
	#undef asynchro_19200						// �{�[���[�g    19,200 �����������[�h
	#undef asynchro_9600						// �{�[���[�g    9,600  �����������[�h
	#undef sci1_asynchro_tx						// ���M�ɐݒ�
	#undef sci1_asynchro_rx						// ��M�ɐݒ�
	#undef sci1_asynchro_txrx					// ����M�ɐݒ�
	//////////////////////// #define ������ �����܂� /////////////////////////
}

/********************************************************/
//  ���O      
//		sci2_asynchronous_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2�����������̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci2_asynchronous_init() 
{	
	////////////////////////// ���[�h��I�� �������� //////////////////////////
//	#define asynchro_38400						// �{�[���[�g    38,400 �����������[�h
//	#define asynchro_19200						// �{�[���[�g    19,200 �����������[�h
	#define asynchro_9600						// �{�[���[�g    9,600  �����������[�h

//	#define sci2_asynchro_tx					// ���M�ɐݒ�
	#define sci2_asynchro_rx					// ��M�ɐݒ�
//	#define sci2_asynchro_txrx					// ����M�ɐݒ�
	////////////////////////// ���[�h��I�� �����܂� //////////////////////////
	
	int cnt1,cnt2;		// delay_time�p

	/************* SCI0 �N���b�N�������[�h�ݒ� (SH/AVR�ƒʐM�p) **************/
	STB.CR3.BIT._SCI2=0;				// SCI�X�^���o�C����
	
    SCI2.SCSCR.BYTE = 0x00;				// SCSCR���W�X�^�N���A
	
	///////////////////// �N���b�N�\�[�X��I�� �������� //////////////////////			
	SCI2.SCSCR.BIT.CKE = 0;				/*	�������������[�h */
										//	00�F�����N���b�N�^SCK �[�q�͓��͒[�q�i���͐M���͖����j
										//	01�F�����N���b�N�^SCK �[�q�̓N���b�N�o��
										//	10�F�O���N���b�N�^SCK �[�q�̓N���b�N����
										//	11�F�O���N���b�N�^SCK �[�q�̓N���b�N����										
	///////////////////// �N���b�N�\�[�X��I�� �����܂� //////////////////////
	
	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �������� //////////////////////									
	/* �R�~���j�P�[�V�������[�h */								
    SCI2.SCSMR.BIT.CA = 0;				//	0�F�������������[�h
										//	1�F�N���b�N���������[�h
	/* �L�����N�^�����O�X */									
	SCI2.SCSMR.BIT.CHR = 0;				//	0�F8 �r�b�g�f�[�^
										//	1�F7 �r�b�g�f�[�^
	/* �p���e�B�C�l�[�u�� */									
	SCI2.SCSMR.BIT._PE = 1;				//	0�F�p���e�B�r�b�g�̕t���A����у`�F�b�N���֎~
										//	1�F�p���e�B�r�b�g�̕t���A����у`�F�b�N������*
	/* �p���e�B���[�h */									
	SCI2.SCSMR.BIT.OE = 0;				//	0�F�����p���e�B
										//	1�F��p���e�B
	/* �X�g�b�v�r�b�g�����O�X */									
	SCI2.SCSMR.BIT.STOP = 1;			//	0�F1 �X�g�b�v�r�b�g*1
										//	1�F2 �X�g�b�v�r�b�g*2
	/* �}���`�v���Z�b�T���[�h */									
	SCI2.SCSMR.BIT.MP = 0;				//	0�F�}���`�v���Z�b�T���[�h���֎~
										//	1�F�}���`�v���Z�b�T���[�h�����i�������������[�h�̂ݗL���j
	/* �N���b�N�Z���N�g1�A0 */									
	SCI2.SCSMR.BIT.CKS = 0;				//	00�FP�ӃN���b�N
										//	01�FP��/4 �N���b�N
										//	10�FP��/16 �N���b�N
										//	11�FP��/64 �N���b�N

	///////////////////// �ʐM�t�H�[�}�b�g�ݒ� �����܂� //////////////////////
	
	////////////////////// �r�b�g���[�g�ݒ�	�������� /////////////////////////
#ifdef	asynchro_19200		
		SCI2.SCBRR = 40;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI2.SCBRR = 80;				// �r�b�g���[�g BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// �r�b�g���[�g�ݒ�	�����܂� /////////////////////////						

	///////////////// �g�p����O���[�q��PFC�̐ݒ� �������� ///////////////////	
	PFC.PACRL3.BIT.PA8MD = 6;			// PA8�̓��o�͐ݒ�(����)	***RXD2_SCI_2***
	PFC.PACRL3.BIT.PA9MD = 6;			// PA9�̓��o�͐ݒ�(�o��)	***TXD2_SCI_2***	
	///////////////// �g�p����O���[�q��PFC�̐ݒ� �����܂� ///////////////////
	
	////////////////////// SCSCR���W�X�^�ݒ� �������� ////////////////////////
#ifdef	sci2_asynchro_tx			
	SCI2.SCSCR.BIT.TE=1;  				// �g�����X�~�b�g�C�l�[�u��:���M���������
	SCI2.SCSCR.BIT.TIE = 0; 			// ���M���荞�ݗv�����֎~
	SCI2.SCSCR.BIT.TEIE = 0;			// ���M�������荞�ݗv�����֎~
#endif//sci0_asynchro_tx	

#ifdef	sci2_asynchro_rx	
    SCI2.SCSCR.BIT.RE=1;  				// ���V�[�u�C�l�[�u��:��M���������	
    SCI2.SCSCR.BIT.RIE=1; 				// ��M���荞�ݗv��������
    SCI2.SCSCR.BIT.TIE=0; 				// ���M���荞�ݗv�����֎~
#endif//sci0_asynchro_rx

#ifdef	sci2_asynchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* ���ӃN���b�N�S�N���b�N�ȏ�ҋ@ */	
	SCI2.SCSCR.BYTE |= 0x30;			// ����M���������	
	SCI2.SCSCR.BIT.RIE = 1; 			// ��M���荞�ݗv��������
	SCI2.SCSCR.BIT.TIE = 1; 			// ���M���荞�ݗv��������
#endif//sci0_asynchro_txrx
	////////////////////// SCSCR���W�X�^�ݒ� �����܂� ////////////////////////

	///////////////// SCI0�̊��荞�݃��x����ݒ� �������� ////////////////////
#ifdef	sci2_asynchro_tx
	INTC.IPRL.BIT._SCI2 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci2_asynchro_tx
#ifdef	sci2_asynchro_rx
	INTC.IPRL.BIT._SCI2 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci2_asynchro_rx
#ifdef	sci2_asynchro_txrx
	INTC.IPRL.BIT._SCI2 = 14;       	// ���荞�݃��x���ݒ�(SCI0)0�`15 0:�Œ� 15:�ō�
#endif//sci2_asynchro_txrx
	///////////////// SCI0�̊��荞�݃��x����ݒ� �����܂� ////////////////////
	
	//////////////////////// #define ������ �������� /////////////////////////
	#undef asynchro_38400						// �{�[���[�g    38,400 �����������[�h
	#undef asynchro_19200						// �{�[���[�g    19,200 �����������[�h
	#undef asynchro_9600						// �{�[���[�g    9,600  �����������[�h
	#undef sci2_asynchro_tx						// ���M�ɐݒ�
	#undef sci2_asynchro_rx						// ��M�ɐݒ�
	#undef sci2_asynchro_txrx					// ����M�ɐݒ�
	//////////////////////// #define ������ �����܂� /////////////////////////
}

/********************************************************/
//  ���O      
//		send_c
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void send_c(char c)
{
	while (SCI0.SCSSR.BIT.TDRE==0);
    SCI0.SCSSR.BIT.TDRE=0;	
    SCI0.SCTDR=c;
}

/********************************************************/
//  ���O      
//		rec_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rec_c(void)
{
	char c;
	
    while ((SCI0.SCSSR.BYTE & 0x40)==0);
	
    c = SCI0.SCRDR;
	SCI0.SCSSR.BYTE = SCI0.SCSSR.BYTE & 0xBF;
	
	return c;
}

/********************************************************/
//  ���O      
//		tx_0	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0���瑗�M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void tx_0(char send)
{
	SCI0.SCTDR = send;			// SCTDR�ɑ��M�f�[�^����������
	SCI0.SCSSR.BIT.TDRE = 0;	// SCSSR��TDRE�t���O��0�ɃN���A
}

/********************************************************/
//  ���O      
//		rx_0	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0�����M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rx_0(void)
{
	char rec;

    rec = SCI0.SCRDR;			// SCTDR�����M�f�[�^��ǂݍ���
	SCI0.SCSSR.BIT.RDRF = 0;	// SCSSR��RDRF�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/
//  ���O      
//		txrx_0	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0���瑗��M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char txrx_0(char send)
{
	char rec;
	
	while(SCI0.SCSSR.BIT.TDRE==0);
	
	SCI0.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI0.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A

	do
	{
		if(SCI0.SCSSR.BIT.ORER == 1)
		{
			SCI0.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI0.SCSSR.BIT.RDRF==0);
	
	SCI0.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI0.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/
//  ���O      
//		put_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void put_c(char c)		
{											
    while (SCI1.SCSSR.BIT.TDRE==0);
    SCI1.SCSSR.BIT.TDRE=0;	
    SCI1.SCTDR=c;
}

/********************************************************/
//  ���O      
//		put_s	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���當���񑗐M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void put_s(char str[])		
{									
    unsigned int lp=0;
    while(str[lp] != 0)
	{
        put_c(str[lp]);
        lp++;
	}
}

/********************************************************/
//  ���O      
//		get_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		��M�����f�[�^
//  �쐬��
//		TUTrobo
//
/********************************************************/
char get_c(void)		
{									
    char c;
	
	while ((SCI1.SCSSR.BYTE & 0x40)==0);
    
	c = SCI1.SCRDR;
	SCI1.SCSSR.BYTE = SCI1.SCSSR.BYTE & 0xBF;
	
	return c;
}

/********************************************************/
//  ���O      
//		tx_1	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���瑗�M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void tx_1(char send)
{
	SCI1.SCTDR = send;			// SCTDR�ɑ��M�f�[�^����������
	SCI1.SCSSR.BIT.TDRE = 0;	// SCSSR��TDRE�t���O��0�ɃN���A
}

/********************************************************/
//  ���O      
//		rx_1	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2�����M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rx_1(void)
{
	char rec;

    rec = SCI1.SCRDR;			// SCTDR�����M�f�[�^��ǂݍ���
	SCI1.SCSSR.BIT.RDRF = 0;	// SCSSR��RDRF�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/
//  ���O      
//		txrx_1	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���瑗��M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char txrx_1(char send)
{
	char rec;
	
	while(SCI1.SCSSR.BIT.TDRE==0);
	
	SCI1.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI1.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A

	do
	{
		if(SCI1.SCSSR.BIT.ORER == 1)
		{
			SCI1.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI1.SCSSR.BIT.RDRF==0);
	
	SCI1.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI1.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/
//  ���O      
//		transmit_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void transmit_c(char c)
{
     while (SCI2.SCSSR.BIT.TDRE==0);
    SCI2.SCSSR.BIT.TDRE=0;	
    SCI2.SCTDR=c;					//�V���A�����M����f�[�^���i�[
}

/********************************************************/
//  ���O      
//		accept_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char accept_c(void)
{
	char accept;
	
    while ((SCI2.SCSSR.BYTE & 0x40)==0);
	
    accept = SCI2.SCRDR;
	SCI2.SCSSR.BYTE = SCI2.SCSSR.BYTE & 0xBF;
	
	return accept;
}

/********************************************************/
//  ���O      
//		tx_2	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2���瑗�M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void tx_2(char send)
{
	SCI2.SCTDR = send;			// SCTDR�ɑ��M�f�[�^����������
	SCI2.SCSSR.BIT.TDRE = 0;	// SCSSR��TDRE�t���O��0�ɃN���A
}

/********************************************************/
//  ���O      
//		rx_2	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2�����M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rx_2(void)
{
	char rec;

    rec = SCI2.SCRDR;			// SCTDR�����M�f�[�^��ǂݍ���
	SCI2.SCSSR.BIT.RDRF = 0;	// SCSSR��RDRF�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/
//  ���O      
//		txrx_2	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2���瑗��M(���荞�ݎg�p��)
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char txrx_2(char send)
{
	char rec;
	
	while(SCI2.SCSSR.BIT.TDRE==0);
	
	SCI2.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI2.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A

	do
	{
		if(SCI2.SCSSR.BIT.ORER == 1)
		{
			SCI2.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI2.SCSSR.BIT.RDRF==0);
	
	SCI2.SCTDR=send;				// SCTDR�ɑ��M�f�[�^����������
	SCI2.SCSSR.BIT.TDRE=0;			// SCSSR��TDRE�t���O��0�ɃN���A
	
	return rec;
}

/********************************************************/	
//  �T�v
//      SCI�֘A
//  �@�\����
//		printf�Ŏg���^��������
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
p_table clear(p_table table)
{
	table.z[0] = 0;
	table.z[1] = 0;
	table.n = 0;
	table.l = 0;
	table.m = 0;
	table.var = 0;
	table.base = 0;
	
	return(table);
}

/********************************************************/
//  ���O      
//		printf	
//  �T�v
//      SCI�֘A
//  �@�\����
//		���������͂���convert�ɂ킽���B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
int printf(const char *str, ...)
{
	p_table table;
	va_list list;
	char c;
	int p,i;
	double v_double;

	va_start(list, str);									//�ψ����ɃA�N�Z�X����O�̏�������
	while(1){
		while((c = *str++) != '%'){							//%���o�Ă���܂ł܂Ń��[�v
			if(c == '\0')return(10);						//NULL�������炨���??
			if(c == '\n')put_c('\r');						//���s
			put_c(c);										//�\��
		}
		table = clear(table);								//table������
		p = 0;												//p������
//      if((*str)=='%')SCI3_OUT_DATA(*str++);   			// '%'�o��
		while(1){
			c = *str++;										//���̕�����GO�I	
 			if(c >= '0' && c <='9'){						//0�`9�܂ł�char�̂Ƃ�
				table.z[p] *= 10;table.z[p] += c - '0';		//�\�������錅����F��
			}else if((c == '.') && (p == 0))p++;			//c��'.'��p��0�̂Ƃ��@p��1
			else if(c == 'l')table.l = 1;					//long int �Ȃ�
			else{
				switch(c){								
					case 'd':								//d�̏ꍇ
					case 'D':								//D�̏ꍇ
						table.base = 10L;					//convert�Ŏg���@����萔
						table.var = va_arg(list, int);		//�ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
						if((long)table.var < 0){			//�l�����̎�
							table.m = 1;					//convert�Ŏg�����̐���1����
							table.var *= -1;				//convert�Ń}�C�i�X�ɂȂ�Ȃ��悤�ɂ��邽��
						}
						convert(table);						//�\��
						break;								//break
					case 'f':								//f�̏ꍇ
					case 'F':								//F�̏ꍇ
						table.base = 10L;					//convert�Ŏg���@����萔�@�i����������int�Ɠ������e�j			
						v_double = va_arg(list, double);	//�ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
						if(v_double < 0){					//�l�����̎�
							table.m = 1;					//convert�Ŏg�����̐���1����
							v_double *= -1;					//convert�Ń}�C�i�X�ɂȂ�Ȃ��悤�ɂ��邽��
						}
						table.var = (long)v_double;			//���������������	
						table.z[0] -= table.z[1]+1;			//���������̌��������i+�P��.�̕����j
						convert(table);						//�\���@�i������ւ�܂�int�Ɠ������e�j
						put_c('.');							//'.'��\��������
						table.z[0] = 1;						//�����������ꌅ�ɂ���
						table.m = 0;						//table.m��������		
						if(table.z[1]==0)table.z[1]=6;		//table.z[1]��0�̂Ƃ������_�ȉ�6����\������
						for(i=0;i<(table.z[1]-1);i++){		
							v_double *= 10;					//�����_�ȉ��̌��𐮐������ɂ���
							table.var = (long)v_double % 10;//���������ɂ���������
							convert(table);					//�\��
						}
						v_double *= 10;						//?
						table.var = (long)v_double % 10;	//?
						convert(table);						//?
						break;
					case 'b':
					case 'B':
					case 'c':
					case 'C':
					case 'o':
					case 'O':
					case 'x':
					case 'X':
					case 's':
					case 'S':
						put_s(va_arg(list, char *));		//?
						break;
					default:str--;							//���������O�ɖ߂��@���̂܂ܕ\������
				}
				break;										//while���ʂ���
			}
		}
	}
	va_end(list);											//�ψ����ɃA�N�Z�X������̏I������
	return(10);												//?
}

/********************************************************/
//  ���O      
//		convert	
//  �T�v
//      SCI�֘A
//  �@�\����
//		printf�����������������\��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void convert(p_table table)
{
 
 	char s[20];												//�\���p�̕�����
 	int i=19,cnt=0;											//i���ǂ��ɂ��̕���������̂������߂�J�E���g�@cnt���\���������Ԃ����߂�J�E���g

	for(i=0;i<20;i++)s[i]=' ';								//�󔒂̂�20�����
	i=19;													//i������������
	if(table.var == 0){										//���l��0�̂Ƃ�
		s[i--] = '0';										//s[19]��'0'��������
		cnt++;												//�\����Ԃ�1���₷
	}
	while(table.var){										//table.var��0�ȊO�̎����[�v
		s[i--] = (table.var % table.base) + '0';			//int����char�ɕϊ�
		table.var /= table.base;							//���̌���GO!
		cnt++;												//�\����Ԃ�1���₷
	}
	if(table.m)s[i] = '-';									//table.m��1�̂Ƃ��}�C�i�X�̕���������
	cnt += table.m;											//table.m��1�̂Ƃ��\����Ԃ�1���₷
	if(cnt < table.z[0])cnt = table.z[0];					//table.z[0]��cnt���傫���ꍇcnt��table.z[0]�Ɠ����ɂ���@�\�����������̌����ǂݍ��񂾐��������������ꍇ�󔒂ɂ���B
	for(i=20-cnt;i<20;i++){									//������𔽓]�����Ȃ���cnt���̋�ԕ����[�v
		put_c(s[i]);										//�\��
	}
	
}

/********************************************************/
//  ���O      
//		itoa
//  �T�v
// 		SCI�֐�
//  �@�\����
//		int��char�ϊ�
//  �p�����^����
//		value	int�^�̕�����
//		buff[]	int�^�̕�����char�^�̕�����ɂȂ�i�[�����
//		radix	���i�����@�Ⴆ��10�i���Ȃ�10
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void itoa(int value,char buff[],int radix)
{
	static const char table[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char *head = buff;
	char *tail = buff;
	char temp;
	
	//�}�C�i�X�����𕶎���ɕϊ�
	if(value<0){
		*tail++='-';
		value=-value;
	}
	//�����l�𕶎���ɕϊ�
	if(value==0){
 		*tail++='0';
	}
	else{
		for(head=tail;value!=0;value=value/radix){
			 *tail++ = table[value%radix];
 		}
	}
	*tail='\0';
	//������̍��E����ւ�
	for(tail--;head<tail;head++,tail--){
		temp=*head;
		*head=*tail;
		*tail=temp;
	}
}