/********************************************************/
//
//  �T�v
//      �|�[�g�֘A
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __IO_H__
#define __IO_H__



/********************************************************/
//�|�[�g�̖��� ����ۂ�
//	CN1									CN2			
//	1	PD0		POWER					1	PA0		PWM6A�@�������[�h20kHz	
//	2	PD1		BUZZER 					2	PA1		PWM6B�@�������[�h20kHz	
//	3	PD2		AIR						3	PA2		PWM6C�@�������[�h20kHz	
//	4	PD3		AIR						4	PA3		PWM6D�@�������[�h20kHz	
//	5	PD4		AIR						5	PA4		laser
//	6	PD5		cet						6	PA5		AIR
//	7	PD6		cet						7	PA6		AIR	
//	8	PD7								8	PA7		AIR
//	9	PE0		LIMIT_SW0 				9	PB0		PWM9A�@�������[�h20kHz		
//	10	PE1		LIMIT_SW1				10	PB1		PWM9C�@�������[�h20kHz		
//	11	PE2		LIMIT_SW2				11	PB2		mode	
//	12	PE3		LIMIT_SW3				12	PB3	    mode
//	13	PE4		LIMIT_SW4				13	PB4		PWM10A	
//	14	PE5		LIMIT_SW5				14	PB5		PWM10C	
//	15	PE6		LIMIT_SW6				15	PB6			
//	16	PE7		LIMIT_SW7				16	PB7			
//	17	P40		AN0						17	PC0		MTCLKG-A	
//	18	P41		AN1						18	PC1		MTCLKH-A	
//	19	P42		AN2						19	PC2     MTCLKE-A	
//	20	P43		AN3						20	PC3		MTCLKF-A	
//	21	P44		AN4						21	PC4		MTCLKC-B	
//	22	P45		AN5						22	PC5		MTCLKD-B	
//	23	P46		AN6						23	PC6		MTCLKA-B	
//	24	P47		AN7						24	PC7		MTCLKB-B
//	25	P30		RxD1	PC				25	P20		TxD0 	�R���g���[��
//	26	P31								26	P21		RxD0 	�R���g���[��
//	27	P32		PWM0C�@�������[�h20kHz	27	P22		SCK0
//	28	P33		PWM0D�@�������[�h20kHz	28	P23		
//	29	P34		PWM0A�@�������[�h20kHz	29	P24		PWM4A�@�������[�h20kHz
//	30	P35								30	P25		PWM4C�@�������[�h20kHz
//	31	P05								31	P26		TxD1 	PC
//	32	P07								32	P27		SCK1
//	33	AVCC							33	P50		TxD2-B  �W���C��
//	34	EMLE							34	P51		SCK2
//	35	MD1								35	P52		RxD2-B �W���C��
//	36	RES								36	P53		
//	37	VCC								37	P54			
//	38	GND								38	P55			
//	39	VCC								39	P12		
//	40	GND								40	P13		PWM0B�@�������[�h20kHz

/********************************************************/
#define SET_P_INPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =0; port##.PCR.BIT.B##pin =1; port##.ICR.BIT.B##pin  =1;}
//ex)SET_PULL_INPUT(PORTE,7); // �v���A�b�v�t���͐ݒ�
#define SET_OUTPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =1;}
#define SET_P_INPUT(port) { port##.DDR.BYTE =0x00; port##.PCR.BYTE =0xFF; port##.ICR.BYTE  =0xFF;}
#define SET_INPUT(port) { port##.DDR.BYTE =0x00; port##.ICR.BYTE  =0xFF;}
#define SET_INPUT_PIN(port,pin) { port##.DDR.BIT.B##pin =0; port##.ICR.BIT.B##pin  =1;}
#define SET_OUTPUT(port) { port##.DDR.BYTE =0xFF;}
#define INPUT_PIN(port,pin) (port##.PORT.BIT.B##pin)
#define OUTPUT_PIN(port,pin) (port##.DR.BIT.B##pin)
#define PWM_PIN(ch,port) (MTU##ch##.TGR##port)

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �|�[�g�֘A �v���g�^�C�v�錾
/********************************************************/
//void power_init(void);							// ���[�^�E�G�A�[�̓d�������p�̏����ݒ�
//void buzzer_init(void);							// BUZZER�̏����ݒ�
//void led_init(void);							// LED�̏����ݒ�
//void mode_init(void);							// ���[�h�I���̏����ݒ�
//void button_init(void);							// �{�^���̏����ݒ�
//void limit_init(void);							// LIMIT�̏����ݒ�

//void front_limit_init(void);					// �}�V���̑O�̃��~�b�g�̏����ݒ�
//void back_limit_init(void);						// �}�V���̌�̃��~�b�g�̏����ݒ�

void io_init(void);		 						// PIN�̏����ݒ�

//void buzzer_on(void);							// BUZZER��ON�ɂ���
//void buzzer_off(void);							// BUZZER��OFF�ɂ���

//void power_on(void);							// �d���������s��
//void power_off(void);							// �d���������s��Ȃ�

//void led_on(void);								// LED��ON�ɂ���
//void led_off(void);								// LED��OFF�ɂ���
//void led_ctrl(char number);						// LED�̓_�������R���g���[������

//char mode(void);								// ���[�h�I��

//char button(void);								// �{�^���F��

//char limit(void);								// ���~�b�g�F��

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �|�[�g�֘A �萔��`
/********************************************************/
#define OPEN	1
#define CLOSE	0
#define ON	1
#define OFF	0


/*----------------------------------------------*/
void motor_o(double raw_duty);					// MOTOR_o�̐ݒ�
void motor_l(double raw_duty);					// MOTOR_l�̐ݒ�
void motor_r(double raw_duty);					// MOTOR_r�̐ݒ�
void motor_servo(int state);					// SERVO�̐ݒ�
void leaf_collect_hand(char state);				// AIR�֐�(���[�t����n���h)
void leaf_esta_hand(char state);				// AIR�֐�(���[�t�ݒu�n���h)
void motor_L_arm(double raw_duty);				//L�A�[��
void motor_fish(double raw_duty);				//�ފ�
//void motor_tower_L_stopper(double raw_duty);	//L�^���[�X�g�b�p�[
//void motor_front_shift(double raw_duty);		//�S�̂�O�ɏo�����
#endif // __IO_H__