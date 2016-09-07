/********************************************************/
//
//  概要
//      計算関連
//  作成者
//		TUTrobo
//
/********************************************************/

#include "setup.h"		//マイコンの設定

/********************************************************/
//  名前      
//		get_ctrl_point
//  概要
// 		計算関数
//  機能説明
//		制御点計算　
//  パラメタ説明
//		pos		基準位置		
//		theta	基準角度
//		dist	制御点までの距離
//  戻り値
//		pe		制御点
//  作成者
//		TUTrobo
//
/********************************************************/
DOUBLE_XY get_ctrl_point(DOUBLE_XY pos,double theta,double dist)
{
	DOUBLE_XY pe;

	//進行方向にdist進んだ点を制御点にする
	//座標変換
	//回転(y成分はゼロ)
	pe.x = dist * cos(theta);					
	pe.y = dist * sin(theta);
	// 平行移動
	pe.x += pos.x;
	pe.y += pos.y;

	return pe;
}

/********************************************************/
//  名前      
//		get_intersection
//  概要
// 		計算関数
//  機能説明
//		2直線の交点を算出(制御点計算用)　
//  パラメタ説明
//		p0,p1			直線が通る点
//		theta0,theta1	直線の傾き角度[rad]
//  戻り値
//		pt				交点の座標
//  作成者
//		TUTrobo
//
/********************************************************/
DOUBLE_XY get_intersection(DOUBLE_XY p0,double theta0,DOUBLE_XY p1,double theta1)
{
	DOUBLE_XY pt;
	double a0,a1,b0,b1;

	//y = ax + b
	//傾き
	a0 = tan(theta0);
	a1 = tan(theta1);
	//切片
	b0 = p0.y - a0 * p0.x;
	b1 = p1.y - a1 * p1.x;
	//交点
	pt.x = (b1 - b0)/(a0 - a1);
	pt.y = a0 * pt.x + b0;

	return pt;
}

/********************************************************/
//  名前      
//		get_bisector
//  概要
// 		計算関数
//  機能説明
//		垂直2等分線の算出　
//  パラメタ説明
//		x軸と平行なとき、m = LIMIT_INF
//		fabs 関数は引数 x の絶対値を計算し，結果を double 型で返す
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void get_bisector(DOUBLE_XY p0,DOUBLE_XY p1,double* m,double* b)
{
	double dx, dy;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	
	if(fabs(dy) < LIMIT_ZERO)						//x軸に平行
	{
		*m = LIMIT_INF_OVER;						//垂直二等分線の傾き　無限大
		*b = p0.x + dx*0.5;							//x座標の中点
	}
	else
	{
		if(fabs(dx) < LIMIT_ZERO) *m = 0;			//y軸に平行　傾き　0
		else                      *m = -dx/dy;		//垂直二等分線の傾き	
		*b = ((p1.y+p0.y)-(*m)*(p1.x+p0.x))*0.5;	//y軸との交点	切片を求めている	
	}

	return;
}

/********************************************************/
//  名前      
//		get_center
//  概要
// 		計算関数
//  機能説明
//		直線の交点を算出　
//  パラメタ説明
//		なし
//  戻り値
//		center				直線の交点
//  作成者
//		TUTrobo
//
/********************************************************/
DOUBLE_XY get_center(double m0, double b0, double m1, double b1)
{
	DOUBLE_XY center;

	if( ABS(m0) >= LIMIT_INF )				//傾きが無限大
	{
		center.x = b0;						
		center.y = m1*center.x + b1;		//連立方程式から求める
	}
	else if( ABS(m1) >= LIMIT_INF )
	{
		center.x = b1;			
		center.y = m0*center.x + b0;		//連立方程式から求める
	}
	else
	{
		center.x = (b0 - b1)/(m1 - m0);		//連立方程式から求める
		center.y = m0*center.x + b0;		//連立方程式から求める
	}


	return center;
}

/********************************************************/
//  名前      
//		get_direction
//  概要
// 		計算関数
//  機能説明
//		回転の中心の左右を判定
//  パラメタ説明
//		なし
//  戻り値
//		x1*y2 - x2*y1				円の中心の判定
//  作成者
//		TUTrobo
//
/********************************************************/
double get_direction(DOUBLE_XY p0, DOUBLE_XY p1, DOUBLE_XY p2)
{
	double x1, y1, x2, y2;

	x1 = p1.x - p0.x;			/* P0 -> P1 */
	y1 = p1.y - p0.y;
	x2 = p2.x - p0.x;			/* P0 -> P2 */
	y2 = p2.y - p0.y;

	return(x1*y2 - x2*y1);		/* 行列式 (P0->P1) (P0->P2) */	//外績
}
