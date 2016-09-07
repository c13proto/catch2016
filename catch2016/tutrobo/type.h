/********************************************************/
//
//  概要
//      プログラムの型名宣言
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 各種型名定義
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
//  概要
//      プログラムの型名宣言 エンコーダの補正値
/********************************************************/
struct correction_value{
	double			ENCODER_RC_L;	// 左のエンコーダの補正値
	double			ENCODER_RC_R;	// 右のエンコーダの補正値
	double			ENCODER_D;		// エンコーダータイヤ直径
	double			ENCODER_D_L;	// 左エンコーダータイヤ直径
	double			ENCODER_D_R;	// 右エンコーダータイヤ直径
	double			ENCODER_T;		// エンコーダートレッド	
};

struct omni_correction_value{

	double			ENCODER_D_X;	//X方向のエンコーダータイヤ直径
	double			ENCODER_D_Y;	//Y方向のエンコーダータイヤ直径


};

/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 マシンコンディション
/********************************************************/
struct machine_condition {
	ENCODER_COUNT 	enc;		//エンコーダ累積カウント
	ENCODER_COUNT	renc;		//エンコーダ累積カウント生
	DOUBLE_LR		v_enc;		//左右エンコーダ車輪速度[mm/sec]
	double			vx;			//x方向の速度[mm/sec]
	double			vy;			//y方向の速度[mm/sec]
	double			v;			//マシン速度[mm/sec]
	double			v_rad;		//マシン進行方向ベクトル[rad]PI~2PI
	double			rad;		//マシン方向[rad]
	double			deg;		//マシン方向[deg]
	double			theta_base;	//マシン方向[rad]
	double			theta;		//マシン方向[rad]
	double			t_theta;	//マシン旋回のための角度[deg]	
	DOUBLE_XY		pos;		//マシン現在座標[mm](x:進行方向, y:左右)
	DOUBLE_LR		duty;		//モータに与えるduty
	DOUBLE_LR		duty_old;	//モータに与えるduty
	DOUBLE_GEAR		diff_gear;	//フィードバックゲイン(差動)
	DOUBLE_GEAR		speed_gear;	//フィードバックゲイン(速度)		
};

typedef struct {
	int				renc;		//エンコーダの累積値
	double			pos;		//座標[mm]
	double			v;			//速度[mm/sec]
	
	double			max_v;		//最大速度[(+-)mm/sec]
	double			aim_v;		//目標速度[mm/sec]
	double			duty;		//現在かけているduty(-100~100)
	char 			mode;//手動，自動，ストップの格納
}arm_condition;


/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 マシンコンディション
/********************************************************/
struct gyro_condition{
	double ax;//ジャイロから見た加速度x[m/(s^2)]
	double ay;//ジャイロから見た加速度y[m/(s^2)]
	double m_ax;//初期状態から見た加速度x[m/(s^2)]
	double m_ay;//初期状態から見た加速度y[m/(s^2)]
	double a_rad;//初期状態から見た加速方向ベクトル[rad]

/*	
	double vx;//速度x[mm/s]
	double vy;//速度y[mm/s]
	double v;//速度[mm/s]
	double v_rad;//速度の方向（radian）
	
	double x;//x座標[mm]
	double y;//y座標[mm]		
*/
};

/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 コマンドのリスト
/********************************************************/
//*** コマンドを追加する場合，ここに登録すること！ ***
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
//  概要
//      プログラムの型名宣言 コマンド制御
/********************************************************/
struct comand_information{
	enum eCMDNAME name;		//コマンド名
	short in1;				//第1引数
	short in2;				//第2引数
	short in3;				//第3引数
	short in4;				//第4引数
	short in5;				//第5引数
	short range;			//曲線の長さ
};


/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 数字の数とその数字を記録する
/********************************************************/
struct num_list{
	int obj;				//数字
	int num;				//数
};


/********************************************************/
//  TUTrobo
//
//  概要
//      プログラムの型名宣言 命令フラグ関連
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
//  概要
//      プログラムの型名宣言 PID制御に用いるパラメータ
/********************************************************/
struct pid_config {
	unsigned short* output;	//出力先
	double duty_lim;	//最大Duty
	double tlrnce;	//許容誤差
	double	P_gain;	//Pゲイン
	double	I_gain;	//Iゲイン
	double	D_gain;	//Dゲイン
};

struct pid_status {
	double current[21];	//現在値
	double target[21];	//目標値
	unsigned char end;	//完了フラグ
	double D_old;
	double integr;
	double duty;
	double debug;
	unsigned char intrpt_cnt;
};

#endif // __TYPE_H__

