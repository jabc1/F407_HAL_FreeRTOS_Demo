#include "MyTask.h"
#if 1
#include "FreeRTOS.h"
#include "task.h"
#include "SysGpio.h"

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
    taskENTER_CRITICAL();           //�����ٽ���
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
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}


void led0_task(void *pvParameters)
{
	while(1)
	{
		SET_GPIO_H(LED1_GPIO);
		vTaskDelay(50);
		SET_GPIO_L(LED1_GPIO);
		vTaskDelay(50);
	}
}   

void led1_task(void *pvParameters)
{
	while(1)
	{
		SET_GPIO_L(LED2_GPIO);
		vTaskDelay(200);
		SET_GPIO_H(LED2_GPIO);
		vTaskDelay(200);
	}
}
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
	RunSysTick();
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
void RunSysTick()
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{
		xPortSysTickHandler();
	}
}


#endif







