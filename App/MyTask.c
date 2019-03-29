#include "FreeRTOS.h"
#include "task.h"
#include "Memory.h"
#include "MyTask.h"
#include "SysGpio.h"
#include "SysUart.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小
#define START_STK_SIZE 		128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

#define LED0_TASK_PRIO		2
#define LED0_STK_SIZE 		50  
TaskHandle_t LED0Task_Handler;
void led0_task(void *pvParameters);

#define LED1_TASK_PRIO		3
#define LED1_STK_SIZE 		50  
TaskHandle_t LED1Task_Handler;
void led1_task(void *pvParameters);

void start_system()
{
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
				(const char*    )"start_task",          //任务名称
				(uint16_t       )START_STK_SIZE,        //任务堆栈大小
				(void*          )NULL,                  //传递给任务函数的参数
				(UBaseType_t    )START_TASK_PRIO,       //任务优先级
				(TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
	vTaskStartScheduler();          //开启任务调度
}
//开始任务任务函数
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();			//进入临界区
	xTaskCreate((TaskFunction_t )led0_task,
				(const char*    )"led0_task",
				(uint16_t       )LED0_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )LED0_TASK_PRIO,
				(TaskHandle_t*  )&LED0Task_Handler);

	xTaskCreate((TaskFunction_t )led1_task,
				(const char*    )"led1_task",
				(uint16_t       )LED1_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )LED1_TASK_PRIO,
				(TaskHandle_t*  )&LED1Task_Handler);
	vTaskDelete(StartTask_Handler);	//删除开始任务
	taskEXIT_CRITICAL();			//退出临界区
}


void led0_task(void *pvParameters)
{
	u8 i;
	while(1)
	{
		for(i=0;i<50;i++)
		{
			SET_GPIO_H(LED1_GPIO);
			delay_us(20);
			SET_GPIO_L(LED1_GPIO);
			delay_us(20);
		}
		vTaskDelay(100);
	}
}   

void led1_task(void *pvParameters)
{
	u8 buf[11];
	while(1)
	{
//		if(UsartType.RX_flag)		// Receive flag
//		{
//			UsartType.RX_flag=0;	// clean flag
//			HAL_UART_Transmit_DMA(&huart1, UsartType.RX_pData, UsartType.RX_Size);
//		}
		if(!fifo_empty(&Uart1Fifo))
		{
			memset(buf,0,sizeof(buf));
			if(fifo_gets(&Uart1Fifo,buf,10))
			{
				//HAL_UART_Transmit_DMA(&huart1,buf,10);
				printf("printf==%s\n",buf);
				myprintf(&huart1,"dma printf=%s\n",buf);
			}
		}
		vTaskDelay(50);
	}
}











