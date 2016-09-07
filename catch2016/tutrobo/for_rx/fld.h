#ifndef __FCU_H__
#define __FCU_H__


#define TOP_ADDR_DB00 0x00100000
#define TOP_ADDR_DB01 0x00100800
#define TOP_ADDR_DB02 0x00101000
#define TOP_ADDR_DB03 0x00101800
#define TOP_ADDR_DB04 0x00102000
#define TOP_ADDR_DB05 0x00102800
#define TOP_ADDR_DB06 0x00103000
#define TOP_ADDR_DB07 0x00103800
#define TOP_ADDR_DB08 0x00104000
#define TOP_ADDR_DB09 0x00104800
#define TOP_ADDR_DB10 0x00105000
#define TOP_ADDR_DB11 0x00105800
#define TOP_ADDR_DB12 0x00106000
#define TOP_ADDR_DB13 0x00106800
#define TOP_ADDR_DB14 0x00107000
#define TOP_ADDR_DB15 0x00107800

typedef union{
	double d;
	unsigned short s[2];
}UDAuS;

typedef struct{
		UDAuS leaf_field[4];
		UDAuS spot1[4];
		UDAuS spot2[4];
		UDAuS spot3[4];
		UDAuS pass_field[4];
		UDAuS get_sucker[4];
		UDAuS V_GOAL[4];
}auto_route;
void fld_init(void);
void reset_fcu(void);
void fld_init_fcu_ram(void);
int fld_init_pclk_notification(void);
int fcu_eraze_db(unsigned long top_addr_db);
int fld_eraze_2KB(unsigned long addr);
int fld_blank_check_2KB(unsigned long addr);
int wait_FRDY(unsigned int t);
int fld_program_8byte(unsigned long addr,UDAuS *fdata);
int fld_enable_read(void);
int fld_program_route(unsigned long addr,auto_route *r);
void fld_debug_route(unsigned long addr);

//void dataflash_write(void);

#define FLD_DEBUG_WRITE() {\
	fcu_eraze_db(TOP_ADDR_DB01);\
	fld_program_route(TOP_ADDR_DB01,&red);\
	fcu_eraze_db(TOP_ADDR_DB02);\
	fld_program_route(TOP_ADDR_DB02,&red);\
	fcu_eraze_db(TOP_ADDR_DB03);\
	fld_program_route(TOP_ADDR_DB03,&red);\
	fcu_eraze_db(TOP_ADDR_DB04);							\
	fld_program_route(TOP_ADDR_DB04,&red);\
	fcu_eraze_db(TOP_ADDR_DB05);\
	fld_program_route(TOP_ADDR_DB05,&blue);\
	fcu_eraze_db(TOP_ADDR_DB06);\
	fld_program_route(TOP_ADDR_DB06,&blue);\
	fcu_eraze_db(TOP_ADDR_DB07);\
	fld_program_route(TOP_ADDR_DB07,&blue);\
	fcu_eraze_db(TOP_ADDR_DB00);\
	fld_program_route(TOP_ADDR_DB00,&blue);\
}


#endif