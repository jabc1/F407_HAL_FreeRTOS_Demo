#include "Debugprintf.h"

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
//��ʹ��DMA����
int fputc(int ch,FILE *f)
{
	while((USART2->SR & 0x40) == 0);
	USART2->DR = (uint8_t)ch;
	return ch;
}

////ʹ��DMA����
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
static uint8_t print_buffer[PRINTF_BUF_SIZE];//��ӡ����
//����һ��DMA����
//huart:���ھ��
//pData�����������ָ��
//Size:�����������
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (uint32_t)pData, (uint32_t)&huart->Instance->DR, Size);//����DMA����
    huart->Instance->CR3 |= USART_CR3_DMAT;//ʹ�ܴ���DMA����
}

void USART_DMA_SendData(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	while(!(__HAL_DMA_GET_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7)));       //�ȴ�DMA_FLAG_TCIF3_7�������
	__HAL_DMA_CLEAR_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7);              //���DMA_FLAG_TCIF3_7������ɱ�־
	HAL_UART_DMAStop(huart);                                         //��������Ժ�رմ���DMA
	MYDMA_USART_Transmit(huart, pData, Size);   //����DMA����
}
/**
*printf��ӡ����
* @param format	printf��ʽ
*/
void printf_dma(const char *format, ...)
{
	uint32_t length;
	va_list args; 
	while((USART1->SR&0X40)==0);
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);//��ʽ������
	//USART_DMA_SendData(&huart1, print_buffer, length);//���� 
	HAL_UART_Transmit_DMA(&huart1,print_buffer,length);
	va_end(args);
}









