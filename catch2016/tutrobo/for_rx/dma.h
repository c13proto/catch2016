#ifndef __DMA__
#define  __DMA__

#define DMA_ENABLE() {}
#define DMA_INIT(ch,form,to,cnt) {\
DMAC0.DMCNT.BIT.DTE=0/*�]���֎~*/\
DMAC0.DMSAR.WORD=from;/*DMA�]�����A�h���X*/\
DMAC0.DMDAR.WORD=to;/*DMA�]����A�h���X*/\
DMAC0.DMCRB.WORD=0x3FF;/*�ő�0->1024*/\
DMAC0.DMTMD.BIT.DCTG=0x00;/*�\�t�g�E�F�A�œ]���v��*/\
DMAC0.DMTMD.BIT.SZ=0x2;//32bit�]��*/\
DMAC0.DMTMD.BIT.MD=0x2; //�u���b�N�]��*/\
DMAC0.DMINT.BIT.DTIE = 1;//�]���I�����荞�݋���*/\
DMAC0.DMCRA.BYTE.DMCRAL=cnt;/**/\

DMAC0.DMCNT.BIT.DTE=1/*�]������*/\
}

DMA_INIT(0,0xFEFFE000,007F8000,8);

//65535-57344
#endif