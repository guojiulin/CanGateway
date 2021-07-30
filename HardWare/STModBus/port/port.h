/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: port.h,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#ifndef _PORT_H
#define _PORT_H

#include <assert.h>
#include <inttypes.h>



//#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION( )  
#define EXIT_CRITICAL_SECTION( )   

typedef uint8_t BOOL;

typedef unsigned char UCHAR;
typedef char CHAR;

typedef uint16_t USHORT;
typedef int16_t SHORT;

typedef uint32_t ULONG;
typedef int32_t LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

/////******************************************************************************
////                               定义Modbus相关参数
////******************************************************************************/

//#define REG_INPUT_START                          (USHORT)0x0001  //起始寄存器
//#define REG_INPUT_NREGS                          (USHORT)4  //寄存器个数
//#define REG_HOLDING_START                        (USHORT)0x0001//保持寄存器
//#define REG_HOLDING_NREGS                        (USHORT)512  //保持寄存器个数


////#define REG_INPUT_START 1000
////#define REG_INPUT_NREGS 4
////#define REG_COILS_START 1000
////#define REG_COILS_SIZE  16
/////******************************************************************************
////                               外部调用功能函数
////******************************************************************************/

////extern USHORT usRegInputBuf[REG_INPUT_NREGS];
////extern USHORT usRegHoldingBuf[REG_HOLDING_NREGS];
////extern USHORT   ucRegCoilsBuf[REG_COILS_SIZE / 8];
//#endif


#define RT_S_DISCRETE_INPUT_START 0
#define RT_S_DISCRETE_INPUT_NDISCRETES 16
#define RT_S_COIL_START 0
#define RT_S_COIL_NCOILS 512
#define RT_S_REG_INPUT_START 0
#define RT_S_REG_INPUT_NREGS 100
#define RT_S_REG_HOLDING_START 0
#define RT_S_REG_HOLDING_NREGS 100


/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START                    RT_S_DISCRETE_INPUT_START
#define S_DISCRETE_INPUT_NDISCRETES               RT_S_DISCRETE_INPUT_NDISCRETES
#define S_COIL_START                              RT_S_COIL_START
#define S_COIL_NCOILS                             RT_S_COIL_NCOILS
#define S_REG_INPUT_START                         RT_S_REG_INPUT_START
#define S_REG_INPUT_NREGS                         RT_S_REG_INPUT_NREGS
#define S_REG_HOLDING_START                       RT_S_REG_HOLDING_START
#define S_REG_HOLDING_NREGS                       RT_S_REG_HOLDING_NREGS
/* salve mode: holding register's all address */
#define          S_HD_RESERVE                     RT_S_HD_RESERVE
/* salve mode: input register's all address */
#define          S_IN_RESERVE                     RT_S_IN_RESERVE
/* salve mode: coil's all address */
#define          S_CO_RESERVE                     RT_S_CO_RESERVE
/* salve mode: discrete's all address */
#define          S_DI_RESERVE                     RT_S_DI_RESERVE

/* -----------------------Master Defines -------------------------------------*/
#define M_DISCRETE_INPUT_START                    RT_M_DISCRETE_INPUT_START
#define M_DISCRETE_INPUT_NDISCRETES               RT_M_DISCRETE_INPUT_NDISCRETES
#define M_COIL_START                              RT_M_COIL_START
#define M_COIL_NCOILS                             RT_M_COIL_NCOILS
#define M_REG_INPUT_START                         RT_M_REG_INPUT_START
#define M_REG_INPUT_NREGS                         RT_M_REG_INPUT_NREGS
#define M_REG_HOLDING_START                       RT_M_REG_HOLDING_START
#define M_REG_HOLDING_NREGS                       RT_M_REG_HOLDING_NREGS
/* master mode: holding register's all address */
#define          M_HD_RESERVE                     RT_M_HD_RESERVE
/* master mode: input register's all address */
#define          M_IN_RESERVE                     RT_M_IN_RESERVE
/* master mode: coil's all address */
#define          M_CO_RESERVE                     RT_M_CO_RESERVE
/* master mode: discrete's all address */
#define          M_DI_RESERVE                     RT_M_DI_RESERVE

#endif

