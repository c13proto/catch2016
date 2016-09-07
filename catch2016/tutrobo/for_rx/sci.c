/********************************************************/
//
//  概要
//      SCI関連
//	更新日時
//		2013/04/26
//  作成者
//		K.yamada @ TUTrobo
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
void sci_init() {	
	
	IOPORT.PFFSCI.BIT.SCI2S = 1;//sci2の入出力ポートをBに設定
/*                ch, baudrate, パリティ,ストップビット,優先度   */
 	SCI_ASYNC_INIT(0, B_19200 , NONE, ONE_STOPBIT, 13);		/* SCI0の初期化 (PScon_AVR用)*/
	SCI_ASYNC_INIT(1, B_19200 , NONE, ONE_STOPBIT, 11);		/* SCI1の初期化 (PCと通信用) */
	SCI_ASYNC_INIT(2, B_19200, NONE, ONE_STOPBIT, 12);		/* SCI2の初期化 (PScon_AVR用) */
//	SCI_ASYNC_INIT(2, B_115200, NONE, ONE_STOPBIT, 15);		/* SCI2の初期化 (ジャイロ用) */11
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
void send_c(char c){
	SCI_SEND(0,c);
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
char rec_c(void){
	return SCI_RECV(0);
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
void put_c(char c){
	SCI_SEND(1,c);											
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
char get_c(void){				
	return SCI1.RDR;
}
/********************************************************/
//  名前      
//		send_c
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
void send_c2(char c){
	SCI_SEND(2,c);
}
/********************************************************/
//  名前      
//		rec_c2	
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
char rec_c2(void){
	return SCI_RECV(2);
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