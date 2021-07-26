/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "mb.h"
#include "mbport.h"
extern void CAN_Send_Message(uint8_t BANID);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ModbusTask */
osThreadId_t ModbusTaskHandle;
const osThreadAttr_t ModbusTask_attributes = {
  .name = "ModbusTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CanTask */
osThreadId_t CanTaskHandle;
const osThreadAttr_t CanTask_attributes = {
  .name = "CanTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CmdTask */
osThreadId_t CmdTaskHandle;
const osThreadAttr_t CmdTask_attributes = {
  .name = "CmdTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myQueue */
osMessageQueueId_t myQueueHandle;
const osMessageQueueAttr_t myQueue_attributes = {
  .name = "myQueue"
};
/* Definitions for myMutex */
osMutexId_t myMutexHandle;
const osMutexAttr_t myMutex_attributes = {
  .name = "myMutex"
};
/* Definitions for myBinarySem */
osSemaphoreId_t myBinarySemHandle;
const osSemaphoreAttr_t myBinarySem_attributes = {
  .name = "myBinarySem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Modbus(void *argument);
void Can(void *argument);
void Cmd(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myMutex */
  myMutexHandle = osMutexNew(&myMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem */
  myBinarySemHandle = osSemaphoreNew(1, 1, &myBinarySem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue */
  myQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ModbusTask */
  ModbusTaskHandle = osThreadNew(Modbus, NULL, &ModbusTask_attributes);

  /* creation of CanTask */
  CanTaskHandle = osThreadNew(Can, NULL, &CanTask_attributes);

  /* creation of CmdTask */
  CmdTaskHandle = osThreadNew(Cmd, NULL, &CmdTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Modbus */
/**
* @brief Function implementing the ModbusTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Modbus */
void Modbus(void *argument)
{
  /* USER CODE BEGIN Modbus */
  /* Infinite loop */
	eMBInit(MB_RTU, 0x01, 1, 115200, MB_PAR_NONE);
	eMBEnable(  );
  for(;;)
  {
			(void)eMBPoll();
    osDelay(1);
  }
  /* USER CODE END Modbus */
}

/* USER CODE BEGIN Header_Can */
/**
* @brief Function implementing the CanTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Can */
void Can(void *argument)
{
  /* USER CODE BEGIN Can */
  /* Infinite loop */
  for(;;)
  {
		for(int i=0; i<8;i++)
		{

		CAN_Send_Message(0x1401013f);
			
		}
		
    osDelay(1);
  }
  /* USER CODE END Can */
}

/* USER CODE BEGIN Header_Cmd */
/**
* @brief Function implementing the CmdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Cmd */
void Cmd(void *argument)
{
  /* USER CODE BEGIN Cmd */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Cmd */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
