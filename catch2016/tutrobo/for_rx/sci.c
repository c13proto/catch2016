/********************************************************/
//
//  �T�v
//      SCI�֘A
//	�X�V����
//		2013/04/26
//  �쐬��
//		K.yamada @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//�}�C�R���̐ݒ�

/********************************************************/
//  ���O      
//		sci_init	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI�̏����ݒ�
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void sci_init() {	
	
	IOPORT.PFFSCI.BIT.SCI2S = 1;//sci2�̓��o�̓|�[�g��B�ɐݒ�
/*                ch, baudrate, �p���e�B,�X�g�b�v�r�b�g,�D��x   */
 	SCI_ASYNC_INIT(0, B_19200 , NONE, ONE_STOPBIT, 13);		/* SCI0�̏����� (PScon_AVR�p)*/
	SCI_ASYNC_INIT(1, B_19200 , NONE, ONE_STOPBIT, 11);		/* SCI1�̏����� (PC�ƒʐM�p) */
	SCI_ASYNC_INIT(2, B_19200, NONE, ONE_STOPBIT, 12);		/* SCI2�̏����� (PScon_AVR�p) */
//	SCI_ASYNC_INIT(2, B_115200, NONE, ONE_STOPBIT, 15);		/* SCI2�̏����� (�W���C���p) */11
}
/********************************************************/
//  ���O      
//		send_c
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void send_c(char c){
	SCI_SEND(0,c);
}
/********************************************************/
//  ���O      
//		rec_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI0�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rec_c(void){
	return SCI_RECV(0);
}
/********************************************************/
//  ���O      
//		put_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void put_c(char c){
	SCI_SEND(1,c);											
}
/********************************************************/
//  ���O      
//		put_s	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1���當���񑗐M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
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
//  ���O      
//		get_c	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI1�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		��M�����f�[�^
//  �쐬��
//		TUTrobo
//
/********************************************************/
char get_c(void){				
	return SCI1.RDR;
}
/********************************************************/
//  ���O      
//		send_c
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2���瑗�M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void send_c2(char c){
	SCI_SEND(2,c);
}
/********************************************************/
//  ���O      
//		rec_c2	
//  �T�v
//      SCI�֘A
//  �@�\����
//		SCI2�����M
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
char rec_c2(void){
	return SCI_RECV(2);
}
/********************************************************/	
//  �T�v
//      SCI�֘A
//  �@�\����
//		printf�Ŏg���^��������
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
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
//  ���O      
//		printf	
//  �T�v
//      SCI�֘A
//  �@�\����
//		���������͂���convert�ɂ킽���B
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
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

	va_start(list, str);									//�ψ����ɃA�N�Z�X����O�̏�������
	while(1){
		while((c = *str++) != '%'){							//%���o�Ă���܂ł܂Ń��[�v
			if(c == '\0')return(10);						//NULL�������炨���??
			if(c == '\n')put_c('\r');						//���s
			put_c(c);										//�\��
		}
		table = clear(table);								//table������
		p = 0;												//p������
//      if((*str)=='%')SCI3_OUT_DATA(*str++);   			// '%'�o��
		while(1){
			c = *str++;										//���̕�����GO�I	
 			if(c >= '0' && c <='9'){						//0�`9�܂ł�char�̂Ƃ�
				table.z[p] *= 10;table.z[p] += c - '0';		//�\�������錅����F��
			}else if((c == '.') && (p == 0))p++;			//c��'.'��p��0�̂Ƃ��@p��1
			else if(c == 'l')table.l = 1;					//long int �Ȃ�
			else{
				switch(c){								
					case 'd':								//d�̏ꍇ
					case 'D':								//D�̏ꍇ
						table.base = 10L;					//convert�Ŏg���@����萔
						table.var = va_arg(list, int);		//�ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
						if((long)table.var < 0){			//�l�����̎�
							table.m = 1;					//convert�Ŏg�����̐���1����
							table.var *= -1;				//convert�Ń}�C�i�X�ɂȂ�Ȃ��悤�ɂ��邽��
						}
						convert(table);						//�\��
						break;								//break
					case 'f':								//f�̏ꍇ
					case 'F':								//F�̏ꍇ
						table.base = 10L;					//convert�Ŏg���@����萔�@�i����������int�Ɠ������e�j			
						v_double = va_arg(list, double);	//�ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
						if(v_double < 0){					//�l�����̎�
							table.m = 1;					//convert�Ŏg�����̐���1����
							v_double *= -1;					//convert�Ń}�C�i�X�ɂȂ�Ȃ��悤�ɂ��邽��
						}
						table.var = (long)v_double;			//���������������	
						table.z[0] -= table.z[1]+1;			//���������̌��������i+�P��.�̕����j
						convert(table);						//�\���@�i������ւ�܂�int�Ɠ������e�j
						put_c('.');							//'.'��\��������
						table.z[0] = 1;						//�����������ꌅ�ɂ���
						table.m = 0;						//table.m��������		
						if(table.z[1]==0)table.z[1]=6;		//table.z[1]��0�̂Ƃ������_�ȉ�6����\������
						for(i=0;i<(table.z[1]-1);i++){		
							v_double *= 10;					//�����_�ȉ��̌��𐮐������ɂ���
							table.var = (long)v_double % 10;//���������ɂ���������
							convert(table);					//�\��
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
					default:str--;							//���������O�ɖ߂��@���̂܂ܕ\������
				}
				break;										//while���ʂ���
			}
		}
	}
	va_end(list);											//�ψ����ɃA�N�Z�X������̏I������
	return(10);												//?
}

/********************************************************/
//  ���O      
//		convert	
//  �T�v
//      SCI�֘A
//  �@�\����
//		printf�����������������\��
//  �p�����^����
//		�Ȃ�
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void convert(p_table table)
{
 	char s[20];												//�\���p�̕�����
 	int i=19,cnt=0;											//i���ǂ��ɂ��̕���������̂������߂�J�E���g�@cnt���\���������Ԃ����߂�J�E���g

	for(i=0;i<20;i++)s[i]=' ';								//�󔒂̂�20�����
	i=19;													//i������������
	if(table.var == 0){										//���l��0�̂Ƃ�
		s[i--] = '0';										//s[19]��'0'��������
		cnt++;												//�\����Ԃ�1���₷
	}
	while(table.var){										//table.var��0�ȊO�̎����[�v
		s[i--] = (table.var % table.base) + '0';			//int����char�ɕϊ�
		table.var /= table.base;							//���̌���GO!
		cnt++;												//�\����Ԃ�1���₷
	}
	if(table.m)s[i] = '-';									//table.m��1�̂Ƃ��}�C�i�X�̕���������
	cnt += table.m;											//table.m��1�̂Ƃ��\����Ԃ�1���₷
	if(cnt < table.z[0])cnt = table.z[0];					//table.z[0]��cnt���傫���ꍇcnt��table.z[0]�Ɠ����ɂ���@�\�����������̌����ǂݍ��񂾐��������������ꍇ�󔒂ɂ���B
	for(i=20-cnt;i<20;i++){									//������𔽓]�����Ȃ���cnt���̋�ԕ����[�v
		put_c(s[i]);										//�\��
	}
	
}

/********************************************************/
//  ���O      
//		itoa
//  �T�v
// 		SCI�֐�
//  �@�\����
//		int��char�ϊ�
//  �p�����^����
//		value	int�^�̕�����
//		buff[]	int�^�̕�����char�^�̕�����ɂȂ�i�[�����
//		radix	���i�����@�Ⴆ��10�i���Ȃ�10
//  �߂�l
//		�Ȃ�
//  �쐬��
//		TUTrobo
//
/********************************************************/
void itoa(int value,char buff[],int radix)
{
	static const char table[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char *head = buff;
	char *tail = buff;
	char temp;
	
	//�}�C�i�X�����𕶎���ɕϊ�
	if(value<0){
		*tail++='-';
		value=-value;
	}
	//�����l�𕶎���ɕϊ�
	if(value==0){
 		*tail++='0';
	}
	else{
		for(head=tail;value!=0;value=value/radix){
			 *tail++ = table[value%radix];
 		}
	}
	*tail='\0';
	//������̍��E����ւ�
	for(tail--;head<tail;head++,tail--){
		temp=*head;
		*head=*tail;
		*tail=temp;
	}
}