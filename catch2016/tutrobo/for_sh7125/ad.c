/********************************************************/
//
//  概要
//      A/D変換関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_init()							//AD変換の初期設定
{

	STB.CR4.BIT._AD0   = 0;				//スタンバイ解除
	AD0.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD0.ADCSR.BIT.STC  = 0;				//AD変換の時間設定(50ステート)
	AD0.ADCSR.BIT.CKSL = 3;				//AD変換の時間設定(Pφ/2)
	AD0.ADCSR.BIT.ADM  = 0;				//AD変換のモード設定(シングルモード)
	AD0.ADCSR.BIT.CH   = 0;				//チャンネルセレクト(シングルモード AN0) 使うのはAN0～3
	
	//※チャンネルセレクトは、int ad_load(int i)で行う。	
}

/********************************************************/
//  名前      
//		ad_load
//  概要
// 		A/D変換関数
//  機能説明
//		A/D変換のチャンネル設定・A/D変換の値の読み取り
//  パラメタ説明
//		ch			チャンネルの値
//		ad_result	A/D変換の値を入れる
//		ad[4]		それぞれに0～3のA/D変換の値を入れる
//  戻り値
//		A/D変換の値
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int ad_load(int ch) 				//AD変換チャンネル設定
{
	int ad_result;
	int ad[4];
	
	AD0.ADCSR.BIT.CH = ch;			//AD変換するチャンネルを設定(ADST=0の時)
	AD0.ADCR.BIT.ADST = 1; 			// AD変換開始
	while(AD0.ADCSR.BIT.ADF == 0);  // AD変換終了待ち
	ad[0] = AD0.ADDR0 >> 6; 		// AN0 10bitで取得
	ad[1] = AD0.ADDR1 >> 6; 		// AN1 10bitで取得
	ad[2] = AD0.ADDR2 >> 6; 		// AN2 10bitで取得
	ad[3] = AD0.ADDR3 >> 6;			// AN3 10bitで取得
	
	ad_result = ad[ch];
	
	AD0.ADCSR.BIT.ADF = 0; 			// AD完了フラグクリア
	
	return ad_result;
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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_init()							
{
/*今は押しボタンになってる
	STB.CR4.BIT._AD0   = 0;				//スタンバイ解除
	AD0.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD0.ADCSR.BIT.TRGE = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD0.ADCSR.BIT.STC  = 0;				//AD変換の時間設定(50ステート)
	AD0.ADCSR.BIT.CKSL = 3;				//AD変換の時間設定(Pφ)
	AD0.ADCSR.BIT.ADM  = 1;				//AD変換のモード設定(4 チャネルスキャンモード)
	AD0.ADCSR.BIT.ADCS = 0;				//AD変換連続スキャン
	AD0.ADCSR.BIT.CH   = 3;				//連続スキャンモード	
*/	
	STB.CR4.BIT._AD1   = 0;				//スタンバイ解除
	AD1.ADCSR.BIT.ADIE = 0;				//ADFのよる割り込みをイネーブルにしない
	AD1.ADCSR.BIT.TRGE = 0;				//MTU,ADTRGトリガよる変換開始を無効
	AD1.ADCSR.BIT.STC  = 0;				//AD変換の時間設定(50ステート)
	AD1.ADCSR.BIT.CKSL = 3;				//AD変換の時間設定(Pφ)
	AD1.ADCSR.BIT.ADM  = 1;				//AD変換のモード設定(4 チャネルスキャンモード)
	AD1.ADCSR.BIT.ADCS = 0;				//AD変換連続スキャン
	AD1.ADCSR.BIT.CH   = 3;				//連続スキャンモード
	
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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_load_0_3(int *ad_data) 				
{
	
	AD0.ADCR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD0.ADCSR.BIT.ADF == 0);  // AD変換終了待ち
	
	ad_data[0] = AD0.ADDR0 >> 6; 	// AN0 10bitで取得
	ad_data[1] = AD0.ADDR1 >> 6; 	// AN1 10bitで取得
	ad_data[2] = AD0.ADDR2 >> 6; 	// AN2 10bitで取得
	ad_data[3] = AD0.ADDR3 >> 6;	// AN3 10bitで取得
	
	AD0.ADCSR.BIT.ADF = 0; 			// AD完了フラグクリア

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
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void ad_load_4_7(int *ad_data) 				
{
	
	AD1.ADCR.BIT.ADST = 1; 			// AD変換開始
	
	while(AD1.ADCSR.BIT.ADF == 0);  // AD変換終了待ち
	
	ad_data[0] = AD1.ADDR4 >> 6; 	// AN0 10bitで取得
	ad_data[1] = AD1.ADDR5 >> 6; 	// AN1 10bitで取得
	ad_data[2] = AD1.ADDR6 >> 6; 	// AN2 10bitで取得
	ad_data[3] = AD1.ADDR7 >> 6;	// AN3 10bitで取得
	
	AD1.ADCSR.BIT.ADF = 0; 			// AD完了フラグクリア

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