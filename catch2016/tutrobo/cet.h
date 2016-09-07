/********************************************************/
//
//  �T�v
//      CET�֘A
//  �쐬��
//		Ido
//
/********************************************************/

#ifndef __CET_H__
#define __CET_H__

#define USE_CET			//CET�g�p
#define TIMER_START(ch) (CMT.CMSTR1.BIT.STR##ch)
/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A �v���g�^�C�v�錾
/********************************************************/
void cet_set_timer(char encnum, char onoff);
char cet_get_timer(char encnum);
void cet_init(void);
unsigned short* get_enc_tcnt(char num);
void cet_edge_action(char encnum);
void cet_clear_action(char encnum);
void cet_get_rpm(double rot_return[]);

/*
unsigned int g_cet_start_clock[ENCODER_NUM];
int g_cet_cntup[ENCODER_NUM],g_cet_tcnt[ENCODER_NUM],g_cet_elapsed[ENCODER_NUM];

unsigned short* g_enc_tcnt[ENCODER_NUM]
*/

struct cet_data{
	unsigned short* enc_tcnt;	//�G���R�[�_�[�J�E���g���W�X�^�ւ̃A�h���X
	unsigned short* timer_tcnt;	//�^�C�}�[�J�E���g���W�X�^�ւ̃A�h���X
	unsigned int start_clock;	//�J�E���g�J�n���̃^�C�}�[�N���b�N
	int cntup;					//�J��オ���
	int last_tcnt;				//�Ō�ɋL�^���ꂽ�G���R�[�_�J�E���g
	int last_elapsed;			//�Ō�ɋL�^���ꂽ�J�E���g����
};

#endif // __CET_H__