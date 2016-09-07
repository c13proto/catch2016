/********************************************************/
//
//  comu.c ver1.6  2012/8/14
//  
//  更新内容
//    2012/8/14  １パケット送信後「|」を5回送信するようにした。
//             
//    2012/8/11  通信を複数行うときの関数での変数共有を改善した。
// 
//
//  概要
//      通信関連
//  作成者
//		K.Yamada @ TUTrobo
//
//  使用方法
//　　　setuo.hに#include "comu.h" する。
//      
//
//      (char)cmd + (int)data + (char)CRC(data) + '|'　
//      を1セットとする。
//      1セットを複数個まとめたものをパケットとする。
//
//  優先順位  
//        高  sci_rx 
//            timer0(main)  
//        低  timer1
//  注意
//        受信格納数はBUFSIZEに依存するためそれ以上のデータは破棄される.

/********************************************************/

#include "setup.h"		//マイコンの設定



/********************************************************/
//  TUTrobo
//
//  概要
//      通信関連 グローバル変数設定
/********************************************************/

#define NORMAL 		0
#define ERROR_WAIT  1
#define ERROR_CRC 	2
#define ERROR_END 	3
#define RECV_END  	5

#define TRUE 	1
#define FALSE   0

#define _BUFSIZE 12
#define SETEND '|'
#define MY_ID '2'
#define MASTER 5
#define PADAWAN 10 
#define NOWAIT 0
#define TIMEOUT_TIME 40000


#ifdef COM0_ENABLE
	volatile unsigned int _bufp0=0;
	volatile unsigned char _buf0[_BUFSIZE][3]={0};
#endif
#ifdef COM1_ENABLE
	volatile unsigned int _bufp1=0;
	volatile unsigned char _buf1[_BUFSIZE][3]={0};
#endif
#ifdef COM2_ENABLE
	volatile unsigned int _bufp2=0;
	volatile unsigned char _buf2[_BUFSIZE][3]={0};
#endif

ps_controller PSCON;
ps_controller PSCON_;

sci_func com[]={
//   			モード 	受信関数 送信関数   保管関数   引出関数       MPID関数  ID 送信データ  フラグの初期化
/*sci ch0*/	{NOWAIT,	rec_c,	send_c,		recv_push,	recv_pop,	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pscon
/*sci ch1*/	,{NOWAIT,	get_c,	put_c,		put_push,	put_pop, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pc
/*sci ch2*/	,{NOWAIT,	rec_c2,	send_c2,	recv_push2,	recv_pop2, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pscon2
/*sci ch2*/	//	,{PADAWAN,	rec_c2,	send_c2,	recv_push2,	recv_pop2, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}
};
/********************************************************/
//
//  名前      
//		controller_data
//  概要
// 		通信関連
//  機能説明
//		受信データの処理				
//  戻り値
//		なし		
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void controller_data(void)
{
	#define  PORT 0
	comu_data c;
	
	if(com[PORT].flg.recv_data==ERROR_CRC)		com[PORT].flg.recv_data = 0;	// エラーフラグ初期化
	else if(com[PORT].flg.recv_data==ERROR_END)	com[PORT].flg.recv_data = 0;	// エラーフラグ初期化	
	while(1){
		if(recv_action(&com[PORT],&c,&_bufp0)==1){	
			switch(c.cmd){
				case 0x24:	PSCON.BUTTON.WORD=c.value.s;
							break;		
				case 0x33:	PSCON.LEFT_STICK.WORD=c.value.s; // dutyを格納	// 角度（0-255度）を格納
							break;			
				case 0x55:	PSCON.RIGHT_STICK.WORD=c.value.s;// dutyを格納// 角度（0-255度）を格納		
							break;						
				case 0x5A:	PSCON.DIRECTION_KEY1.WORD=c.value.s;
							break;	
				case 0x69:  PSCON.DIRECTION_KEY2.WORD=c.value.s;
							break;	
				case 0x96:  PSCON.PRESSURE1.WORD=c.value.s;
							break;				
				case 0x99:  PSCON.PRESSURE2.WORD=c.value.s;
							break;									
				case 0xAA:  PSCON.PRESSURE3.WORD=c.value.s;
							break;				
				case 0xCC:  PSCON.PRESSURE4.WORD=c.value.s;	
							break;									
			   	}							
		}
		else{
			break; 	
		}
#ifndef LIST_MODE	
		if(_bufp0==0){
			break;
		}
#else		
		if(com[PORT].head.next==NULL){
			break;
		}
#endif
	}
	
			
}

void controller2_data(void)
{
	#define  PORT 2
	comu_data c;
	
	if(com[PORT].flg.recv_data==ERROR_CRC)		com[PORT].flg.recv_data = 0;	// エラーフラグ初期化
	else if(com[PORT].flg.recv_data==ERROR_END)	com[PORT].flg.recv_data = 0;	// エラーフラグ初期化	
	while(1){
		if(recv_action(&com[PORT],&c,&_bufp2)==1){	
			switch(c.cmd){
				case 0x24:	PSCON_.BUTTON.WORD=c.value.s;
							break;		
				case 0x33:	PSCON_.LEFT_STICK.WORD=c.value.s; // dutyを格納	// 角度（0-255度）を格納
							break;			
				case 0x55:	PSCON_.RIGHT_STICK.WORD=c.value.s;// dutyを格納// 角度（0-255度）を格納		
							break;						
				case 0x5A:	PSCON_.DIRECTION_KEY1.WORD=c.value.s;
							break;	
				case 0x69:  PSCON_.DIRECTION_KEY2.WORD=c.value.s;
							break;	
				case 0x96:  PSCON_.PRESSURE1.WORD=c.value.s;
							break;				
				case 0x99:  PSCON_.PRESSURE2.WORD=c.value.s;
							break;									
				case 0xAA:  PSCON_.PRESSURE3.WORD=c.value.s;
							break;				
				case 0xCC:  PSCON_.PRESSURE4.WORD=c.value.s;	
							break;									
			   	}							
		}
		else{
			break; 	
		}
#ifndef LIST_MODE	
		if(_bufp2==0){
			break;
		}
#else		
		if(com[PORT].head.next==NULL){
			break;
		}
#endif
	}
	
			
}

/********************************************************/
//
//  名前      
//		pscon_debug
//  概要
// 		通信関連
//  機能説明
//		受信データの確認				
//  戻り値
//		なし		
//  作成者
//		yamamuro
//
/********************************************************/
void pscon_debug(void){
#if 1
	printf("PSCON1=%d, %d, %d, %d,",DUTY_LX,DUTY_LY,DUTY_RX,DUTY_RY);
	if(HALF_1!=0)
	{
		if(PS_BTN(SELECT)==0)printf("SELECT,");	// セレクトボタン
		if(PS_BTN(L3)==0)printf("L3,");	// L3ボタン
		if(PS_BTN(R3)==0)printf("R3,");	// R3ボタン
		if(PS_BTN(START)==0)printf("START,");	// スタートボタン
		if(PS_BTN(UP)==0)printf("UP,");	// 十字キー：↑ボタン
		if(PS_BTN(RIGHT)==0)printf("RIGHT,");	// 十字キー：→ボタン
		if(PS_BTN(DOWN)==0)printf("DOWN,");	// 十字キー：↓ボタン
		if(PS_BTN(LEFT)==0)printf("LEFT,");	// 十字キー：←ボタン
		if(PS_BTN(L2)==0)printf("L2,");	// L2ボタン
		if(PS_BTN(R2)==0)printf("R2,");	// R2ボタン
		if(PS_BTN(L1)==0)printf("L1,");	// L1ボタン
		if(PS_BTN(R1)==0)printf("R1,");	// R1ボタン
		if(PS_BTN(SANKAKU)==0)printf("SANKAKU,");	// △ボタン
		if(PS_BTN(MARU)==0)printf("MARU,");	// ○ボタン
		if(PS_BTN(BATSU)==0)printf("BATSU,");	// ×ボタン
		if(PS_BTN(SHIKAKU)==0)printf("SHIKAKU,");	// □ボタン
	}
	printf("\r\n");
		
		
#else
		printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
		HALF_1 ,HALF_2 ,DUTY_LX ,DUTY_LY,DUTY_RX ,DUTY_RY,D_direction_R ,D_direction_L,D_direction_U,D_direction_D,
		PSCON_PRE_SANKAKU,PSCON_PRE_MARU,PSCON_PRE_BATSU,PSCON_PRE_SHIKAKU,PSCON_PRE_L1,PSCON_PRE_R1,PSCON_PRE_L2,PSCON_PRE_R2);
#endif
}
void pscon2_debug(void){
	
	
	printf("PSCON1=%d, %d, %d, %d,",DUTY_LX,DUTY_LY,DUTY_RX,DUTY_RY);
	if(HALF_1!=0)
	{
		if(PS_BTN(SELECT)==0)printf("SELECT,");	// セレクトボタン
		if(PS_BTN(L3)==0)printf("L3,");	// L3ボタン
		if(PS_BTN(R3)==0)printf("R3,");	// R3ボタン
		if(PS_BTN(START)==0)printf("START,");	// スタートボタン
		if(PS_BTN(UP)==0)printf("UP,");	// 十字キー：↑ボタン
		if(PS_BTN(RIGHT)==0)printf("RIGHT,");	// 十字キー：→ボタン
		if(PS_BTN(DOWN)==0)printf("DOWN,");	// 十字キー：↓ボタン
		if(PS_BTN(LEFT)==0)printf("LEFT,");	// 十字キー：←ボタン
		if(PS_BTN(L2)==0)printf("L2,");	// L2ボタン
		if(PS_BTN(R2)==0)printf("R2,");	// R2ボタン
		if(PS_BTN(L1)==0)printf("L1,");	// L1ボタン
		if(PS_BTN(R1)==0)printf("R1,");	// R1ボタン
		if(PS_BTN(SANKAKU)==0)printf("SANKAKU,");	// △ボタン
		if(PS_BTN(MARU)==0)printf("MARU,");	// ○ボタン
		if(PS_BTN(BATSU)==0)printf("BATSU,");	// ×ボタン
		if(PS_BTN(SHIKAKU)==0)printf("SHIKAKU,");	// □ボタン
	}
	
	printf("PSCON2=%d, %d, %d, %d,",DUTY_LX_,DUTY_LY_,DUTY_RX_,DUTY_RY_);
		//ボタン設定(押されたら1)
	if(HALF_1_!=0)
	{
		if(PS_BTN_(SELECT)==0)printf("SELECT,");	// セレクトボタン
		if(PS_BTN_(L3)==0)printf("L3,");	// L3ボタン
		if(PS_BTN_(R3)==0)printf("R3,");	// R3ボタン
		if(PS_BTN_(START)==0)printf("START,");	// スタートボタン
		if(PS_BTN_(UP)==0)printf("UP,");	// 十字キー：↑ボタン
		if(PS_BTN_(RIGHT)==0)printf("RIGHT,");	// 十字キー：→ボタン
		if(PS_BTN_(DOWN)==0)printf("DOWN,");	// 十字キー：↓ボタン
		if(PS_BTN_(LEFT)==0)printf("LEFT,");	// 十字キー：←ボタン
		if(PS_BTN_(L2)==0)printf("L2,");	// L2ボタン
		if(PS_BTN_(R2)==0)printf("R2,");	// R2ボタン
		if(PS_BTN_(L1)==0)printf("L1,");	// L1ボタン
		if(PS_BTN_(R1)==0)printf("R1,");	// R1ボタン
		if(PS_BTN_(SANKAKU)==0)printf("SANKAKU,");	// △ボタン
		if(PS_BTN_(MARU)==0)printf("MARU,");	// ○ボタン
		if(PS_BTN_(BATSU)==0)printf("BATSU,");	// ×ボタン
		if(PS_BTN_(SHIKAKU)==0)printf("SHIKAKU,");	// □ボタン
	}
	printf("\r\n");
		
}
/********************************************************/
//
//  名前      
//		PC_data
//  概要
// 		通信関連
//  機能説明
//		受信データの処理				
//  戻り値
//		なし		
//  作成者
//		K.Yamada @ TUTrobo #IDO
//
/********************************************************/
void PC_data(void)
{

	comu_data c;
	
	if(com[1].flg.recv_data == ERROR_CRC)		com[1].flg.recv_data = 0;	// エラーフラグ初期化
	else if(com[1].flg.recv_data == ERROR_END)	com[1].flg.recv_data = 0;	// エラーフラグ初期化	
	while(1){
		if(recv_action(&com[1],&c,&_bufp1)==1){	
			//comm_action(c.cmd,(int)c.value.s);						
		}
		else{
			break; 	
		}
#ifndef LIST_MODE	
		if(_bufp1==0){
			break;
		}
#else		
		if(com[1].head.next==NULL){
			break;
		}
#endif
	}
	
			
}


/********************************************************/
//  名前      
//		quick_send
//  概要
// 		通信関連
//  機能説明
//		送信関数
//  注意事項
//      sci_modeによって動作が変わる。MASTER:送信 PADAWAN:？		
//  パラメタ説明
//		ポートの種類(sci_func)
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
#if 0
void quick_send(sci_func *f, int data1, int data2){
	static int d_cnt=0;
	static int c_cnt=0;
	int i;
	unsigned int a=0;
	static unsigned char pre_data[3];//受信データを格納用
    
	int raw_data;				//データの格納用		   
	int res = 0;			//返り値

	if(f->flg.send==1){
		//put_c('R');						
		return -1;
	}
	//f->mp_send('0');//mp用
	if(data1 < 0)			//符号判定
	{
		data1  = -data1;
		data1 |= 0x8000;
	}
	if(data2 < 0)			//符号判定
	{
		data2  = -data2;
		data2 |= 0x8000;
	}
	com_data[0] = object;
	com_data[1] = (unsigned char)(data >> 8);
	com_data[2] = (unsigned char)(data & 0xFF);
	com_data[3] = (unsigned char)(data >> 8);
	com_data[4] = (unsigned char)(data & 0xFF);
	com_data[5] = SETEND; 
	com_data[6] = SETEND; 
	com_data[7] = SETEND; 
	f->flg.send=1;//送信開始
//						put_c('6');						
	//transmission(f);
	return res;	
	
	if(f->flg.send!=0){//goサインが出た場合
		
		for(c_cnt=0;c_cnt<CMD_NUMBER;c_cnt++){
			for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++){
				f->put(f->buff_send[c_cnt][d_cnt]); //データ送信
				f->flg.recv = 0;//受信を受けたら1
			}
			if(f->sci_mode!=NOWAIT){
				while(f->flg.recv_data==NORMAL){
					a++;//受信を待つ
					if(a>60000){
						a=0;
						f->flg.recv_data=ERROR_WAIT;
						break;
					}
				}
				if(f->flg.recv_data == RECV_END){
						f->flg.recv_data=0;
						f->pop(pre_data);//リターンデータの取出し	
						for(i=0;i<3;i++)if(f->buff_send[c_cnt][i]!=pre_data[i]){//送信データと受信データを比較
										c_cnt--;//再送
										break;
						}			
				}
				else c_cnt--;//再送
					
			}
			f->flg.recv_data = 0;//フラグクリア
		}
		//データ１パケット終了
		//パケット終了後に｜を送信して同期を合わせる。
		if(f->sci_mode!=NOWAIT){
			f->put('|'); //データ送信
			/*
			f->flg.recv = 0;//受信を受けたら1
			while(f->flg.recv == 0){
				a++;//受信を待つ
				if(a>TIMEOUT_TIME){
					a=0;
					f->put('|'); //データ送信
				}
			}*/
			f->sci_mode=PADAWAN;
		}
		else for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++)f->put('|'); //データ送信
		f->flg.send=0;//送信動作終了
	}
}
#endif

/********************************************************/
//  名前      
//		transmission
//  概要
// 		通信関連
//  機能説明
//		送信関数
//  注意事項
//      sci_modeによって動作が変わる。MASTER:送信 PADAWAN:？		
//  パラメタ説明
//		ポートの種類(sci_func)
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void transmission(sci_func *f){
	static int d_cnt=0;
	static int c_cnt=0;
	int i;
	unsigned int a=0;
	static unsigned char pre_data[3];//受信データを格納用
    
	if(f->flg.send!=0){//goサインが出た場合
		
		for(c_cnt=0;c_cnt<CMD_NUMBER;c_cnt++){
			for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++){
				f->put(f->buff_send[c_cnt][d_cnt]); //データ送信
				f->flg.recv = 0;//受信を受けたら1
			}
			if(f->sci_mode!=NOWAIT){
				while(f->flg.recv_data==NORMAL){
					a++;//受信を待つ
					if(a>60000){
						a=0;
						f->flg.recv_data=ERROR_WAIT;
						break;
					}
				}
				if(f->flg.recv_data == RECV_END){
						f->flg.recv_data=0;
						f->pop(pre_data);//リターンデータの取出し	
						for(i=0;i<3;i++)if(f->buff_send[c_cnt][i]!=pre_data[i]){//送信データと受信データを比較
										c_cnt--;//再送
										break;
						}			
				}
				else c_cnt--;//再送
					
			}
			f->flg.recv_data = 0;//フラグクリア
		}
		//データ１パケット終了
		//パケット終了後に｜を送信して同期を合わせる。
		if(f->sci_mode!=NOWAIT){
			f->put('|'); //データ送信
			/*
			f->flg.recv = 0;//受信を受けたら1
			while(f->flg.recv == 0){
				a++;//受信を待つ
				if(a>TIMEOUT_TIME){
					a=0;
					f->put('|'); //データ送信
				}
			}*/
			f->sci_mode=PADAWAN;
		}
		else for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++)f->put('|'); //データ送信
		f->flg.send=0;//送信動作終了
	}
}
/********************************************************/
//  名前      
//		receipt
//  概要
// 		通信関連
//  機能説明
//		受信関数
//  注意事項
//      sci_modeによって動作が変わる。MASTER:送信 PADAWAN:受信
//  パラメタ説明
//		""ポートの種類(sci_func)
//  戻り値
//		なし
//
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void receipt(sci_func *f){
	f->tem_data[f->cnt_recv_data] = f->get();    //受信データ格納
	f->flg.recv = TRUE;//受信通知
	if(f->sci_mode == PADAWAN && f->flg.recv_data == RECV_END){	 					// 受信データがあるが、本当に正しければ次に来る値は頭文字が違うはず    
		if(f->tem_data[0] == f->old_code)f->flg.recv_data = NORMAL;				// 再送してきた。保持データの消去
		else{
			f->recv_data[0] = f->old_code;
			f->recv_data[1] = f->tem_data[1];
			f->recv_data[2] = f->tem_data[2];
			f->push(f->recv_data);
			f->flg.recv_end 	= TRUE;
			f->flg.recv_data 	= NORMAL;
			if(f->tem_data[0] == SETEND)return;
		}
	}
	if(f->tem_data[0]==SETEND)f->cnt_recv_data = -1;	// カウントリセット
	else switch(f->cnt_recv_data){
		case 0: f->old_code	= f->tem_data[0];			
			break;
		case 1:	
			f->raw_data	=	((f->tem_data[1])<<8);	
			break;
		case 2: 
			f->raw_data |=	(f->tem_data[2]);		
			break;
		case 3: 
			if(f->tem_data[3] != crc_calc(f->raw_data))f->flg.recv_data = ERROR_CRC;//errorフラグCRC不一致
			f->raw_data=0;
			break;
		case 4: 
			f->cnt_recv_data = -1;// カウントリセット 
			if(f->tem_data[4] != SETEND)f->flg.recv_data = ERROR_END;//errorフラグ//終了記号不一致
			if(f->flg.recv_data == NORMAL){					//正常受信
				switch(f->sci_mode){
					case NOWAIT:	f->push(f->tem_data);
									f->flg.recv_end = TRUE;
									//put_s("4\n");
			
									break;
		   			case MASTER:	f->push(f->tem_data);
					case PADAWAN: 	f->flg.recv_data = RECV_END;//受信完了フラグ
									break;
					}
				}
			else switch(f->sci_mode){
				case PADAWAN: 		f->flg.recv_data = NORMAL;//フラグクリア
									break;
				}
			break;
	}
	if(f->sci_mode==PADAWAN){
		if(f->tem_data[0]!=SETEND){
			if(f->cnt_recv_data>=0) f->put(f->tem_data[f->cnt_recv_data]);         //受信データを返す
			else f->put(f->tem_data[4]);         //受信データを返す
		}
	}
	f->cnt_recv_data++;
}
/********************************************************/
//  名前      
//		put_push
//  概要
// 		関連
//  機能説明
//		スタック入力関数
//  パラメタ説明
//		文字
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void put_push(unsigned char *c){
#ifndef LIST_MODE
	int i;
	if(_bufp1!=_BUFSIZE)
	{
		for(i=0;i<3;i++)_buf1[_bufp1][i]=c[i];
		_bufp1++;
	}
#else
	comList *p,*q;
	//push_on=1;
	p = com[1].head.next;   /* 先頭要素の次の要素のアドレス */
	q= &(com[1].head);
	while( p != NULL)
	{
		q=p;
		p = p->next;   /* 次の要素へ進む */
	}
	/*if(q->data.cmd==c[0]){
		q->data.value.ch[0]=c[1];
		q->data.value.ch[1]=c[2];
	}
	else*/
	{
		comList *clist = (comList*)malloc(sizeof(comList));
		if( clist == NULL ){
			put_s( " no memory " );
			return;
		}
		clist->next = NULL;
		clist->data.cmd=c[0];
		clist->data.value.ch[0]=c[1];
		clist->data.value.ch[1]=c[2];
		q->next=clist;
		//put_c('P');
	}
#endif
	
}
/********************************************************/
//  名前      
//		put_pop
//  概要
// 		関連
//  機能説明
//		スタック出力関数
//  パラメタ説明
//		なし
//  戻り値
//		スタック
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void put_pop(unsigned char* c){
#ifndef LIST_MODE
	int i;
	if(_bufp1!=0)
	{
		_bufp1--;
		for(i=0;i<3;i++)c[i]=_buf1[_bufp1][i];
	}
#else
	comList *p;
	//put_c('c');
	if(com[1].head.next!=NULL){
		//put_c('d');
		p = com[1].head.next;   /* 先頭要素の次の要素のアドレス */
		c[0]=p->data.cmd;
		c[1]=p->data.value.ch[0];
		c[2]=p->data.value.ch[1];
		//put_c('e');
		SCI1.SCR.BIT.RIE=0;//割り込み禁止
		//IEN(SCI1,RXI1) = 0;
		
		com[1].head.next=p->next;
		//put_c('f');//dePfで止まる
		free(p);
		//IEN(SCI1,RXI1) = 1;
		
		SCI1.SCR.BIT.RIE=1;//割り込み許可
		
	}
#endif


}
/********************************************************/
//  名前      
//		recv_push
//  概要
// 		関連
//  機能説明
//		スタック入力関数
//  パラメタ説明
//		文字
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void recv_push(unsigned char *c){
#ifndef LIST_MODE
	int i;
	if(_bufp0!=_BUFSIZE)
	{
		for(i=0;i<3;i++)_buf0[_bufp0][i]=c[i];
		_bufp0++;
	}
#else
	comList *p,*q;
	//push_on=1;
	p = com[0].head.next;   /* 先頭要素の次の要素のアドレス */
	q = &(com[0].head);
	while( p != NULL)
	{
		q=p;
		p = p->next;   /* 次の要素へ進む */
	}
	/*if(q->data.cmd==c[0]){
		q->data.value.ch[0]=c[1];
		q->data.value.ch[1]=c[2];
	}
	else*/
	{
		comList *clist = (comList*)malloc(sizeof(comList));
		if( clist == NULL ){
			put_s( " no memory " );
			return;
		}
		clist->next = NULL;
		clist->data.cmd=c[0];
		clist->data.value.ch[0]=c[1];
		clist->data.value.ch[1]=c[2];
		q->next=clist;
//		put_c('P');
	}
#endif
}
/********************************************************/
//  名前      
//		recv_pop
//  概要
// 		関連
//  機能説明
//		スタック出力関数
//  パラメタ説明
//		なし
//  戻り値
//		スタック
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void recv_pop(unsigned char* c){
#ifndef LIST_MODE
	int i;
	if(_bufp0!=0){
		_bufp0--;
		for(i=0;i<3;i++)c[i]=_buf0[_bufp0][i];
	}
#else
	comList *p;
//	put_c('c');
	if(com[0].head.next!=NULL){
//		put_c('d');
		p = com[0].head.next;   /* 先頭要素の次の要素のアドレス */
		c[0]=p->data.cmd;
		c[1]=p->data.value.ch[0];
		c[2]=p->data.value.ch[1];
//		put_c('e');
		SCI0.SCR.BIT.RIE=0;//割り込み禁止
	//	IEN(SCI0,RXI0) = 0;
		com[0].head.next=p->next;
//		put_c('f');//dePfで止まる
		free(p);
	//	IEN(SCI0,RXI0) = 1;
		SCI0.SCR.BIT.RIE=1;//割り込み許可
		
	}
#endif
}
#ifdef COM2_ENABLE
/********************************************************/
//  名前      
//		recv_push2
//  概要
// 		関連
//  機能説明
//		スタック入力関数
//  パラメタ説明
//		文字
//  戻り値
//		なし
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void recv_push2(unsigned char *c){
	int i;
	if(_bufp2!=_BUFSIZE)
	{
		for(i=0;i<3;i++)_buf2[_bufp2][i]=c[i];
		_bufp2++;
	}
}
/********************************************************/
//  名前      
//		recv_pop2
//  概要
// 		関連
//  機能説明
//		スタック出力関数
//  パラメタ説明
//		なし
//  戻り値
//		スタック
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void recv_pop2(unsigned char* c){
	int i;
	if(_bufp2!=0)
	{
		_bufp2--;
		for(i=0;i<3;i++)c[i]=_buf2[_bufp2][i];
	}
}
#endif
/********************************************************/
//  名前      
//		directions
//  概要
// 		通信関連
//  機能説明
//		送信データの作成
//  パラメタ説明
//		data		送信データ
//		cmd			送信データの内容
//		CMD_NUMBER	送信データの種類
//  戻り値
//		res		コマンドの判定
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
int directions(sci_func *f,int data,int cmd)
{	
	int raw_data;				//データの格納用		   
	int res = 0;			//返り値

	if(f->flg.send==1){
								put_c('R');						
		return -1;
	}
	if(cmd==0)
	{
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'E',f->buff_send[0]);		//送信データを格納	
	}	
	if(cmd==1)
	{
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'I',f->buff_send[0]);		//送信データを格納		
	}
	
	if(cmd==2)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'C',f->buff_send[0]);		//送信データを格納    
	}	
	
	if(cmd==3)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'D',f->buff_send[0]);		//送信データを格納    
	}	
	
	if(cmd==4)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'S',f->buff_send[0]);		//送信データを格納    
	}								

	if(cmd==5)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'R',f->buff_send[0]);		//送信データを格納    
	}	
	
	if(cmd==6)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'A',f->buff_send[0]);		//送信データを格納    
	}	
	
	if(cmd==7)
	{	
			//f->mp_send('0');//mp用
			raw_data = data;					//送信データ取得	
			com_data(raw_data,'B',f->buff_send[0]);		//送信データを格納    
	}				
	//else if(cmd==CMD_NUMBER)f->flg.send=1;//送信開始
	//if(f->sci_mode==MASTER)
	if(f->sci_mode==PADAWAN)f->sci_mode=MASTER;
	f->flg.send=1;//送信開始
//						put_c('6');						
	//transmission(f);
	return res;

}
/********************************************************/
//  名前      
//		com_data
//  概要
// 		通信関連
//  機能説明
//		通信で送るためのデータを作成	
//  パラメタ説明
//		raw_data	送るたい生データ
//		object		判別文字
//      crc         CRC
//		com_data	送信データ
//  戻り値
//		なし
//	注意事項
//		-32768から32767までの範囲の値しか送れない
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
void com_data(int raw_data,char object,unsigned char *com_data)
{
	int data;				//引値の格納用
//	long c=0;
	data = raw_data;
	if(data < 0)			//符号判定
	{
		data  = -data;
		data |=	0x8000;
	}
	com_data[0] = object;
	com_data[1] = (unsigned char)(data >> 8);
	com_data[2] = (unsigned char)(data & 0xFF);
//	com_data[3] = crc_calc(object|(crc_calc(data)<<8));//CRCを出す。
	com_data[3] = crc_calc(data);//データのみからCRCを出す。
	com_data[4] = SETEND;
}
/********************************************************/
//  名前      
//		crc_calc
//  概要
// 		通信関連
//  機能説明
//		送信データからCRC値を計算	CRC-7
//  パラメタ説明
//		data		送信データ
//  戻り値
//		CRCの値	
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
unsigned char crc_calc(int data)
{
	int i;
	unsigned int buf;
	buf=data;
	for(i=8;i>=0;i--)if((buf & (0x80<<i))==(0x80<<i))
	{
		buf=buf^(0x89<<i);
	}
	buf=buf & 0xFF;
	return (unsigned char)buf;
}

/********************************************************/
//  名前      
//		recv_action
//  概要
// 		通信関連
//  機能説明
//		受信データの処理
//  パラメタ説明
//      なし
//  戻り値
//		コマンド
//  作成者
//		K.Yamada @ TUTrobo
//
/********************************************************/
int recv_action(sci_func *f,comu_data* c,volatile unsigned int *buf)
{	
	unsigned char recvv_data[3];

#ifndef LIST_MODE
	if(f->flg.recv_end == 1)
	{		
		f->pop(recvv_data);
		c->cmd=recvv_data[0];
		c->value.s=0;
		c->value.s=((((recvv_data[1]))<<8)&0xff00)|(recvv_data[2]);
		if(*buf ==0)f->flg.recv_end = 0;

		return 1;
	}
	return 0; 
	
#else 
	//if(head0.next != NULL){
	if(f->head.next != NULL){
		f->pop(recvv_data);
		c->cmd=recvv_data[0];
		c->value.ch[0]=recvv_data[1];
		c->value.ch[1]=recvv_data[2];
		return 1;
	}
	return 0; 
	
#endif
}

/********************************************************/
//  名前      
//		sign_change
//  概要
// 		割り込み関連
//  機能説明
//		通信で送られてくる16bitデータの正負を付ける
//  パラメタ説明
//		data	受信データ					
//  戻り値
//		b_16		送られたデータを正負付きに変更
//	注意事項
//		戻り値がintのため16ビットしか格納できない
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int sign_change(int raw_data)
{
	int b_16 = 0x00;				//戻り値のレジスタ
	int signflag;
	int data;
					
	signflag = data = raw_data;		// 生データを格納
	signflag &= 0x8000;				// マイナス符号があるかの判定
	data &= 0x7fff;					// マイナスの意味も含まれているので、絶対値に変換
				
	if(signflag == 0x8000) 
	{
		data = -data;
	}
	
	b_16 = data;

	return b_16;			//返り値：結合した数字
}