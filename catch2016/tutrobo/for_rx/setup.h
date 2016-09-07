/********************************************************/
//
//  概要
//      マイコンの設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __SETUP_H__
#define __SETUP_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      マイコンの設定 読み込みヘッダファイル宣言
/********************************************************/

#include <stdio.h>
#include <stdarg.h> 	//printf 関数のような可変個の実引数の操作に関する型とマクロの定義
#include <math.h>		//一般的な数値演算および変換を計算する関数のセットを宣言

#include "ad.h"			//A/D変換設定
//#include "../individual/yamamuro.h"  //山室個人関数
#include "../calc.h"		//計算関連定義
#include "clock.h"		//CLOCK設定
#include "cmt.h"		//CMT関連
#include "../type.h"		//プログラムの型名宣言
#include "../common.h"		//共通の設定事項
//#include "../comu.h"		//通信関連定義
#include "../control.h"	//マシン移動制御関連
//#include "../controller.h"	//コントローラー関連
#include "enc.h"		//エンコーダ関連
#include "../feedback.h"	//フィードバック関連定義
#include "../interrupt.h"	//割り込み関連定義
#include "io.h"			//ピン設定
#include "../../iodefine.h"	//PINdefine
#include "../omuni.h"		//オムニ関連
#include "../macro.h"		//計算用マクロ定義
#include "../path.h"		// パス（コマンド）設定
#include "pwm.h"		//PWM設定
#include "sci.h"		//SCI関連設定
//#include "sence.h"		//計測関連定義
#include "../../typedefine.h"	//型の別名宣言 
//#include "wdt.h"		//WDT関連定義
//#include "table.h"

extern volatile char *send_data;	// 出力関数のため(データ本体)
extern volatile char send_data_cnt;	// 出力関数のため(データ数)

/********************************************************/
//  TUTrobo
//
//  概要
//      マイコンの設定 プロトタイプ宣言
/********************************************************/
void MTU2_init(void);	//MTU2のスタンバイ解除
void setup(void); 		//初期設定
void debug(void);
#endif // __SETUP_H__