/********************************************************/
//
//  概要
//      A/D変換関連
//  注意
//		マイコン依存ファイル!!
//  作成者
//		K.yamada@ TUTrobo
//
/********************************************************/


#include "../setup.h"		//マイコンの設定

//#define AD0_SINGLE_10
#define AD0_SCAN_10

//#define AD1_SINGLE_10
#define AD1_SCAN_10

//AD_SINGLE_12
//AD_SCAN_12

int ad[4];

#if 0
/////////////////////////////////////////////////////////

/*******AD変換シングルスキャンモードのプログラム********/

/********************************************************/
//  名前      
//		ad_init
//  概要
// 		A/D変換関数
//  機能説明
//		A/Dの初期化
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		@ TUTrobo
//
/********************************************************/
void ad_init()							//AD変換の初期設定
{
//SH7125
#if 0
	STB.CR4.BIT._AD0   = 0;				//スタンバイ解除
	AD0.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD0.ADCSR.BIT.STC  = 0;				//AD変換の時間設定(50ステート)
	AD0.ADCSR.BIT.CKSL = 3;				//AD変換の時間設定(Pφ/2)
	AD0.ADCSR.BIT.ADM  = 0;				//AD変換のモード設定(シングルモード)
	AD0.ADCSR.BIT.CH   = 0;				//チャンネルセレクト(シングルモード AN0) 使うのはAN0～3
	
	//※チャンネルセレクトは、int ad_load(int i)で行う。	
#endif
}




/****AD変換シングルスキャンモードのプログラムここまで***/

/////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////

/*********AD変換連続スキャンモードのプログラム**********/

/********************************************************/
//  名前      
//		ad_init(連続スキャンモード)
//  概要
// 		A/D変換関数
//  機能説明
//		A/Dの初期化
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		 @ TUTrobo
//
/********************************************************/
void ad_init()							
{
	PORT4.ICR.BYTE = 0xFF;				// ポート入力設定
#if defined(AD0_SINGLE_10) || defined(AD0_SCAN_10)	
	MSTP_AD0 = 0;						//スリープ偏移解除
	AD0.ADCSR.BIT.ADST = 0; 			// AD変換停止
	AD0.ADDPR.BIT.DPSEL = 1;			//データをMSBによせる
	AD0.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD0.ADCR.BIT.TRGS = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD0.ADSSTR= 75;						//0.52[us]+ADSSTR/48[Mhz]>=2[us]
	                                    //ADSSTR >= 71.04
	AD0.ADCR.BIT.CKS = 3;				//AD変換の時間設定(Pφ) 48Mhz
	AD0.ADCSR.BIT.CH  = 3;				//AD変換のモード設定(4 チャネルスキャンモード)
	#ifdef AD0_SCAN_10
		AD0.ADCR.BIT.MODE   = 3;				//スキャンモード
	#endif
#endif

#if defined(AD1_SINGLE_10) || defined(AD1_SCAN_10)	
	MSTP_AD1 = 0;						//スリープ偏移解除
	AD1.ADCSR.BIT.ADST = 0; 			// AD変換停止
	AD1.ADDPR.BIT.DPSEL = 1;
	AD1.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD1.ADCR.BIT.TRGS = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD1.ADSSTR= 75;						//0.52[us]+ADSSTR/48[Mhz]>=2[us]
	                                    //ADSSTR >= 71.04
	AD1.ADCR.BIT.CKS = 3;				//AD変換の時間設定(Pφ) 48Mhz
	AD1.ADCSR.BIT.CH  = 3;				//AD変換のモード設定(4 チャネルスキャンモード)	
	#ifdef AD1_SCAN_10
		AD1.ADCR.BIT.MODE   = 3;				//スキャンモード
	#endif
#endif
}

/********************************************************/
//  名前      
//		ad_load(連続スキャンモード)
//  概要
// 		A/D変換関数
//  機能説明
//		チャンネル0~3を一度に読み取る
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		 @ TUTrobo
//
/********************************************************/
void ad_load_0_3(int *ad_data) 				
{
	
	AD0.ADCSR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD0.ADCSR.BIT.ADST == 1);  // AD変換終了待ち
	
	ad_data[0] = AD0.ADDRA >> 6; 	// AN0 10bitで取得
	ad_data[1] = AD0.ADDRB >> 6; 	// AN1 10bitで取得
	ad_data[2] = AD0.ADDRC >> 6; 	// AN2 10bitで取得
	ad_data[3] = AD0.ADDRD >> 6;	// AN3 10bitで取得
	
}

/********************************************************/
//  名前      
//		ad_load(連続スキャンモード)
//  概要
// 		A/D変換関数
//  機能説明
//		チャンネル4~7を一度に読み取る
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		@ TUTrobo
//
/********************************************************/
void ad_load_4_7(int *ad_data) 				
{
	
	AD1.ADCSR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD1.ADCSR.BIT.ADST == 1);  // AD変換終了待ち
	
	ad_data[0] = AD1.ADDRA >> 6; 	// AN0 10bitで取得
	ad_data[1] = AD1.ADDRB >> 6; 	// AN1 10bitで取得
	ad_data[2] = AD1.ADDRC >> 6; 	// AN2 10bitで取得
	ad_data[3] = AD1.ADDRD >> 6;	// AN3 10bitで取得
	
}
void ad_load_0_7(int *ad_data) 				
{
	AD0.ADCSR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD0.ADCSR.BIT.ADST == 1);  // AD変換終了待ち
	
	ad_data[0] = AD0.ADDRA >> 6; 	// AN0 10bitで取得
	ad_data[1] = AD0.ADDRB >> 6; 	// AN1 10bitで取得
	ad_data[2] = AD0.ADDRC >> 6; 	// AN2 10bitで取得
	ad_data[3] = AD0.ADDRD >> 6;	// AN3 10bitで取得
	
	AD1.ADCSR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD1.ADCSR.BIT.ADST == 1);  // AD変換終了待ち
	
	ad_data[4] = AD1.ADDRA >> 6; 	// AN0 10bitで取得
	ad_data[5] = AD1.ADDRB >> 6; 	// AN1 10bitで取得
	ad_data[6] = AD1.ADDRC >> 6; 	// AN2 10bitで取得
	ad_data[7] = AD1.ADDRD >> 6;	// AN3 10bitで取得
	
}
/******AD変換連続スキャンモードのプログラムここまで*****/

/////////////////////////////////////////////////////////

/********************************************************/
//  名前      
//		PID_control
//  概要
// 		PID制御
//  機能説明
//		目標座標と現在位置およびゲイン設定を受け取り、dutyを返す
//  パラメタ説明
//		mokuhyou:目標座標
//		position:現在座標
//		max_duty:かけていい最大のduty(0~100で受け取る)
//		Kp,Ki,Kd:比例ゲイン、微分ゲイン、積分ゲイン
//		num		:0~3までの番号(char型)。プログラム内で同時にこの関数を呼び出すときはnumを分ける
//  戻り値
//		-100~100のduty(int型)
//  作成者
//		山室
//
/********************************************************/
int PID_control(double mokuhyou,double position,int max_duty,double Kp,double Ki,double Kd,char num)
{
	int duty[4];
	static double comp_P[4],comp_I[4],comp_D[4];//P,I,D成分
	static double old_position[4],old_mokuhyou[4];//過去の座標、目標座標
	
	if(old_mokuhyou[num] != mokuhyou)//目標座標が変わったらP,I,D成分を初期化
	{
		comp_P[num]=0.0;
		comp_I[num]=0.0;
		comp_D[num]=0.0;
		old_position[num]=0.0;
		old_mokuhyou[num]=0.0;
	}
	
	comp_P[num] = Kp*(mokuhyou - position);
	comp_I[num] +=Ki*comp_P[num];
	comp_D[num] = Kd*(position-old_position[num]);
	
	duty[num] = (int)(comp_P[num] + comp_I[num] + comp_D[num]+0.5);//int型に治すときに四捨五入したいので0.5を足している
	
	if(duty[num]>max_duty)duty[num]=max_duty;//頭打ち
	if(duty[num]<-max_duty)duty[num]=-max_duty;//底打ち
	
	old_position[num] = position;
	old_mokuhyou[num] = mokuhyou;
	
//	printf("%.1f\t%.1f\t%.1f\n",mokuhyou,position,comp_P[num]);
	
	return duty[num];
	
}
double PID_control_d(double mokuhyou,double position,double max_duty,double Kp,double Ki,double Kd,double I_reset_range,char num)
{
	double duty[10];
	static double comp_P[10],comp_I[10],comp_D[10];//P,I,D成分
	static double old_position[10],old_mokuhyou[10];//過去の座標、目標座標
	
	if(old_mokuhyou[num] != mokuhyou)//目標座標が変わったらP,I,D成分を初期化
	{
		comp_P[num]=0.0;
		comp_I[num]=0.0;
		comp_D[num]=0.0;
		old_position[num]=0.0;
		old_mokuhyou[num]=0.0;
	}
	
	comp_P[num] = Kp*(mokuhyou - position);
	comp_I[num] +=Ki*comp_P[num];
	comp_D[num] = Kd*(position-old_position[num]);
	
	if(ABS(mokuhyou-position)<=I_reset_range)comp_I[num]=0.0;//ある程度近づいたらI成分を初期化する（ほとんどの操作はこれをするべき？）
		
	duty[num] = comp_P[num] + comp_I[num] + comp_D[num];
	
	if(duty[num]>max_duty)duty[num]=max_duty;//頭打ち
	if(duty[num]<-max_duty)duty[num]=-max_duty;//底打ち
	
	old_position[num] = position;
	old_mokuhyou[num] = mokuhyou;
	
//	printf("%.1f\t%.1f\t%.1f\n",mokuhyou,position,comp_P[num]);
	
	return duty[num];
	
}