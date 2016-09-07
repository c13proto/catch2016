/********************************************************/
//
//  概要
//  	SCI関連設定
//	更新日時
//		2013/04/26
//  作成者
//		TUTrobo
//
/********************************************************/

#ifndef __SCI_H__
#define __SCI_H__

#define B_115200 25//12
#define B_76800	38//19	
// ボーレート    38,400 歩調同期モード			
#define B_38400	77//38					
// ビットレート BRR = (48,000,000[Hz]/(32*38,400[bps]))-1 => 19	ボーレート    19,200 歩調同期モード
#define B_19200 155//77                 
// ボーレート    9,600  歩調同期モード
#define B_9600	311//155					

#define EVEN  0x10
#define ODD   0x11
#define NONE  0x00
#define ONE_STOPBIT  0x01
#define TWO_STOPBITS 0x10
#define SCI_ASYNC_INIT(ch,baudrate,parity,stop,priority) {\
	/************* SCI0 クロック同期モード設定 (SH/AVRと通信用) **************/\
	MSTP_SCI##ch = 0;						/* SCIスタンバイ解除*/\
	SCI##ch##.SCMR.BIT.SMIF=0;				/* データフォーマットLSBより*/\
    SCI##ch##.SCR.BYTE = 0x00;				/* SCSCRレジスタクリア*/\
	SCI##ch##.SEMR.BIT.ABCS=1;				/*		*/\
	/*/////////////////// クロックソースを選択 ここから ////////////////////*/\
	SCI##ch##.SCR.BIT.CKE = 0;				/*	調歩同期式モード */\
										/*	00：内部クロック／SCK 端子は入力端子（入力信号は無視）*/\
										/*	01：内部クロック／SCK 端子はクロック出力 */\
										/*	10：外部クロック／SCK 端子はクロック入力 */\
										/*	11：外部クロック／SCK 端子はクロック入力 */\
	/*/////////////////// クロックソースを選択 ここまで ////////////////////*/	\
	/*/////////////////// 通信フォーマット設定 ここから ////////////////////*/	\
	/* コミュニケーションモード */								\
    SCI##ch##.SMR.BIT.CM = 0;				/*	0：調歩同期式モード*/	\
										/*	1：クロック同期式モード*/\
	/* キャラクタレングス */									\
	SCI##ch##.SMR.BIT.CHR = 0;				/*	0：8 ビットデータ*/\
										/*	1：7 ビットデータ*/\
	/* パリティイネーブル */									\
	SCI##ch##.SMR.BIT.PE = (parity>1)?1:0;	/*	0：パリティビットの付加、およびチェックを禁止*/\
										/*	1：パリティビットの付加、およびチェックを許可*/\
	/* パリティモード */									\
	SCI##ch##.SMR.BIT.PM = parity&0x1;				/*	0：偶数パリティ*/\
										/*	1：奇数パリティ*/\
	/* ストップビットレングス */									\
	SCI##ch##.SMR.BIT.STOP = (stop>>1)&0x1;				/*	0：1 ストップビット*1 */\
										/*	1：2 ストップビット*2 */\
	/* マルチプロセッサモード */									\
	SCI##ch##.SMR.BIT.MP = 0;				/*	0：マルチプロセッサモードを禁止 */\
										/*	1：マルチプロセッサモードを許可（調歩同期式モードのみ有効）*/\
	/* クロックセレクト1、0 */									\
	SCI##ch##.SMR.BIT.CKS = 0;				/*	00：Pφクロック*/\
										/*	01：Pφ/64 クロック*/\
										/*	10：Pφ/16 クロック*/\
										/*	11：Pφ/64 クロック*/\
	/*/////////////////// 通信フォーマット設定 ここまで ////////////////////*/\
	/* ビットレート設定	ここから*/\
	SCI##ch##.BRR = baudrate;	\
	{volatile int i;for(i=0;i<50;i++);}		/*1ビット期間待機*/\
	/* ビットレート設定	ここまで*/			\
	/*//////////////////// SCSCRレジスタ設定 ここから //////////////////////*/\
	SCI##ch##_RX_ENABLE /*PORT3.ICR.BIT.B0 = 1; \//入力バッファを使用する←これがないと受信できない*/\
	SCI##ch##.SCR.BYTE |= 0x30;			/* 送受信動作を許可	*/\
	SCI##ch##.SCR.BIT.RIE = 1; 			/* 受信割り込み要求を許可*/\
    SCI##ch##.SCR.BIT.TIE = 0; 			/* 送信割り込み要求を禁止*/\
	/*//////////////////// SCSCRレジスタ設定 ここまで //////////////////////*/\
	/*/////////////// SCI0の割り込みレベルを設定 ここから ///////////////////*/\
	IEN(SCI##ch,RXI##ch) = 0;  /*割り込み禁止*/\
	IPR(SCI##ch,RXI##ch) = priority; /* 割り込みレベル設定()0～15 0:最低 15:最高*/\
	IEN(SCI##ch,RXI##ch) = 1; /*割り込み許可*/\
	IEN(SCI##ch,ERI##ch) = 0;  /*割り込み禁止*/\
	IPR(SCI##ch,ERI##ch) = priority; /* 割り込みレベル設定()0～15 0:最低 15:最高*/\
	IEN(SCI##ch,ERI##ch) = 1; /*割り込み許可*/\
	/*/////////////// SCI0の割り込みレベルを設定 ここまで //////////////////*/\
}

#define SCI0_RX_ENABLE {PORT2.ICR.BIT.B1 = 1;} 
#define SCI1_RX_ENABLE {PORT3.ICR.BIT.B0 = 1;} 
#define SCI2_RX_ENABLE {PORT5.ICR.BIT.B2 = 1;} 

#define SCI_PRIORITY_CHANGE(ch,priority){\
	IEN(SCI##ch,RXI##ch) = 0;  /*割り込み禁止*/\
	IPR(SCI##ch,RXI##ch) = priority; /* 割り込みレベル設定()0～15 0:最低 15:最高*/\
	IEN(SCI##ch,RXI##ch) = 1; /*割り込み許可*/\
	IEN(SCI##ch,ERI##ch) = 0;  /*割り込み禁止*/\
	IPR(SCI##ch,ERI##ch) = priority; /* 割り込みレベル設定()0～15 0:最低 15:最高*/\
	IEN(SCI##ch,ERI##ch) = 1; /*割り込み許可*/\
}

#define SCI_SEND(ch,c) {\
 	while (SCI##ch##.SSR.BIT.TDRE==0);\
    SCI##ch##.SSR.BIT.TDRE=0;	\
    SCI##ch##.TDR=c;					/*シリアル送信するデータを格納*/\
}
#define SCI_RECV(ch) (SCI##ch##.RDR)


#define SCI_ERI(ch) {\
	if(SCI##ch##.SSR.BIT.ORER==1){\
	/*	put_c('o');*/\
	/*	put_c(ch+0x30);*/\
		SCI##ch##.SSR.BIT.ORER=0;\
	}\
	if(SCI##ch##.SSR.BIT.FER==1){\
		put_c('f');\
		SCI##ch##.SSR.BIT.FER=0;\
	}\
	if(SCI##ch##.SSR.BIT.PER==1){\
		put_c('p');\
		SCI##ch##.SSR.BIT.PER=0;\
}}
//SCI_SEND(1)

//	#define sci0_asynchronous					// SCI0を歩調同期モードに設定
//	#define sci0_synchronous					// SCI0をクロック同期式モードに設定

	#define sci1_asynchronous					// SCI0を歩調同期モードに設定
	
//	#define sci2_asynchronous					// SCI0を歩調同期モードに設定

/********************************************************/
//  TUTrobo
//
//  概要
//      SCI関連設定 再定義
/********************************************************/
#undef puts
#undef putc
#undef getc


#define puts	put_s
#define putc	put_c
#define getc	get_c

/********************************************************/
//  TUTrobo
//
//  概要
//      SCI関連設定 printf用型名宣言
/********************************************************/
typedef struct{
	int z[2],n,l,m;
	unsigned long var,base;
}p_table;

/********************************************************/
//  TUTrobo
//
//  概要
//      SCI関連設定 プロトタイプ宣言
/********************************************************/
void sci_init(); 				// SCIの初期設定

void send_c(char c);			// SCI0から送信
char rec_c(void);				// SCI0から受信
void send_c2(char c);			// SCI2から送信
char rec_c2(void);				// SCI2から受信

void put_s(char *);				// SCI1から送信
void put_c(char );				// SCI1から文字列送信
char get_c(void);				// SCI1から受信

int printf(const char *, ...);	// 文字列を解析してconvertにわたす。
p_table clear(p_table);			// p_table初期化
void convert(p_table table);	// printfからもらった文字列を表示
void itoa(int value,char buff[],int radix);	//int→char変換

/********************************************************/
//  TUTrobo
//
//  概要
//      SCI関連設定 割り込みフラグ関連
/********************************************************/
#define COM0_START()	{SCI0.SCSCR.BIT.TIE = 1;}
#define COM0_END()		{SCI0.SCSCR.BIT.TIE = 0;}

#endif // __SCI_H__