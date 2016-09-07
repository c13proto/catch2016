/********************************************************/
//
//  �T�v
//      �}�V���ړ�����֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/

#ifndef __CONTROL_H__
#define __CONTROL_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A �v���g�^�C�v�錾
/********************************************************/
void cmd_init(void);			// �R�}���h�̏����ݒ�
char mode_control(void);		// ���[�h�̑I��
void task_control(void);		// �ꍇ�킯������path�̓������s��


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A �R�}���h���
/********************************************************/
#define CMD_HOLD			0				// �p��
#define CMD_END				1				// �I��
#define CMD_END_ALL			2				// �S�ďI��(�^�X�N��~)

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A �w��T�C�N���҂�(wait_cycle)�p
/********************************************************/
#define WAIT_CNT_FINISH		0				// �J�E���g�I��
#define WAIT_CNT_CONTINUE	1				// �J�E���g�p��

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A PATH�֘A
/********************************************************/
extern unsigned short task_number;
extern struct comand_information cmd_inf;	// comArray�̒l���󂯎��^

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �}�V���ړ�����֘A �v���g�^�C�v�錾
/********************************************************/
void enc_getrot(double *rot);
void pcon_update(char num, double current);
void pcon_setting(char num, double lim, double tlrnce);
void pcon_gain(char num, double gain_P, double gain_I, double gain_D);
void pcon_motor(char num, double duty, char sign);
double pcon_pid(char num,double target);
double pcon_manual(char num,double duty);
int comm_action(char cmd,int data);
char shoot_seq(char flag,double *rot);
char reload_seq(char flag,int ad[4],int ad_old[4]);
int terminal_control(char c);
void shooter_control(void);
/********************************************************/
//  TUTrobo
//
//  �T�v
//      �G���R�[�_�֘A�p�����[�^
/********************************************************/
//0�`1�̒l���w�肷�邱�ƁB���݈ʒu��0�C�I�_��1
#define ENC_D	40	//�G���R�[�_�[�z�C�[�����a (���Ԃ̏ꍇ�A���W���[��1*����40�ŋ��܂�)
#define	RND_PLS	800		//���]�̃p���X��
//#define PI		3.1416  //�~����
/********************************************************/
//  TUTrobo
//
//  �T�v
//      ����֘A�p�����[�^
/********************************************************/
#define	MM_PER_ROT	2.0		//#�G���R�[�_�[���]�ŕω�����ʒu[mm]
#define	CENTER_MM	55.5	//#0�x�̎��̃��[�^�[�ʒu[mm] 49-43 OLD:57.5
#define	ROT_RADIUS	150.0	//#����@�\�̉�]���a[mm] 207.5
#define DEBUG_NUM	2	//tera=0���Ɍ��ݒl�̃O���t�o�͂�����PCON�ԍ�

/********************************************************/
//  TUTrobo
//
//  �T�v
//      IDO�֘A �O���[�o���ϐ��ݒ�
/********************************************************/
extern char c_dbg[10];
extern char cnt_dbg;
extern int recv_cnt;
extern char print_g;
extern double print_data[4][21];

extern int send_flg;

extern struct command_parameters cmdp;
extern struct pid_config pcon[];
extern struct pid_status psta[];

extern int ad_debug_g[4],tera;
extern char encd_g,enc_reset_g;
extern double rot_cnt_g[2],pid_duty_g[2],p1_g,i1_g,p2_g,i2_g,p3_g,i3_g;



#endif // __CONTROL_H__