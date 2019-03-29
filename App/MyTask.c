#include "FreeRTOS.h"
#include "task.h"

#include "MyTask.h"
#include "SysGpio.h"
#include "SysUart.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С
#define START_STK_SIZE 		128
//������
TaskHandle_t StartTask_Handler;
//������
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
	xTaskCreate((TaskFunction_t )start_task,            //������
				(const char*    )"start_task",          //��������
				(uint16_t       )START_STK_SIZE,        //�����ջ��С
				(void*          )NULL,                  //���ݸ��������Ĳ���
				(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
				(TaskHandle_t*  )&StartTask_Handler);   //������              
	vTaskStartScheduler();          //�����������
}
//��ʼ����������
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();			//�����ٽ���
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
	vTaskDelete(StartTask_Handler);	//ɾ����ʼ����
	taskEXIT_CRITICAL();			//�˳��ٽ���
}


void led0_task(void *pvParameters)
{
	u8 i;
	while(1)
	{
		for(i=0;i<2;i++)
		{
			SET_GPIO_H(LED1_GPIO);
			delay_xms(20);
			SET_GPIO_L(LED1_GPIO);
			delay_xms(20);
		}
		vTaskDelay(500);
	}
}   

void led1_task(void *pvParameters)
{
	while(1)
	{
		if(UsartType.RX_flag)		// Receive flag
		{
			UsartType.RX_flag=0;	// clean flag
			HAL_UART_Transmit_DMA(&huart1, UsartType.RX_pData, UsartType.RX_Size);
		}
		vTaskDelay(1);
	}
}











