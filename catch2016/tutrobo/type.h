/********************************************************/
//
//  �T�v
//      �v���O�����̌^���錾
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �e��^����`
/********************************************************/
typedef struct type1{
	int r,l;
}ENCODER_COUNT;

typedef struct type2{
	double r,l;
}DOUBLE_LR;

typedef struct type3{
	double x,y;
}DOUBLE_XY;

typedef struct type4{
	double Kp,Ki,Kd;
}DOUBLE_GEAR;

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �G���R�[�_�̕␳�l
/********************************************************/
struct correction_value{
	double			ENCODER_RC_L;	// ���̃G���R�[�_�̕␳�l
	double			ENCODER_RC_R;	// �E�̃G���R�[�_�̕␳�l
	double			ENCODER_D;		// �G���R�[�_�[�^�C�����a
	double			ENCODER_D_L;	// ���G���R�[�_�[�^�C�����a
	double			ENCODER_D_R;	// �E�G���R�[�_�[�^�C�����a
	double			ENCODER_T;		// �G���R�[�_�[�g���b�h	
};

struct omni_correction_value{

	double			ENCODER_D_X;	//X�����̃G���R�[�_�[�^�C�����a
	double			ENCODER_D_Y;	//Y�����̃G���R�[�_�[�^�C�����a


};

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �}�V���R���f�B�V����
/********************************************************/
struct machine_condition {
	ENCODER_COUNT 	enc;		//�G���R�[�_�ݐσJ�E���g
	ENCODER_COUNT	renc;		//�G���R�[�_�ݐσJ�E���g��
	DOUBLE_LR		v_enc;		//���E�G���R�[�_�ԗ֑��x[mm/sec]
	double			vx;			//x�����̑��x[mm/sec]
	double			vy;			//y�����̑��x[mm/sec]
	double			v;			//�}�V�����x[mm/sec]
	double			v_rad;		//�}�V���i�s�����x�N�g��[rad]PI~2PI
	double			rad;		//�}�V������[rad]
	double			deg;		//�}�V������[deg]
	double			theta_base;	//�}�V������[rad]
	double			theta;		//�}�V������[rad]
	double			t_theta;	//�}�V������̂��߂̊p�x[deg]	
	DOUBLE_XY		pos;		//�}�V�����ݍ��W[mm](x:�i�s����, y:���E)
	DOUBLE_LR		duty;		//���[�^�ɗ^����duty
	DOUBLE_LR		duty_old;	//���[�^�ɗ^����duty
	DOUBLE_GEAR		diff_gear;	//�t�B�[�h�o�b�N�Q�C��(����)
	DOUBLE_GEAR		speed_gear;	//�t�B�[�h�o�b�N�Q�C��(���x)		
};

typedef struct {
	int				renc;		//�G���R�[�_�̗ݐϒl
	double			pos;		//���W[mm]
	double			v;			//���x[mm/sec]
	
	double			max_v;		//�ő呬�x[(+-)mm/sec]
	double			aim_v;		//�ڕW���x[mm/sec]
	double			duty;		//���݂����Ă���duty(-100~100)
	char 			mode;//�蓮�C�����C�X�g�b�v�̊i�[
}arm_condition;


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �}�V���R���f�B�V����
/********************************************************/
struct gyro_condition{
	double ax;//�W���C�����猩�������xx[m/(s^2)]
	double ay;//�W���C�����猩�������xy[m/(s^2)]
	double m_ax;//������Ԃ��猩�������xx[m/(s^2)]
	double m_ay;//������Ԃ��猩�������xy[m/(s^2)]
	double a_rad;//������Ԃ��猩�����������x�N�g��[rad]

/*	
	double vx;//���xx[mm/s]
	double vy;//���xy[mm/s]
	double v;//���x[mm/s]
	double v_rad;//���x�̕����iradian�j
	
	double x;//x���W[mm]
	double y;//y���W[mm]		
*/
};

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �R�}���h�̃��X�g
/********************************************************/
//*** �R�}���h��ǉ�����ꍇ�C�����ɓo�^���邱�ƁI ***
enum eCMDNAME{
	C_MASE , UP_MASE, DOWN_MASE ,
	S_MASE , ST_MASE ,C_TURN , C_MOVE ,
	C_STOP , C_GEAR , C_WAIT ,
	C_MAP  , C_SENCE, C_COM  , C_LIM,
	C_SLA  , C_END  
};

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �R�}���h����
/********************************************************/
struct comand_information{
	enum eCMDNAME name;		//�R�}���h��
	short in1;				//��1����
	short in2;				//��2����
	short in3;				//��3����
	short in4;				//��4����
	short in5;				//��5����
	short range;			//�Ȑ��̒���
};


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 �����̐��Ƃ��̐������L�^����
/********************************************************/
struct num_list{
	int obj;				//����
	int num;				//��
};


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 ���߃t���O�֘A
/********************************************************/
struct command_parameters{
	int	shot_spd; //target_g(mode1)
	int shot_dgr; //target_g(mode2)
	int shot; //ctrl_g(mode1)
	char rotation; //ctrl_g(mode2)
	char trigger; //lock_ctrl_g
	char reload; //rld_ctrl_g
	char mode; //mode_g
	char shot_rdy; //ctrl_g(mode1)
	char shot_dbg; //ctrl_g(mode1)
};


/********************************************************/
//  TUTrobo
//
//  �T�v
//      �v���O�����̌^���錾 PID����ɗp����p�����[�^
/********************************************************/
struct pid_config {
	unsigned short* output;	//�o�͐�
	double duty_lim;	//�ő�Duty
	double tlrnce;	//���e�덷
	double	P_gain;	//P�Q�C��
	double	I_gain;	//I�Q�C��
	double	D_gain;	//D�Q�C��
};

struct pid_status {
	double current[21];	//���ݒl
	double target[21];	//�ڕW�l
	unsigned char end;	//�����t���O
	double D_old;
	double integr;
	double duty;
	double debug;
	unsigned char intrpt_cnt;
};

#endif // __TYPE_H__

