#include "Debugprintf.h"

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
//不使用DMA发送
int fputc(int ch,FILE *f)
{
	while((USART2->SR & 0x40) == 0);
	USART2->DR = (uint8_t)ch;
	return ch;
}

////使用DMA发送
//void myprintf(UART_HandleTypeDef *huart, char *fmt,...)
//{
//	char buffer[200];
//	uint8_t len=0;
//	va_list arg_ptr;
//	va_start(arg_ptr,fmt);
//	len = vsnprintf(buffer,200, fmt, arg_ptr);
//	while(HAL_BUSY == HAL_UART_Transmit_DMA(huart,(uint8_t*)buffer, len));
//	HAL_ResumeTick();
//	va_end(arg_ptr);
//}
#define PRINTF_BUF_SIZE     512
static uint8_t print_buffer[PRINTF_BUF_SIZE];//打印缓存
//开启一次DMA传输
//huart:串口句柄
//pData：传输的数据指针
//Size:传输的数据量
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (uint32_t)pData, (uint32_t)&huart->Instance->DR, Size);//开启DMA传输
    huart->Instance->CR3 |= USART_CR3_DMAT;//使能串口DMA发送
}

void USART_DMA_SendData(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	while(!(__HAL_DMA_GET_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7)));       //等待DMA_FLAG_TCIF3_7传输完成
	__HAL_DMA_CLEAR_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7);              //清除DMA_FLAG_TCIF3_7传输完成标志
	HAL_UART_DMAStop(huart);                                         //传输完成以后关闭串口DMA
	MYDMA_USART_Transmit(huart, pData, Size);   //启动DMA传输
}
/**
*printf打印函数
* @param format	printf格式
*/
void printf_dma(const char *format, ...)
{
	uint32_t length;
	va_list args; 
	while((USART1->SR&0X40)==0);
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);//格式化内容
	//USART_DMA_SendData(&huart1, print_buffer, length);//发送 
	HAL_UART_Transmit_DMA(&huart1,print_buffer,length);
	va_end(args);
}









