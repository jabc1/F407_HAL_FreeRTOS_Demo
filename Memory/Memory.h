#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		Uart1Len		1024*2+1
#define		TagLen			1024*5+1

extern FIFO_t	Uart1Fifo;
extern u8 Uart1Buf[];

extern FIFO_t TagFifo;
extern u8 TagBug[TagLen];

void Init_memory(void);

#endif



