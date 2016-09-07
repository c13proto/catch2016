/********************************************************/
//
//  概要
//      SCI関連
//	更新日時
//		2013/02/02
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

/********************************************************/
//  名前      
//		sci_init	
//  概要
//      SCI関連
//  機能説明
//		SCIの初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void sci_init() 
{
	/********************* SCI0の初期化 (SH/AVRと通信用) *********************/
#ifdef	sci0_synchronous
	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
	sci0_synchronous_init();
	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
#endif//sci0_synchronous

#ifdef	sci0_asynchronous
	/*************** SCI0 歩調同期モード設定 (SH/AVRと通信用) ****************/
	sci0_asynchronous_init();
	/*************** SCI0 歩調同期モード設定 (SH/AVRと通信用) ****************/
#endif//sci0_asynchronous	
	/********************* SCI0の初期化 (SH/AVRと通信用) *********************/	

	//-----------------------------------------------------------------------//	
	
	/*********************** SCI1の初期化 (PCと通信用) ***********************/
#ifdef	sci1_asynchronous
	/***************** SCI1 歩調同期モード設定 (PCと通信用) ******************/
	sci1_asynchronous_init();
	/***************** SCI1 歩調同期モード設定 (PCと通信用) ******************/
#endif//sci1_asynchronous	
	/*********************** SCI1の初期化 (PCと通信用) ***********************/	

	//-----------------------------------------------------------------------//

	/********************* SCI2の初期化 (SH/AVRと通信用) *********************/
#ifdef	sci2_asynchronous
	/*************** SCI2 歩調同期モード設定 (SH/AVRと通信用) ****************/
	sci2_asynchronous_init();
	/*************** SCI2 歩調同期モード設定 (SH/AVRと通信用) ****************/
#endif//sci2_asynchronous	
	/********************* SCI2の初期化 (SH/AVRと通信用) *********************/	
	
}

/********************************************************/
//  名前      
//		sci0_asynchronous_init	
//  概要
//      SCI関連
//  機能説明
//		SCI0調歩同期式の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void sci0_asynchronous_init() 
{	
	////////////////////////// モードを選択 ここから //////////////////////////
	#define asynchro_115200						// ボーレート   115,200 歩調同期モード	
//	#define asynchro_38400						// ボーレート    38,400 歩調同期モード
//	#define asynchro_19200						// ボーレート    19,200 歩調同期モード
//	#define asynchro_9600						// ボーレート    9,600  歩調同期モード

//	#define sci0_asynchro_tx					// 送信に設定
	#define sci0_asynchro_rx					// 受信に設定
//	#define sci0_asynchro_txrx					// 送受信に設定
	////////////////////////// モードを選択 ここまで //////////////////////////
	
	int cnt1,cnt2;		// delay_time用

	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
	STB.CR3.BIT._SCI0=0;				// SCIスタンバイ解除
	
    SCI0.SCSCR.BYTE = 0x00;				// SCSCRレジスタクリア
	
	///////////////////// クロックソースを選択 ここから //////////////////////			
	SCI0.SCSCR.BIT.CKE = 0;				/*	調歩同期式モード */
										//	00：内部クロック／SCK 端子は入力端子（入力信号は無視）
										//	01：内部クロック／SCK 端子はクロック出力
										//	10：外部クロック／SCK 端子はクロック入力
										//	11：外部クロック／SCK 端子はクロック入力										
	///////////////////// クロックソースを選択 ここまで //////////////////////
	
	///////////////////// 通信フォーマット設定 ここから //////////////////////									
	/* コミュニケーションモード */								
    SCI0.SCSMR.BIT.CA = 0;				//	0：調歩同期式モード
										//	1：クロック同期式モード
	/* キャラクタレングス */									
	SCI0.SCSMR.BIT.CHR = 0;				//	0：8 ビットデータ
										//	1：7 ビットデータ
	/* パリティイネーブル */									
	SCI0.SCSMR.BIT._PE = 0;				//	0：パリティビットの付加、およびチェックを禁止
										//	1：パリティビットの付加、およびチェックを許可*
	/* パリティモード */									
	SCI0.SCSMR.BIT.OE = 0;				//	0：偶数パリティ
										//	1：奇数パリティ
	/* ストップビットレングス */									
	SCI0.SCSMR.BIT.STOP = 0;			//	0：1 ストップビット*1
										//	1：2 ストップビット*2
	/* マルチプロセッサモード */									
	SCI0.SCSMR.BIT.MP = 0;				//	0：マルチプロセッサモードを禁止
										//	1：マルチプロセッサモードを許可（調歩同期式モードのみ有効）
	/* クロックセレクト1、0 */									
	SCI0.SCSMR.BIT.CKS = 0;				//	00：Pφクロック
										//	01：Pφ/4 クロック
										//	10：Pφ/16 クロック
										//	11：Pφ/64 クロック

	///////////////////// 通信フォーマット設定 ここまで //////////////////////
	
	////////////////////// ビットレート設定	ここから /////////////////////////
#ifdef	asynchro_115200		
		SCI0.SCBRR = 6;				// ビットレート BRR = (25,000,000[Hz]/(32*115,200[bps]))-1 => 6	
#endif
#ifdef	asynchro_19200		
		SCI0.SCBRR = 40;				// ビットレート BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI0.SCBRR = 80;				// ビットレート BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// ビットレート設定	ここまで /////////////////////////						

	///////////////// 使用する外部端子のPFCの設定 ここから ///////////////////	
	PFC.PACRL1.BIT.PA0MD = 1;			// PA0の入出力設定(入力)	***RXD0_SCI_0***
	PFC.PACRL1.BIT.PA1MD = 1;			// PA1の入出力設定(出力)	***TXD0_SCI_0***
//	PFC.PACRL1.BIT.PA2MD = 1;			// SCK0 入出力設定(入出力）	***SCK0_SCI_0***
	///////////////// 使用する外部端子のPFCの設定 ここまで ///////////////////
	
	////////////////////// SCSCRレジスタ設定 ここから ////////////////////////
#ifdef	sci0_asynchro_tx			
	SCI0.SCSCR.BIT.TE=1;  				// トランスミットイネーブル:送信動作を許可
	SCI0.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
	SCI0.SCSCR.BIT.TEIE = 0;			// 送信完了割り込み要求を禁止
#endif//sci0_asynchro_tx	

#ifdef	sci0_asynchro_rx	
    SCI0.SCSCR.BIT.RE=1;  				// レシーブイネーブル:受信動作を許可	
    SCI0.SCSCR.BIT.RIE=1; 				// 受信割り込み要求を許可
    SCI0.SCSCR.BIT.TIE=0; 				// 送信割り込み要求を禁止
#endif//sci0_asynchro_rx

#ifdef	sci0_asynchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* 周辺クロック４クロック以上待機 */	
	SCI0.SCSCR.BYTE |= 0x30;			// 送受信動作を許可	
	SCI0.SCSCR.BIT.RIE = 1; 			// 受信割り込み要求を許可
	SCI0.SCSCR.BIT.TIE = 1; 			// 送信割り込み要求を許可
#endif//sci0_asynchro_txrx
	////////////////////// SCSCRレジスタ設定 ここまで ////////////////////////

	///////////////// SCI0の割り込みレベルを設定 ここから ////////////////////
#ifdef	sci0_asynchro_tx
	INTC.IPRL.BIT._SCI0 = 15;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_asynchro_tx
#ifdef	sci0_asynchro_rx
	INTC.IPRL.BIT._SCI0 = 15;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_asynchro_rx
#ifdef	sci0_asynchro_txrx
	INTC.IPRL.BIT._SCI0 = 15;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_asynchro_txrx
	///////////////// SCI0の割り込みレベルを設定 ここまで ////////////////////
	
	//////////////////////// #define 無効化 ここから /////////////////////////
	#undef asynchro_38400						// ボーレート    38,400 歩調同期モード
	#undef asynchro_19200						// ボーレート    19,200 歩調同期モード
	#undef asynchro_9600						// ボーレート    9,600  歩調同期モード
	#undef sci0_asynchro_tx						// 送信に設定
	#undef sci0_asynchro_rx						// 受信に設定
	#undef sci0_asynchro_txrx					// 送受信に設定
	//////////////////////// #define 無効化 ここまで /////////////////////////
}

/********************************************************/
//  名前      
//		sci0_synchronous_init	
//  概要
//      SCI関連
//  機能説明
//		SCI0クロック同期式の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void sci0_synchronous_init() 
{
	////////////////////////// モードを選択 ここから //////////////////////////
//	#define sci0_synchro_master					// マスターに設定
//	#define synchro_3125000						// ボーレート 3,125,000 クロック同期式モード
//	#define synchro_1000000						// ボーレート 1,000,000 クロック同期式モード
//	#define synchro_500000						// ボーレート   500,000 クロック同期式モード
//	#define synchro_38400						// ボーレート    38,400 クロック同期式モード
	
	#define sci0_synchro_slave					// スレーブに設定

//	#define sci0_synchro_tx						// 送信に設定
	#define sci0_synchro_rx						// 受信に設定
//	#define sci0_synchro_txrx					// 送受信に設定
	////////////////////////// モードを選択 ここまで //////////////////////////
	
	int cnt1,cnt2;		// delay_time用

	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
	STB.CR3.BIT._SCI0=0;				// SCIスタンバイ解除
	
    SCI0.SCSCR.BYTE = 0x00;				// SCSCRレジスタクリア
	
	///////////////////// クロックソースを選択 ここから //////////////////////
#ifdef	sci0_synchro_master				/* マスターに設定 */				
	SCI0.SCSCR.BIT.CKE = 0;				/*	クロック同期式モード */
										//	00：内部クロック／SCK 端子は同期クロック出力
										//	01：内部クロック／SCK 端子は同期クロック出力
										//	10：外部クロック／SCK 端子は同期クロック入力
										//	11：外部クロック／SCK 端子は同期クロック入力
#endif	// sci0_synchro_master

#ifdef	sci0_synchro_slave				/* スレーブに設定 */									
	SCI0.SCSCR.BIT.CKE = 3;				/*	クロック同期式モード */
										//	00：内部クロック／SCK 端子は同期クロック出力
										//	01：内部クロック／SCK 端子は同期クロック出力
										//	10：外部クロック／SCK 端子は同期クロック入力
										//	11：外部クロック／SCK 端子は同期クロック入力
#endif	// sci0_synchro_slave										
	///////////////////// クロックソースを選択 ここまで //////////////////////
	
	///////////////////// 通信フォーマット設定 ここから //////////////////////									
	/* コミュニケーションモード */								
    SCI0.SCSMR.BIT.CA = 1;				//	0：調歩同期式モード
										//	1：クロック同期式モード
	/* キャラクタレングス */									
	SCI0.SCSMR.BIT.CHR = 0;				//	0：8 ビットデータ
										//	1：7 ビットデータ
	/* パリティイネーブル */									
	SCI0.SCSMR.BIT._PE = 1;				//	0：パリティビットの付加、およびチェックを禁止
										//	1：パリティビットの付加、およびチェックを許可*
	/* パリティモード */									
	SCI0.SCSMR.BIT.OE = 1;				//	0：偶数パリティ
										//	1：奇数パリティ
	/* ストップビットレングス */									
	SCI0.SCSMR.BIT.STOP = 1;			//	0：1 ストップビット*1
										//	1：2 ストップビット*2
	/* マルチプロセッサモード */									
	SCI0.SCSMR.BIT.MP = 0;				//	0：マルチプロセッサモードを禁止
										//	1：マルチプロセッサモードを許可（調歩同期式モードのみ有効）
	/* クロックセレクト1、0 */									
	SCI0.SCSMR.BIT.CKS = 0;				//	00：Pφクロック
										//	01：Pφ/4 クロック
										//	10：Pφ/16 クロック
										//	11：Pφ/64 クロック
	///////////////////// 通信フォーマット設定 ここまで //////////////////////
	
	////////////////////// ビットレート設定	ここから /////////////////////////
#ifdef	synchro_3125000		
		SCI0.SCBRR = 1;					// ビットレート BRR = (25,000,000/(8*(1/2)*3,125,000))-1 => 1	
#endif		
#ifdef	synchro_1000000		
		SCI0.SCBRR = 5;					// ビットレート BRR = (25,000,000/(8*(1/2)*1,000,000))-1 => 5
#endif	
#ifdef	synchro_500000					
		SCI0.SCBRR = 12;				// ビットレート BRR = (25,000,000/(8*(1/2)*500,000))-1 => 12	
#endif	
#ifdef	synchro_38400		
		SCI0.SCBRR = 162;				// ビットレート BRR = (25,000,000[Hz]/(8*(1/2)*38,400[bps]))-1 => 162	
#endif	
	////////////////////// ビットレート設定	ここまで /////////////////////////						

	///////////////// 使用する外部端子のPFCの設定 ここから ///////////////////	
	PFC.PACRL1.BIT.PA0MD = 1;			// PA0の入出力設定(入力)	***RXD0_SCI_0***
	PFC.PACRL1.BIT.PA1MD = 1;			// PA1の入出力設定(出力)	***TXD0_SCI_0***
	PFC.PACRL1.BIT.PA2MD = 1;			// SCK0 入出力設定(入出力）	***SCK0_SCI_0***
	///////////////// 使用する外部端子のPFCの設定 ここまで ///////////////////
	
	////////////////////// SCSCRレジスタ設定 ここから ////////////////////////
#ifdef	sci0_synchro_tx			
	SCI0.SCSCR.BIT.TE=1;  				// トランスミットイネーブル:送信動作を許可
	SCI0.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
	SCI0.SCSCR.BIT.TEIE = 1;			// 送信完了割り込み要求を禁止
#endif//sci0_synchro_tx	

#ifdef	sci0_synchro_rx	
    SCI0.SCSCR.BIT.RE=1;  				// レシーブイネーブル:受信動作を許可	
    SCI0.SCSCR.BIT.RIE=1; 				// 受信割り込み要求を許可
    SCI0.SCSCR.BIT.TIE=0; 				// 送信割り込み要求を禁止
#endif//sci0_synchro_rx

#ifdef	sci0_synchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* 周辺クロック４クロック以上待機 */	
	SCI0.SCSCR.BYTE |= 0x30;			// 送受信動作を許可	
	SCI0.SCSCR.BIT.RIE = 1; 			// 受信割り込み要求を許可
	SCI0.SCSCR.BIT.TIE = 1; 			// 送信割り込み要求を許可
#endif//sci0_synchro_txrx
	////////////////////// SCSCRレジスタ設定 ここまで ////////////////////////

	///////////////// SCI0の割り込みレベルを設定 ここから ////////////////////
#ifdef	sci0_synchro_tx
	INTC.IPRL.BIT._SCI0 = 13;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_synchro_tx
#ifdef	sci0_synchro_rx
	INTC.IPRL.BIT._SCI0 = 13;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_synchro_rx
#ifdef	sci0_synchro_txrx
	INTC.IPRL.BIT._SCI0 = 13;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci0_synchro_txrx
	///////////////// SCI0の割り込みレベルを設定 ここまで ////////////////////
	
	//////////////////////// #define 無効化 ここから /////////////////////////
	#undef sci0_synchro_master					// マスターに設定
	#undef synchro_3125000						// ボーレート 3,125,000 クロック同期式モード
	#undef synchro_1000000						// ボーレート 1,000,000 クロック同期式モード
	#undef synchro_500000						// ボーレート   500,000 クロック同期式モード
	#undef synchro_38400						// ボーレート    38,400 クロック同期式モード	
	#undef sci0_synchro_slave					// スレーブに設定
	#undef sci0_synchro_tx						// 送信に設定
	#undef sci0_synchro_rx						// 受信に設定
	#undef sci0_synchro_txrx					// 送受信に設定
	//////////////////////// #define 無効化 ここまで /////////////////////////
}

/********************************************************/
//  名前      
//		sci1_asynchronous_init	
//  概要
//      SCI関連
//  機能説明
//		SCI1調歩同期式の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void sci1_asynchronous_init() 
{	
	////////////////////////// モードを選択 ここから //////////////////////////
//	#define asynchro_38400						// ボーレート    38,400 歩調同期モード
	#define asynchro_19200						// ボーレート    19,200 歩調同期モード
//	#define asynchro_9600						// ボーレート    9,600  歩調同期モード

//	#define sci1_asynchro_tx					// 送信に設定
//	#define sci1_asynchro_rx					// 受信に設定
	#define sci1_asynchro_txrx					// 送受信に設定
	////////////////////////// モードを選択 ここまで //////////////////////////

	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
	STB.CR3.BIT._SCI1 = 0;				// SCIスタンバイ解除
	
    SCI1.SCSCR.BYTE = 0x00;				// SCSCRレジスタクリア
	
	///////////////////// クロックソースを選択 ここから //////////////////////			
	SCI1.SCSCR.BIT.CKE = 0;				/*	調歩同期式モード */
										//	00：内部クロック／SCK 端子は入力端子（入力信号は無視）
										//	01：内部クロック／SCK 端子はクロック出力
										//	10：外部クロック／SCK 端子はクロック入力
										//	11：外部クロック／SCK 端子はクロック入力										
	///////////////////// クロックソースを選択 ここまで //////////////////////
	
	///////////////////// 通信フォーマット設定 ここから //////////////////////									
	/* コミュニケーションモード */								
    SCI1.SCSMR.BIT.CA = 0;				//	0：調歩同期式モード
										//	1：クロック同期式モード
	/* キャラクタレングス */									
	SCI1.SCSMR.BIT.CHR = 0;				//	0：8 ビットデータ
										//	1：7 ビットデータ
	/* パリティイネーブル */									
	SCI1.SCSMR.BIT._PE = 0;				//	0：パリティビットの付加、およびチェックを禁止
										//	1：パリティビットの付加、およびチェックを許可*
	/* パリティモード */									
	SCI1.SCSMR.BIT.OE = 0;				//	0：偶数パリティ
										//	1：奇数パリティ
	/* ストップビットレングス */									
	SCI1.SCSMR.BIT.STOP = 0;			//	0：1 ストップビット*1
										//	1：2 ストップビット*2
	/* マルチプロセッサモード */									
	SCI1.SCSMR.BIT.MP = 0;				//	0：マルチプロセッサモードを禁止
										//	1：マルチプロセッサモードを許可（調歩同期式モードのみ有効）
	/* クロックセレクト1、0 */									
	SCI1.SCSMR.BIT.CKS = 0;				//	00：Pφクロック
										//	01：Pφ/4 クロック
										//	10：Pφ/16 クロック
										//	11：Pφ/64 クロック

	///////////////////// 通信フォーマット設定 ここまで //////////////////////
	
	////////////////////// ビットレート設定	ここから /////////////////////////
#ifdef	asynchro_38400		
		SCI1.SCBRR = 19;				// ビットレート BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 19	
#endif
#ifdef	asynchro_19200		
		SCI1.SCBRR = 40;				// ビットレート BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI1.SCBRR = 80;				// ビットレート BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// ビットレート設定	ここまで /////////////////////////						

	///////////////// 使用する外部端子のPFCの設定 ここから ///////////////////	
	PFC.PACRL1.BIT.PA3MD = 1;			// PA3の入出力設定(入力)	***RXD1_SCI_0***
	PFC.PACRL2.BIT.PA4MD = 1;			// PA4の入出力設定(出力)	***TXD1_SCI_0***
//	PFC.PACRL2.BIT.PA5MD = 1;			// SCK1 入出力設定(入出力）	***SCK1_SCI_0***
	///////////////// 使用する外部端子のPFCの設定 ここまで ///////////////////
	
	////////////////////// SCSCRレジスタ設定 ここから ////////////////////////
#ifdef	sci1_asynchro_tx			
	SCI1.SCSCR.BIT.TE   = 1;  			// トランスミットイネーブル:送信動作を許可
	SCI1.SCSCR.BIT.TIE  = 0; 			// 送信割り込み要求を禁止
	SCI1.SCSCR.BIT.TEIE = 0;			// 送信完了割り込み要求を禁止
#endif//sci0_asynchro_tx	

#ifdef	sci1_asynchro_rx	
    SCI1.SCSCR.BIT.RE  = 1;  			// レシーブイネーブル:受信動作を許可
//	SCI1.SCSCR.BIT.TE  = 1;  			// トランスミットイネーブル:送信動作を許可
	SCI1.SCSCR.BIT.RIE = 1; 			// 受信割り込み要求を許可
    SCI1.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
#endif//sci0_asynchro_rx

#ifdef	sci1_asynchro_txrx
	SCI1.SCSCR.BYTE |= 0x30;			// 送受信動作を許可	
	SCI1.SCSCR.BIT.RIE = 1; 			// 受信割り込み要求を許可
    SCI1.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
#endif//sci0_asynchro_txrx
	////////////////////// SCSCRレジスタ設定 ここまで ////////////////////////

	///////////////// SCI0の割り込みレベルを設定 ここから ////////////////////
#ifdef	sci1_asynchro_tx
	INTC.IPRL.BIT._SCI1 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci1_asynchro_tx
#ifdef	sci1_asynchro_rx
	INTC.IPRL.BIT._SCI1 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci1_asynchro_rx
#ifdef	sci1_asynchro_txrx
	INTC.IPRL.BIT._SCI1 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci1_asynchro_txrx
	///////////////// SCI0の割り込みレベルを設定 ここまで ////////////////////
	
	//////////////////////// #define 無効化 ここから /////////////////////////
	#undef asynchro_38400						// ボーレート    38,400 歩調同期モード
	#undef asynchro_19200						// ボーレート    19,200 歩調同期モード
	#undef asynchro_9600						// ボーレート    9,600  歩調同期モード
	#undef sci1_asynchro_tx						// 送信に設定
	#undef sci1_asynchro_rx						// 受信に設定
	#undef sci1_asynchro_txrx					// 送受信に設定
	//////////////////////// #define 無効化 ここまで /////////////////////////
}

/********************************************************/
//  名前      
//		sci2_asynchronous_init	
//  概要
//      SCI関連
//  機能説明
//		SCI2調歩同期式の初期設定
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void sci2_asynchronous_init() 
{	
	////////////////////////// モードを選択 ここから //////////////////////////
//	#define asynchro_38400						// ボーレート    38,400 歩調同期モード
//	#define asynchro_19200						// ボーレート    19,200 歩調同期モード
	#define asynchro_9600						// ボーレート    9,600  歩調同期モード

//	#define sci2_asynchro_tx					// 送信に設定
	#define sci2_asynchro_rx					// 受信に設定
//	#define sci2_asynchro_txrx					// 送受信に設定
	////////////////////////// モードを選択 ここまで //////////////////////////
	
	int cnt1,cnt2;		// delay_time用

	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/
	STB.CR3.BIT._SCI2=0;				// SCIスタンバイ解除
	
    SCI2.SCSCR.BYTE = 0x00;				// SCSCRレジスタクリア
	
	///////////////////// クロックソースを選択 ここから //////////////////////			
	SCI2.SCSCR.BIT.CKE = 0;				/*	調歩同期式モード */
										//	00：内部クロック／SCK 端子は入力端子（入力信号は無視）
										//	01：内部クロック／SCK 端子はクロック出力
										//	10：外部クロック／SCK 端子はクロック入力
										//	11：外部クロック／SCK 端子はクロック入力										
	///////////////////// クロックソースを選択 ここまで //////////////////////
	
	///////////////////// 通信フォーマット設定 ここから //////////////////////									
	/* コミュニケーションモード */								
    SCI2.SCSMR.BIT.CA = 0;				//	0：調歩同期式モード
										//	1：クロック同期式モード
	/* キャラクタレングス */									
	SCI2.SCSMR.BIT.CHR = 0;				//	0：8 ビットデータ
										//	1：7 ビットデータ
	/* パリティイネーブル */									
	SCI2.SCSMR.BIT._PE = 1;				//	0：パリティビットの付加、およびチェックを禁止
										//	1：パリティビットの付加、およびチェックを許可*
	/* パリティモード */									
	SCI2.SCSMR.BIT.OE = 0;				//	0：偶数パリティ
										//	1：奇数パリティ
	/* ストップビットレングス */									
	SCI2.SCSMR.BIT.STOP = 1;			//	0：1 ストップビット*1
										//	1：2 ストップビット*2
	/* マルチプロセッサモード */									
	SCI2.SCSMR.BIT.MP = 0;				//	0：マルチプロセッサモードを禁止
										//	1：マルチプロセッサモードを許可（調歩同期式モードのみ有効）
	/* クロックセレクト1、0 */									
	SCI2.SCSMR.BIT.CKS = 0;				//	00：Pφクロック
										//	01：Pφ/4 クロック
										//	10：Pφ/16 クロック
										//	11：Pφ/64 クロック

	///////////////////// 通信フォーマット設定 ここまで //////////////////////
	
	////////////////////// ビットレート設定	ここから /////////////////////////
#ifdef	asynchro_19200		
		SCI2.SCBRR = 40;				// ビットレート BRR = (25,000,000[Hz]/(32*19,200[bps]))-1 => 40	
#endif	
#ifdef	asynchro_9600		
		SCI2.SCBRR = 80;				// ビットレート BRR = (25,000,000[Hz]/(32*9,600[bps]))-1 => 80	
#endif	
	////////////////////// ビットレート設定	ここまで /////////////////////////						

	///////////////// 使用する外部端子のPFCの設定 ここから ///////////////////	
	PFC.PACRL3.BIT.PA8MD = 6;			// PA8の入出力設定(入力)	***RXD2_SCI_2***
	PFC.PACRL3.BIT.PA9MD = 6;			// PA9の入出力設定(出力)	***TXD2_SCI_2***	
	///////////////// 使用する外部端子のPFCの設定 ここまで ///////////////////
	
	////////////////////// SCSCRレジスタ設定 ここから ////////////////////////
#ifdef	sci2_asynchro_tx			
	SCI2.SCSCR.BIT.TE=1;  				// トランスミットイネーブル:送信動作を許可
	SCI2.SCSCR.BIT.TIE = 0; 			// 送信割り込み要求を禁止
	SCI2.SCSCR.BIT.TEIE = 0;			// 送信完了割り込み要求を禁止
#endif//sci0_asynchro_tx	

#ifdef	sci2_asynchro_rx	
    SCI2.SCSCR.BIT.RE=1;  				// レシーブイネーブル:受信動作を許可	
    SCI2.SCSCR.BIT.RIE=1; 				// 受信割り込み要求を許可
    SCI2.SCSCR.BIT.TIE=0; 				// 送信割り込み要求を禁止
#endif//sci0_asynchro_rx

#ifdef	sci2_asynchro_txrx
	for(cnt = 0; cnt < 65536; cnt ++);	/* 周辺クロック４クロック以上待機 */	
	SCI2.SCSCR.BYTE |= 0x30;			// 送受信動作を許可	
	SCI2.SCSCR.BIT.RIE = 1; 			// 受信割り込み要求を許可
	SCI2.SCSCR.BIT.TIE = 1; 			// 送信割り込み要求を許可
#endif//sci0_asynchro_txrx
	////////////////////// SCSCRレジスタ設定 ここまで ////////////////////////

	///////////////// SCI0の割り込みレベルを設定 ここから ////////////////////
#ifdef	sci2_asynchro_tx
	INTC.IPRL.BIT._SCI2 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci2_asynchro_tx
#ifdef	sci2_asynchro_rx
	INTC.IPRL.BIT._SCI2 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci2_asynchro_rx
#ifdef	sci2_asynchro_txrx
	INTC.IPRL.BIT._SCI2 = 14;       	// 割り込みレベル設定(SCI0)0～15 0:最低 15:最高
#endif//sci2_asynchro_txrx
	///////////////// SCI0の割り込みレベルを設定 ここまで ////////////////////
	
	//////////////////////// #define 無効化 ここから /////////////////////////
	#undef asynchro_38400						// ボーレート    38,400 歩調同期モード
	#undef asynchro_19200						// ボーレート    19,200 歩調同期モード
	#undef asynchro_9600						// ボーレート    9,600  歩調同期モード
	#undef sci2_asynchro_tx						// 送信に設定
	#undef sci2_asynchro_rx						// 受信に設定
	#undef sci2_asynchro_txrx					// 送受信に設定
	//////////////////////// #define 無効化 ここまで /////////////////////////
}

/********************************************************/
//  名前      
//		send_c
//  概要
//      SCI関連
//  機能説明
//		SCI0から送信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void send_c(char c)
{
	while (SCI0.SCSSR.BIT.TDRE==0);
    SCI0.SCSSR.BIT.TDRE=0;	
    SCI0.SCTDR=c;
}

/********************************************************/
//  名前      
//		rec_c	
//  概要
//      SCI関連
//  機能説明
//		SCI0から受信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char rec_c(void)
{
	char c;
	
    while ((SCI0.SCSSR.BYTE & 0x40)==0);
	
    c = SCI0.SCRDR;
	SCI0.SCSSR.BYTE = SCI0.SCSSR.BYTE & 0xBF;
	
	return c;
}

/********************************************************/
//  名前      
//		tx_0	
//  概要
//      SCI関連
//  機能説明
//		SCI0から送信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void tx_0(char send)
{
	SCI0.SCTDR = send;			// SCTDRに送信データを書き込み
	SCI0.SCSSR.BIT.TDRE = 0;	// SCSSRのTDREフラグを0にクリア
}

/********************************************************/
//  名前      
//		rx_0	
//  概要
//      SCI関連
//  機能説明
//		SCI0から受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char rx_0(void)
{
	char rec;

    rec = SCI0.SCRDR;			// SCTDRから受信データを読み込み
	SCI0.SCSSR.BIT.RDRF = 0;	// SCSSRのRDRFフラグを0にクリア
	
	return rec;
}

/********************************************************/
//  名前      
//		txrx_0	
//  概要
//      SCI関連
//  機能説明
//		SCI0から送受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char txrx_0(char send)
{
	char rec;
	
	while(SCI0.SCSSR.BIT.TDRE==0);
	
	SCI0.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI0.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア

	do
	{
		if(SCI0.SCSSR.BIT.ORER == 1)
		{
			SCI0.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI0.SCSSR.BIT.RDRF==0);
	
	SCI0.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI0.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア
	
	return rec;
}

/********************************************************/
//  名前      
//		put_c	
//  概要
//      SCI関連
//  機能説明
//		SCI1から送信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void put_c(char c)		
{											
    while (SCI1.SCSSR.BIT.TDRE==0);
    SCI1.SCSSR.BIT.TDRE=0;	
    SCI1.SCTDR=c;
}

/********************************************************/
//  名前      
//		put_s	
//  概要
//      SCI関連
//  機能説明
//		SCI1から文字列送信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void put_s(char str[])		
{									
    unsigned int lp=0;
    while(str[lp] != 0)
	{
        put_c(str[lp]);
        lp++;
	}
}

/********************************************************/
//  名前      
//		get_c	
//  概要
//      SCI関連
//  機能説明
//		SCI1から受信
//  パラメタ説明
//		なし
//  戻り値
//		受信したデータ
//  作成者
//		TUTrobo
//
/********************************************************/
char get_c(void)		
{									
    char c;
	
	while ((SCI1.SCSSR.BYTE & 0x40)==0);
    
	c = SCI1.SCRDR;
	SCI1.SCSSR.BYTE = SCI1.SCSSR.BYTE & 0xBF;
	
	return c;
}

/********************************************************/
//  名前      
//		tx_1	
//  概要
//      SCI関連
//  機能説明
//		SCI1から送信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void tx_1(char send)
{
	SCI1.SCTDR = send;			// SCTDRに送信データを書き込み
	SCI1.SCSSR.BIT.TDRE = 0;	// SCSSRのTDREフラグを0にクリア
}

/********************************************************/
//  名前      
//		rx_1	
//  概要
//      SCI関連
//  機能説明
//		SCI2から受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char rx_1(void)
{
	char rec;

    rec = SCI1.SCRDR;			// SCTDRから受信データを読み込み
	SCI1.SCSSR.BIT.RDRF = 0;	// SCSSRのRDRFフラグを0にクリア
	
	return rec;
}

/********************************************************/
//  名前      
//		txrx_1	
//  概要
//      SCI関連
//  機能説明
//		SCI1から送受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char txrx_1(char send)
{
	char rec;
	
	while(SCI1.SCSSR.BIT.TDRE==0);
	
	SCI1.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI1.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア

	do
	{
		if(SCI1.SCSSR.BIT.ORER == 1)
		{
			SCI1.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI1.SCSSR.BIT.RDRF==0);
	
	SCI1.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI1.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア
	
	return rec;
}

/********************************************************/
//  名前      
//		transmit_c	
//  概要
//      SCI関連
//  機能説明
//		SCI2から送信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void transmit_c(char c)
{
     while (SCI2.SCSSR.BIT.TDRE==0);
    SCI2.SCSSR.BIT.TDRE=0;	
    SCI2.SCTDR=c;					//シリアル送信するデータを格納
}

/********************************************************/
//  名前      
//		accept_c	
//  概要
//      SCI関連
//  機能説明
//		SCI2から受信
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char accept_c(void)
{
	char accept;
	
    while ((SCI2.SCSSR.BYTE & 0x40)==0);
	
    accept = SCI2.SCRDR;
	SCI2.SCSSR.BYTE = SCI2.SCSSR.BYTE & 0xBF;
	
	return accept;
}

/********************************************************/
//  名前      
//		tx_2	
//  概要
//      SCI関連
//  機能説明
//		SCI2から送信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void tx_2(char send)
{
	SCI2.SCTDR = send;			// SCTDRに送信データを書き込み
	SCI2.SCSSR.BIT.TDRE = 0;	// SCSSRのTDREフラグを0にクリア
}

/********************************************************/
//  名前      
//		rx_2	
//  概要
//      SCI関連
//  機能説明
//		SCI2から受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char rx_2(void)
{
	char rec;

    rec = SCI2.SCRDR;			// SCTDRから受信データを読み込み
	SCI2.SCSSR.BIT.RDRF = 0;	// SCSSRのRDRFフラグを0にクリア
	
	return rec;
}

/********************************************************/
//  名前      
//		txrx_2	
//  概要
//      SCI関連
//  機能説明
//		SCI2から送受信(割り込み使用時)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
char txrx_2(char send)
{
	char rec;
	
	while(SCI2.SCSSR.BIT.TDRE==0);
	
	SCI2.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI2.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア

	do
	{
		if(SCI2.SCSSR.BIT.ORER == 1)
		{
			SCI2.SCSSR.BIT.ORER = 0;
			break;
		}
	}while(SCI2.SCSSR.BIT.RDRF==0);
	
	SCI2.SCTDR=send;				// SCTDRに送信データを書き込み
	SCI2.SCSSR.BIT.TDRE=0;			// SCSSRのTDREフラグを0にクリア
	
	return rec;
}

/********************************************************/	
//  概要
//      SCI関連
//  機能説明
//		printfで使う型を初期化
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
p_table clear(p_table table)
{
	table.z[0] = 0;
	table.z[1] = 0;
	table.n = 0;
	table.l = 0;
	table.m = 0;
	table.var = 0;
	table.base = 0;
	
	return(table);
}

/********************************************************/
//  名前      
//		printf	
//  概要
//      SCI関連
//  機能説明
//		文字列を解析してconvertにわたす。
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
int printf(const char *str, ...)
{
	p_table table;
	va_list list;
	char c;
	int p,i;
	double v_double;

	va_start(list, str);									//可変引数にアクセスする前の初期処理
	while(1){
		while((c = *str++) != '%'){							//%が出てくるまでまでループ
			if(c == '\0')return(10);						//NULLがきたらおわり??
			if(c == '\n')put_c('\r');						//改行
			put_c(c);										//表示
		}
		table = clear(table);								//table初期化
		p = 0;												//p初期化
//      if((*str)=='%')SCI3_OUT_DATA(*str++);   			// '%'出力
		while(1){
			c = *str++;										//次の文字へGO！	
 			if(c >= '0' && c <='9'){						//0～9までのcharのとき
				table.z[p] *= 10;table.z[p] += c - '0';		//表示させる桁数を認識
			}else if((c == '.') && (p == 0))p++;			//cが'.'でpが0のとき　pは1
			else if(c == 'l')table.l = 1;					//long int など
			else{
				switch(c){								
					case 'd':								//dの場合
					case 'D':								//Dの場合
						table.base = 10L;					//convertで使う　割る定数
						table.var = va_arg(list, int);		//可変引数にアクセスしてその変数を取り出す処理
						if((long)table.var < 0){			//値が負の時
							table.m = 1;					//convertで使う桁の数を1つ足す
							table.var *= -1;				//convertでマイナスにならないようにするため
						}
						convert(table);						//表示
						break;								//break
					case 'f':								//fの場合
					case 'F':								//Fの場合
						table.base = 10L;					//convertで使う　割る定数　（ここから上のintと同じ内容）			
						v_double = va_arg(list, double);	//可変引数にアクセスしてその変数を取り出す処理
						if(v_double < 0){					//値が負の時
							table.m = 1;					//convertで使う桁の数を1つ足す
							v_double *= -1;					//convertでマイナスにならないようにするため
						}
						table.var = (long)v_double;			//整数部分だけ代入	
						table.z[0] -= table.z[1]+1;			//整数部分の桁数を代入（+１は.の部分）
						convert(table);						//表示　（ここらへんまでintと同じ内容）
						put_c('.');							//'.'を表示させる
						table.z[0] = 1;						//整数部分を一桁にする
						table.m = 0;						//table.mを初期化		
						if(table.z[1]==0)table.z[1]=6;		//table.z[1]が0のとき小数点以下6桁を表示する
						for(i=0;i<(table.z[1]-1);i++){		
							v_double *= 10;					//小数点以下の桁を整数部分にする
							table.var = (long)v_double % 10;//整数部分にした桁を代入
							convert(table);					//表示
						}
						v_double *= 10;						//?
						table.var = (long)v_double % 10;	//?
						convert(table);						//?
						break;
					case 'b':
					case 'B':
					case 'c':
					case 'C':
					case 'o':
					case 'O':
					case 'x':
					case 'X':
					case 's':
					case 'S':
						put_s(va_arg(list, char *));		//?
						break;
					default:str--;							//文字列を一つ前に戻す　％のまま表示する
				}
				break;										//whileをぬける
			}
		}
	}
	va_end(list);											//可変引数にアクセスした後の終了処理
	return(10);												//?
}

/********************************************************/
//  名前      
//		convert	
//  概要
//      SCI関連
//  機能説明
//		printfからもらった文字列を表示
//  パラメタ説明
//		なし
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void convert(p_table table)
{
 
 	char s[20];												//表示用の文字列
 	int i=19,cnt=0;											//iがどこにその文字を入れるのかを決めるカウント　cntが表示させる空間を決めるカウント

	for(i=0;i<20;i++)s[i]=' ';								//空白のを20個分作る
	i=19;													//iを初期化する
	if(table.var == 0){										//数値が0のとき
		s[i--] = '0';										//s[19]に'0'を代入する
		cnt++;												//表示空間を1つ増やす
	}
	while(table.var){										//table.varが0以外の時ループ
		s[i--] = (table.var % table.base) + '0';			//intからcharに変換
		table.var /= table.base;							//次の桁にGO!
		cnt++;												//表示空間を1つ増やす
	}
	if(table.m)s[i] = '-';									//table.mが1のときマイナスの符号をつける
	cnt += table.m;											//table.mが1のとき表示空間を1つ増やす
	if(cnt < table.z[0])cnt = table.z[0];					//table.z[0]がcntより大きい場合cntをtable.z[0]と同じにする　表示させたいの桁が読み込んだ数字よりも小さい場合空白にする。
	for(i=20-cnt;i<20;i++){									//文字列を反転させながらcnt数の空間分ループ
		put_c(s[i]);										//表示
	}
	
}

/********************************************************/
//  名前      
//		itoa
//  概要
// 		SCI関数
//  機能説明
//		int→char変換
//  パラメタ説明
//		value	int型の文字列
//		buff[]	int型の文字列がchar型の文字列になり格納される
//		radix	何進数か　例えば10進数なら10
//  戻り値
//		なし
//  作成者
//		TUTrobo
//
/********************************************************/
void itoa(int value,char buff[],int radix)
{
	static const char table[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char *head = buff;
	char *tail = buff;
	char temp;
	
	//マイナス符号を文字列に変換
	if(value<0){
		*tail++='-';
		value=-value;
	}
	//整数値を文字列に変換
	if(value==0){
 		*tail++='0';
	}
	else{
		for(head=tail;value!=0;value=value/radix){
			 *tail++ = table[value%radix];
 		}
	}
	*tail='\0';
	//文字列の左右入れ替え
	for(tail--;head<tail;head++,tail--){
		temp=*head;
		*head=*tail;
		*tail=temp;
	}
}