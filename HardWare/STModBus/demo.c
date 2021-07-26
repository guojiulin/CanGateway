/*
 * FreeModbus Libary: BARE Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"

#include "port.h"

#include "usart.h"

/* ----------------------- Defines ------------------------------------------*/


/* ----------------------- Static variables ---------------------------------*/

/* ----------------------- Start implementation -----------------------------*/






/******************************************************************************
                               ����Modbus��ز���
******************************************************************************/

USHORT usRegInputStart = REG_INPUT_START;
USHORT usRegInputBuf[REG_INPUT_NREGS];

USHORT usRegHoldingStart = REG_HOLDING_START;
USHORT usRegHoldingBuf[REG_HOLDING_NREGS];

/**
  *****************************************************************************
  * @Name   : ��������Ĵ���
  *
  * @Brief  : ��Ӧ������0x04 -> eMBFuncReadInputRegister
  *
  * @Input  : *pucRegBuffer�����ݻ���������Ӧ������
  *           usAddress:     �Ĵ�����ַ
  *           usNRegs:       �����Ĵ�������
  *
  * @Output : none
  *
  * @Return : Modbus״̬��Ϣ
  *****************************************************************************
**/
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//�жϵ�ַ�Ϸ���
	//
	if ((usAddress >= REG_INPUT_START) && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
	{
		iRegIndex = (int)(usAddress - usRegInputStart);
		while (usNRegs > 0)
		{
			*pucRegBuffer++ = (UCHAR)( usRegInputBuf[iRegIndex] >> 8);  //��8λ�ֽ�
			*pucRegBuffer++ = (UCHAR)( usRegInputBuf[iRegIndex] & 0xFF); //��8λ�ֽ�
			iRegIndex++;
			usNRegs--;
		}
	}
	else  //�����ַ
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : �������ּĴ���
  *
  * @Brief  : ��Ӧ������0x06 -> eMBFuncWriteHoldingRegister
  *                    0x16 -> eMBFuncWriteMultipleHoldingRegister
  *                    0x03 -> eMBFuncReadHoldingRegister
  *                    0x23 -> eMBFuncReadWriteMultipleHoldingRegister
  *
  * @Input  : *pucRegBuffer�����ݻ���������Ӧ������
  *           usAddress:     �Ĵ�����ַ
  *           usNRegs:       �����Ĵ�������
  *           eMode:         ������
  *
  * @Output : none
  *
  * @Return : Modbus״̬��Ϣ
  *****************************************************************************
**/
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//�жϵ�ַ�Ƿ�Ϸ�
	//
	if((usAddress >= REG_HOLDING_START) && ((usAddress + usNRegs) <= (REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		//
		//���ݹ�������в���
		//
		switch(eMode)
		{
			case MB_REG_READ:  //�����ּĴ���
					while(usNRegs > 0)
					{
						*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] >> 8);  //��8λ�ֽ�
						*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] & 0xFF); //��8λ�ֽ�
						iRegIndex++;
						usNRegs--;
					}                            
					break;
					
			case MB_REG_WRITE:  //д���ּĴ���
					while(usNRegs > 0)
					{
						usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;  //��8λ�ֽ�
						usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;  //��8λ�ֽ�
						iRegIndex++;
						usNRegs--;
					}
					break;
		}
	}
	else  //�����ַ
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : ������Ȧ
  *
  * @Brief  : ��Ӧ������0x01 -> eMBFuncReadCoils
  *                    0x05 -> eMBFuncWriteCoil
  *                    0x15 -> д�����Ȧ eMBFuncWriteMultipleCoils
  *
  * @Input  : *pucRegBuffer�����ݻ���������Ӧ������
  *           usAddress:     �Ĵ�����ַ
  *           usNRegs:       �����Ĵ�������
  *           eMode:         ������
  *
  * @Output : none
  *
  * @Return : Modbus״̬��Ϣ
  *****************************************************************************
**/
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int          iRegIndex = 0;
	
	//
	//�жϵ�ַ�Ϸ���
	//
	if ((usAddress >= REG_HOLDING_START) && ((usAddress + usNCoils) <= (REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		iRegIndex = (int)(usAddress - usRegHoldingStart);
		//
		//���ݹ��������
		//
		switch (eMode)
		{
			case MB_REG_READ:  //��ȡ����
				while (usNCoils > 0)
				{
					*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] >> 8);  //��8λ�ֽ�
					*pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] & 0xFF);  //��8λ�ֽ�
					iRegIndex++;
					usNCoils--;
				}
				break;
				
			case MB_REG_WRITE:  //д����
				while (usNCoils > 0)
				{
					usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;  //��8λ�ֽ�
					usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;  //��8λ�ֽ�
					iRegIndex++;
					usNCoils--;
				}
				break;
		}
	}
	else  //�����ַ
	{
		eStatus = MB_ENOREG;
	}
	
	return eStatus;
}

/**
  *****************************************************************************
  * @Name   : ������ɢ�Ĵ���
  *
  * @Brief  : ��Ӧ������0x02 -> eMBFuncReadDiscreteInputs
  *
  * @Input  : *pucRegBuffer�����ݻ���������Ӧ������
  *           usAddress:     �Ĵ�����ַ
  *           usNRegs:       �����Ĵ�������
  *
  * @Output : none
  *
  * @Return : Modbus״̬��Ϣ
  *****************************************************************************
**/
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	pucRegBuffer = pucRegBuffer;
	
	return MB_ENOREG;
}
