/********************************************************/
//
//  概要
//      割り込み関連
//	更新日時
//		
//  作成者
//		@ TUTrobo
//
/********************************************************/
//割り込みをするには                 
//resetprg.cの
//#define SR_Init    0x00000000
//にする

#include <machine.h>
#include "../../vect.h"

#include "../setup.h"		//マイコンの設定
	
/********************************************************/
//  名前      
//		int_cmt_cmt0
//  概要
// 		割り込み関連
//  機能説明
//		タイマ割り込み関数
//	注意事項
//		intprg.cで定義している
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_cmt_cmt0(void)
{

}

/********************************************************/
//  名前      
//		int_cmt_cmt1
//  概要
// 		割り込み関連
//  機能説明
//		タイマ割り込み関数
//	注意事項
//		intprg.cで定義している
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int cmt1_counter=0;
void int_cmt_cmt1(void)
{
	cmt1_counter++;//10msごとに入っている
	
	arm_condition_update();
		
	//プレステコンからの受信/////////////////////////////////////////////////////	
	recieve_data_input();				//受信割り込みから受け取った値を格納（中でdutyも計算している）

	
	input_register_ctrl();						//dutyをレジスタに格納
	

	cmt1_counter=0;
}

/********************************************************/
//  名前      
//		int_sci1_rxi1
//  概要
// 		割り込み関連
//  機能説明
//		受信割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci1_rxi1(void)	
{
	receipt(&com[1]); 
}

/********************************************************/
//  名前      
//		int_sci1_eri1
//  概要
// 		割り込み関連
//  機能説明
//		受信エラー割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci1_eri1(void)
{
		SCI_ERI(1);
}

/********************************************************/
//  名前      
//		int_sci0_txi0
//  概要
// 		割り込み関連
//  機能説明
//		送信割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_txi0(void)
{	
}

/********************************************************/
//  名前      
//		int_sci0_tei0
//  概要
// 		割り込み関連
//  機能説明
//		送信完了割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_tei0(void)
{
}

/********************************************************/
//  名前      
//		int_sci0_rxi0
//  概要
// 		割り込み関連
//  機能説明
//		受信割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_rxi0(void)
{
	receipt(&com[0]);
	
	//割り込み優先度変更
//	SCI_PRIORITY_CHANGE(0,12);
//	SCI_PRIORITY_CHANGE(2,13);
}

/********************************************************/
//  名前      
//		int_sci0_eri0
//  概要
// 		割り込み関連
//  機能説明
//		受信エラー割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci0_eri0(void){
	SCI_ERI(0);	
}

/********************************************************/
//  名前      
//		int_sci2_rxi2
//  概要
// 		割り込み関連
//  機能説明
//		受信割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void int_sci2_rxi2(void){
	receipt(&com[2]);
	//割り込み優先度変更
//	SCI_PRIORITY_CHANGE(0,13);
//	SCI_PRIORITY_CHANGE(2,12);
//	R1350N(SCI_RECV(2));
}
/********************************************************/
//  名前      
//		int_sci2_eri2
//  概要
// 		割り込み関連
//  機能説明
//		受信エラー割り込み関数
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void int_sci2_eri2(void){
	SCI_ERI(2);
}
/********************************************************/
//  名前      
//		R1350N
//  概要
// 		割り込み関連
//  機能説明
//		受信割り込み関数 master側
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		
//  作成者
//		Ido @ TUT
//
/********************************************************/
int angle,accX,accY,accZ;
int m_angle;

void R1350N(unsigned char c)	
{
	static unsigned char j_buffer[15],j_data;
	static int j_state,j_counter;
	static int angle_counter=0;
	static int old_angle;
	
	j_data=c;
		
	switch(j_state){
		case 0:
			//put_c('0');
			if(j_data==0xAA){j_state++;}break;
		
		case 1:
			//put_c('1');
			if(j_data==0x00){j_state++;}
			else{j_counter=0;j_state=0;}break;
		
		case 2:
			//put_c('2');
			j_buffer[j_counter] = j_data;
			j_counter++;
			
			if(j_counter>=13)
			{
				int sum=0;
				int i;
				for(i=0;i<11;i++)sum += j_buffer[i];
				if((sum & 0xff) == j_buffer[12])
				{
					angle	= ((j_buffer[2] << 8) | j_buffer[1]);
					if(angle&0x8000){
						angle^=0xFFFF;
						angle+=1;
						angle*=-1;
					}
					
					accX	= ((j_buffer[6] << 8) | j_buffer[5]);
					if(accX&0x8000){
						accX^=0xFFFF;
						accX+=1;
						accX*=-1;
					}					
					
					accY	= ((j_buffer[8] << 8) | j_buffer[7]);
					if(accY&0x8000){
						accY^=0xFFFF;
						accY+=1;
						accY*=-1;
					}
										
					accZ	= ((j_buffer[10] << 8) | j_buffer[9]);
					if(accZ&0x8000){
						accZ^=0xFFFF;
						accZ+=1;
						accZ*=-1;
					}
				//	put_c('3');
				//	for(j=0;j<100;j++);//delay
					
				}
				j_state=0;
				j_counter=0;
			}break;
	}
	
	if(angle-old_angle > 18000)angle_counter--;
	else if(angle-old_angle < -18000)angle_counter++;
	else angle_counter+=0;
	
	
	m_angle=-(angle_counter*36000+angle);
	old_angle=angle;
}

