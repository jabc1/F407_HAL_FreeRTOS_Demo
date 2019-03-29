#include "main.h"
#include "SysClock.h"
#include "arm_base_define.h"
#include "SysTime.h"
#include "SysGpio.h"
#include "MyTask.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_TIM3_Init();
	MX_GPIO_Init();
	start_system();
	while(1)
	{
//		SET_GPIO_H(LED1_GPIO);
//		HAL_Delay(200);
//		SET_GPIO_L(LED1_GPIO);
//		HAL_Delay(200);
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}






