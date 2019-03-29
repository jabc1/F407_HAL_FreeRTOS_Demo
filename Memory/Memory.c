#include "Memory.h"

FIFO_t Uart1Fifo;
u8 Uart1Buf[Uart1Len];

FIFO_t TagFifo;
u8 TagBug[TagLen];


void Init_memory()
{
	fifo_init(&Uart1Fifo,Uart1Buf,Uart1Len);
	fifo_init(&TagFifo,TagBug,TagLen);
}









