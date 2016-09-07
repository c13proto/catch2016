/********************************************************/
//
//  �T�v
//      �}�V���ړ�����֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/

#include "setup.h"		//�}�C�R���̐ݒ�



//�O���[�o���ϐ��錾//
struct comand_information cmd_inf;			// comArray�̒l���󂯎��^
struct machine_condition macond;			// �}�V����񂪊i�[����Ă���
struct gyro_condition gcond;				// �W���C���̏��
unsigned short task_number;					// task_control�Ŏg�p
unsigned char task_mode;					// task�̃��[�h�I���Ŏg�p

#if 0

//�I���W�i��K//
double ratio;
/********************************************************/
//
//  �T�v
//      �}�V���ړ�����֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/
#ifdef USE_CET
	#define CONTROL_CYCLE	0.01	//�������[s]
#else
	#define CONTROL_CYCLE	0.01	//�������[s]
#endif
#define FILTER_TIME		0.1		//�ꎟ�x��t�B���^�W��(���g�p)
#define PCON_NUM	4	//pid_config�̐�
#define VEL_PID		//define����Ƒ��x�^PID���s��

//���ˊ֘A
#define DEFAULT_SHOOT_SPEED	3100 //������]���x[RPM]
#define SHT_LIMIT 5500 //0.5[r/10ms]	������]���x[RPM]
#define ANG_LIMIT 10 //10�x
#ifndef VEL_PID
	//�ʒu�^PID�p�Q�C��
	#define ROLLER_P_GAIN 0.3//0.01 //���˃��[���[�pP�Q�C��
	#define ROLLER_I_GAIN 0.1//0.2 //���˃��[���[�pI�Q�C��
	#define ROLLER_D_GAIN 0.1//0.01 //���˃��[���[�pD�Q�C��	
#else
	//���x�^PID�p�Q�C��
	#define ROLLER_P_GAIN 0.15//0.1 //���˃��[���[�pP�Q�C��
	#define ROLLER_I_GAIN 0.1//0.075 //���˃��[���[�pI�Q�C��
	#define ROLLER_D_GAIN 0.1//0.003 //���˃��[���[�pD�Q�C��	
#endif
#define ROLLER_TOLERANCE 50.0	//���˃��[���[���e�덷

//���U���u�֘A
#define RELOAD_DEFAULT_AD	443//500������Ԃł�AD�l(�ڂݎ󂯓n���҂�)
#define RELOAD_SHOOT_AD		875//���ˎ���AD�l
#ifndef VEL_PID
	//�ʒu�^PID�p�Q�C��
	#define RELOAD_P_GAIN	0.04 //P�Q�C��
	#define RELOAD_I_GAIN	0.00 //I�Q�C��
	#define RELOAD_D_GAIN	0.00 //D�Q�C��
#else	
	//���x�^PID�p�Q�C��
	#define RELOAD_P_GAIN	0.03 //P�Q�C��
	#define RELOAD_I_GAIN	0.02 //I�Q�C��
	#define RELOAD_D_GAIN	0.0 //D�Q�C��
#endif
#define RELOAD_DUTY_LIM	80	//DUTY����
#define RELOAD_TOLERANCE	50	//AD�l���e�덷
#define RELOAD_THRESHOLD	50	//�����ʒu�ɖ߂�ۂɂ��̐����ȏ�΍�������΃I���ɂ���

//��{�ڑ��U�֘A
#define RELOAD2_DEFAULT_AD	835	//������Ԃł�AD�l(���U�ʒu)
#define RELOAD2_WAIT_AD		150	//�ڂݎ󂯓n���҂��̈ʒu��AD�l
#define RELOAD2_SHOOT_AD	150	//���ˎ��̈ʒu��AD�l
#ifndef VEL_PID
	//�ʒu�^PID�p�Q�C��
	#define RELOAD2_P_GAIN	0.2 //P�Q�C��
	#define RELOAD2_I_GAIN	0.0 //I�Q�C��
	#define RELOAD2_D_GAIN	0.0 //D�Q�C��
#else
	//���x�^PID�p�Q�C��
	#define RELOAD2_P_GAIN	0.2 //P�Q�C��
	#define RELOAD2_I_GAIN	0.0 //I�Q�C��
	#define RELOAD2_D_GAIN	0.0 //D�Q�C��
#endif
#define RELOAD2_DUTY_LIM	50		//DUTY����
#define RELOAD2_TOLERANCE	20		//AD�l���e�덷


#define TERATERM_COMU //�e���^�[�~�i�����g���ē�����
#define DEBUG_MODE //�f�o�b�O�p
#define SENKAI_INIT

/********************************************************/
//  TUTrobo
//
//  �T�v
//      IDO�֘A �O���[�o���ϐ��ݒ�
/********************************************************/
int ad_debug_g[4];
char encd_g = 0;
double rot_cnt_g[2],pid_duty_g[2],p1_g=0.0,i1_g=0.0,p2_g=0.0,i2_g=0.0,p3_g=0.0,i3_g=0.0;
#ifdef TERATERM_COMU
	char c_dbg[10];
	char cnt_dbg = 0;
#endif
int recv_cnt=0;
int send_flg=0;
char print_g=0;
double print_data[4][21];

struct command_parameters cmdp={
	0, //���ˉ�]���x
	0, //����p�x
	0, //���ˊJ�n
	0, //����J�n
	0, //�������쓮
	-1, //�đ��U���
	0, //���샂�[�h 1:���˗p���[���[���� 2:����A�������A�đ��U����
	-1,
	0,
};

/******** �e��PID����ɗp����p�����[�^�͈ȉ��������� ********/ 
struct pid_config pcon[PCON_NUM]={
//	�o�͐�				�ő�Duty			���e�덷			P�Q�C��				I�Q�C��				D�Q�C��		
	{&(ROLLER1_PWM),	100.0,				ROLLER_TOLERANCE,	ROLLER_P_GAIN,	ROLLER_I_GAIN,	ROLLER_D_GAIN}, //���[���[���
	{&(ROLLER2_PWM),	100.0,				ROLLER_TOLERANCE,	ROLLER_P_GAIN,	ROLLER_I_GAIN,	ROLLER_D_GAIN},	//���[���[���
	{&(RELOAD1_PWM),	RELOAD_DUTY_LIM,	RELOAD_TOLERANCE,	RELOAD_P_GAIN,	RELOAD_I_GAIN,	RELOAD_D_GAIN},//���U
	{&(RELOAD2_PWM),	RELOAD2_DUTY_LIM,	RELOAD2_TOLERANCE,	RELOAD2_P_GAIN,	RELOAD2_I_GAIN,	RELOAD2_D_GAIN},//��{�ڑ��U		
};

struct pid_status psta[PCON_NUM]; //PCON�̊e���Ԃ��i�[����ϐ�

double sP_g=0.0,sI_g=0.0,sD_g=0.0;

/********************************************************/
//  ���O      
//		shooter_control
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		���ˑS�ʂ̐���
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void shooter_control(void){
	static int ad_old[4]={9999,9999,9999,9999},ad_proper[4]={9999,9999,9999,9999};
	static char first=0,print_num=0;
//	static unsigned char end_cnt[4]={0,0,0,0};
//	static char enc_reset_g=0;
	
	double rot[2];
	int ad[4],i;//,counter;
	char for_n;
	
	//��M�f�[�^����
//	if(cmdp.mode == 1)controller_data(); //���[�h1�̊�Ղł̂݃R���g���[���[��ǂ�
	
	//�Z���T�[�f�[�^����
	#ifdef USE_CET
	cet_get_rpm(rot); //�Ō�ɋ��߂�ꂽ��]����rot�ɑ��
	//���ʂ����ǁA�O�̎d�l����rot��10ms�Ԃł̉�]���Ȃ̂ŁA�݊�����ۂ��߂ɏ��Z
	rot[0] /= -6000.0;
	rot[1] /= -6000.0;
	#else
	enc_getrot(rot); //�G���R�[�_�[�J�E���g����Ɏ���]�������߂�
	#endif
	
	ad_load_0_3(ad);
	
	//AD�l������
	if(first==0){
	for(i=0; i<4; i++){
		ad_debug_g[i] = ad[i]; //ad[i]
		if(ad_old[i] == 9999)
			ad_old[i] = ad[i];
	}
		first=1;
	}
	
	PC_data();
	if(cmdp.shot_dbg){
		directions(&com[1],(int)(psta[DEBUG_NUM].current[0]),6);
	//	directions(&com[1],(int)(psta[0].current[0]),7);
	}
	
	switch(shoot_flag_g){
		case 0: //����
			//cmdp.reload = -1;
			//cmdp.shot = 0;
			break;
		
		case 1: //�c�؎󂯎��
		//	cmdp.reload = 0;
			break;
			
		case 2: //���[���[��]
			cmdp.shot = 1;
			LASER_OUT=1;
			break;
	}
	
	
	//���˃V�[�P���X
	shoot_seq(cmdp.shot,rot);
	//print_g++;
	//�đ��U�V�[�P���X
	reload_seq(cmdp.reload,ad,ad_old);
	
	if(tera==0){
		if(print_data[DEBUG_NUM][0] == -1.0 && print_num > 0){
			for(for_n=0; for_n<print_num-1; for_n++){
				print_data[DEBUG_NUM][for_n] = print_data[DEBUG_NUM][for_n+1];
			}
			print_data[DEBUG_NUM][print_num-1] = -1.0;
			print_num--;
			//put_s("MINUS\n");
		}
		//put_s("CONTAIN\n");
		if(cmdp.shot_dbg){
			print_data[DEBUG_NUM][print_num] = fabs(psta[DEBUG_NUM].current[0]);
			if(print_num >= 20){
				print_data[DEBUG_NUM][print_num-1] = (print_data[DEBUG_NUM][print_num-1] + print_data[DEBUG_NUM][print_num]) / 2;
				//put_s("OVERFLOW\n");
			}
			else
				print_num++;
		}
	}
	
	//���l�X�V
//	rot_old[0]=rot[0];
//	rot_old[1]=rot[1];
	for(i=0; i<4; i++){
		if(abs(ad[i]-ad_old[i]) < 100 && ad_old[i] != 9999)
			ad_old[i] = ad[i]; //ad[i]
		else if(ad_old[i] != 9999){
			ad_old[i] = 9999;
			ad_proper[i] = ad[i];
		}else if(ABS(ad[i]-ad_proper[i]) < 100){
			ad_old[i] = ad[i];
			ad_proper[i] = 9999;
		}
			
	}
	/*ad_old[0] = ad[0];
	ad_old[1] = ad[1];
	ad_old[2] = ad[2];
	ad_old[3] = ad[3];
	*/
}

/********************************************************/
//  ���O      
//		shoot_seq
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�p�����[�^�ɉ����Ĕ��˃V�[�P���X���s��
//	���ӎ���
//		
//  �p�����^����
//		
//  �߂�l
//		
//  �쐬��
//		IDO
//
/********************************************************/
char shoot_seq(int flag,double *rot){
	static char cnt=0;
	double target,duty0,duty1;
	//����]���x�𒴂������~ & �m�C�Y�΍�
	if(fabs(rot[0]*6000.0) > SHT_LIMIT || fabs(rot[1]*6000.0) > SHT_LIMIT){
		cnt++;
		if(cnt >= 10){
			ROLLER1_PWM = anti_lock_pwm(0.0);
			ROLLER2_PWM = anti_lock_pwm(0.0);
			cmdp.shot = 0;
			cnt = 0;
		}
		return 0;
	} else {
		cnt = 0;
	}	
	pcon_update(0,rot[0]*6000.0);
	pcon_update(1,-rot[1]*6000.0);
	if(flag == 1){
		target = (double)cmdp.shot_spd;
		duty0 = pcon_pid(0,target);
		duty1 = pcon_pid(1,target);

		if(psta[0].end >= 12/(CONTROL_CYCLE*100) && psta[1].end >= 12/(CONTROL_CYCLE*100)){
			if(cmdp.shot_rdy) // && cmdp.reload == 2
				cmdp.reload = 3;
		}else if(cmdp.shot_rdy == -1){
			cmdp.shot_rdy = 0;
		}
	}else if(flag==0){
		duty0 = pcon_manual(0, 0.0);
		duty1 = pcon_manual(1, 0.0);
		cmdp.shot_rdy = -1;
	}else if(flag>1){
		duty0 = duty1 = 65.0;
		cmdp.shot_rdy = -1;
	}
	pcon_motor(0,-duty0,0);	//duty�o��
	pcon_motor(1,-duty1,0);	//duty�o��
	return 1;	
}

/********************************************************/
//  ���O      
//		reload_seq
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�p�����[�^�ɉ�����(��)���U�V�[�P���X���s��
//	���ӎ���
//		
//  �p�����^����
//		
//  �߂�l
//		
//  �쐬��
//		IDO
//
/********************************************************/
char reload_seq(char flag,int ad[4],int ad_old[4]){
	static unsigned int wait=0;
	double duty;
	char for_n;
	//1�{��		
	if(ad_old[0] != 9999){ //AD�l������ĂȂ���������s
		pcon_update(2,ad[0]);
		if(cmdp.reload < 3){ //�ҋ@��� �c�؎󂯓n���̂��ߓW�J
			duty = pcon_pid(2,(double)RELOAD_DEFAULT_AD);
		}
		else if(cmdp.reload == 3){ //���U ���U�ʒu�Ɉړ��A��莞�ԑҋ@��ɓW�J�ʒu��
			duty = pcon_pid(2,(double)RELOAD_SHOOT_AD);
			wait++;
			//sum += psta[2].current[0]-psta[2].current[1];
			if(psta[2].end > 0){
				//���U���̉��������͋@�B���x�̖���A�����_�ł͍s��Ȃ�
				//duty = 5.0; 
				if(psta[0].target[9]-psta[0].current[9] > 200 && psta[0].current[8] - psta[0].current[9] > 5 && psta[0].current[9] - psta[0].current[10] < -5 && tera==1 && print_g==0){
					print_g=1;
					for(for_n=0; for_n<20; for_n++){
						print_data[0][for_n] = psta[0].current[for_n];
						print_data[1][for_n] = psta[1].current[for_n];
						print_data[2][for_n] = psta[2].current[for_n];
						print_data[3][for_n] = (double)wait;
					}
				}			
					
				
				if(psta[2].end > 80/(CONTROL_CYCLE*100)){
					wait = 0;
					cmdp.reload = 0; //2 //�����ʒu�ɖ߂�
					comm_action('S',8); //���[���[��~
					put_s("END\n");
					//print_g=1;
					//for(for_n=0; for_n<10; for_n++){
					//	print_data[0][for_n] = psta[0].current[for_n];
					//	print_data[1][for_n] = psta[1].current[for_n];
					//}					
				}
			}
		}else if(cmdp.reload == 4){ //���U �Q�C�������p
			duty = pcon_pid(2,(double)RELOAD_SHOOT_AD);
			if(psta[2].end > 80/(CONTROL_CYCLE*100)){
				cmdp.reload = 5; //2
				psta[2].end = 0;
			}
		}else if(cmdp.reload == 5){ //���U �Q�C�������p
			duty = pcon_pid(2,(double)RELOAD_DEFAULT_AD);
			if(psta[2].end > 80/(CONTROL_CYCLE*100)){
				cmdp.reload = 4; //2
				psta[2].end = 0;
			}
		}				
		
		//�K�E�I���I�t����
		if(psta[2].target[0] == (double)RELOAD_DEFAULT_AD){ //���U���ɕςȋ������N�����Ȃ��悤�A�I���I�t�͏����ʒu�Ɍ������Ă��鎞�̂ݍs��
			if(psta[2].current[0] - psta[2].target[0] > RELOAD_THRESHOLD){ //�΍����������l��������������I��
				duty = -5.0;
				psta[2].duty = 0.0;
			}else if(psta[2].current[0] > psta[2].target[0]){ //�΍����������l�����Ⴂ���A��]�����͏����ʒu�ɖ߂�����Ȃ�I�t
				duty = 0.0;	
				psta[2].duty = 0.0;
			}		
	}
	}else{//AD�l������Ă��烂�[�^�[��~
		duty = 0.0;
	}
	pcon_motor(2,duty,1);	//duty�o��

	//2�{��
	if(ad_old[1] != 9999){ //AD�l������ĂȂ���������s
		pcon_update(3,ad[1]);
		
		//���ˈʒu�Ɉړ����鎞��Duty�������ɂ߂čō������グ��
		if(cmdp.reload == 1)
			pcon_setting(3,60,-1); 
		else
			pcon_setting(3,50,-1);
			
		if(cmdp.reload == -1){ //�����Z�b�g�A�b�v ���U�ʒu�Ɏ��[
			duty = pcon_pid(3,(double)RELOAD2_DEFAULT_AD);
		}else if(cmdp.reload == 0){ //�ҋ@��� �c�؎󂯓n���̂��ߓW�J
			duty = pcon_pid(3,(double)RELOAD2_WAIT_AD);
		}else if(cmdp.reload == 1){ //���U ���ˈʒu�Ɉړ�
			duty = pcon_pid(3,(double)RELOAD2_DEFAULT_AD);
			if(psta[3].end > 8/(CONTROL_CYCLE*100))
				cmdp.reload = 2;
		}else if(cmdp.reload >= 2){ //���U ���ˈʒu�Ɉړ�
			duty = pcon_pid(3,(double)RELOAD2_SHOOT_AD);
			}
	}else{
		duty = 0.0;

	}
	pcon_motor(3,duty,1);	//duty�o��
//	printf("%d\n",wait);
	return 1;
}

/********************************************************/
//  ���O      
//		enc_getrot
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�G���R�[�_�[�̒l���������ĉ�]���x�����߂�B
//	���ӎ���
//		
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//
/********************************************************/

void enc_getrot(double rot_return[]) 				
{
	static int cnt[2], cnt_old[2], cnt_diff[2];
	double rot[2];
	cnt[0] = ENC1_TCNT;//MTU21.TCNT;
	cnt[1] = ENC2_TCNT;//MTU22.TCNT;
	cnt_diff[0] = -1*(short)((unsigned short)cnt[0] - (unsigned short)cnt_old[0]); //�O��̊���ݎ��̃J�E���g���ƁA���݂̃J�E���g���̍�
	cnt_diff[1] = -1*(short)((unsigned short)cnt[1] - (unsigned short)cnt_old[1]); //�O��̊���ݎ��̃J�E���g���ƁA���݂̃J�E���g���̍�
	
	rot[0] = (double)cnt_diff[0] / RND_PLS; //�P�ʎ��Ԃŉ���]������
	rot[1] = (double)cnt_diff[1] / RND_PLS; //�P�ʎ��Ԃŉ���]������
	cnt_old[0] = cnt[0];
	cnt_old[1] = cnt[1];
	rot_return[0] = rot[0];
	rot_return[1] = rot[1];
}


/********************************************************/
//  ���O      
//		pcon_update
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		PCON���l&���ݒl�X�V
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ��A���ݒl
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//		
//
/********************************************************/
void pcon_update(char num, double current){
	char for_n;
	for(for_n=19; for_n>=0; for_n--){
		psta[num].target[for_n+1] = psta[num].target[for_n];
		psta[num].current[for_n+1] = psta[num].current[for_n];
	//	print_data[3][for_n+1] = print_data[3][for_n];
	}
	psta[num].current[0] = current;
	//print_data[3][0] = psta[num].duty;
	
/*	if(psta[num].intrpt_cnt<255)
		psta[num].intrpt_cnt++;
	else
		psta[num].intrpt_cnt=0;
*/
}
	
		
/********************************************************/
//  ���O      
//		pcon_setting
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		PCON�̊e��p�����[�^��ύX
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ��A�ő�A���e�덷
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//		
//
/********************************************************/
void pcon_setting(char num, double lim, double tlrnce){
	if(lim >= 0.0)
		pcon[num].duty_lim = lim;
	if(tlrnce >= 0.0)
		pcon[num].tlrnce = tlrnce;
	
}		

/********************************************************/
//  ���O      
//		pcon_gain
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		PCON�̊e��޲݂�ύX
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ��A�e�Q�C��
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//		
//
/********************************************************/
void pcon_gain(char num, double gain_P, double gain_I, double gain_D){
	if(gain_P >= 0.0)
		pcon[num].P_gain = gain_P;
	if(gain_I >= 0.0)
		pcon[num].I_gain = gain_I;
	if(gain_D >= 0.0)
		pcon[num].D_gain = gain_D;
}	
	
/********************************************************/
//  ���O      
//		pcon_motor
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		pcon.output�Ɏw�肳���A�h���X��DUTY���o��
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ��ADUTY�A�T�C���}�O�j�`���[�h�t���O
//  �߂�l
//		�Ȃ�
//  �쐬��
//		IDO
//	
//
/********************************************************/
void pcon_motor(char num, double duty, char sign){
	if(sign) //�Ō�̃t���O��1�Ȃ�T�C���}�O�j�`���[�h�p�̊֐��𗘗p���ďo��
		*(pcon[num].output) = sign_mag_pwm(duty);
	else
		*(pcon[num].output) = anti_lock_pwm(duty);
}		
	
/********************************************************/
//  ���O      
//		pcon_pid
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�^����ꂽPCON���ƖڕW�l��PID������s���ADuty��Ԃ�
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ��A�ڕW�l
//  �߂�l
//		Duty
//  �쐬��
//		IDO
//		
//
/********************************************************/
double pcon_pid(char num,double target){
	char for_n;
	double diff[3],sht_P,sht_I,sht_D,duty;
	
	psta[num].target[0] = target;
	//�ڕW���ς�������ɂ͓��B�t���O�A�����������l�A��Duty�A�ϕ�����(�ʒu�^�p)���N���A
	if(psta[num].target[1] != target){
		psta[num].end = 0;
		psta[num].D_old = 0;
		psta[num].duty = 0;
		psta[num].integr = 0;
	}
	
	for(for_n=0; for_n<3; for_n++){
		diff[for_n] = psta[num].target[for_n] - psta[num].current[for_n]; //�΍� diff[0]=���ݒl�Adiff[1]=��T�C�N���O�̒l
	}
	#ifndef VEL_PID
	//�ʒu�^PID
	sht_P = diff[0];
	if(sht_P*pcon[num].P_gain < pcon[num].duty_lim) //���тɓ�������ϕ����������Z
		psta[num].integr += diff[0] * (CONTROL_CYCLE * 100);
	else
		psta[num].integr = 0;
	sht_I = psta[num].integr;
	sht_D =  (diff[0] - diff[1]) / (CONTROL_CYCLE*100); // ((diff[1] - diff[2])*FILTER_TIME+(diff[0] - diff[1])) / (CONTROL_CYCLE*100);
	//sht_D = (pcon[num].current[1] - pcon[num].current[0]) / (CONTROL_CYCLE*100);
	pcon[num].duty = sht_P*pcon[num].P_gain + sht_I*pcon[num].I_gain  + sht_D*pcon[num].D_gain;
	#else
	//���x�^PID
	sht_P = diff[0] - diff[1]; //��ᐬ��
	sht_I = diff[0] * CONTROL_CYCLE; //�ϕ�����
	sht_D = (diff[0] + diff[2] - 2*diff[1]) / (CONTROL_CYCLE*100);  //��������
	//sht_D = (2*pcon[num].current[1] - pcon[num].current[0] - pcon[num].current[2]) / (CONTROL_CYCLE*100);
	psta[num].duty += sht_P*pcon[num].P_gain + sht_I*pcon[num].I_gain  + sht_D*pcon[num].D_gain; //duty���Z
	#endif
	psta[num].D_old = sht_D; //�������l�X�V
	
	
	duty = psta[num].duty;
	//duty����
	if(pcon[num].duty_lim != 0){
		if(duty > pcon[num].duty_lim)
			duty = pcon[num].duty_lim;
		if(duty < -pcon[num].duty_lim)
			duty = -pcon[num].duty_lim;
	}
	
	//�I������
	if(fabs(diff[0]) <= pcon[num].tlrnce)
		if(psta[num].end>=250) //�I�[�o�[�t���[�h�~
			psta[num].end=250;
		else
			psta[num].end++;
	else
		if(psta[num].end>0)
			psta[num].end--;
		
	return duty;
}

/********************************************************/
//  ���O      
//		pcon_manual
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�����duty�Ő�����s��
//	���ӎ���
//		
//  �p�����^����
//		PCON�ԍ�
//  �߂�l
//		Duty
//  �쐬��
//		IDO
//		
//
/********************************************************/
double pcon_manual(char num,double duty){
	psta[num].target[0] = psta[num].current[0];
	psta[num].D_old = 0;
	psta[num].duty = duty; //duty���
	
	//duty����
	if(psta[num].duty > pcon[num].duty_lim)
		psta[num].duty = pcon[num].duty_lim;
	if(psta[num].duty < -pcon[num].duty_lim)
		psta[num].duty = -pcon[num].duty_lim;
		
	return psta[num].duty;
	//pcon[num].end=0;
}

/********************************************************/
//
//  ���O      
//		comm_action
//  �T�v
// 		�}�V������
//  �@�\����
//		�R�}���h�ɉ������A�N�V���������s
//	�p�����[�^
//		�R�}���h�A�f�[�^				
//  �߂�l
//		����		
//  �쐬��
//		IDO
//	���l
//		�\�肾��
//		mode 2�͐���E���b�N�E�đ��U�𐧌䂷���ՂŁA�o�b���������Ɍq������
//		mode 1�͔��˗p�̃��[���[�̂ݐ��䂷���ՂŁAmode 2�̊�ՂƖ��߂�����肵�ē���
//
/********************************************************/
int comm_action(char cmd,int data)
{
	//printf("cmd:%s value:%d\n",cmd,data);
	switch(cmd){
		case 'E': //�G���[�֘A
			if(data==0){
				printf("\nCommand Accepted\n"); //E0�ŃR�}���h��M���m�F
				return 1;
			}				
			
			if(data==1){
				printf("\nInvalid Command\n"); //E1�͖���`�̃R�}���h������ꂽ��
				return 1;
			}
			if(data==2){
				printf("\nInvalid Data Range\n"); //E2�͑��x�A�p�x�̎w��Ŕ͈͊O�̐��l���w�肳�ꂽ��
				return 1;
			}
			if(data==9999){
				//printf("E9999");
				directions(&com[1],1,0); //E2�͑��x�A�p�x�̎w��Ŕ͈͊O�̐��l���w�肳�ꂽ��
				return 1;
			}	
			break;				
		case 'Q':
			tera=1;
			printf("change tera\n");
			break;
		case 'C': //���ˉ�]���x�w��
			if(cmdp.mode==2){
				directions(&com[0],data,2);
				return 1;
			}
			else{
				if(ABS(data) <= SHT_LIMIT){ //��]���x����
					cmdp.shot_spd = data;
//					directions(&com[0],0,0);
				}
//				else directions(&com[0],2,0);
				return 1;
			}
			break;
			
		case 'X': //���˃��[���[P�Q�C��
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].P_gain = sP_g = (double)data/32767.0;
				else
				pcon[0].P_gain = pcon[1].P_gain = (double)data/32767.0;
				
			}
			break;
			

		case 'Y': //���˃��[���[I�Q�C��
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].I_gain = sI_g = (double)data/32767.0;
				else
				pcon[0].I_gain = pcon[1].I_gain  = (double)data/32767.0;
			}
			break;
			

		case 'Z': //���˃��[���[D�Q�C��
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].D_gain = sD_g = (double)data/32767.0;
				else
				pcon[0].D_gain = pcon[1].D_gain = (double)data/32767.0;
			}
			break;						

		case 'R': //�đ��U
			if(cmdp.mode==1){
				if(cmdp.reload == -1)
					cmdp.reload = 0;
				return 1;						
			}else if(cmdp.mode == 2){
//				directions(&com[0],data,CMD_R);
			}
			break;
				
		case 'I': //�����Z�b�g�A�b�v	
			if(data==1){ //���[�h�P�p
				cmdp.mode = 1;
//				enc2_init();	
				cmdp.shot_spd = DEFAULT_SHOOT_SPEED;	
				cmdp.reload = -1;
//				directions(&com[0],3,1);
				puts("MODE1_SETUP");
//				PE.DRL.BIT.B4 = 1;
//				PE.DRL.BIT.B5 = 1;
//				PE.DRL.BIT.B6 = 1;
//				PE.DRL.BIT.B7 = 1;
				sP_g = ROLLER_P_GAIN;
				sI_g = ROLLER_I_GAIN;
				sD_g = ROLLER_D_GAIN;
				return 1;		
			}
			if(data==2){ //���[�h�Q�p
				cmdp.mode = 2;
//				pwm_init2();
//				sci2_init();
				cmdp.shot_dgr = 0;	
				cmdp.rotation = 1;//1
//				cmdp.reload = -1;
				//cmdp.trigger = 0;
				directions(&com[0],1,1);
				comm_action('E',0);
				puts("MODE2_SETUP");
				return 1;
			}	
			if(data==3){ //�e���^�[���ł̑���M�m�F�p
				printf("\nsetup_ok\n");
//				PE.DRL.BIT.B4 = 1;
//				power_ON();
				return 1;
			}											
			break;		
		case 'S': //����(Shoot)�A�X�^�[�g�E�X�g�b�v����Ȃ��I			
			if(data==1){ //���˃V�[�P���X�J�n
				//PC���疽�߂�S1��������ꂽ�炻�̂܂ܓ]��
				LASER_OUT=1;	
				if(cmdp.mode==2){ 
					directions(&com[0],1,4);
					return 1;
				}
				else if(cmdp.mode==1){ //���[���[�p��Ղ�S1���󂯎������O���[�o���ϐ��̃t���O�𗧂ĂāAinterrupt�̃^�C�}���荞�݂Ń��[���[�𐧌�
						if(cmdp.reload == -1){
							cmdp.reload = 0;
						}else{
							/*if(cmdp.shot){
								cmdp.shot = 0;	
								MTU20.TGRA = anti_lock_pwm(0);
								MTU20.TGRB = anti_lock_pwm(0);
							}
							else*/ 
							cmdp.shot = 1;
							if(cmdp.reload == 0)
								cmdp.reload = 1;
	//						directions(&com[0],0,0);	
						//	put_s("S1");
							if(cmdp.shot_rdy == 0){
								cmdp.shot_rdy = 1;
							}
						}
						return 1;
				}							
			}	
			if(data==2){ //���[���[�e�X�g
				if(cmdp.mode==2){
					directions(&com[0],8,4);
					return 1;
				}
				else if(cmdp.mode==1){
					if(cmdp.shot_spd == 0)
						cmdp.reload = 4;
					else 
						cmdp.shot = 1;
					cmdp.shot_rdy = 0;
					cmdp.shot_dbg = 1;
					//directions(&com[0],0,0);		
//					PE.DRL.BIT.B15 = 0;	
					return 1;	
				}							
			}							
			if(data==8){ //���[���[������~
				LASER_OUT=0;	
				if(cmdp.mode==2){
					directions(&com[0],8,4);
					return 1;
				}
				else if(cmdp.mode==1){
					cmdp.shot = 0;	
					cmdp.shot_dbg = 0;
					cmdp.reload = 0;
					shoot_flag_g = 1;
					ROLLER1_PWM = anti_lock_pwm(0);
					ROLLER2_PWM = anti_lock_pwm(0);
					cmdp.shot_rdy = 0;
					directions(&com[1],1,0);
//					PE.DRL.BIT.B15 = 0;	
					return 1;	
				}							
			}	
			if(data>=10){ //���[���[�����Duty�ŉ�]������
				if(cmdp.mode==2){
					directions(&com[0],9,4);
					return 1;
				}
				else if(cmdp.mode==1){
					if(data>=500)
						data=500;
					cmdp.shot = data/10;	
					return 1;
				}							
			}														
			break;								
		}			
		return 0;
}

/********************************************************/
//  ���O      
//		terminal_control
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		PC����̃R�}���h����
//	���ӎ���
//		
//  �p�����^����
//		��M�����f�[�^
//  �߂�l
//		1:����
//  �쐬��
//		IDO
//
/********************************************************/
int tera=1
int terminal_control(char c){
	int data;
	if(tera==1){
		c_dbg[cnt_dbg] = c; //char�^�z��Ɏ�M���������������Ă���
		//��؂蕶�����󂯕t�����當�������r���A��������5�Ȃ牺4����int�ɕϊ����ăf�[�^�Ƃ��āA��ꌅ�̕����ŕ���
		if(c_dbg[cnt_dbg] == '|'){
			if(cnt_dbg != 5){
				put_s("\nInvalid Length\n");
			}
			else{
				data = atoi(&c_dbg[1]);
				switch(c_dbg[0]){
					//comm_action�œ���̃R�}���h�����M����Ă����ꍇ�̓�����s����
					case 'I':
						//directions(&com0,data,1);
						comm_action('I',data);
						//printf("I%04d",data);
						break;
					case 'C':
						//directions(&com0,data,2);
						comm_action('C',data);
						//printf("C%04d",data);
						break;
	/*				case 'D':
						//directions(&com0,data,3);
						printf("D%04d",data);
						comm_action('D',data);
						break;
	*/
					case 'S':
						//directions(&com0,data,4);
						//printf("S%04d",data);
						comm_action('S',data);
						break;
					case 'R':
						//directions(&com0,data,4);
						//printf("R%04d",data);
						cmdp.reload = data;
						//comm_action('R',data);
						break;		
					case 'X':
						//directions(&com0,data,4);
						//printf("X%04d",data);
						
						comm_action('X',data);
						break;
					case 'Y':
						//directions(&com0,data,4);
						//printf("Y%04d",data);
						
						comm_action('Y',data);
						break;
					case 'Z':
						//directions(&com0,data,4);
						//printf("Z%04d",data);
							
						comm_action('Z',data);
						break;															
					case 'T': //
						if(data==1111){
							//put_s("DBG_TGL");
								if(encd_g)
									encd_g = 0;
								else
									encd_g = 1;
						}else if(data==10){
							//printf("setup\n");
							cmdp.mode = 2;
							cmdp.shot_dgr = 0;	
							cmdp.rotation = 1;
							cmdp.trigger = 0;
//							sci2_init();
						}else if(data==9999){
							/*cmdp.mode = 1;
							enc2_init();	
							cmdp.shot_spd = 500;
							put_s("MODE1_ON");
							*/
//							directions(&com[0],2,1);
						}
						break;
					case 'P': //PC
						//printf("change comu\n");
						if(data==0000)
							tera=0;
						break;
					default:
						put_s("\nUnknown Command\n");
						break;
				}
				put_c(c_dbg[0]);
				printf("%04d\n",data);
			} //cnt
			cnt_dbg = -1;
			memset(c_dbg, 0, sizeof(c_dbg)); //char������
		}	
		cnt_dbg++;
		if(cnt_dbg >= 10){ //�G���[�h�~
			put_s("\nCount Overflow\n");
			cnt_dbg = 0;
		}
		return 1;
	}
	return 0;//receipt(&com[1]); 
}

/*
void pid_tuning(double *rot){
	double slope,inter;
	static double slope_max = 0,inter_max = 0;
	static struct enc_data data_array[4];
	static unsigned int time = 0;
	static char num=0;

	//PID�I�[�g�`���[�j���O(�C���f�B�V���������@)
	if(cmdp.mode == 1){
		if(fabs(rot[0]) < 3000){
			if(auto_g){
//				MTU20.TGRA = anti_lock_pwm(AUTO_DUTY);
				data_array[num].data = rot[0];
				data_array[num].time = time;
				time++;
				num++;
				if(num == 4){
					regress_line(data_array, 5, 4, &slope, &inter);
					num = 0;
					if(slope > slope_max){ //�ő�l�X�V
						slope_max = slope;
						inter_max = inter;
					}
					if(slope < 0.00006 && time > 200){ //�I������
						set_params(slope_max,inter_max,rot[0],AUTO_DUTY);
						auto_g=0;
						time = 0;
						num = 0;
						slope_max = 0;
						inter_max = 0;
						MTU20.TGRA = anti_lock_pwm(0);
					}
				
				}
			}else if(time > 0){
			time = 0;
			num = 0;
			slope_max = 0;
			inter_max = 0;
			}
		}else{
			auto_g=0;
			time = 0;
			num = 0;
			slope_max = 0;
			inter_max = 0;
			//MTU20.TGRA = anti_lock_pwm(0);
			printf("ENC_ERROR\n");
		}
	}
}
*/	
/********************************************************/
//  ���O      
//		gear
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		���[�^�̃Q�C����ύX
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		res		�R�}���h�̔���
//  �쐬��
//		TUTrobo
//
/********************************************************/
int gear(int gear_number)
{
	int res = CMD_END;

	const DOUBLE_GEAR diff[]  = {
								  //{   Kp,   Ki,   	Kd}
//									{0.001,0.001,   0.0001},
//									{0.001,  0.0,  0.00012},
									{0.001,  0.0,  	0.0002},
									{  1.0,  0.0,  	   0.0},
									{  0.5,  0.0,  	   0.0},
									{  0.2,  0.0,  	   0.0},
									{  0.7,  0.0,      0.0},
								 };




	
	const DOUBLE_GEAR speed[] = {
								   //{   Kp,   Ki,   Kd}
									 {0.002,  0.0,  0.0},
									 {0.002,  0.0,  0.0},
									 {0.002,  0.0,  0.0},
									 {0.002,  0.0,  0.0},
								 };
								 	
	macond.diff_gear.Kp  = diff[gear_number].Kp;
	macond.diff_gear.Ki  = diff[gear_number].Ki;
	macond.diff_gear.Kd  = diff[gear_number].Kd;

	macond.speed_gear.Kp = speed[gear_number].Kp;
	macond.speed_gear.Ki = speed[gear_number].Ki;
	macond.speed_gear.Kd = speed[gear_number].Kd;

	return res;
}


/********************************************************/
//  ���O      
//		cmd_init
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�R�}���h�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void cmd_init(void)				
{
	task_number = 0;
	task_mode = mode_control();
//	cmd_inf = cmdArray[task_mode][task_number];			
}


/********************************************************/
//  ���O      
//		mode_control
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�R�}���h�̑I��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		mode		���[�h�I��
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
char mode_control(void)				
{
	char flag = 0;
	
	if(mode() == 'R')
	{
		flag = 0;
	}
	if(mode() == 'B')
	{
		flag = 1;
	}

	return flag;
}


/********************************************************/
//  ���O      
//		task_control
//  �T�v
// 		�}�V���ړ�����֘A
//  �@�\����
//		�ꍇ�킯������path�̓������s��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void task_control(void)		
{
	int cmd_res = 0;
	static char range_flag = 0;
//	char read_duty = 0;				// ���s�n�R�}���h���ǂ���
//	char read_theta = 0;
//	static double base = 0.0;		// �O��̃R�}���h�Ŏw�肵��duty
//	static char maplice_count = 0;
		
	switch(cmd_inf.name)
	{
		default:
				break;
	}
	
//	pwm_set_ctrl(macond.duty.l,macond.duty.r);	
	
	if(cmd_res == CMD_END)
	{
		task_number++;	
//		cmd_inf = cmdArray[task_mode][task_number];
		range_flag = 0;
		
//		printf("CHENG_CMD\n");
		
	}
	else if(cmd_res == CMD_END_ALL)
	{
		
//		printf("TASK_ALL_END\n");	
		
	}
	
}
#endif