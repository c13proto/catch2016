/********************************************************/
//
//  comu.c ver1.6  2012/8/14
//  
//  �X�V���e
//    2012/8/14  �P�p�P�b�g���M��u|�v��5�񑗐M����悤�ɂ����B
//             
//    2012/8/11  �ʐM�𕡐��s���Ƃ��̊֐��ł̕ϐ����L�����P�����B
// 
//
//  �T�v
//      �ʐM�֘A
//  �쐬��
//		K.Yamada @ TUTrobo
//
//  �g�p���@
//�@�@�@setuo.h��#include "comu.h" ����B
//      
//
//      (char)cmd + (int)data + (char)CRC(data) + '|'�@
//      ��1�Z�b�g�Ƃ���B
//      1�Z�b�g�𕡐��܂Ƃ߂����̂��p�P�b�g�Ƃ���B
//
//  �D�揇��  
//        ��  sci_rx 
//            timer0(main)  
//        ��  timer1
//  ����
//        ��M�i�[����BUFSIZE�Ɉˑ����邽�߂���ȏ�̃f�[�^�͔j�������.

/********************************************************/

#include "setup.h"		//�}�C�R���̐ݒ�



/********************************************************/
//  TUTrobo
//
//  �T�v
//      �ʐM�֘A �O���[�o���ϐ��ݒ�
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
//   			���[�h 	��M�֐� ���M�֐�   �ۊǊ֐�   ���o�֐�       MPID�֐�  ID ���M�f�[�^  �t���O�̏�����
/*sci ch0*/	{NOWAIT,	rec_c,	send_c,		recv_push,	recv_pop,	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pscon
/*sci ch1*/	,{NOWAIT,	get_c,	put_c,		put_push,	put_pop, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pc
/*sci ch2*/	,{NOWAIT,	rec_c2,	send_c2,	recv_push2,	recv_pop2, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}//pscon2
/*sci ch2*/	//	,{PADAWAN,	rec_c2,	send_c2,	recv_push2,	recv_pop2, 	'0',{0}, 0,{0,0,0,0,0},0,0,{0},{0},}
};
/********************************************************/
//
//  ���O      
//		controller_data
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		��M�f�[�^�̏���				
//  �߂�l
//		�Ȃ�		
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
void controller_data(void)
{
	#define  PORT 0
	comu_data c;
	
	if(com[PORT].flg.recv_data==ERROR_CRC)		com[PORT].flg.recv_data = 0;	// �G���[�t���O������
	else if(com[PORT].flg.recv_data==ERROR_END)	com[PORT].flg.recv_data = 0;	// �G���[�t���O������	
	while(1){
		if(recv_action(&com[PORT],&c,&_bufp0)==1){	
			switch(c.cmd){
				case 0x24:	PSCON.BUTTON.WORD=c.value.s;
							break;		
				case 0x33:	PSCON.LEFT_STICK.WORD=c.value.s; // duty���i�[	// �p�x�i0-255�x�j���i�[
							break;			
				case 0x55:	PSCON.RIGHT_STICK.WORD=c.value.s;// duty���i�[// �p�x�i0-255�x�j���i�[		
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
	
	if(com[PORT].flg.recv_data==ERROR_CRC)		com[PORT].flg.recv_data = 0;	// �G���[�t���O������
	else if(com[PORT].flg.recv_data==ERROR_END)	com[PORT].flg.recv_data = 0;	// �G���[�t���O������	
	while(1){
		if(recv_action(&com[PORT],&c,&_bufp2)==1){	
			switch(c.cmd){
				case 0x24:	PSCON_.BUTTON.WORD=c.value.s;
							break;		
				case 0x33:	PSCON_.LEFT_STICK.WORD=c.value.s; // duty���i�[	// �p�x�i0-255�x�j���i�[
							break;			
				case 0x55:	PSCON_.RIGHT_STICK.WORD=c.value.s;// duty���i�[// �p�x�i0-255�x�j���i�[		
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
//  ���O      
//		pscon_debug
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		��M�f�[�^�̊m�F				
//  �߂�l
//		�Ȃ�		
//  �쐬��
//		yamamuro
//
/********************************************************/
void pscon_debug(void){
#if 1
	printf("PSCON1=%d, %d, %d, %d,",DUTY_LX,DUTY_LY,DUTY_RX,DUTY_RY);
	if(HALF_1!=0)
	{
		if(PS_BTN(SELECT)==0)printf("SELECT,");	// �Z���N�g�{�^��
		if(PS_BTN(L3)==0)printf("L3,");	// L3�{�^��
		if(PS_BTN(R3)==0)printf("R3,");	// R3�{�^��
		if(PS_BTN(START)==0)printf("START,");	// �X�^�[�g�{�^��
		if(PS_BTN(UP)==0)printf("UP,");	// �\���L�[�F���{�^��
		if(PS_BTN(RIGHT)==0)printf("RIGHT,");	// �\���L�[�F���{�^��
		if(PS_BTN(DOWN)==0)printf("DOWN,");	// �\���L�[�F���{�^��
		if(PS_BTN(LEFT)==0)printf("LEFT,");	// �\���L�[�F���{�^��
		if(PS_BTN(L2)==0)printf("L2,");	// L2�{�^��
		if(PS_BTN(R2)==0)printf("R2,");	// R2�{�^��
		if(PS_BTN(L1)==0)printf("L1,");	// L1�{�^��
		if(PS_BTN(R1)==0)printf("R1,");	// R1�{�^��
		if(PS_BTN(SANKAKU)==0)printf("SANKAKU,");	// ���{�^��
		if(PS_BTN(MARU)==0)printf("MARU,");	// ���{�^��
		if(PS_BTN(BATSU)==0)printf("BATSU,");	// �~�{�^��
		if(PS_BTN(SHIKAKU)==0)printf("SHIKAKU,");	// ���{�^��
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
		if(PS_BTN(SELECT)==0)printf("SELECT,");	// �Z���N�g�{�^��
		if(PS_BTN(L3)==0)printf("L3,");	// L3�{�^��
		if(PS_BTN(R3)==0)printf("R3,");	// R3�{�^��
		if(PS_BTN(START)==0)printf("START,");	// �X�^�[�g�{�^��
		if(PS_BTN(UP)==0)printf("UP,");	// �\���L�[�F���{�^��
		if(PS_BTN(RIGHT)==0)printf("RIGHT,");	// �\���L�[�F���{�^��
		if(PS_BTN(DOWN)==0)printf("DOWN,");	// �\���L�[�F���{�^��
		if(PS_BTN(LEFT)==0)printf("LEFT,");	// �\���L�[�F���{�^��
		if(PS_BTN(L2)==0)printf("L2,");	// L2�{�^��
		if(PS_BTN(R2)==0)printf("R2,");	// R2�{�^��
		if(PS_BTN(L1)==0)printf("L1,");	// L1�{�^��
		if(PS_BTN(R1)==0)printf("R1,");	// R1�{�^��
		if(PS_BTN(SANKAKU)==0)printf("SANKAKU,");	// ���{�^��
		if(PS_BTN(MARU)==0)printf("MARU,");	// ���{�^��
		if(PS_BTN(BATSU)==0)printf("BATSU,");	// �~�{�^��
		if(PS_BTN(SHIKAKU)==0)printf("SHIKAKU,");	// ���{�^��
	}
	
	printf("PSCON2=%d, %d, %d, %d,",DUTY_LX_,DUTY_LY_,DUTY_RX_,DUTY_RY_);
		//�{�^���ݒ�(�����ꂽ��1)
	if(HALF_1_!=0)
	{
		if(PS_BTN_(SELECT)==0)printf("SELECT,");	// �Z���N�g�{�^��
		if(PS_BTN_(L3)==0)printf("L3,");	// L3�{�^��
		if(PS_BTN_(R3)==0)printf("R3,");	// R3�{�^��
		if(PS_BTN_(START)==0)printf("START,");	// �X�^�[�g�{�^��
		if(PS_BTN_(UP)==0)printf("UP,");	// �\���L�[�F���{�^��
		if(PS_BTN_(RIGHT)==0)printf("RIGHT,");	// �\���L�[�F���{�^��
		if(PS_BTN_(DOWN)==0)printf("DOWN,");	// �\���L�[�F���{�^��
		if(PS_BTN_(LEFT)==0)printf("LEFT,");	// �\���L�[�F���{�^��
		if(PS_BTN_(L2)==0)printf("L2,");	// L2�{�^��
		if(PS_BTN_(R2)==0)printf("R2,");	// R2�{�^��
		if(PS_BTN_(L1)==0)printf("L1,");	// L1�{�^��
		if(PS_BTN_(R1)==0)printf("R1,");	// R1�{�^��
		if(PS_BTN_(SANKAKU)==0)printf("SANKAKU,");	// ���{�^��
		if(PS_BTN_(MARU)==0)printf("MARU,");	// ���{�^��
		if(PS_BTN_(BATSU)==0)printf("BATSU,");	// �~�{�^��
		if(PS_BTN_(SHIKAKU)==0)printf("SHIKAKU,");	// ���{�^��
	}
	printf("\r\n");
		
}
/********************************************************/
//
//  ���O      
//		PC_data
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		��M�f�[�^�̏���				
//  �߂�l
//		�Ȃ�		
//  �쐬��
//		K.Yamada @ TUTrobo #IDO
//
/********************************************************/
void PC_data(void)
{

	comu_data c;
	
	if(com[1].flg.recv_data == ERROR_CRC)		com[1].flg.recv_data = 0;	// �G���[�t���O������
	else if(com[1].flg.recv_data == ERROR_END)	com[1].flg.recv_data = 0;	// �G���[�t���O������	
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
//  ���O      
//		quick_send
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		���M�֐�
//  ���ӎ���
//      sci_mode�ɂ���ē��삪�ς��BMASTER:���M PADAWAN:�H		
//  �p�����^����
//		�|�[�g�̎��(sci_func)
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
#if 0
void quick_send(sci_func *f, int data1, int data2){
	static int d_cnt=0;
	static int c_cnt=0;
	int i;
	unsigned int a=0;
	static unsigned char pre_data[3];//��M�f�[�^���i�[�p
    
	int raw_data;				//�f�[�^�̊i�[�p		   
	int res = 0;			//�Ԃ�l

	if(f->flg.send==1){
		//put_c('R');						
		return -1;
	}
	//f->mp_send('0');//mp�p
	if(data1 < 0)			//��������
	{
		data1  = -data1;
		data1 |= 0x8000;
	}
	if(data2 < 0)			//��������
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
	f->flg.send=1;//���M�J�n
//						put_c('6');						
	//transmission(f);
	return res;	
	
	if(f->flg.send!=0){//go�T�C�����o���ꍇ
		
		for(c_cnt=0;c_cnt<CMD_NUMBER;c_cnt++){
			for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++){
				f->put(f->buff_send[c_cnt][d_cnt]); //�f�[�^���M
				f->flg.recv = 0;//��M���󂯂���1
			}
			if(f->sci_mode!=NOWAIT){
				while(f->flg.recv_data==NORMAL){
					a++;//��M��҂�
					if(a>60000){
						a=0;
						f->flg.recv_data=ERROR_WAIT;
						break;
					}
				}
				if(f->flg.recv_data == RECV_END){
						f->flg.recv_data=0;
						f->pop(pre_data);//���^�[���f�[�^�̎�o��	
						for(i=0;i<3;i++)if(f->buff_send[c_cnt][i]!=pre_data[i]){//���M�f�[�^�Ǝ�M�f�[�^���r
										c_cnt--;//�đ�
										break;
						}			
				}
				else c_cnt--;//�đ�
					
			}
			f->flg.recv_data = 0;//�t���O�N���A
		}
		//�f�[�^�P�p�P�b�g�I��
		//�p�P�b�g�I����Ɂb�𑗐M���ē��������킹��B
		if(f->sci_mode!=NOWAIT){
			f->put('|'); //�f�[�^���M
			/*
			f->flg.recv = 0;//��M���󂯂���1
			while(f->flg.recv == 0){
				a++;//��M��҂�
				if(a>TIMEOUT_TIME){
					a=0;
					f->put('|'); //�f�[�^���M
				}
			}*/
			f->sci_mode=PADAWAN;
		}
		else for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++)f->put('|'); //�f�[�^���M
		f->flg.send=0;//���M����I��
	}
}
#endif

/********************************************************/
//  ���O      
//		transmission
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		���M�֐�
//  ���ӎ���
//      sci_mode�ɂ���ē��삪�ς��BMASTER:���M PADAWAN:�H		
//  �p�����^����
//		�|�[�g�̎��(sci_func)
//  �߂�l
//		�Ȃ�
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
void transmission(sci_func *f){
	static int d_cnt=0;
	static int c_cnt=0;
	int i;
	unsigned int a=0;
	static unsigned char pre_data[3];//��M�f�[�^���i�[�p
    
	if(f->flg.send!=0){//go�T�C�����o���ꍇ
		
		for(c_cnt=0;c_cnt<CMD_NUMBER;c_cnt++){
			for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++){
				f->put(f->buff_send[c_cnt][d_cnt]); //�f�[�^���M
				f->flg.recv = 0;//��M���󂯂���1
			}
			if(f->sci_mode!=NOWAIT){
				while(f->flg.recv_data==NORMAL){
					a++;//��M��҂�
					if(a>60000){
						a=0;
						f->flg.recv_data=ERROR_WAIT;
						break;
					}
				}
				if(f->flg.recv_data == RECV_END){
						f->flg.recv_data=0;
						f->pop(pre_data);//���^�[���f�[�^�̎�o��	
						for(i=0;i<3;i++)if(f->buff_send[c_cnt][i]!=pre_data[i]){//���M�f�[�^�Ǝ�M�f�[�^���r
										c_cnt--;//�đ�
										break;
						}			
				}
				else c_cnt--;//�đ�
					
			}
			f->flg.recv_data = 0;//�t���O�N���A
		}
		//�f�[�^�P�p�P�b�g�I��
		//�p�P�b�g�I����Ɂb�𑗐M���ē��������킹��B
		if(f->sci_mode!=NOWAIT){
			f->put('|'); //�f�[�^���M
			/*
			f->flg.recv = 0;//��M���󂯂���1
			while(f->flg.recv == 0){
				a++;//��M��҂�
				if(a>TIMEOUT_TIME){
					a=0;
					f->put('|'); //�f�[�^���M
				}
			}*/
			f->sci_mode=PADAWAN;
		}
		else for(d_cnt=0;d_cnt<ONESET_LEN;d_cnt++)f->put('|'); //�f�[�^���M
		f->flg.send=0;//���M����I��
	}
}
/********************************************************/
//  ���O      
//		receipt
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		��M�֐�
//  ���ӎ���
//      sci_mode�ɂ���ē��삪�ς��BMASTER:���M PADAWAN:��M
//  �p�����^����
//		""�|�[�g�̎��(sci_func)
//  �߂�l
//		�Ȃ�
//
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
void receipt(sci_func *f){
	f->tem_data[f->cnt_recv_data] = f->get();    //��M�f�[�^�i�[
	f->flg.recv = TRUE;//��M�ʒm
	if(f->sci_mode == PADAWAN && f->flg.recv_data == RECV_END){	 					// ��M�f�[�^�����邪�A�{���ɐ�������Ύ��ɗ���l�͓��������Ⴄ�͂�    
		if(f->tem_data[0] == f->old_code)f->flg.recv_data = NORMAL;				// �đ����Ă����B�ێ��f�[�^�̏���
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
	if(f->tem_data[0]==SETEND)f->cnt_recv_data = -1;	// �J�E���g���Z�b�g
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
			if(f->tem_data[3] != crc_calc(f->raw_data))f->flg.recv_data = ERROR_CRC;//error�t���OCRC�s��v
			f->raw_data=0;
			break;
		case 4: 
			f->cnt_recv_data = -1;// �J�E���g���Z�b�g 
			if(f->tem_data[4] != SETEND)f->flg.recv_data = ERROR_END;//error�t���O//�I���L���s��v
			if(f->flg.recv_data == NORMAL){					//�����M
				switch(f->sci_mode){
					case NOWAIT:	f->push(f->tem_data);
									f->flg.recv_end = TRUE;
									//put_s("4\n");
			
									break;
		   			case MASTER:	f->push(f->tem_data);
					case PADAWAN: 	f->flg.recv_data = RECV_END;//��M�����t���O
									break;
					}
				}
			else switch(f->sci_mode){
				case PADAWAN: 		f->flg.recv_data = NORMAL;//�t���O�N���A
									break;
				}
			break;
	}
	if(f->sci_mode==PADAWAN){
		if(f->tem_data[0]!=SETEND){
			if(f->cnt_recv_data>=0) f->put(f->tem_data[f->cnt_recv_data]);         //��M�f�[�^��Ԃ�
			else f->put(f->tem_data[4]);         //��M�f�[�^��Ԃ�
		}
	}
	f->cnt_recv_data++;
}
/********************************************************/
//  ���O      
//		put_push
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N���͊֐�
//  �p�����^����
//		����
//  �߂�l
//		�Ȃ�
//  �쐬��
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
	p = com[1].head.next;   /* �擪�v�f�̎��̗v�f�̃A�h���X */
	q= &(com[1].head);
	while( p != NULL)
	{
		q=p;
		p = p->next;   /* ���̗v�f�֐i�� */
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
//  ���O      
//		put_pop
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N�o�͊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�X�^�b�N
//  �쐬��
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
		p = com[1].head.next;   /* �擪�v�f�̎��̗v�f�̃A�h���X */
		c[0]=p->data.cmd;
		c[1]=p->data.value.ch[0];
		c[2]=p->data.value.ch[1];
		//put_c('e');
		SCI1.SCR.BIT.RIE=0;//���荞�݋֎~
		//IEN(SCI1,RXI1) = 0;
		
		com[1].head.next=p->next;
		//put_c('f');//dePf�Ŏ~�܂�
		free(p);
		//IEN(SCI1,RXI1) = 1;
		
		SCI1.SCR.BIT.RIE=1;//���荞�݋���
		
	}
#endif


}
/********************************************************/
//  ���O      
//		recv_push
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N���͊֐�
//  �p�����^����
//		����
//  �߂�l
//		�Ȃ�
//  �쐬��
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
	p = com[0].head.next;   /* �擪�v�f�̎��̗v�f�̃A�h���X */
	q = &(com[0].head);
	while( p != NULL)
	{
		q=p;
		p = p->next;   /* ���̗v�f�֐i�� */
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
//  ���O      
//		recv_pop
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N�o�͊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�X�^�b�N
//  �쐬��
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
		p = com[0].head.next;   /* �擪�v�f�̎��̗v�f�̃A�h���X */
		c[0]=p->data.cmd;
		c[1]=p->data.value.ch[0];
		c[2]=p->data.value.ch[1];
//		put_c('e');
		SCI0.SCR.BIT.RIE=0;//���荞�݋֎~
	//	IEN(SCI0,RXI0) = 0;
		com[0].head.next=p->next;
//		put_c('f');//dePf�Ŏ~�܂�
		free(p);
	//	IEN(SCI0,RXI0) = 1;
		SCI0.SCR.BIT.RIE=1;//���荞�݋���
		
	}
#endif
}
#ifdef COM2_ENABLE
/********************************************************/
//  ���O      
//		recv_push2
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N���͊֐�
//  �p�����^����
//		����
//  �߂�l
//		�Ȃ�
//  �쐬��
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
//  ���O      
//		recv_pop2
//  �T�v
// 		�֘A
//  �@�\����
//		�X�^�b�N�o�͊֐�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�X�^�b�N
//  �쐬��
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
//  ���O      
//		directions
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		���M�f�[�^�̍쐬
//  �p�����^����
//		data		���M�f�[�^
//		cmd			���M�f�[�^�̓��e
//		CMD_NUMBER	���M�f�[�^�̎��
//  �߂�l
//		res		�R�}���h�̔���
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
int directions(sci_func *f,int data,int cmd)
{	
	int raw_data;				//�f�[�^�̊i�[�p		   
	int res = 0;			//�Ԃ�l

	if(f->flg.send==1){
								put_c('R');						
		return -1;
	}
	if(cmd==0)
	{
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'E',f->buff_send[0]);		//���M�f�[�^���i�[	
	}	
	if(cmd==1)
	{
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'I',f->buff_send[0]);		//���M�f�[�^���i�[		
	}
	
	if(cmd==2)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'C',f->buff_send[0]);		//���M�f�[�^���i�[    
	}	
	
	if(cmd==3)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'D',f->buff_send[0]);		//���M�f�[�^���i�[    
	}	
	
	if(cmd==4)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'S',f->buff_send[0]);		//���M�f�[�^���i�[    
	}								

	if(cmd==5)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'R',f->buff_send[0]);		//���M�f�[�^���i�[    
	}	
	
	if(cmd==6)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'A',f->buff_send[0]);		//���M�f�[�^���i�[    
	}	
	
	if(cmd==7)
	{	
			//f->mp_send('0');//mp�p
			raw_data = data;					//���M�f�[�^�擾	
			com_data(raw_data,'B',f->buff_send[0]);		//���M�f�[�^���i�[    
	}				
	//else if(cmd==CMD_NUMBER)f->flg.send=1;//���M�J�n
	//if(f->sci_mode==MASTER)
	if(f->sci_mode==PADAWAN)f->sci_mode=MASTER;
	f->flg.send=1;//���M�J�n
//						put_c('6');						
	//transmission(f);
	return res;

}
/********************************************************/
//  ���O      
//		com_data
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		�ʐM�ő��邽�߂̃f�[�^���쐬	
//  �p�����^����
//		raw_data	���邽�����f�[�^
//		object		���ʕ���
//      crc         CRC
//		com_data	���M�f�[�^
//  �߂�l
//		�Ȃ�
//	���ӎ���
//		-32768����32767�܂ł͈̔͂̒l��������Ȃ�
//  �쐬��
//		K.Yamada @ TUTrobo
//
/********************************************************/
void com_data(int raw_data,char object,unsigned char *com_data)
{
	int data;				//���l�̊i�[�p
//	long c=0;
	data = raw_data;
	if(data < 0)			//��������
	{
		data  = -data;
		data |=	0x8000;
	}
	com_data[0] = object;
	com_data[1] = (unsigned char)(data >> 8);
	com_data[2] = (unsigned char)(data & 0xFF);
//	com_data[3] = crc_calc(object|(crc_calc(data)<<8));//CRC���o���B
	com_data[3] = crc_calc(data);//�f�[�^�݂̂���CRC���o���B
	com_data[4] = SETEND;
}
/********************************************************/
//  ���O      
//		crc_calc
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		���M�f�[�^����CRC�l���v�Z	CRC-7
//  �p�����^����
//		data		���M�f�[�^
//  �߂�l
//		CRC�̒l	
//  �쐬��
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
//  ���O      
//		recv_action
//  �T�v
// 		�ʐM�֘A
//  �@�\����
//		��M�f�[�^�̏���
//  �p�����^����
//      �Ȃ�
//  �߂�l
//		�R�}���h
//  �쐬��
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
//  ���O      
//		sign_change
//  �T�v
// 		���荞�݊֘A
//  �@�\����
//		�ʐM�ő����Ă���16bit�f�[�^�̐�����t����
//  �p�����^����
//		data	��M�f�[�^					
//  �߂�l
//		b_16		����ꂽ�f�[�^�𐳕��t���ɕύX
//	���ӎ���
//		�߂�l��int�̂���16�r�b�g�����i�[�ł��Ȃ�
//  �쐬��
//		K.Ishimori @ TUTrobo
//
/********************************************************/
int sign_change(int raw_data)
{
	int b_16 = 0x00;				//�߂�l�̃��W�X�^
	int signflag;
	int data;
					
	signflag = data = raw_data;		// ���f�[�^���i�[
	signflag &= 0x8000;				// �}�C�i�X���������邩�̔���
	data &= 0x7fff;					// �}�C�i�X�̈Ӗ����܂܂�Ă���̂ŁA��Βl�ɕϊ�
				
	if(signflag == 0x8000) 
	{
		data = -data;
	}
	
	b_16 = data;

	return b_16;			//�Ԃ�l�F������������
}