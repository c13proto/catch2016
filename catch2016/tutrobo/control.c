/********************************************************/
//
//  概要
//      マシン移動制御関連
//  作成者
//		TUTrobo
//
/********************************************************/

#include "setup.h"		//マイコンの設定



//グローバル変数宣言//
struct comand_information cmd_inf;			// comArrayの値を受け取る型
struct machine_condition macond;			// マシン情報が格納されている
struct gyro_condition gcond;				// ジャイロの状態
unsigned short task_number;					// task_controlで使用
unsigned char task_mode;					// taskのモード選択で使用

#if 0

//オリジナルK//
double ratio;
/********************************************************/
//
//  概要
//      マシン移動制御関連
//  作成者
//		TUTrobo
//
/********************************************************/
#ifdef USE_CET
	#define CONTROL_CYCLE	0.01	//制御周期[s]
#else
	#define CONTROL_CYCLE	0.01	//制御周期[s]
#endif
#define FILTER_TIME		0.1		//一次遅れフィルタ係数(未使用)
#define PCON_NUM	4	//pid_configの数
#define VEL_PID		//defineすると速度型PIDを行う

//発射関連
#define DEFAULT_SHOOT_SPEED	3100 //初期回転速度[RPM]
#define SHT_LIMIT 5500 //0.5[r/10ms]	制限回転速度[RPM]
#define ANG_LIMIT 10 //10度
#ifndef VEL_PID
	//位置型PID用ゲイン
	#define ROLLER_P_GAIN 0.3//0.01 //発射ローラー用Pゲイン
	#define ROLLER_I_GAIN 0.1//0.2 //発射ローラー用Iゲイン
	#define ROLLER_D_GAIN 0.1//0.01 //発射ローラー用Dゲイン	
#else
	//速度型PID用ゲイン
	#define ROLLER_P_GAIN 0.15//0.1 //発射ローラー用Pゲイン
	#define ROLLER_I_GAIN 0.1//0.075 //発射ローラー用Iゲイン
	#define ROLLER_D_GAIN 0.1//0.003 //発射ローラー用Dゲイン	
#endif
#define ROLLER_TOLERANCE 50.0	//発射ローラー許容誤差

//装填装置関連
#define RELOAD_DEFAULT_AD	443//500初期状態でのAD値(つぼみ受け渡し待ち)
#define RELOAD_SHOOT_AD		875//発射時のAD値
#ifndef VEL_PID
	//位置型PID用ゲイン
	#define RELOAD_P_GAIN	0.04 //Pゲイン
	#define RELOAD_I_GAIN	0.00 //Iゲイン
	#define RELOAD_D_GAIN	0.00 //Dゲイン
#else	
	//速度型PID用ゲイン
	#define RELOAD_P_GAIN	0.03 //Pゲイン
	#define RELOAD_I_GAIN	0.02 //Iゲイン
	#define RELOAD_D_GAIN	0.0 //Dゲイン
#endif
#define RELOAD_DUTY_LIM	80	//DUTY制限
#define RELOAD_TOLERANCE	50	//AD値許容誤差
#define RELOAD_THRESHOLD	50	//初期位置に戻る際にこの数字以上偏差があればオンにする

//二本目装填関連
#define RELOAD2_DEFAULT_AD	835	//初期状態でのAD値(装填位置)
#define RELOAD2_WAIT_AD		150	//つぼみ受け渡し待ちの位置のAD値
#define RELOAD2_SHOOT_AD	150	//発射時の位置のAD値
#ifndef VEL_PID
	//位置型PID用ゲイン
	#define RELOAD2_P_GAIN	0.2 //Pゲイン
	#define RELOAD2_I_GAIN	0.0 //Iゲイン
	#define RELOAD2_D_GAIN	0.0 //Dゲイン
#else
	//速度型PID用ゲイン
	#define RELOAD2_P_GAIN	0.2 //Pゲイン
	#define RELOAD2_I_GAIN	0.0 //Iゲイン
	#define RELOAD2_D_GAIN	0.0 //Dゲイン
#endif
#define RELOAD2_DUTY_LIM	50		//DUTY制限
#define RELOAD2_TOLERANCE	20		//AD値許容誤差


#define TERATERM_COMU //テラターミナルを使って動かす
#define DEBUG_MODE //デバッグ用
#define SENKAI_INIT

/********************************************************/
//  TUTrobo
//
//  概要
//      IDO関連 グローバル変数設定
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
	0, //発射回転速度
	0, //旋回角度
	0, //発射開始
	0, //旋回開始
	0, //引き金作動
	-1, //再装填状態
	0, //動作モード 1:発射用ローラー制御 2:旋回、引き金、再装填制御
	-1,
	0,
};

/******** 各部PID制御に用いるパラメータは以下をいじる ********/ 
struct pid_config pcon[PCON_NUM]={
//	出力先				最大Duty			許容誤差			Pゲイン				Iゲイン				Dゲイン		
	{&(ROLLER1_PWM),	100.0,				ROLLER_TOLERANCE,	ROLLER_P_GAIN,	ROLLER_I_GAIN,	ROLLER_D_GAIN}, //ローラー一個目
	{&(ROLLER2_PWM),	100.0,				ROLLER_TOLERANCE,	ROLLER_P_GAIN,	ROLLER_I_GAIN,	ROLLER_D_GAIN},	//ローラー二個目
	{&(RELOAD1_PWM),	RELOAD_DUTY_LIM,	RELOAD_TOLERANCE,	RELOAD_P_GAIN,	RELOAD_I_GAIN,	RELOAD_D_GAIN},//装填
	{&(RELOAD2_PWM),	RELOAD2_DUTY_LIM,	RELOAD2_TOLERANCE,	RELOAD2_P_GAIN,	RELOAD2_I_GAIN,	RELOAD2_D_GAIN},//二本目装填		
};

struct pid_status psta[PCON_NUM]; //PCONの各種状態を格納する変数

double sP_g=0.0,sI_g=0.0,sD_g=0.0;

/********************************************************/
//  名前      
//		shooter_control
//  概要
// 		マシン移動制御関連
//  機能説明
//		発射全般の制御
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
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
	
	//受信データ処理
//	if(cmdp.mode == 1)controller_data(); //モード1の基盤でのみコントローラーを読む
	
	//センサーデータ処理
	#ifdef USE_CET
	cet_get_rpm(rot); //最後に求められた回転数をrotに代入
	//無駄だけど、前の仕様だとrotは10ms間での回転数なので、互換性を保つために除算
	rot[0] /= -6000.0;
	rot[1] /= -6000.0;
	#else
	enc_getrot(rot); //エンコーダーカウントを基に軸回転数を求める
	#endif
	
	ad_load_0_3(ad);
	
	//AD値初期化
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
		case 0: //初期
			//cmdp.reload = -1;
			//cmdp.shot = 0;
			break;
		
		case 1: //苗木受け取り
		//	cmdp.reload = 0;
			break;
			
		case 2: //ローラー回転
			cmdp.shot = 1;
			LASER_OUT=1;
			break;
	}
	
	
	//発射シーケンス
	shoot_seq(cmdp.shot,rot);
	//print_g++;
	//再装填シーケンス
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
	
	//旧値更新
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
//  名前      
//		shoot_seq
//  概要
// 		マシン移動制御関連
//  機能説明
//		パラメータに応じて発射シーケンスを行う
//	注意事項
//		
//  パラメタ説明
//		
//  戻り値
//		
//  作成者
//		IDO
//
/********************************************************/
char shoot_seq(int flag,double *rot){
	static char cnt=0;
	double target,duty0,duty1;
	//一定回転速度を超えたら停止 & ノイズ対策
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
	pcon_motor(0,-duty0,0);	//duty出力
	pcon_motor(1,-duty1,0);	//duty出力
	return 1;	
}

/********************************************************/
//  名前      
//		reload_seq
//  概要
// 		マシン移動制御関連
//  機能説明
//		パラメータに応じて(再)装填シーケンスを行う
//	注意事項
//		
//  パラメタ説明
//		
//  戻り値
//		
//  作成者
//		IDO
//
/********************************************************/
char reload_seq(char flag,int ad[4],int ad_old[4]){
	static unsigned int wait=0;
	double duty;
	char for_n;
	//1本目		
	if(ad_old[0] != 9999){ //AD値が乱れてなかったら実行
		pcon_update(2,ad[0]);
		if(cmdp.reload < 3){ //待機状態 苗木受け渡しのため展開
			duty = pcon_pid(2,(double)RELOAD_DEFAULT_AD);
		}
		else if(cmdp.reload == 3){ //装填 装填位置に移動、一定時間待機後に展開位置へ
			duty = pcon_pid(2,(double)RELOAD_SHOOT_AD);
			wait++;
			//sum += psta[2].current[0]-psta[2].current[1];
			if(psta[2].end > 0){
				//装填時の押さえつけは機械強度の問題上、現時点では行わない
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
					cmdp.reload = 0; //2 //初期位置に戻す
					comm_action('S',8); //ローラー停止
					put_s("END\n");
					//print_g=1;
					//for(for_n=0; for_n<10; for_n++){
					//	print_data[0][for_n] = psta[0].current[for_n];
					//	print_data[1][for_n] = psta[1].current[for_n];
					//}					
				}
			}
		}else if(cmdp.reload == 4){ //装填 ゲイン調整用
			duty = pcon_pid(2,(double)RELOAD_SHOOT_AD);
			if(psta[2].end > 80/(CONTROL_CYCLE*100)){
				cmdp.reload = 5; //2
				psta[2].end = 0;
			}
		}else if(cmdp.reload == 5){ //装填 ゲイン調整用
			duty = pcon_pid(2,(double)RELOAD_DEFAULT_AD);
			if(psta[2].end > 80/(CONTROL_CYCLE*100)){
				cmdp.reload = 4; //2
				psta[2].end = 0;
			}
		}				
		
		//必殺オンオフ制御
		if(psta[2].target[0] == (double)RELOAD_DEFAULT_AD){ //装填時に変な挙動を起こさないよう、オンオフは初期位置に向かっている時のみ行う
			if(psta[2].current[0] - psta[2].target[0] > RELOAD_THRESHOLD){ //偏差がしきい値よりも高かったらオン
				duty = -5.0;
				psta[2].duty = 0.0;
			}else if(psta[2].current[0] > psta[2].target[0]){ //偏差がしきい値よりも低いが、回転方向は初期位置に戻る方向ならオフ
				duty = 0.0;	
				psta[2].duty = 0.0;
			}		
	}
	}else{//AD値が乱れてたらモーター停止
		duty = 0.0;
	}
	pcon_motor(2,duty,1);	//duty出力

	//2本目
	if(ad_old[1] != 9999){ //AD値が乱れてなかったら実行
		pcon_update(3,ad[1]);
		
		//発射位置に移動する時はDuty制限を緩めて最高速を上げる
		if(cmdp.reload == 1)
			pcon_setting(3,60,-1); 
		else
			pcon_setting(3,50,-1);
			
		if(cmdp.reload == -1){ //初期セットアップ 装填位置に収納
			duty = pcon_pid(3,(double)RELOAD2_DEFAULT_AD);
		}else if(cmdp.reload == 0){ //待機状態 苗木受け渡しのため展開
			duty = pcon_pid(3,(double)RELOAD2_WAIT_AD);
		}else if(cmdp.reload == 1){ //装填 発射位置に移動
			duty = pcon_pid(3,(double)RELOAD2_DEFAULT_AD);
			if(psta[3].end > 8/(CONTROL_CYCLE*100))
				cmdp.reload = 2;
		}else if(cmdp.reload >= 2){ //装填 発射位置に移動
			duty = pcon_pid(3,(double)RELOAD2_SHOOT_AD);
			}
	}else{
		duty = 0.0;

	}
	pcon_motor(3,duty,1);	//duty出力
//	printf("%d\n",wait);
	return 1;
}

/********************************************************/
//  名前      
//		enc_getrot
//  概要
// 		マシン移動制御関連
//  機能説明
//		エンコーダーの値を処理して回転速度を求める。
//	注意事項
//		
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		IDO
//
/********************************************************/

void enc_getrot(double rot_return[]) 				
{
	static int cnt[2], cnt_old[2], cnt_diff[2];
	double rot[2];
	cnt[0] = ENC1_TCNT;//MTU21.TCNT;
	cnt[1] = ENC2_TCNT;//MTU22.TCNT;
	cnt_diff[0] = -1*(short)((unsigned short)cnt[0] - (unsigned short)cnt_old[0]); //前回の割り個み時のカウント数と、現在のカウント数の差
	cnt_diff[1] = -1*(short)((unsigned short)cnt[1] - (unsigned short)cnt_old[1]); //前回の割り個み時のカウント数と、現在のカウント数の差
	
	rot[0] = (double)cnt_diff[0] / RND_PLS; //単位時間で何回転したか
	rot[1] = (double)cnt_diff[1] / RND_PLS; //単位時間で何回転したか
	cnt_old[0] = cnt[0];
	cnt_old[1] = cnt[1];
	rot_return[0] = rot[0];
	rot_return[1] = rot[1];
}


/********************************************************/
//  名前      
//		pcon_update
//  概要
// 		マシン移動制御関連
//  機能説明
//		PCON旧値&現在値更新
//	注意事項
//		
//  パラメタ説明
//		PCON番号、現在値
//  戻り値
//		なし
//  作成者
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
//  名前      
//		pcon_setting
//  概要
// 		マシン移動制御関連
//  機能説明
//		PCONの各種パラメータを変更
//	注意事項
//		
//  パラメタ説明
//		PCON番号、最大、許容誤差
//  戻り値
//		なし
//  作成者
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
//  名前      
//		pcon_gain
//  概要
// 		マシン移動制御関連
//  機能説明
//		PCONの各種ｹﾞｲﾝを変更
//	注意事項
//		
//  パラメタ説明
//		PCON番号、各ゲイン
//  戻り値
//		なし
//  作成者
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
//  名前      
//		pcon_motor
//  概要
// 		マシン移動制御関連
//  機能説明
//		pcon.outputに指定されるアドレスへDUTYを出力
//	注意事項
//		
//  パラメタ説明
//		PCON番号、DUTY、サインマグニチュードフラグ
//  戻り値
//		なし
//  作成者
//		IDO
//	
//
/********************************************************/
void pcon_motor(char num, double duty, char sign){
	if(sign) //最後のフラグが1ならサインマグニチュード用の関数を利用して出力
		*(pcon[num].output) = sign_mag_pwm(duty);
	else
		*(pcon[num].output) = anti_lock_pwm(duty);
}		
	
/********************************************************/
//  名前      
//		pcon_pid
//  概要
// 		マシン移動制御関連
//  機能説明
//		与えられたPCON情報と目標値でPID制御を行い、Dutyを返す
//	注意事項
//		
//  パラメタ説明
//		PCON番号、目標値
//  戻り値
//		Duty
//  作成者
//		IDO
//		
//
/********************************************************/
double pcon_pid(char num,double target){
	char for_n;
	double diff[3],sht_P,sht_I,sht_D,duty;
	
	psta[num].target[0] = target;
	//目標が変わった時には到達フラグ、微分成分旧値、現Duty、積分成分(位置型用)をクリア
	if(psta[num].target[1] != target){
		psta[num].end = 0;
		psta[num].D_old = 0;
		psta[num].duty = 0;
		psta[num].integr = 0;
	}
	
	for(for_n=0; for_n<3; for_n++){
		diff[for_n] = psta[num].target[for_n] - psta[num].current[for_n]; //偏差 diff[0]=現在値、diff[1]=一サイクル前の値
	}
	#ifndef VEL_PID
	//位置型PID
	sht_P = diff[0];
	if(sht_P*pcon[num].P_gain < pcon[num].duty_lim) //比例帯に入ったら積分成分を加算
		psta[num].integr += diff[0] * (CONTROL_CYCLE * 100);
	else
		psta[num].integr = 0;
	sht_I = psta[num].integr;
	sht_D =  (diff[0] - diff[1]) / (CONTROL_CYCLE*100); // ((diff[1] - diff[2])*FILTER_TIME+(diff[0] - diff[1])) / (CONTROL_CYCLE*100);
	//sht_D = (pcon[num].current[1] - pcon[num].current[0]) / (CONTROL_CYCLE*100);
	pcon[num].duty = sht_P*pcon[num].P_gain + sht_I*pcon[num].I_gain  + sht_D*pcon[num].D_gain;
	#else
	//速度型PID
	sht_P = diff[0] - diff[1]; //比例成分
	sht_I = diff[0] * CONTROL_CYCLE; //積分成分
	sht_D = (diff[0] + diff[2] - 2*diff[1]) / (CONTROL_CYCLE*100);  //微分成分
	//sht_D = (2*pcon[num].current[1] - pcon[num].current[0] - pcon[num].current[2]) / (CONTROL_CYCLE*100);
	psta[num].duty += sht_P*pcon[num].P_gain + sht_I*pcon[num].I_gain  + sht_D*pcon[num].D_gain; //duty加算
	#endif
	psta[num].D_old = sht_D; //微分旧値更新
	
	
	duty = psta[num].duty;
	//duty制限
	if(pcon[num].duty_lim != 0){
		if(duty > pcon[num].duty_lim)
			duty = pcon[num].duty_lim;
		if(duty < -pcon[num].duty_lim)
			duty = -pcon[num].duty_lim;
	}
	
	//終了判定
	if(fabs(diff[0]) <= pcon[num].tlrnce)
		if(psta[num].end>=250) //オーバーフロー防止
			psta[num].end=250;
		else
			psta[num].end++;
	else
		if(psta[num].end>0)
			psta[num].end--;
		
	return duty;
}

/********************************************************/
//  名前      
//		pcon_manual
//  概要
// 		マシン移動制御関連
//  機能説明
//		特定のdutyで制御を行う
//	注意事項
//		
//  パラメタ説明
//		PCON番号
//  戻り値
//		Duty
//  作成者
//		IDO
//		
//
/********************************************************/
double pcon_manual(char num,double duty){
	psta[num].target[0] = psta[num].current[0];
	psta[num].D_old = 0;
	psta[num].duty = duty; //duty代入
	
	//duty制限
	if(psta[num].duty > pcon[num].duty_lim)
		psta[num].duty = pcon[num].duty_lim;
	if(psta[num].duty < -pcon[num].duty_lim)
		psta[num].duty = -pcon[num].duty_lim;
		
	return psta[num].duty;
	//pcon[num].end=0;
}

/********************************************************/
//
//  名前      
//		comm_action
//  概要
// 		マシン制御
//  機能説明
//		コマンドに応じたアクションを実行
//	パラメータ
//		コマンド、データ				
//  戻り値
//		成否		
//  作成者
//		IDO
//	備考
//		予定だと
//		mode 2は旋回・ロック・再装填を制御する基盤で、ＰＣもこっちに繋げられる
//		mode 1は発射用のローラーのみ制御する基盤で、mode 2の基盤と命令をやり取りして動作
//
/********************************************************/
int comm_action(char cmd,int data)
{
	//printf("cmd:%s value:%d\n",cmd,data);
	switch(cmd){
		case 'E': //エラー関連
			if(data==0){
				printf("\nCommand Accepted\n"); //E0でコマンド受信を確認
				return 1;
			}				
			
			if(data==1){
				printf("\nInvalid Command\n"); //E1は未定義のコマンドが送られた時
				return 1;
			}
			if(data==2){
				printf("\nInvalid Data Range\n"); //E2は速度、角度の指定で範囲外の数値が指定された時
				return 1;
			}
			if(data==9999){
				//printf("E9999");
				directions(&com[1],1,0); //E2は速度、角度の指定で範囲外の数値が指定された時
				return 1;
			}	
			break;				
		case 'Q':
			tera=1;
			printf("change tera\n");
			break;
		case 'C': //発射回転速度指定
			if(cmdp.mode==2){
				directions(&com[0],data,2);
				return 1;
			}
			else{
				if(ABS(data) <= SHT_LIMIT){ //回転速度制限
					cmdp.shot_spd = data;
//					directions(&com[0],0,0);
				}
//				else directions(&com[0],2,0);
				return 1;
			}
			break;
			
		case 'X': //発射ローラーPゲイン
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].P_gain = sP_g = (double)data/32767.0;
				else
				pcon[0].P_gain = pcon[1].P_gain = (double)data/32767.0;
				
			}
			break;
			

		case 'Y': //発射ローラーIゲイン
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].I_gain = sI_g = (double)data/32767.0;
				else
				pcon[0].I_gain = pcon[1].I_gain  = (double)data/32767.0;
			}
			break;
			

		case 'Z': //発射ローラーDゲイン
			if(cmdp.mode==1){
				if(cmdp.shot_spd == 0)
					pcon[2].D_gain = sD_g = (double)data/32767.0;
				else
				pcon[0].D_gain = pcon[1].D_gain = (double)data/32767.0;
			}
			break;						

		case 'R': //再装填
			if(cmdp.mode==1){
				if(cmdp.reload == -1)
					cmdp.reload = 0;
				return 1;						
			}else if(cmdp.mode == 2){
//				directions(&com[0],data,CMD_R);
			}
			break;
				
		case 'I': //初期セットアップ	
			if(data==1){ //モード１用
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
			if(data==2){ //モード２用
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
			if(data==3){ //テラタームでの送受信確認用
				printf("\nsetup_ok\n");
//				PE.DRL.BIT.B4 = 1;
//				power_ON();
				return 1;
			}											
			break;		
		case 'S': //発射(Shoot)、スタート・ストップじゃない！			
			if(data==1){ //発射シーケンス開始
				//PCから命令がS1が発せられたらそのまま転送
				LASER_OUT=1;	
				if(cmdp.mode==2){ 
					directions(&com[0],1,4);
					return 1;
				}
				else if(cmdp.mode==1){ //ローラー用基盤がS1を受け取ったらグローバル変数のフラグを立てて、interruptのタイマ割り込みでローラーを制御
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
			if(data==2){ //ローラーテスト
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
			if(data==8){ //ローラー強制停止
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
			if(data>=10){ //ローラーを一定Dutyで回転させる
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
//  名前      
//		terminal_control
//  概要
// 		マシン移動制御関連
//  機能説明
//		PCからのコマンド制御
//	注意事項
//		
//  パラメタ説明
//		受信したデータ
//  戻り値
//		1:成功
//  作成者
//		IDO
//
/********************************************************/
int tera=1
int terminal_control(char c){
	int data;
	if(tera==1){
		c_dbg[cnt_dbg] = c; //char型配列に受信した文字を代入していく
		//区切り文字を受け付けたら文字数を比較し、文字数が5なら下4桁をintに変換してデータとして、上一桁の文字で分岐
		if(c_dbg[cnt_dbg] == '|'){
			if(cnt_dbg != 5){
				put_s("\nInvalid Length\n");
			}
			else{
				data = atoi(&c_dbg[1]);
				switch(c_dbg[0]){
					//comm_actionで特定のコマンドが送信されてきた場合の動作を行える
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
			memset(c_dbg, 0, sizeof(c_dbg)); //char初期化
		}	
		cnt_dbg++;
		if(cnt_dbg >= 10){ //エラー防止
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

	//PIDオートチューニング(インディシャル応答法)
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
					if(slope > slope_max){ //最大値更新
						slope_max = slope;
						inter_max = inter;
					}
					if(slope < 0.00006 && time > 200){ //終了処理
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
//  名前      
//		gear
//  概要
// 		マシン移動制御関連
//  機能説明
//		モータのゲインを変更
//  パラメタ説明
//		なし
//  戻り値
//		res		コマンドの判定
//  作成者
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
//  名前      
//		cmd_init
//  概要
// 		マシン移動制御関連
//  機能説明
//		コマンドの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
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
//  名前      
//		mode_control
//  概要
// 		マシン移動制御関連
//  機能説明
//		コマンドの選択
//  パラメタ説明
//		なし
//  戻り値
//		mode		モード選択
//  作成者
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
//  名前      
//		task_control
//  概要
// 		マシン移動制御関連
//  機能説明
//		場合わけをしてpathの動きを行う
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void task_control(void)		
{
	int cmd_res = 0;
	static char range_flag = 0;
//	char read_duty = 0;				// 走行系コマンドかどうか
//	char read_theta = 0;
//	static double base = 0.0;		// 前回のコマンドで指定したduty
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