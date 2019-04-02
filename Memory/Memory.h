#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		Uart1Len			1024*3+1
#define		TagCacheLen			1024*3+1//用于缓存标签信息
#define		TagLen				1024*2+1//用于缓存解析出来的信息

extern FIFO_t	Uart1Fifo;
extern u8 Uart1Buf[];

extern FIFO_t TagFifo;
extern u8 TagCacheBuf[];

extern FIFO_t TagFifo;
extern u8 TagBuf[];

void Init_memory(void);

#endif



