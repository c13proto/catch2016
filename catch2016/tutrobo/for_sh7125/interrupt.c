/********************************************************/
//
//  概要
//      割り込み関連
//	更新日時
//		2013/02/02
//  作成者
//		K.ishimori @ TUTrobo
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
	
	SCI0.SCSCR.BIT.TIE = 1; 	// 送信割り込み要求を許可
	SCI0.SCSCR.BIT.TEIE = 1;	// 送信完了割り込み要求を許可

	CMT0.CMCSR.BIT.CMF = 0;		// フラグクリア	
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
int cmt1_counter;
void int_cmt_cmt1(void)
{

	
//	map_update();						//ジャイロと2つのエンコーダを用いてマップの更新(coordinate_omni)

	//プレステコンからの受信/////////////////////////////////////////////////////
	
	recieve_data_input();				//受信割り込みから受け取った値を格納（中でdutyも計算している）
	
	/////////////////////////////////////////////////////////////////////////////
	
	
	//各処理系///////////////////////////////////////////////////////////////////
	
	
//	gyro_map();							//ジャイロMAP状態の更新
	
	////////////////////////////////////////////////////////////////////////////
	
	//手動制御//////////////////////////////////////////////////////////////////
	input_register_ctrl();						//手動制御(dutyをレジスタに格納)

	
	CMT1.CMCSR.BIT.CMF = 0;		// フラグクリア
	
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
	rx_storage_processing(COM1);
//	com1_rx[0][0] = rx_1();		// データ受信
//	SCI1.SCSSR.BIT.RDRF = 0;	// SCSSRのRDRFフラグを0にクリア
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
#ifdef	sci1_synchronous	
		sci1_synchronous_init();
		SCI1.SCSSR.BIT.ORER = 0;
#endif//sci1_synchronous

#ifdef	sci1_asynchronous	
		sci1_asynchronous_init();
		//SCI1.SCSSR.BIT.ORER = 0;

		if(SCI1.SCSSR.BIT.ORER==1){
			printf("\nCOM1_o\n");
			SCI1.SCSSR.BIT.ORER=0;
		}
		if(SCI1.SCSSR.BIT.FER==1){
			printf("\nCOM1_f\n");
			SCI1.SCSSR.BIT.FER=0;
		}
		if(SCI1.SCSSR.BIT.PER==1){
			printf("\nCOM1_p\n");
			SCI1.SCSSR.BIT.PER=0;
		}
	
		SCI1.SCSSR.BIT.ORER = 0;
		SCI1.SCSSR.BIT.PER = 0;
		SCI1.SCSSR.BIT.FER = 0;
#endif//sci1_asynchronous

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
	tx_0(tx_storage_processing(0,LOAD));// データ送信
	SCI0.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
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
	SCI0.SCSSR.BIT.TEND = 0;	// SCSSRのTDREフラグを0にクリア
	SCI0.SCSCR.BIT.TEIE = 0;	// 送信完了割り込み要求を禁止	
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
//	rx_storage_processing(0);
	R1350N(rec_c());
//	put_c('R');
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
void int_sci0_eri0(void)
{
#ifdef	sci0_synchronous	
		sci0_synchronous_init();
		SCI0.SCSSR.BIT.ORER = 0;
#endif//sci0_synchronous

#ifdef	sci0_asynchronous	
		sci0_asynchronous_init();
		//SCI0.SCSSR.BIT.ORER = 0;

		if(SCI0.SCSSR.BIT.ORER==1){
//			put_c('o');
			printf("\no\n");
			SCI0.SCSSR.BIT.ORER=0;
		}
		if(SCI0.SCSSR.BIT.FER==1){
//			put_c('f');
			printf("\nf\n");
			SCI0.SCSSR.BIT.FER=0;
		}
		if(SCI0.SCSSR.BIT.PER==1){
//			put_c('p');
			printf("\np\n");
			SCI0.SCSSR.BIT.PER=0;
		}
	
		SCI0.SCSSR.BIT.ORER = 0;
		SCI0.SCSSR.BIT.PER = 0;
		SCI0.SCSSR.BIT.FER = 0;
#endif//sci0_asynchronous

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
	
//	put_c('R');
	
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
				int i,j;
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
//	receipt(&com0);
	
	if(angle-old_angle > 18000)angle_counter--;
	else if(angle-old_angle < -18000)angle_counter++;
	else angle_counter+=0;
	
	
	m_angle=-(angle_counter*36000+angle);


	old_angle=angle;


}

/********************************************************/
//  名前      
//		after_recieve
//  概要
// 		割り込み関連
//  機能説明
//		受信したデータから各種プログラムを実行する　
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void after_recieve(void)
{
	
}