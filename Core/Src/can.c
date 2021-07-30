/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "mb.h"
#include "mbport.h"
CAN_HandleTypeDef hcan;
CAN_FilterTypeDef  CAN_FilterInitStructure;


CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8] = {0};
uint8_t               RxData[8] = {0};
uint32_t              TxMailbox;
unsigned char data[64];
//#define REG_COILS_SIZE      512
//extern unsigned char ucRegCoilsBuf[REG_COILS_SIZE / 8];
//extern USHORT usRegHoldingBuf[REG_HOLDING_NREGS];
extern UCHAR  ucSCoilBuf[S_COIL_NCOILS/8];
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 9;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_7TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = ENABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
	 CAN_FilterInitStructure.FilterBank=1;//指定过滤器为1
  CAN_FilterInitStructure.FilterMode=CAN_FILTERMODE_IDMASK;//指定过滤器为标识符屏蔽位模式
  CAN_FilterInitStructure.FilterScale=CAN_FILTERSCALE_32BIT;//过滤器位宽为32位
  CAN_FilterInitStructure.FilterIdHigh=0x0000;// 过滤器标识符的高16位值
  CAN_FilterInitStructure.FilterIdLow=0x0000;//	 过滤器标识符的低16位值
  CAN_FilterInitStructure.FilterMaskIdHigh=0x0000;//过滤器屏蔽标识符的高16位值
  CAN_FilterInitStructure.FilterMaskIdLow=0x0000;//	过滤器屏蔽标识符的低16位值
  CAN_FilterInitStructure.FilterFIFOAssignment=CAN_RX_FIFO0;// 设定了指向过滤器的FIFO为0
  CAN_FilterInitStructure.FilterActivation=ENABLE;// 使能过滤器
	CAN_FilterInitStructure.SlaveStartFilterBank = 14;
	

	if (HAL_CAN_ConfigFilter(&hcan, &CAN_FilterInitStructure) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
 
  /* Start the CAN peripheral */
  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
 
  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
	
  /* Activate CAN TX notification */
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
	
//  TxHeader.ExtId = 0x1401013F;
//  TxHeader.RTR = CAN_RTR_DATA;
//  TxHeader.IDE = CAN_ID_EXT;
//  TxHeader.DLC = 8;
//  TxHeader.TransmitGlobalTime = DISABLE;


  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Send_Message(int BANID)
{   
  	switch(BANID)
		{	case 0:
				TxHeader.ExtId = 0x1401013F;
				break;
			case 1:
				TxHeader.ExtId = 0x1401023F;
				break;
			case 2:
				TxHeader.ExtId = 0x1401033F;
				break;
			case 3:
				TxHeader.ExtId = 0x1401043F;
				break;
			case 4:
				TxHeader.ExtId = 0x1401053F;
				break;
			case 5:
				TxHeader.ExtId = 0x1401063F;
				break;
			case 6:
				TxHeader.ExtId = 0x1401073F;
				break;
			case 7:
				TxHeader.ExtId = 0x1401083F;
				break;
				}
		
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.IDE = CAN_ID_EXT;
			TxHeader.DLC = 8;
			TxHeader.TransmitGlobalTime = DISABLE;


//   for(int i=0;i<64;i++)
// {
//     unsigned char c=0;
// 		for(int loop=0;loop<8;loop++)
// 	{
// 		c=(usRegHoldingBuf[loop+8*i]<<(7-loop))|c;
// 	}
//     data[i]=c;	
//}
//	for(int loop=0;loop<8;loop++)
// 	{
// 	TxData[loop] = data[loop+(8*BANID)];
// 	}


	for(int loop=0;loop<8;loop++)
 	{
 	TxData[loop] = ucSCoilBuf[loop+(8*BANID)];
 	}
//				for(int loop = (BANID*8);loop<8+(BANID*8);loop++)
//				{
//					TxData[loop] = ucMCoilBuf[loop];
//				}

	HAL_CAN_AddTxMessage(&hcan,&TxHeader,TxData,&TxMailbox);
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
  /* Get RX message */
	int BANID;
	RxHeader.ExtId = 0x00; 
  RxHeader.RTR = CAN_RTR_DATA;
  RxHeader.IDE = CAN_ID_EXT;
  RxHeader.DLC = 8;
	HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &RxHeader, RxData);
			
	switch(RxHeader.ExtId)
		{
			case 0x18013F01:
				BANID  = 0;
				break;
		  case 0x18013F02:
				BANID  = 1;
				break;
		  case 0x18013F03:
				BANID  = 2;
				break;
		  case 0x18013F04:
				BANID  = 3;
				break;
		  case 0x18013F05:
				BANID  = 4;
				break;
			case 0x18013F06:
				BANID  = 5;
				break;
			case 0x18013F07:
				BANID  = 6;
				break;
			case 0x18013F08:
				BANID  = 7;
				break;
		}
	
			for(int loop=0;loop<8;loop++)
			{
			ucSCoilBuf[loop+(8*BANID)] = RxData[loop] ;
			}

}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
