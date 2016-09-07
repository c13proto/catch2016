/********************************************************/
//
//  �T�v
//      �v���֘A
//  �쐬��
//		TUTrobo
//
/********************************************************/

#include "setup.h"		//�}�C�R���̐ݒ�

#define LATCH_CNT	10000					//���b�`�̃J�E���g��(�J�E���g���~�^�X�N����[ms])


/********************************************************/
//  ���O      
//		show_macond
//  �T�v
// 		�v���֘A
//  �@�\����
//		�G���R�[�_�␳�p�̃f�o�b�N�֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/

void show_macond(void)	
{
	
	/********************** show_macond�I�� ��������***********************/
	
//	#define path_debug				// PATH�f�o�b�N�Z�b�g
//	#define map_debug				// MAP�f�o�b�N
//	#define new_machine_correction	// �}�V���␳�Z�b�g �V��
	#define new_machine_correction_omni	// ���̃I���j�΂�
//	#define old_machine_correction	// �}�V���␳�Z�b�g ����

	/********************** show_macond�I�� ��������***********************/

//	static int LatchCnt = 0;
	
//	LatchCnt++;
	
//	if(LatchCnt == LATCH_CNT)
//	{

#ifdef	path_debug		
		/************************** PATH�f�o�b�N **************************/		
		
		/* �}�V���ʒu����ь��݂�PATH�̒l */
		printf("((%d)(%5d,%5d,%5d))x=%6.1f, y=%6.1f, th=%6.2f , v = %6.1f ,duty_l = %6.1f,duty_r = %6.1f\n",cmd_inf.name,cmd_inf.in1,cmd_inf.in2,cmd_inf.in3,macond.pos.x,macond.pos.y,macond.theta*180/PI,macond.v,macond.duty.l,macond.duty.r);
				
		/*********************** PATH�f�o�b�N�Z�b�g ***********************/
#endif

#ifdef	map_debug		
		/************************* �}�b�v�f�o�b�N *************************/		
		
		/* �}�V���ʒu����ь��݂�PATH�̒l */
		printf("%6.1f,%6.1f\n",macond.pos.x,macond.pos.y);
				
		/*********************** PATH�f�o�b�N�Z�b�g ***********************/
#endif

#ifdef	new_machine_correction
		/*********************** �}�V���␳�Z�b�g �V�� *********************/

		/* �}�V���␳�̃f�o�b�N */
		printf("%d\t\n", macond.renc.l);		// x�̃G���R�[�_�J�E���g
		printf("%d\t\n", macond.renc.r);		// y�̃G���R�[�_�J�E���g
		printf("%f\t\n", macond.t_theta);	// �}�V���p�x
		printf("%f\t\n" , macond.pos.x);	// x���W
		printf("%f\t\n" , macond.pos.y);	// x���W
		/* ���s */
		printf("\n");
			
		/*********************** �}�V���␳�Z�b�g �V�� *********************/
#endif

#ifdef	new_machine_correction_omni
		/*********************** �}�V���␳�Z�b�g �V�� *********************/

		/* �}�V���␳�̃f�o�b�N */
		printf("%d\t\n", macond.renc.l);		// x���W
		printf("%d\t\n", macond.renc.r);		// y���W
		printf("%f\t\n", macond.t_theta);	// �}�V���p�x
		/* ���s */
		printf("\n");
			
		/*********************** �}�V���␳�Z�b�g �V�� *********************/
#endif
	
#ifdef	old_machine_correction	
		/*********************** �}�V���␳�Z�b�g ���� *********************/

		/* �}�V���␳�̃f�o�b�N */
		printf("x = %6.1f,\t y = %6.1f,\t th = %6.1f,\t t_th = %6.1f,\t",macond.pos.x,macond.pos.y,macond.theta*180/PI,macond.t_theta);
		/* �G���R�[�_�J�E���g�̃f�o�b�N */
		printf("enc_cnt.l=%d,enc_cnt.r=%d\t",macond.enc.l,macond.enc.r);				
		/* �G���R�[�_�̑��s�����̃f�o�b�N(���݂�excel�Ōv�Z���Ă��邽�ߕs�v) */ 
//		printf("dist.l=%f, dist.r=%f\n",(double)(macond.enc.l)/ENCODER_RES * PI * ENCODER_D_L,(double)(macond.enc.r)/ENCODER_RES * PI * ENCODER_D_R);	//�G���R�[�_�^�C���̈ړ�����
		/* ���s */
		printf("\n");
			
		/*********************** �}�V���␳�Z�b�g ���� *********************/
#endif	
//		LatchCnt = 0;
//	}

}



/********************************************************/
//  ���O      
//		map_update
//  �T�v
// 		�v���֘A
//  �@�\����
//		�G���R�[�_�̃J�E���g��ǂݎ��
//		�J�E���g����}�V���R���f�B�V���������߂�B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void map_update(void)	//�E,�������ւ����x,y��������ւ��
{		
//	unsigned short debug;

	ENCODER_COUNT enc_cnt;
	enc_cnt.l = MTU1.TCNT;
	enc_cnt.r = MTU2.TCNT;
//	coordinate(enc_cnt);
	
//	coordinate_omni(enc_cnt);
	
//	debug=65536-enc_cnt.r;
//	printf("l=%5d,r=%5d\n",enc_cnt.l,debug);
}

/********************************************************/
//  ���O      
//		coordinate
//  �T�v
// 		�v���֘A
//  �@�\����
//		�J�E���g����}�V���R���f�B�V���������߂�B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void coordinate(ENCODER_COUNT enc_cnt)
{
	
	static ENCODER_COUNT cnt_old;		//�ߋ��̃G���R�[�_�J�E���g
	ENCODER_COUNT renc = macond.renc;	//�G���R�[�_�J�E���g�̗ݐϒl
	ENCODER_COUNT enc;					//�E�ƍ��̃G���R�[�_�����ꂼ��i�񂾋���
	ENCODER_COUNT cnt_diff;				//�G���R�[�_�J�E���g�̍�
	DOUBLE_LR v_enc = macond.v_enc;		//�E�ƍ��̃G���R�[�_�����ꂼ��i�񂾑��x
	DOUBLE_LR v_enc_old;				//�ߋ��̉E�ƍ��̃G���R�[�_�����ꂼ��i�񂾑��x
	DOUBLE_XY pos = macond.pos;			//�}�V���̌��݈ʒu
	double v,theta;						//�}�V���̑��x�Amase_ctrl�̊p�x
	int tmp;							//�Е��̃G���R�[�_�𒆐S�ɂ������Ɉ��]�������̃G���R�[�_�̃p���X��
	double t_theta;						//����v���O�����̂��߂̊p�x
//	DOUBLE_LR a;						//�}�V���̉����x

	
	cnt_diff.l =  (short)((unsigned short)enc_cnt.l - (unsigned short)cnt_old.l);		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	cnt_diff.r = -(short)((unsigned short)enc_cnt.r - (unsigned short)cnt_old.r);		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	
	cnt_old = enc_cnt;				//�ߋ��̃G���R�[�_�J�E���g��ۑ�
	
	renc.l += cnt_diff.l;			//���̃G���R�[�_�J�E���g�̗ݐϒl
	renc.r += cnt_diff.r;			//�E�̃G���R�[�_�J�E���g�̗ݐϒl

	enc.l = renc.l * ENCODER_RC_L;	//���̃G���R�[�_���i�񂾋���
	enc.r = renc.r * ENCODER_RC_R;	//�E�̃G���R�[�_���i�񂾋���

// �}�V������
	tmp = TMP;													//�Е��̃G���R�[�_�𒆐S�ɂ������Ɉ��]�������̃G���R�[�_�̃p���X�������߂�B
																//(2.0 * PI * ENCODER_T ) / ( PI * ENCODER_D ) * ENCODER_RES

	theta = macond.theta_base;									//macond.theta_base�ɂ͂��߂̊p�x����͂��ēK�؂Ȋp�x�ɂ��邱�Ƃ��ł���B(�Ȃ��Ă�����?)
	
	theta += 2.0 * (PI / tmp) * ((int)(enc.r - enc.l) % tmp);	//((int)(enc.r - enc.l) % tmp_int)	>> 	�}�V�����]������̃p���X���ŗ]������߂邱�Ƃɂ����]������̊��������߂Ă���(�v�Z�����l�̓p���X�������܂�)
																//�p���X���̍������]������̃p���X���Ŋ���ƈ��]������̊��������߂邱�Ƃ��ł��A�����2.0 * PI�������邱�Ƃɂ�胉�W�A���ŋ��߂邱�Ƃ��ł���B
																//tmp��int�^�ɂȂ��Ă��闝�R�͈��]������̃p���X���������_�ȉ��ɂȂ�Ƃ��傤�ǈ��]�����߂邱�Ƃ��ł��Ȃ��Ȃ邽��
																//�}�V���̌��������W�A���ŕ\�L

	if     ( theta >  PI )theta -= 2*PI;						//�p�x�̕ω��̈��ύX
	else if( theta < -PI )theta += 2*PI;						//�p�x�̕ω��̈��ύX
	
// ��Ίp�x
	t_theta = macond.theta_base;								//macond.theta_base�ɂ͂��߂̊p�x����͂��ēK�؂Ȋp�x�ɂ��邱�Ƃ��ł���B(�Ȃ��Ă�����?)
	
	t_theta = (360.0 / tmp) * (int)(enc.r - enc.l);				//���̌v�Z��ʂɂ��Ă���̂�(int)(enc.r - enc.l)�̍�������(�]��ł͂Ȃ�)
																//����[deg]�ŋ��߂Ă���B
	
// ���݈ʒu
//	pos.x += ( ( cnt_diff.l + cnt_diff.r ) / 2 ) * PI * ENCODER_D / ENCODER_RES * cos(theta);
//	pos.y += ( ( cnt_diff.l + cnt_diff.r ) / 2 ) * PI * ENCODER_D / ENCODER_RES * sin(theta);
	
//	pos.x +=  REVISE * ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2 ) * PI / ENCODER_RES * cos(theta);
//	pos.y +=  REVISE * ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2 ) * PI / ENCODER_RES * sin(theta);

//	pos.x += ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2.0 ) * PI / ENCODER_RES * cos(theta);
//	pos.y += ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2.0 ) * PI / ENCODER_RES * sin(theta);

	pos.x += ( (double)( cnt_diff.l + cnt_diff.r ) / 2.0 ) * PI * ENCODER_D / ENCODER_RES * cos(theta);
	pos.y += ( (double)( cnt_diff.l + cnt_diff.r ) / 2.0 ) * PI * ENCODER_D / ENCODER_RES * sin(theta);

// �ߋ��̃G���R�[�_�̑��x��ۑ�
	v_enc_old = v_enc;
	
// ���x
	v_enc.l = cnt_diff.l * 1000 / FEEDBACK_INTERVAL * PI * ENCODER_D_L / ENCODER_RES;
	v_enc.r = cnt_diff.r * 1000 / FEEDBACK_INTERVAL * PI * ENCODER_D_R / ENCODER_RES;
	
//	printf("%6.1f,%6.1f\n",v_enc.l,v_enc.r);

	v = (v_enc.l + v_enc.r) / 2;
	
// �����x
//	a.l = (v_enc.l - v_enc_old.l) / FEEDBACK_INTERVAL * 1000;
//	a.r = (v_enc.r - v_enc_old.r) / FEEDBACK_INTERVAL * 1000;
	
// �v�Z�����l���}�V���R���f�B�V�����ɑ��
	macond.renc      = renc;
	macond.enc       = enc;
	macond.v_enc     = v_enc;
//	macond.v_enc_old = v_enc_old;
	macond.theta     = theta;
	macond.t_theta   = t_theta;
	macond.v         = v;
//	macond.a	     = a;
	macond.pos       = pos;
	
//	show_macond();
	
}


/********************************************************/
//  ���O      
//		coordinate_omni
//  �T�v
// 		�v���֘A
//  �@�\����
//		�J�E���g����}�V���R���f�B�V���������߂�B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		��܂ނ� @ TUTrobo
//
/********************************************************/
#if 0
void coordinate_omni(ENCODER_COUNT enc_cnt)
{
	#define loop_time 0.01		//�t�B�[�h�o�b�N����[sec]
	
	static ENCODER_COUNT cnt_old;		//�ߋ��̃G���R�[�_�J�E���g
	ENCODER_COUNT renc=macond.renc;		//�G���R�[�_�J�E���g�̗ݐϒl
	double kaiten_x,kaiten_y;			//xy�G���R�[�_�̉�]��
	ENCODER_COUNT cnt_diff;				//�G���R�[�_�J�E���g�̍�
	DOUBLE_LR v_enc = macond.v_enc;		//�E�ƍ��̃G���R�[�_�����ꂼ��i�񂾑��x
	DOUBLE_LR v_enc_old;				//�ߋ���xy�̃G���R�[�_�����ꂼ��i�񂾑��x
	DOUBLE_XY pos = macond.pos;			//�}�V���̌��݈ʒu
	double vx,vy,v,v_rad;			//�}�V���̑��x�Amase_ctrl�̊p�x
	int tmp=ENCODER_RES;				//���]�������̃G���R�[�_�̃p���X��
	double t_theta;						//����v���O�����̂��߂̊p�x
	double diff_pos_x,diff_pos_y;		//x,y�̍�
	static double old_pos_x,old_pos_y;

	char zone;
	
	zone=mode();//�Ԑ���

// ��Ίp�x(degree)
	t_theta = (double)m_angle/100.0;//degree
// -PI~PI�̐�Ίp�x(rad)
//	theta = (double)angle*PI/18000.0;//rad
	
	cnt_diff.l = -1*(-(short)((unsigned short)enc_cnt.l - (unsigned short)cnt_old.l));		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	cnt_diff.r = -1*((short)((unsigned short)enc_cnt.r - (unsigned short)cnt_old.r));		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	
	renc.l+=cnt_diff.l;
	renc.r+=cnt_diff.r;
	
	kaiten_x = cnt_diff.l /(double)tmp;	//X�����̃G���R�[�_���i�񂾉�]���i�O�Ƃ̍��j
	kaiten_y = cnt_diff.r /(double)tmp;	//Y�����̃G���R�[�_���i�񂾉�]���i�O�Ƃ̍��j

	diff_pos_x=ENCODER_D_X*PI*kaiten_x*mycos(t_theta*PI/180.0)-ENCODER_D_Y*PI*kaiten_y*mysin(t_theta*PI/180.0);
	diff_pos_y=ENCODER_D_X*PI*kaiten_x*mysin(t_theta*PI/180.0)+ENCODER_D_Y*PI*kaiten_y*mycos(t_theta*PI/180.0);

// ���݈ʒu
	pos.x += diff_pos_x;
	pos.y += diff_pos_y;

// ���ݑ��x
	vx=diff_pos_x/(loop_time*cmt1_counter);
	vy=diff_pos_y/(loop_time*cmt1_counter);
	
	v=sqrt(POW2(vx)+POW2(vy));
	
	cmt1_counter=0;

// �i�s�����x�N�g��(PI~2PI)

	v_rad = atan3(vy,vx);
	if(v_rad<0)v_rad+=2.0*PI;

// �ߋ��̃G���R�[�_�̑��x��ۑ�
	v_enc_old = v_enc;
	
	cnt_old=enc_cnt;
	
// �v�Z�����l���}�V���R���f�B�V�����ɑ��
	macond.renc      = renc;
//	macond.enc       = enc;
//	macond.v_enc     = v_enc;
//	macond.v_enc_old = v_enc_old;
//	macond.theta     = theta;
	macond.t_theta   = t_theta;
	macond.vx		 = vx;
	macond.vy		 = vy;
	macond.v         = v;
	macond.v_rad	 = v_rad;
//	macond.a	     = a;
	macond.pos       = pos;
	
	if(ABS(macond.pos.x-old_pos_x)>300.0)macond.pos.x=old_pos_x;
	if(ABS(macond.pos.y-old_pos_y)>300.0)macond.pos.y=old_pos_y;
//	show_macond();
	cnt_old=enc_cnt;
	old_pos_x=macond.pos.x;
	old_pos_y=macond.pos.y;
	

	
}
#endif
/********************************************************/
//  ���O      
//		slip_stoper
//  �T�v
// 		���x����֘A
//  �@�\����
//		�ڕWduty�����{�b�g������Ȃ��悤�ɐ��䂷��	
//  �p�����^����
//		aim_duty	�ڕWduty
//		ratio		�ڕW���x��
//		drive_K		�����Ȃ��悤�ɂ��鐧���l
//  �߂�l
//		drive		�␳���ꂽduty		
//  �쐬��
//		N.TAKAHASHI @ TUTrobo
//
/********************************************************/
double slip_stoper(double aim_duty,DOUBLE_LR ratio)
{
	double drive;
	
	const double drive_K = 10.0;

/********************************************************/	
	//���S�͂̋��ߕ�(�ȈՃo�[�W����)
	
	//�����̂Q��*���񔼌a	mr��^2
	//m:����	r:���񔼌a	��:�p���x
	
	//v_L(���̃^�C��duty) = ratio.l * aim_duty
	//v_R(�E�̃^�C��duty) = ratio.r * aim_duty
	
	//r = (duty�̘a)          �� (duty�̍���)        �~ (�^�C���g���b�g�̔���)
	//  = (v_L + v_R)         �� (v_R - v_L)  		 �~ (�^�C���g���b�g�̔���)
	//  = (ratio.l + ratio.r) /  (ratio.r - ratio.l) *  (TIRE_T / 2.0)
	
	//��= (duty�̍���) 		             �� (�^�C���g���b�g)
	//  = (v_R - v_L)  		             �� (�^�C���g���b�g)
	//  = (ratio.r - ratio.l) * aim_duty / TIRE_T
	
	//r��^2 = (duty�̘a)          �~ (duty�̍���)        �� (�^�C���g���b�g)
	//      = (v_L + v_R)         �~ (v_R - v_L)  		 �� (�^�C���g���b�g)
	//      = (ratio.l *  aim_duty + ratio.r * aim_duty) *  (ratio.r * aim_duty - ratio.l * aim_duty) /  (TIRE_T)
	//      = (ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)
	
	//m�萔���������Ƃ��΂悭�ˁ@by���
	
/********************************************************/
	//�␳�l(drive)�̎Z�o���@
	
	//(ratio.l + ratio.r) * (ratio.r - ratio.l) * drive * drive / (TIRE_T) = drive_K
	//��L�̎�������
	//����
	//drive = sqrt( (drive_K * TIRE_T) /  (lr_ratio.r - lr_ratio.l) )	�i�O�i������j
	//���̉���O�㍶�E�̂S�ʂ�ŏꍇ����
	
/********************************************************/

	//�����Ȃ��悤�ɂ��鐧���l�̂��߂̃f�o�b�N
//	printf("%f\n",ABS((ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)));
	
	if(ABS((ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)) > drive_K)	//���{�b�g�����肻���Ȃ�␳
	{
		if(aim_duty > 0)  //�ڕWduty�����̂Ƃ�    
		{
			if(ratio.r > 1.0){drive =  (sqrt( (drive_K * TIRE_T) /  (ratio.r - ratio.l) ));}		//�i�O�i�����j
			else			 {drive =  (sqrt( (drive_K * TIRE_T) / -(ratio.r - ratio.l) ));}		//�i�O�i�E���j
		}
		else if(aim_duty < 0)//�ڕWduty�����̂Ƃ�
		{	
			if(ratio.r > 1.0){drive = -(sqrt( (drive_K * TIRE_T) /  (ratio.r - ratio.l) ));}		//�i��ލ����j
			else			 {drive = -(sqrt( (drive_K * TIRE_T) / -(ratio.r - ratio.l) ));}		//�i��މE���j
		}	
	}
	else																							//���{�b�g������Ȃ��Ƃ�
	{
		drive = aim_duty;
	}
	
	return drive;
}

/********************************************************/
//  ���O      
//		gyro_map
//  �T�v
// 		�v���֘A
//  �@�\����
//		�W���C���̃J�E���g��ǂݎ��
//		�J�E���g����}�V���R���f�B�V���������߂�B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
#if 0
void gyro_map(void)	//�E,�������ւ����x,y��������ւ��
{
//	#define loop_time 0.01 //�^�C�}���荞�݂̓������
	
//	static double old_ax,old_ay;
//	static double old_vx,old_vy;
	
	static double test_ax[10];
	static double test_ay[10];//�I�t�Z�b�g�̂��߂̌^
	static double offset_ax;
	static double offset_ay;
	
	int i;
	double ax_max,ax_min,ay_max,ay_min;
	double m_angle_rad;
	
	 m_angle_rad = (double)m_angle*PI/18000.0;
	
	for(i=0;i<9;i++)//�ߋ�10���̒l������
	{
		test_ax[9-i]=test_ax[8-i];	//printf("[%d]=%.2f\n",9-i,test_ax[9-i]);
		test_ay[9-i]=test_ay[8-i];	//printf("[%d]=%.2f\n",9-i,test_ay[9-i]);
	}
	test_ax[0]=(double)accX/100.0;
	test_ay[0]=(double)accY/100.0;
	
	//printf("[0]=%.2f\n",test_ay[0]);
	
	ax_max=test_ax[0];ax_min=test_ax[0];
	ay_max=test_ay[0];ay_min=test_ay[0];
	
	
	for(i=0;i<=9;i++)//�ߋ�10���̒l����ő�ƍŏ�������o��
	{
		if(test_ax[i]>ax_max)ax_max=test_ax[i];
		if(test_ax[i]<ax_min)ax_min=test_ax[i];
		if(test_ay[i]>ay_max)ay_max=test_ay[i];
		if(test_ay[i]<ay_min)ay_min=test_ay[i];
	}
	
//	printf("x_max=%.2f\t",ax_max);
//	printf("x_min=%.2f\t",ax_min);
//	printf("ax=%.2f\n",(double)accX/100.0);
	
	
	if( ABS(ax_max-ax_min)<0.1)offset_ax=test_ax[0];//max��min�̍������Ȃ���΍��̒l���I�t�Z�b�g�Ƃ��đ��
	if( ABS(ay_max-ay_min)<0.1)offset_ay=test_ay[0];
	

	gcond.ax=test_ax[0]-offset_ax;//�����x[m/s^2]�̑��(�I�t�Z�b�g���ǂ����邩)
	gcond.ay=test_ay[0]-offset_ay;
	
	gcond.m_ax=gcond.ax*mycos(m_angle_rad)-gcond.ay*mysin(m_angle_rad);
	gcond.m_ay=gcond.ax*mysin(m_angle_rad)+gcond.ay*mycos(m_angle_rad);

	gcond.a_rad=atan3(gcond.m_ay,gcond.m_ax)+PI;//�v���X�ƃR���̓��͂Ɣ�r�ł���悤�A0~2PI�ɂ���B

/*	
//	printf("ax=%.2f\n",gcond.ax);ok!
//	printf("old_ax=%.2f\n",old_ax);ok!
//	printf("ax=%.2f\t,off_ax=%.2f\n",test_ax[0],offset_ax);
//	printf("ay=%.2f\t,off_ay=%.2f\n",test_ay[0],offset_ay);


//	printf("%f\t",gcond.vx);
	
	gcond.vx += old_ax*loop_time*1000.0;//���x[mm/s]�̌v�Z
	gcond.vy += old_ay*loop_time*1000.0;
	gcond.v  = sqrt( POW2(gcond.vx) + POW2(gcond.vy) );
	gcond.v_rad=atan2(gcond.vy,gcond.vx);//���x�����̊p�x�̌v�Z
	
//	printf("%f\n",old_ax*0.010*1000.0);
//	printf("%f\n",gcond.vx);

	
	gcond.x += old_vx*loop_time;//x���W[mm]�̌v�Z
	gcond.y += old_vy*loop_time;
	
	
	old_ax=gcond.ax;
	old_ay=gcond.ay;
	old_vx=gcond.vx;
	old_vy=gcond.vy;		
*/
}
#endif