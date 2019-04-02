#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		Uart1Len			1024*3+1
#define		TagCacheLen			1024*3+1//���ڻ����ǩ��Ϣ
#define		TagLen				1024*2+1//���ڻ��������������Ϣ

extern FIFO_t	Uart1Fifo;
extern u8 Uart1Buf[];

extern FIFO_t TagFifo;
extern u8 TagCacheBuf[];

extern FIFO_t TagFifo;
extern u8 TagBuf[];

void Init_memory(void);

#endif



