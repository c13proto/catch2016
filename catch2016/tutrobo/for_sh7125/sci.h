/********************************************************/
//
//  概要
//  	SCI関連設定
//	更新日時
//		2013/02/02 
//  作成者
//		TUTrobo
//
/********************************************************/

#ifndef __SCI_H__
#define __SCI_H__
	
	#define sci0_asynchronous					// SCI0を歩調同期モードに設定
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
void sci0_asynchronous_init();	// SCI0調歩同期式の初期設定
void sci0_synchronous_init();	// SCI0クロック同期式の初期設定
void sci1_asynchronous_init();	// SCI1調歩同期式の初期設定
void sci2_asynchronous_init();	// SCI2調歩同期式の初期設定

void send_c(char c);			// SCI0から送信
char rec_c(void);				// SCI0から受信
void tx_0(char send);			// SCI0から送信(割り込み使用時)
char rx_0(void);				// SCI0から受信(割り込み使用時)
char txrx_0(char send);			// SCI0から送受信(割り込み使用時)

void put_s(char *);				// SCI1から送信
void put_c(char );				// SCI1から文字列送信
char get_c(void);				// SCI1から受信
void tx_1(char send);			// SCI1から送信(割り込み使用時)
char rx_1(void);				// SCI1から受信(割り込み使用時)
char txrx_1(char send);			// SCI1から送受信(割り込み使用時)

void transmit_c(char c);		// SCI2から送信
char accept_c(void);			// SCI2から受信
void tx_2(char send);			// SCI2から送信(割り込み使用時)
char rx_2(void);				// SCI2から受信(割り込み使用時)
char txrx_2(char send);			// SCI2から送受信(割り込み使用時)


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