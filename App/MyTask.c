#include "FreeRTOS.h"
#include "task.h"
#include "Memory.h"
#include "MyTask.h"
#include "SysGpio.h"
#include "SysUart.h"
#include "Debugprintf.h"
#include "Command.h"
#include "Analysis.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小
#define START_STK_SIZE 		128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

#define MASTER1_TASK_PRIO		2
#define MASTER1_STK_SIZE 		50
TaskHandle_t MASTER1Task_Handler;
void master1_task(void *pvParameters);

#define MASTER2_TASK_PRIO		3
#define MASTER2_STK_SIZE 		50
TaskHandle_t MASTER2Task_Handler;
void master2_task(void *pvParameters);

#define MASTER3_TASK_PRIO		3
#define MASTER3_STK_SIZE 		50
TaskHandle_t MASTER3Task_Handler;
void master3_task(void *pvParameters);

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
	xTaskCreate((TaskFunction_t )master1_task,
				(const char*    )"master1_task",
				(uint16_t       )MASTER1_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER1_TASK_PRIO,
				(TaskHandle_t*  )&MASTER1Task_Handler);

	xTaskCreate((TaskFunction_t )master2_task,
				(const char*    )"master2_tas",
				(uint16_t       )MASTER2_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER2_TASK_PRIO,
				(TaskHandle_t*  )&MASTER2Task_Handler);

	xTaskCreate((TaskFunction_t )master3_task,
				(const char*    )"master3_tas",
				(uint16_t       )MASTER3_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER3_TASK_PRIO,
				(TaskHandle_t*  )&MASTER3Task_Handler);
	vTaskDelete(StartTask_Handler);	//删除开始任务
	taskEXIT_CRITICAL();			//退出临界区
}


void master1_task(void *pvParameters)
{
	//u16 time = 0;
	u8 i=0;
	//one_cmd();
	while(1)
	{
		i = !i;
		if(i)
		{
			SET_GPIO_H(LED1_GPIO);
			SET_GPIO_L(LED2_GPIO);
		}
		else
		{
			SET_GPIO_L(LED1_GPIO);
			SET_GPIO_H(LED2_GPIO);
		}
		//printf_dma("uart1 dma printf=%04d\n",time++);
		vTaskDelay(100);
	}
}

void master2_task(void *pvParameters)
{
	u8 t1,t2,t3;
	u8 len,lentemp;
	u8 buf[10];
	while(1)
	{
		if(!fifo_empty(&TagFifo))
		{
			memset(buf,0,sizeof(buf));
			tag_out_fifo(&TagFifo,&t1,&t2,&t3,&buf[0]);
			printf_dma("%d%d%d%s",t1,t2,t3,buf);
			//printf("%d%d%d%s",t1,t2,t3,buf);
		}
		vTaskDelay(30);
	}
}

void master3_task(void *pvParameters)
{
	u8 len,lentemp;
	u8 buf[10];
	while(1)
	{
		if(!fifo_empty(&Uart1Fifo))
		{
			if(info_out_fifo(&Uart1Fifo,&len,&tagdata.data[0]))
			{
				find_tag(tagdata.data,&lentemp,&tagdata.tag[0]);
			}
		}
		vTaskDelay(20);
	}
}









