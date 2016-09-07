/********************************************************/
//
//  概要
//      計算関連
//  作成者
//		TUTrobo
//
/********************************************************/

#ifndef __CALC_H__
#define __CALC_H__

#include "type.h"		//プログラムの型名宣言

/********************************************************/
//  TUTrobo
//
//  概要
//      A/D変換設定 プロトタイプ宣言
/********************************************************/
DOUBLE_XY get_ctrl_point(DOUBLE_XY,double,double);				// 制御点計算
DOUBLE_XY get_intersection(DOUBLE_XY,double,DOUBLE_XY,double);	// 2直線の交点を算出(制御点計算用)
void get_bisector(DOUBLE_XY, DOUBLE_XY, double*, double*);		// 垂直2等分線の算出
DOUBLE_XY get_center(double, double, double, double);			// 直線の交点を算出
double get_direction(DOUBLE_XY, DOUBLE_XY, DOUBLE_XY);			// 回転の中心の左右を判定

/********************************************************/
//  TUTrobo
//
//  概要
//      ベジェ曲線ポイント計算(3次)
/********************************************************/
#define get_bezier3_point(p0,p1,p2,p3,t) (POW3(1-(t))*p0 + 3*POW2(1-(t))*(t)*(p1) + 3*(1-(t))*POW2(t)*(p2) + POW3(t)*(p3))


#endif // __CALC_H__