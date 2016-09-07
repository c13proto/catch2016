#ifndef __DMA__
#define  __DMA__

#define DMA_ENABLE() {}
#define DMA_INIT(ch,form,to,cnt) {\
DMAC0.DMCNT.BIT.DTE=0/*転送禁止*/\
DMAC0.DMSAR.WORD=from;/*DMA転送元アドレス*/\
DMAC0.DMDAR.WORD=to;/*DMA転送先アドレス*/\
DMAC0.DMCRB.WORD=0x3FF;/*最大0->1024*/\
DMAC0.DMTMD.BIT.DCTG=0x00;/*ソフトウェアで転送要求*/\
DMAC0.DMTMD.BIT.SZ=0x2;//32bit転送*/\
DMAC0.DMTMD.BIT.MD=0x2; //ブロック転送*/\
DMAC0.DMINT.BIT.DTIE = 1;//転送終了割り込み許可*/\
DMAC0.DMCRA.BYTE.DMCRAL=cnt;/**/\

DMAC0.DMCNT.BIT.DTE=1/*転送許可*/\
}

DMA_INIT(0,0xFEFFE000,007F8000,8);

//65535-57344
#endif