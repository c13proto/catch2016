/********************************************************/
//
//  概要
//      計測関連
//  作成者
//		TUTrobo
//
/********************************************************/

#include "setup.h"		//マイコンの設定

#define LATCH_CNT	10000					//ラッチのカウント数(カウント数×タスク周期[ms])


/********************************************************/
//  名前      
//		show_macond
//  概要
// 		計測関連
//  機能説明
//		エンコーダ補正用のデバック関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/

void show_macond(void)	
{
	
	/********************** show_macond選択 ここから***********************/
	
//	#define path_debug				// PATHデバックセット
//	#define map_debug				// MAPデバック
//	#define new_machine_correction	// マシン補正セット 新式
	#define new_machine_correction_omni	// ↑のオムニばん
//	#define old_machine_correction	// マシン補正セット 旧式

	/********************** show_macond選択 ここから***********************/

//	static int LatchCnt = 0;
	
//	LatchCnt++;
	
//	if(LatchCnt == LATCH_CNT)
//	{

#ifdef	path_debug		
		/************************** PATHデバック **************************/		
		
		/* マシン位置および現在のPATHの値 */
		printf("((%d)(%5d,%5d,%5d))x=%6.1f, y=%6.1f, th=%6.2f , v = %6.1f ,duty_l = %6.1f,duty_r = %6.1f\n",cmd_inf.name,cmd_inf.in1,cmd_inf.in2,cmd_inf.in3,macond.pos.x,macond.pos.y,macond.theta*180/PI,macond.v,macond.duty.l,macond.duty.r);
				
		/*********************** PATHデバックセット ***********************/
#endif

#ifdef	map_debug		
		/************************* マップデバック *************************/		
		
		/* マシン位置および現在のPATHの値 */
		printf("%6.1f,%6.1f\n",macond.pos.x,macond.pos.y);
				
		/*********************** PATHデバックセット ***********************/
#endif

#ifdef	new_machine_correction
		/*********************** マシン補正セット 新式 *********************/

		/* マシン補正のデバック */
		printf("%d\t\n", macond.renc.l);		// xのエンコーダカウント
		printf("%d\t\n", macond.renc.r);		// yのエンコーダカウント
		printf("%f\t\n", macond.t_theta);	// マシン角度
		printf("%f\t\n" , macond.pos.x);	// x座標
		printf("%f\t\n" , macond.pos.y);	// x座標
		/* 改行 */
		printf("\n");
			
		/*********************** マシン補正セット 新式 *********************/
#endif

#ifdef	new_machine_correction_omni
		/*********************** マシン補正セット 新式 *********************/

		/* マシン補正のデバック */
		printf("%d\t\n", macond.renc.l);		// x座標
		printf("%d\t\n", macond.renc.r);		// y座標
		printf("%f\t\n", macond.t_theta);	// マシン角度
		/* 改行 */
		printf("\n");
			
		/*********************** マシン補正セット 新式 *********************/
#endif
	
#ifdef	old_machine_correction	
		/*********************** マシン補正セット 旧式 *********************/

		/* マシン補正のデバック */
		printf("x = %6.1f,\t y = %6.1f,\t th = %6.1f,\t t_th = %6.1f,\t",macond.pos.x,macond.pos.y,macond.theta*180/PI,macond.t_theta);
		/* エンコーダカウントのデバック */
		printf("enc_cnt.l=%d,enc_cnt.r=%d\t",macond.enc.l,macond.enc.r);				
		/* エンコーダの走行距離のデバック(現在はexcelで計算しているため不要) */ 
//		printf("dist.l=%f, dist.r=%f\n",(double)(macond.enc.l)/ENCODER_RES * PI * ENCODER_D_L,(double)(macond.enc.r)/ENCODER_RES * PI * ENCODER_D_R);	//エンコーダタイヤの移動距離
		/* 改行 */
		printf("\n");
			
		/*********************** マシン補正セット 旧式 *********************/
#endif	
//		LatchCnt = 0;
//	}

}



/********************************************************/
//  名前      
//		map_update
//  概要
// 		計測関連
//  機能説明
//		エンコーダのカウントを読み取る
//		カウントからマシンコンディションを求める。
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void map_update(void)	//右,左を入れ替えるとx,y軸が入れ替わる
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
//  名前      
//		coordinate
//  概要
// 		計測関連
//  機能説明
//		カウントからマシンコンディションを求める。
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void coordinate(ENCODER_COUNT enc_cnt)
{
	
	static ENCODER_COUNT cnt_old;		//過去のエンコーダカウント
	ENCODER_COUNT renc = macond.renc;	//エンコーダカウントの累積値
	ENCODER_COUNT enc;					//右と左のエンコーダがそれぞれ進んだ距離
	ENCODER_COUNT cnt_diff;				//エンコーダカウントの差
	DOUBLE_LR v_enc = macond.v_enc;		//右と左のエンコーダがそれぞれ進んだ速度
	DOUBLE_LR v_enc_old;				//過去の右と左のエンコーダがそれぞれ進んだ速度
	DOUBLE_XY pos = macond.pos;			//マシンの現在位置
	double v,theta;						//マシンの速度、mase_ctrlの角度
	int tmp;							//片方のエンコーダを中心にした時に一回転した時のエンコーダのパルス数
	double t_theta;						//旋回プログラムのための角度
//	DOUBLE_LR a;						//マシンの加速度

	
	cnt_diff.l =  (short)((unsigned short)enc_cnt.l - (unsigned short)cnt_old.l);		//エンコーダの回転の向きをここで補正する。
	cnt_diff.r = -(short)((unsigned short)enc_cnt.r - (unsigned short)cnt_old.r);		//エンコーダの回転の向きをここで補正する。
	
	cnt_old = enc_cnt;				//過去のエンコーダカウントを保存
	
	renc.l += cnt_diff.l;			//左のエンコーダカウントの累積値
	renc.r += cnt_diff.r;			//右のエンコーダカウントの累積値

	enc.l = renc.l * ENCODER_RC_L;	//左のエンコーダが進んだ距離
	enc.r = renc.r * ENCODER_RC_R;	//右のエンコーダが進んだ距離

// マシン方向
	tmp = TMP;													//片方のエンコーダを中心にした時に一回転した時のエンコーダのパルス数を求める。
																//(2.0 * PI * ENCODER_T ) / ( PI * ENCODER_D ) * ENCODER_RES

	theta = macond.theta_base;									//macond.theta_baseにはじめの角度を入力して適切な角度にすることができる。(なくてもいい?)
	
	theta += 2.0 * (PI / tmp) * ((int)(enc.r - enc.l) % tmp);	//((int)(enc.r - enc.l) % tmp_int)	>> 	マシン一回転あたりのパルス数で余りを求めることにより一回転あたりの割合を求めている(計算した値はパルス数が求まる)
																//パルス数の差を一回転あたりのパルス数で割ると一回転あたりの割合を求めることができ、それに2.0 * PIをかけることによりラジアンで求めることができる。
																//tmpがint型になっている理由は一回転あたりのパルス数が少数点以下になるとちょうど一回転が求めることができなくなるため
																//マシンの向きをラジアンで表記

	if     ( theta >  PI )theta -= 2*PI;						//角度の変化領域を変更
	else if( theta < -PI )theta += 2*PI;						//角度の変化領域を変更
	
// 絶対角度
	t_theta = macond.theta_base;								//macond.theta_baseにはじめの角度を入力して適切な角度にすることができる。(なくてもいい?)
	
	t_theta = (360.0 / tmp) * (int)(enc.r - enc.l);				//この計算を別にしているのは(int)(enc.r - enc.l)の差だから(余りではない)
																//この[deg]で求めている。
	
// 現在位置
//	pos.x += ( ( cnt_diff.l + cnt_diff.r ) / 2 ) * PI * ENCODER_D / ENCODER_RES * cos(theta);
//	pos.y += ( ( cnt_diff.l + cnt_diff.r ) / 2 ) * PI * ENCODER_D / ENCODER_RES * sin(theta);
	
//	pos.x +=  REVISE * ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2 ) * PI / ENCODER_RES * cos(theta);
//	pos.y +=  REVISE * ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2 ) * PI / ENCODER_RES * sin(theta);

//	pos.x += ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2.0 ) * PI / ENCODER_RES * cos(theta);
//	pos.y += ( ( cnt_diff.l * ENCODER_D_L + cnt_diff.r * ENCODER_D_R) / 2.0 ) * PI / ENCODER_RES * sin(theta);

	pos.x += ( (double)( cnt_diff.l + cnt_diff.r ) / 2.0 ) * PI * ENCODER_D / ENCODER_RES * cos(theta);
	pos.y += ( (double)( cnt_diff.l + cnt_diff.r ) / 2.0 ) * PI * ENCODER_D / ENCODER_RES * sin(theta);

// 過去のエンコーダの速度を保存
	v_enc_old = v_enc;
	
// 速度
	v_enc.l = cnt_diff.l * 1000 / FEEDBACK_INTERVAL * PI * ENCODER_D_L / ENCODER_RES;
	v_enc.r = cnt_diff.r * 1000 / FEEDBACK_INTERVAL * PI * ENCODER_D_R / ENCODER_RES;
	
//	printf("%6.1f,%6.1f\n",v_enc.l,v_enc.r);

	v = (v_enc.l + v_enc.r) / 2;
	
// 加速度
//	a.l = (v_enc.l - v_enc_old.l) / FEEDBACK_INTERVAL * 1000;
//	a.r = (v_enc.r - v_enc_old.r) / FEEDBACK_INTERVAL * 1000;
	
// 計算した値をマシンコンディションに代入
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
//  名前      
//		coordinate_omni
//  概要
// 		計測関連
//  機能説明
//		カウントからマシンコンディションを求める。
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		やまむろ @ TUTrobo
//
/********************************************************/
#if 0
void coordinate_omni(ENCODER_COUNT enc_cnt)
{
	#define loop_time 0.01		//フィードバック周期[sec]
	
	static ENCODER_COUNT cnt_old;		//過去のエンコーダカウント
	ENCODER_COUNT renc=macond.renc;		//エンコーダカウントの累積値
	double kaiten_x,kaiten_y;			//xyエンコーダの回転数
	ENCODER_COUNT cnt_diff;				//エンコーダカウントの差
	DOUBLE_LR v_enc = macond.v_enc;		//右と左のエンコーダがそれぞれ進んだ速度
	DOUBLE_LR v_enc_old;				//過去のxyのエンコーダがそれぞれ進んだ速度
	DOUBLE_XY pos = macond.pos;			//マシンの現在位置
	double vx,vy,v,v_rad;			//マシンの速度、mase_ctrlの角度
	int tmp=ENCODER_RES;				//一回転した時のエンコーダのパルス数
	double t_theta;						//旋回プログラムのための角度
	double diff_pos_x,diff_pos_y;		//x,yの差
	static double old_pos_x,old_pos_y;

	char zone;
	
	zone=mode();//赤青判定

// 絶対角度(degree)
	t_theta = (double)m_angle/100.0;//degree
// -PI~PIの絶対角度(rad)
//	theta = (double)angle*PI/18000.0;//rad
	
	cnt_diff.l = -1*(-(short)((unsigned short)enc_cnt.l - (unsigned short)cnt_old.l));		//エンコーダの回転の向きをここで補正する。
	cnt_diff.r = -1*((short)((unsigned short)enc_cnt.r - (unsigned short)cnt_old.r));		//エンコーダの回転の向きをここで補正する。
	
	renc.l+=cnt_diff.l;
	renc.r+=cnt_diff.r;
	
	kaiten_x = cnt_diff.l /(double)tmp;	//X方向のエンコーダが進んだ回転数（前との差）
	kaiten_y = cnt_diff.r /(double)tmp;	//Y方向のエンコーダが進んだ回転数（前との差）

	diff_pos_x=ENCODER_D_X*PI*kaiten_x*mycos(t_theta*PI/180.0)-ENCODER_D_Y*PI*kaiten_y*mysin(t_theta*PI/180.0);
	diff_pos_y=ENCODER_D_X*PI*kaiten_x*mysin(t_theta*PI/180.0)+ENCODER_D_Y*PI*kaiten_y*mycos(t_theta*PI/180.0);

// 現在位置
	pos.x += diff_pos_x;
	pos.y += diff_pos_y;

// 現在速度
	vx=diff_pos_x/(loop_time*cmt1_counter);
	vy=diff_pos_y/(loop_time*cmt1_counter);
	
	v=sqrt(POW2(vx)+POW2(vy));
	
	cmt1_counter=0;

// 進行方向ベクトル(PI~2PI)

	v_rad = atan3(vy,vx);
	if(v_rad<0)v_rad+=2.0*PI;

// 過去のエンコーダの速度を保存
	v_enc_old = v_enc;
	
	cnt_old=enc_cnt;
	
// 計算した値をマシンコンディションに代入
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
//  名前      
//		slip_stoper
//  概要
// 		速度制御関連
//  機能説明
//		目標dutyをロボットが滑らないように制御する	
//  パラメタ説明
//		aim_duty	目標duty
//		ratio		目標速度比
//		drive_K		滑るらないようにする制限値
//  戻り値
//		drive		補正されたduty		
//  作成者
//		N.TAKAHASHI @ TUTrobo
//
/********************************************************/
double slip_stoper(double aim_duty,DOUBLE_LR ratio)
{
	double drive;
	
	const double drive_K = 10.0;

/********************************************************/	
	//遠心力の求め方(簡易バージョン)
	
	//速さの２乗*旋回半径	mrω^2
	//m:質量	r:旋回半径	ω:角速度
	
	//v_L(左のタイヤduty) = ratio.l * aim_duty
	//v_R(右のタイヤduty) = ratio.r * aim_duty
	
	//r = (dutyの和)          ÷ (dutyの差分)        × (タイヤトレットの半分)
	//  = (v_L + v_R)         ÷ (v_R - v_L)  		 × (タイヤトレットの半分)
	//  = (ratio.l + ratio.r) /  (ratio.r - ratio.l) *  (TIRE_T / 2.0)
	
	//ω= (dutyの差分) 		             ÷ (タイヤトレット)
	//  = (v_R - v_L)  		             ÷ (タイヤトレット)
	//  = (ratio.r - ratio.l) * aim_duty / TIRE_T
	
	//rω^2 = (dutyの和)          × (dutyの差分)        ÷ (タイヤトレット)
	//      = (v_L + v_R)         × (v_R - v_L)  		 ÷ (タイヤトレット)
	//      = (ratio.l *  aim_duty + ratio.r * aim_duty) *  (ratio.r * aim_duty - ratio.l * aim_duty) /  (TIRE_T)
	//      = (ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)
	
	//m定数だし割っとけばよくね　by直皓
	
/********************************************************/
	//補正値(drive)の算出方法
	
	//(ratio.l + ratio.r) * (ratio.r - ratio.l) * drive * drive / (TIRE_T) = drive_K
	//上記の式を解く
	//↓解
	//drive = sqrt( (drive_K * TIRE_T) /  (lr_ratio.r - lr_ratio.l) )	（前進左回り基準）
	//この解を前後左右の４通りで場合分け
	
/********************************************************/

	//滑るらないようにする制限値のためのデバック
//	printf("%f\n",ABS((ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)));
	
	if(ABS((ratio.l + ratio.r) *  (ratio.r - ratio.l) * aim_duty * aim_duty /  (TIRE_T)) > drive_K)	//ロボットが滑りそうなら補正
	{
		if(aim_duty > 0)  //目標dutyが正のとき    
		{
			if(ratio.r > 1.0){drive =  (sqrt( (drive_K * TIRE_T) /  (ratio.r - ratio.l) ));}		//（前進左回り）
			else			 {drive =  (sqrt( (drive_K * TIRE_T) / -(ratio.r - ratio.l) ));}		//（前進右回り）
		}
		else if(aim_duty < 0)//目標dutyが負のとき
		{	
			if(ratio.r > 1.0){drive = -(sqrt( (drive_K * TIRE_T) /  (ratio.r - ratio.l) ));}		//（後退左回り）
			else			 {drive = -(sqrt( (drive_K * TIRE_T) / -(ratio.r - ratio.l) ));}		//（後退右回り）
		}	
	}
	else																							//ロボットが滑らないとき
	{
		drive = aim_duty;
	}
	
	return drive;
}

/********************************************************/
//  名前      
//		gyro_map
//  概要
// 		計測関連
//  機能説明
//		ジャイロのカウントを読み取る
//		カウントからマシンコンディションを求める。
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
#if 0
void gyro_map(void)	//右,左を入れ替えるとx,y軸が入れ替わる
{
//	#define loop_time 0.01 //タイマ割り込みの入る周期
	
//	static double old_ax,old_ay;
//	static double old_vx,old_vy;
	
	static double test_ax[10];
	static double test_ay[10];//オフセットのための型
	static double offset_ax;
	static double offset_ay;
	
	int i;
	double ax_max,ax_min,ay_max,ay_min;
	double m_angle_rad;
	
	 m_angle_rad = (double)m_angle*PI/18000.0;
	
	for(i=0;i<9;i++)//過去10個分の値を見る
	{
		test_ax[9-i]=test_ax[8-i];	//printf("[%d]=%.2f\n",9-i,test_ax[9-i]);
		test_ay[9-i]=test_ay[8-i];	//printf("[%d]=%.2f\n",9-i,test_ay[9-i]);
	}
	test_ax[0]=(double)accX/100.0;
	test_ay[0]=(double)accY/100.0;
	
	//printf("[0]=%.2f\n",test_ay[0]);
	
	ax_max=test_ax[0];ax_min=test_ax[0];
	ay_max=test_ay[0];ay_min=test_ay[0];
	
	
	for(i=0;i<=9;i++)//過去10個分の値から最大と最小を割り出す
	{
		if(test_ax[i]>ax_max)ax_max=test_ax[i];
		if(test_ax[i]<ax_min)ax_min=test_ax[i];
		if(test_ay[i]>ay_max)ay_max=test_ay[i];
		if(test_ay[i]<ay_min)ay_min=test_ay[i];
	}
	
//	printf("x_max=%.2f\t",ax_max);
//	printf("x_min=%.2f\t",ax_min);
//	printf("ax=%.2f\n",(double)accX/100.0);
	
	
	if( ABS(ax_max-ax_min)<0.1)offset_ax=test_ax[0];//maxとminの差が少なければ今の値をオフセットとして代入
	if( ABS(ay_max-ay_min)<0.1)offset_ay=test_ay[0];
	

	gcond.ax=test_ax[0]-offset_ax;//加速度[m/s^2]の代入(オフセットをどうするか)
	gcond.ay=test_ay[0]-offset_ay;
	
	gcond.m_ax=gcond.ax*mycos(m_angle_rad)-gcond.ay*mysin(m_angle_rad);
	gcond.m_ay=gcond.ax*mysin(m_angle_rad)+gcond.ay*mycos(m_angle_rad);

	gcond.a_rad=atan3(gcond.m_ay,gcond.m_ax)+PI;//プレスとコンの入力と比較できるよう、0~2PIにする。

/*	
//	printf("ax=%.2f\n",gcond.ax);ok!
//	printf("old_ax=%.2f\n",old_ax);ok!
//	printf("ax=%.2f\t,off_ax=%.2f\n",test_ax[0],offset_ax);
//	printf("ay=%.2f\t,off_ay=%.2f\n",test_ay[0],offset_ay);


//	printf("%f\t",gcond.vx);
	
	gcond.vx += old_ax*loop_time*1000.0;//速度[mm/s]の計算
	gcond.vy += old_ay*loop_time*1000.0;
	gcond.v  = sqrt( POW2(gcond.vx) + POW2(gcond.vy) );
	gcond.v_rad=atan2(gcond.vy,gcond.vx);//速度方向の角度の計算
	
//	printf("%f\n",old_ax*0.010*1000.0);
//	printf("%f\n",gcond.vx);

	
	gcond.x += old_vx*loop_time;//x座標[mm]の計算
	gcond.y += old_vy*loop_time;
	
	
	old_ax=gcond.ax;
	old_ay=gcond.ay;
	old_vx=gcond.vx;
	old_vy=gcond.vy;		
*/
}
#endif