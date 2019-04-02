/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Debugprintf.c
Description		: 实现串口打印重定向问题，方便以后格式化输出
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-30
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Debugprintf.h"
/*******************************************************************************
* @Function		:printf(const char *format, ...)
* @Description	:不使用dma进行串口重定向
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数
struct __FILE
{
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)
{
	x = x;
}
int fputc(int ch,FILE *f)
{
	while((USART1->SR & 0x40) == 0);
	USART1->DR = (uint8_t)ch;
	return ch;
}

/*******************************************************************************
* @Function		:printf_dma()
* @Description	:使用dma进行串口重定向
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void printf_dma(const char *format, ...)
{
	char print_buffer[512];
	u16 length;
	va_list args; 
	while((USART1->SR&0X40)==0);//等待串口发送完成
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);//格式化内容
	while(HAL_BUSY == HAL_UART_Transmit_DMA(&huart1,(u8 *)print_buffer,length));//等待发送完成
	va_end(args);
}









