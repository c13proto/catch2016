/********************************************************/
//
//  概要
//      データフラッシュ関連
//  注意
//		マイコン依存ファイル!!
//      プログラムをマイコンに書き込むとそれまでのデータがおかしくなる可能性がある。
//  作成者
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"
#define FLD_TMOUT 	-1
#define FLD_BLANK 	2
#define FLD_NOBLANK 3
#define FLD_ERROR 	4
#define FLD_OK 		5
void fld_init(void){
	fld_init_fcu_ram();

	fld_init_pclk_notification();
}
void reset_fcu(void){
	FLASH.FRESETR.BIT.FRESET =1;
	//wait 35usec  0.01usec
	{volatile int i;for(i=0;i<3600;i++);}
	//clear FCU reset
	FLASH.FRESETR.BIT.FRESET = 0 ;
}	

void fld_init_fcu_ram(void){
	static const int fcu_ram_size =8*1024;
	volatile unsigned char  *fcu_ram =(unsigned long *)0x007F8000;
	const volatile unsigned char *fcu_fw =(unsigned long *)0xFEFFE000;
	int i;
	if(FLASH.FENTRYR.WORD & 0x00ff){
		FLASH.FENTRYR.WORD = 0xAA00;
	}
	FLASH.FCURAME.WORD = 0xC401;
	for(i=0;i<fcu_ram_size/sizeof(unsigned char);i++){
		*(fcu_ram+i) = *(fcu_fw+i);
	}
}
int fld_init_pclk_notification(void){
	volatile unsigned char *addr_b =(unsigned char *)(0x00100000);
	volatile unsigned short *addr_w=(unsigned short *)(0x00100000);
	/* change P/E mode  */
	if((FLASH.FENTRYR.WORD & 0x00ff) != 0x0080){
		FLASH.FENTRYR.WORD = 0xAA80;
	}
	FLASH.PCKAR.BIT.PCKA = 48;
	
	*addr_b = 0xE9;
	*addr_b = 0x03;
	*addr_w = 0x0F0F;
	*addr_w = 0x0F0F;
	*addr_w = 0x0F0F;
	*addr_b = 0xD0;

	//timeout is 120us
	if(wait_FRDY(120)==FLD_TMOUT){
		//put_c('r');
		reset_fcu();
	}
	//error check
	if(FLASH.FSTATR0.BIT.ILGLERR == 1){
		return FLD_ERROR;
	}
	return FLD_OK;
}
int fcu_eraze_db(unsigned long top_addr_db){
//	unsigned long top_addr_db00 = 0x00100000;
	int d;
	if((FLASH.FENTRYR.WORD & 0x00ff)!=0x0080){
		FLASH.FENTRYR.WORD = 0xAA80;
	}
	if((d=fld_blank_check_2KB(top_addr_db))!=FLD_BLANK){
		//printf("eraze:%d  ",fld_eraze_2KB(top_addr_db));
		fld_eraze_2KB(top_addr_db);
	
	}
	//printf("blank:%d\n",d);
	
}
int fld_eraze_2KB(unsigned long addr){
	volatile unsigned char *addr_b =(unsigned char *)addr;
	int ret = FLD_OK;
	FLASH.FWEPROR.BIT.FLWE = 1;
	
	FLASH.DFLWE0.WORD=0x1EFF;
	FLASH.DFLWE1.WORD=0xE1FF;
	*addr_b = 0x20;
	*addr_b = 0xD0;
	
	if(wait_FRDY(250*1100)==FLD_TMOUT){
		reset_fcu();
	}
	//error
	if((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.ERSERR== 1)){
		ret=FLD_ERROR;
	}
	//protect
	FLASH.FWEPROR.BIT.FLWE = 2 ;
	FLASH.DFLWE0.WORD=0x1E00;
	FLASH.DFLWE1.WORD=0xE100;
	return ret;
}

int fld_blank_check_2KB(unsigned long addr){
	volatile unsigned char *addr_b =(unsigned char *)addr;
	FLASH.FMODR.BIT.FRDMD = 1;
	FLASH.DFLBCCNT.BIT.BCSIZE = 1;
	*addr_b =0x71;
	*addr_b =0xD0;
	
	if(wait_FRDY(770)==FLD_TMOUT){
		reset_fcu();
	}
	//error check
	if(FLASH.FSTATR0.BIT.ILGLERR == 1 ){
		return FLD_ERROR;
	}
	if(FLASH.DFLBCSTAT.BIT.BCST == 0){
		return FLD_BLANK;
	}
	return FLD_NOBLANK;
}
int wait_FRDY(unsigned int t){
	unsigned int wait_cnt=0;
	while(FLASH.FSTATR0.BIT.FRDY == 0){	
		if(wait_cnt>(t*100)){
//			put_c('c');
			return FLD_TMOUT;
		}
		wait_cnt++;
	}
	return 1;	
}

int fld_program_8byte(unsigned long addr,UDAuS *fdata){
	
	volatile unsigned char *addr_b =(unsigned char *)addr;
	volatile unsigned short *addr_w =(unsigned short *)addr;
	int i,ret=FLD_OK;
	FLASH.FWEPROR.BIT.FLWE =1;
	FLASH.DFLWE0.WORD =0x1EFF;
	FLASH.DFLWE0.WORD =0xE1FF;
	*addr_b = 0xE8;
	*addr_b = 0x04;
	for(i=0;i<2;i++){
		*addr_w = fdata[0].s[i];
	}
	for(i=0;i<2;i++){
		*addr_w = fdata[1].s[i];
	}
	*addr_b =0xD0;
	if(wait_FRDY(2*1100)==FLD_TMOUT){
		reset_fcu();
	}
	//error
	if((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.PRGERR ==1)){
		ret=FLD_ERROR;
	}
	//protect
	FLASH.FWEPROR.BIT.FLWE = 2 ;
	FLASH.DFLWE0.WORD=0x1E00;
	FLASH.DFLWE1.WORD=0xE100;
	return ret;
		
}
int fld_program_route(unsigned long addr,auto_route *r){
	volatile unsigned char *addr_b =(unsigned char *)addr;
	volatile unsigned short *addr_w =(unsigned short *)addr;
	int j,ret=FLD_OK;
	FLASH.FWEPROR.BIT.FLWE =1;
	FLASH.DFLWE0.WORD =0x1EFF;
	FLASH.DFLWE0.WORD =0xE1FF;
	*addr_b = 0xE8;
	*addr_b = 0x40;
	//for(j=0;j<64;j++)*addr_w = *(wdata+j);
	
	for(j=0;j<4;j++){
		*addr_w = r->leaf_field[j].s[0];
		*addr_w = r->leaf_field[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->spot1[j].s[0];
		*addr_w = r->spot1[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->spot2[j].s[0];
		*addr_w = r->spot2[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->spot3[j].s[0];
		*addr_w = r->spot3[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->pass_field[j].s[0];
		*addr_w = r->pass_field[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->get_sucker[j].s[0];
		*addr_w = r->get_sucker[j].s[1];
	}
	for(j=0;j<4;j++){
		*addr_w = r->V_GOAL[j].s[0];
		*addr_w = r->V_GOAL[j].s[1];
	}
	for(j=0;j<8;j++)*addr_w = 0;
	
	*addr_b =0xD0;
	
	if(wait_FRDY(5*1100)==FLD_TMOUT){
		reset_fcu();
	}
	//error
	if((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.PRGERR ==1)){
		ret=FLD_ERROR;
	}
	//protect
	FLASH.FWEPROR.BIT.FLWE = 2 ;
	FLASH.DFLWE0.WORD=0x1E00;
	FLASH.DFLWE1.WORD=0xE100;
	return ret;
}
int fld_enable_read(void){
	if(FLASH.FENTRYR.WORD & 0x00ff){
		FLASH.FENTRYR.WORD =0xAA00;
	}
	FLASH.DFLRE0.WORD = 0x2DFF;
	FLASH.DFLRE1.WORD = 0xD2FF;
	return FLD_OK;
}
void fld_debug_route(unsigned long addr){
/*	
	int i;
	auto_route *rt;	
	fld_enable_read();
	rt=(auto_route *)addr;
	if(addr==TOP_ADDR_DB01)printf("red = {{ ");
	else if(addr==TOP_ADDR_DB02)printf("blue = {{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->leaf_field[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->spot1[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->spot2[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->spot3[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->pass_field[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->get_sucker[i].d);
	printf(" },\n{ ");
	for(i=0;i<4;i++)printf("%f, ",rt->V_GOAL[i].d);
	printf(" }};\n");
	printf("status:%d\n",FLASH.FASTAT.BYTE);
*/
}

#if 0
void dataflash_write(void){
	static char old_sw=0;
	static char input;
	static char old_input;
	static char count=0;
	char zone=mode();
	
	if(PSCON_PRE_MARU>0 && HALF_1==251)input=1;//右アナログスティックと○ボタンでROMへ代入
	else input=0;

	if(old_input==0 && input==1)//コントローラからROMへ代入
	{
		count++;
		
		if(count==1)
		{
			put_c('1');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.leaf_field[0].d=macond.pos.x;
				blue.leaf_field[1].d=macond.pos.y;
				blue.leaf_field[2].d=macond.t_theta;
				blue.leaf_field[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);
			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.leaf_field[0].d=macond.pos.x;
				red.leaf_field[1].d=macond.pos.y;
				red.leaf_field[2].d=macond.t_theta;
				red.leaf_field[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==2)
		{
			put_c('2');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.spot1[0].d=macond.pos.x;
				blue.spot1[1].d=macond.pos.y;
				blue.spot1[2].d=macond.t_theta;
				blue.spot1[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.spot1[0].d=macond.pos.x;
				red.spot1[1].d=macond.pos.y;
				red.spot1[2].d=macond.t_theta;
				red.spot1[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==3)
		{
			put_c('3');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.spot2[0].d=macond.pos.x;
				blue.spot2[1].d=macond.pos.y;
				blue.spot2[2].d=macond.t_theta;
				blue.spot2[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.spot2[0].d=macond.pos.x;
				red.spot2[1].d=macond.pos.y;
				red.spot2[2].d=macond.t_theta;
				red.spot2[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==4)
		{
			put_c('4');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.spot3[0].d=macond.pos.x;
				blue.spot3[1].d=macond.pos.y;
				blue.spot3[2].d=macond.t_theta;
				blue.spot3[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.spot3[0].d=macond.pos.x;
				red.spot3[1].d=macond.pos.y;
				red.spot3[2].d=macond.t_theta;
				red.spot3[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==5)
		{
			put_c('5');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.pass_field[0].d=macond.pos.x;
				blue.pass_field[1].d=macond.pos.y;
				blue.pass_field[2].d=macond.t_theta;
				blue.pass_field[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.pass_field[0].d=macond.pos.x;
				red.pass_field[1].d=macond.pos.y;
				red.pass_field[2].d=macond.t_theta;
				red.pass_field[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==6)
		{
			put_c('6');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.get_sucker[0].d=macond.pos.x;
				blue.get_sucker[1].d=macond.pos.y;
				blue.get_sucker[2].d=macond.t_theta;
				blue.get_sucker[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.get_sucker[0].d=macond.pos.x;
				red.get_sucker[1].d=macond.pos.y;
				red.get_sucker[2].d=macond.t_theta;
				red.get_sucker[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else if(count==7)
		{
			put_c('7');
			
			if(zone=='B')//青ゾーンの時
			{			
				blue.V_GOAL[0].d=macond.pos.x;
				blue.V_GOAL[1].d=macond.pos.y;
				blue.V_GOAL[2].d=macond.t_theta;
				blue.V_GOAL[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB02);
				fld_program_route(TOP_ADDR_DB02,&blue);

			}
			else if(zone=='R')//赤ゾーンの時
			{
				red.V_GOAL[0].d=macond.pos.x;
				red.V_GOAL[1].d=macond.pos.y;
				red.V_GOAL[2].d=macond.t_theta;
				red.V_GOAL[3].d=fishing_rod_position;
				fcu_eraze_db(TOP_ADDR_DB01);
				fld_program_route(TOP_ADDR_DB01,&red);
			}
		}
		else
		{
			fld_debug_route(TOP_ADDR_DB01);
			fld_debug_route(TOP_ADDR_DB02);
		}
	}



	//ボタンを使ってのROMへの代入
	if(PORTE.PORT.BIT.B4==0 && old_sw==1){
	switch(~(PORTE.PORT.BYTE)&0x0f){
		case 0:
		case 8:
			fld_debug_route(TOP_ADDR_DB01);
			fld_debug_route(TOP_ADDR_DB02);
			break;
		case 9:
		{
			put_c('9');
			blue.leaf_field[0].d=macond.pos.x;
			blue.leaf_field[1].d=macond.pos.y;
			blue.leaf_field[2].d=macond.t_theta;
			blue.leaf_field[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		
		case 10:
		{
			put_s('10');
			blue.spot1[0].d=macond.pos.x;
			blue.spot1[1].d=macond.pos.y;
			blue.spot1[2].d=macond.t_theta;
			blue.spot1[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		case 11:
		{
			put_s("11");
			blue.spot2[0].d=macond.pos.x;
			blue.spot2[1].d=macond.pos.y;
			blue.spot2[2].d=macond.t_theta;
			blue.spot2[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		case 12:
		{
			put_s("12");
			blue.spot3[0].d=macond.pos.x;
			blue.spot3[1].d=macond.pos.y;
			blue.spot3[2].d=macond.t_theta;
			blue.spot3[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		case 13:
		{
			put_s("13");
			blue.pass_field[0].d=macond.pos.x;
			blue.pass_field[1].d=macond.pos.y;
			blue.pass_field[2].d=macond.t_theta;
			blue.pass_field[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
	
		}
			break;
		case 14:
		{
			put_s("14");
			blue.get_sucker[0].d=macond.pos.x;
			blue.get_sucker[1].d=macond.pos.y;
			blue.get_sucker[2].d=macond.t_theta;
			blue.get_sucker[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		case 15:
		{
			put_s("15");
			blue.V_GOAL[0].d=macond.pos.x;
			blue.V_GOAL[1].d=macond.pos.y;
			blue.V_GOAL[2].d=macond.t_theta;
			blue.V_GOAL[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB02);
			fld_program_route(TOP_ADDR_DB02,&blue);
		}
			break;
		case 1:
		{
			put_s("1");
			fcu_eraze_db(TOP_ADDR_DB01);
			red.leaf_field[0].d=macond.pos.x;
			red.leaf_field[1].d=macond.pos.y;
			red.leaf_field[2].d=macond.t_theta;
			red.leaf_field[3].d=fishing_rod_position;
			fld_program_route(TOP_ADDR_DB01,&red);
			//fld_debug_route(TOP_ADDR_DB01);
			//fld_debug_route(TOP_ADDR_DB02);
		}
			break;
		
		case 2:
		{
			put_s("2");
			fcu_eraze_db(TOP_ADDR_DB01);
			red.spot1[0].d=macond.pos.x;
			red.spot1[1].d=macond.pos.y;
			red.spot1[2].d=macond.t_theta;
			red.spot1[3].d=fishing_rod_position;
			fld_program_route(TOP_ADDR_DB01,&red);
		}
			break;
		case 3:
		{
			put_s("3");
			fcu_eraze_db(TOP_ADDR_DB01);
			red.spot2[0].d=macond.pos.x;
			red.spot2[1].d=macond.pos.y;
			red.spot2[2].d=macond.t_theta;
			red.spot2[3].d=fishing_rod_position;
			fld_program_route(TOP_ADDR_DB01,&red);
	
		}
			break;
		case 4:
		{
			put_s("4");
			fcu_eraze_db(TOP_ADDR_DB01);
			red.spot3[0].d=macond.pos.x;
			red.spot3[1].d=macond.pos.y;
			red.spot3[2].d=macond.t_theta;
			red.spot3[3].d=fishing_rod_position;
			fld_program_route(TOP_ADDR_DB01,&red);
		}
			break;
		case 5:
		{
			put_s("5");
			red.pass_field[0].d=macond.pos.x;
			red.pass_field[1].d=macond.pos.y;
			red.pass_field[2].d=macond.t_theta;
			red.pass_field[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB01);
			fld_program_route(TOP_ADDR_DB01,&red);
	
		}
			break;
		case 6:
		{
			put_s("6");
			red.get_sucker[0].d=macond.pos.x;
			red.get_sucker[1].d=macond.pos.y;
			red.get_sucker[2].d=macond.t_theta;
			red.get_sucker[3].d=fishing_rod_position;
			fcu_eraze_db(TOP_ADDR_DB01);
			fld_program_route(TOP_ADDR_DB01,&red);
		}
			break;
		case 7:
		{
			put_s("7");
			fcu_eraze_db(TOP_ADDR_DB01);
			red.V_GOAL[0].d=macond.pos.x;
			red.V_GOAL[1].d=macond.pos.y;
			red.V_GOAL[2].d=macond.t_theta;
			red.V_GOAL[3].d=fishing_rod_position;
			fld_program_route(TOP_ADDR_DB01,&red);
		}
			break;		
		}
	}	
	old_sw=PORTE.PORT.BIT.B4;
	old_input=input;

}

#endif