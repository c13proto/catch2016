/********************************************************/
//
//  comu.c ver1.5  2012/8/11
//  
//  概要
//  	通信関連設定  
//  作成者
//		K.Yamaada @TUTrobo
//
/********************************************************/

#ifndef __COMU_H__
#define __COMU_H__


#define CMD_NUMBER 1
#define ONESET_LEN 5

#define COM0_ENABLE
#define COM1_ENABLE
#define COM2_ENABLE


/********************************************************/
//  TUTrobo
//
//  概要
//      通信関連 グローバル変数設定
/********************************************************/
typedef union{
	short s;
	unsigned char ch[2]; 
}comValue;

typedef struct{
	unsigned char cmd;
	comValue value;
}comu_data;

typedef struct comList{
	comu_data data;
	struct comList *next;	
}comList;

typedef struct{
	volatile unsigned char sci_mode;//モード
	char (*get)(void); //受信関数
	void (*put)(char); //送信関数
	void (*push)(unsigned char*); //保管関数
	void (*pop)(unsigned char*);  //引出関数
//	void (*mp_send)(char);//MPID送信用
	unsigned char mpID;//ID
	unsigned char buff_send[CMD_NUMBER][ONESET_LEN];
	volatile int cnt_recv_data;//カウント
	struct{
		volatile unsigned char recv_data:3;//状態
		volatile unsigned char send:1;//送れ
		volatile unsigned char recv:1;//受け取ったぞ
		volatile unsigned char recv_end:1;//これで終わり
		volatile unsigned char mp:1; //mpフラグ
	}flg;
	volatile int raw_data;//一時データ保存
	unsigned char old_code;//前のコマンド
	unsigned char tem_data[ONESET_LEN];//一時受信データ保存
	unsigned char recv_data[3];//必要受信データ
	comList head;
}sci_func;

//リトルエンディアン用
#if  defined(CPU_RX621)
typedef struct{
	union{
		unsigned short WORD;
		struct{
			unsigned char HALF2;
			unsigned char HALF1;
		}BYTE;
		struct{
			unsigned char L2:1;//0
			unsigned char R2:1;//1
			unsigned char L1:1;//2
			unsigned char R1:1;//3
			unsigned char SANKAKU:1;//4
			unsigned char MARU:1;//5
			unsigned char BATSU:1;//6
			unsigned char SHIKAKU:1;//7
			unsigned char SELECT:1;//8
			unsigned char L3:1;//9
			unsigned char R3:1;//10
			unsigned char START:1;//11
			unsigned char UP:1;//12
			unsigned char RIGHT:1;//13
			unsigned char DOWN:1;//14
			unsigned char LEFT:1;//15
		}BIT;
	}BUTTON;
	union{
		unsigned short WORD;
		struct{
			unsigned char Y;
			unsigned char X;
		}BYTE;
		struct{
			unsigned char DEGREE;
			unsigned char DUTY;
		}DATA;
		
	}RIGHT_STICK;
	union{
		unsigned short WORD;
		struct{
			unsigned char Y;
			unsigned char X;
		}BYTE;
			struct{
			unsigned char DEGREE;
			unsigned char DUTY;
		}DATA;
	
	}LEFT_STICK;
	union{
		unsigned short WORD;
		struct{
			unsigned char LEFT;
			unsigned char RIGHT;
		}BYTE;
		
	}DIRECTION_KEY1;
	union{
		unsigned short WORD;
		struct{
			unsigned char DOWN;
			unsigned char UP;
		}BYTE;
		
	}DIRECTION_KEY2;
	union{
		unsigned short WORD;
		struct{
			unsigned char MARU;
			unsigned char SANKAKU;
		}BYTE;
		
	}PRESSURE1;
	union{
		unsigned short WORD;
		struct{
			unsigned char SHIKAKU;
			unsigned char BATSU;
		}BYTE;
		
	}PRESSURE2;
	union{
		unsigned short WORD;
		struct{
			unsigned char R1;
			unsigned char L1;
		}BYTE;
		
	}PRESSURE3;
	union{
		unsigned short WORD;
		struct{
			unsigned char R2;
			unsigned char L2;
		}BYTE;
	}PRESSURE4;
}ps_controller;
/*
//ビッグエンディアン用
#else
typedef struct{
	union{
		unsigned short WORD;
		struct{
			unsigned char HALF1;
			unsigned char HALF2;
		}BYTE;
		struct{
			unsigned char LEFT:1;//15
			unsigned char DOWN:1;//14
			unsigned char RIGHT:1;//13
			unsigned char UP:1;//12
			unsigned char START:1;//11
			unsigned char R3:1;//10
			unsigned char L3:1;//9
			unsigned char SELECT:1;//8
			unsigned char SHIKAKU:1;//7
			unsigned char BATSU:1;//6
			unsigned char MARU:1;//5
			unsigned char SANKAKU:1;//4
			unsigned char R1:1;//3
			unsigned char L1:1;//2
			unsigned char R2:1;//1
			unsigned char L2:1;//0
		}BIT;
	}BUTTON;
	union{
		unsigned short WORD;
		struct{
			unsigned char X;
			unsigned char Y;
		}BYTE;
		struct{
			unsigned char DUTY;
			unsigned char DEGREE;
		}DATA;
		
	}RIGHT_STICK;
	union{
		unsigned short WORD;
		struct{
			unsigned char X;
			unsigned char Y;
		}BYTE;
			struct{
			unsigned char DUTY;
			unsigned char DEGREE;
		}DATA;
		
		
	}LEFT_STICK;
	union{
		unsigned short WORD;
		struct{
			unsigned char RIGHT;
			unsigned char LEFT;
		}BYTE;
		
	}DIRECTION_KEY1;
	union{
		unsigned short WORD;
		struct{
			unsigned char UP;
			unsigned char DOWN;
		}BYTE;
		
	}DIRECTION_KEY2;
	union{
		unsigned short WORD;
		struct{
			unsigned char SANKAKU;
			unsigned char MARU;
		}BYTE;
		
	}PRESSURE1;
	union{
		unsigned short WORD;
		struct{
			unsigned char BATSU;
			unsigned char SHIKAKU;
		}BYTE;
		
	}PRESSURE2;
	union{
		unsigned short WORD;
		struct{
			unsigned char L1;
			unsigned char R1;
		}BYTE;
		
	}PRESSURE3;
	union{
		unsigned short WORD;
		struct{
			unsigned char L2;
			unsigned char R2;
		}BYTE;
	}PRESSURE4;
}ps_controller;
*/
#endif

		
extern ps_controller PSCON;
#define PS_BTN(b) 				PSCON.BUTTON.BIT.##b
#define PS_PRE3(b) 				PSCON.PRESSURE3.BYTE.##b

#define HALF_1 					PSCON.BUTTON.BYTE.HALF1 
#define HALF_2 					PSCON.BUTTON.BYTE.HALF2
#define DUTY_LX 					PSCON.LEFT_STICK.DATA.DUTY
#define DUTY_LY 				PSCON.LEFT_STICK.DATA.DEGREE 
#define DUTY_RX 					PSCON.RIGHT_STICK.DATA.DUTY
#define DUTY_RY 				PSCON.RIGHT_STICK.DATA.DEGREE
#define D_direction_R   		PSCON.DIRECTION_KEY1.BYTE.RIGHT
#define D_direction_L   		PSCON.DIRECTION_KEY1.BYTE.LEFT
#define D_direction_U   		PSCON.DIRECTION_KEY2.BYTE.UP
#define D_direction_D   		PSCON.DIRECTION_KEY2.BYTE.DOWN

#define PSCON_PRE_SANKAKU		PSCON.PRESSURE1.BYTE.SANKAKU
#define PSCON_PRE_MARU			PSCON.PRESSURE1.BYTE.MARU
#define PSCON_PRE_BATSU			PSCON.PRESSURE2.BYTE.BATSU
#define PSCON_PRE_SHIKAKU		PSCON.PRESSURE2.BYTE.SHIKAKU

#define PSCON_PRE_L1			PSCON.PRESSURE3.BYTE.L1
#define PSCON_PRE_R1			PSCON.PRESSURE3.BYTE.R1
#define PSCON_PRE_L2			PSCON.PRESSURE4.BYTE.L2
#define PSCON_PRE_R2			PSCON.PRESSURE4.BYTE.R2


extern ps_controller PSCON_;
#define PS_BTN_(b) 				PSCON_.BUTTON.BIT.##b
#define PS_PRE3_(b) 			PSCON_.PRESSURE3.BYTE.##b

#define HALF_1_ 				PSCON_.BUTTON.BYTE.HALF1 
#define HALF_2_ 				PSCON_.BUTTON.BYTE.HALF2
#define DUTY_LX_ 				PSCON_.LEFT_STICK.DATA.DUTY
#define DUTY_LY_ 				PSCON_.LEFT_STICK.DATA.DEGREE 
#define DUTY_RX_ 				PSCON_.RIGHT_STICK.DATA.DUTY
#define DUTY_RY_ 				PSCON_.RIGHT_STICK.DATA.DEGREE
#define D_direction_R_    		PSCON_.DIRECTION_KEY1.BYTE.RIGHT
#define D_direction_L_   		PSCON_.DIRECTION_KEY1.BYTE.LEFT
#define D_direction_U_   		PSCON_.DIRECTION_KEY2.BYTE.UP
#define D_direction_D_   		PSCON_.DIRECTION_KEY2.BYTE.DOWN

#define PSCON_PRE_SANKAKU_		PSCON_.PRESSURE1.BYTE.SANKAKU
#define PSCON_PRE_MARU_			PSCON_.PRESSURE1.BYTE.MARU
#define PSCON_PRE_BATSU_		PSCON_.PRESSURE2.BYTE.BATSU
#define PSCON_PRE_SHIKAKU_		PSCON_.PRESSURE2.BYTE.SHIKAKU

#define PSCON_PRE_L1_			PSCON_.PRESSURE3.BYTE.L1
#define PSCON_PRE_R1_			PSCON_.PRESSURE3.BYTE.R1
#define PSCON_PRE_L2_			PSCON_.PRESSURE4.BYTE.L2
#define PSCON_PRE_R2_			PSCON_.PRESSURE4.BYTE.R2


extern sci_func com[];

/********************************************************/
//  TUTrobo
//
//  概要
//      通信関連 関数プロトタイプ宣言
/********************************************************/
void pscon_debug(void);
void pscon2_debug(void);
void comu_init(void);
void receipt(sci_func*);
void transmission(sci_func*);
#ifdef COM0_ENABLE
	void recv_push(unsigned char*);
	void recv_pop(unsigned char*);
#endif
#ifdef COM1_ENABLE
	void put_push(unsigned char*);
	void put_pop(unsigned char*);
#endif
#ifdef COM2_ENABLE
	void recv_push2(unsigned char*);
	void recv_pop2(unsigned char*);
#endif	

void com_data(int,char,unsigned char*);	//SH/AVRとの通信で送るためのデータを作成
int directions(sci_func*,int,int);//SH/AVRとの通信
int recv_action(sci_func*,comu_data*,volatile unsigned int*);
int sign_change(int raw_data);
unsigned char crc_calc(int);
void controller_data(void);
void controller2_data(void);
void SH_data(void);
void PC_data(void);
#endif

