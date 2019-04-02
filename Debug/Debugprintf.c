/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Debugprintf.c
Description		: ʵ�ִ��ڴ�ӡ�ض������⣬�����Ժ��ʽ�����
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
* @Description	:��ʹ��dma���д����ض���
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
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
* @Description	:ʹ��dma���д����ض���
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
	while((USART1->SR&0X40)==0);//�ȴ����ڷ������
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);//��ʽ������
	while(HAL_BUSY == HAL_UART_Transmit_DMA(&huart1,(u8 *)print_buffer,length));//�ȴ��������
	va_end(args);
}









