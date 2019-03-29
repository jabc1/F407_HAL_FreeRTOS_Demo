#ifndef _sys_uart_h
#define _sys_uart_h
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"
#include "arm_base_define.h"

#define RX_LEN		2048
typedef struct
{
	u8  RX_flag:1;        //IDLE receive flag
	u16 RX_Size;          //receive length
	u8  RX_pData[RX_LEN]; //DMA receive buffer
}USART_RECEIVETYPE;  

extern USART_RECEIVETYPE UsartType;
extern UART_HandleTypeDef huart1;


void MX_USART1_UART_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
void UsartReceive_IDLE(UART_HandleTypeDef *huart);

#endif



