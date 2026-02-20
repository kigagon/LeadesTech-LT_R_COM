/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

extern SPI_HandleTypeDef hspi1;

unsigned short CRC16(unsigned char *crcdata, unsigned short usDataLen);
void LED_Control(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin , uint16_t Staus);
void Check_UART_Receive(uint8_t Check);
void Board_Config(uint8_t Board);
void delay_us(uint16_t time);

void Compile_Date(void);

void Read_Sub_Version(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Relay7_TX_LED_Pin GPIO_PIN_2
#define Relay7_TX_LED_GPIO_Port GPIOE
#define Relay7_RX_LED_Pin GPIO_PIN_3
#define Relay7_RX_LED_GPIO_Port GPIOE
#define Relay7_ST_LED_Pin GPIO_PIN_4
#define Relay7_ST_LED_GPIO_Port GPIOE
#define Relay7_DC_Pin GPIO_PIN_5
#define Relay7_DC_GPIO_Port GPIOE
#define COM_4CH_SEL_Pin GPIO_PIN_13
#define COM_4CH_SEL_GPIO_Port GPIOC
#define SYS_LED2_Pin GPIO_PIN_14
#define SYS_LED2_GPIO_Port GPIOC
#define SYS_LED1_Pin GPIO_PIN_15
#define SYS_LED1_GPIO_Port GPIOC
#define REPEATER_LED_Pin GPIO_PIN_0
#define REPEATER_LED_GPIO_Port GPIOH
#define COM_MODE_Pin GPIO_PIN_1
#define COM_MODE_GPIO_Port GPIOH
#define Relay6_TX_LED_Pin GPIO_PIN_0
#define Relay6_TX_LED_GPIO_Port GPIOC
#define Relay6_RX_LED_Pin GPIO_PIN_1
#define Relay6_RX_LED_GPIO_Port GPIOC
#define Relay6_ST_LED_Pin GPIO_PIN_2
#define Relay6_ST_LED_GPIO_Port GPIOC
#define Relay6_DC_Pin GPIO_PIN_3
#define Relay6_DC_GPIO_Port GPIOC
#define SPI_CS_Pin GPIO_PIN_4
#define SPI_CS_GPIO_Port GPIOA
#define Relay5_TX_LED_Pin GPIO_PIN_5
#define Relay5_TX_LED_GPIO_Port GPIOC
#define Relay5_RX_LED_Pin GPIO_PIN_0
#define Relay5_RX_LED_GPIO_Port GPIOB
#define Relay5_ST_LED_Pin GPIO_PIN_1
#define Relay5_ST_LED_GPIO_Port GPIOB
#define Relay5_DC_Pin GPIO_PIN_2
#define Relay5_DC_GPIO_Port GPIOB
#define Relay4_TX_LED_Pin GPIO_PIN_9
#define Relay4_TX_LED_GPIO_Port GPIOE
#define Relay4_RX_LED_Pin GPIO_PIN_10
#define Relay4_RX_LED_GPIO_Port GPIOE
#define Relay4_ST_LED_Pin GPIO_PIN_11
#define Relay4_ST_LED_GPIO_Port GPIOE
#define Relay4_DC_Pin GPIO_PIN_12
#define Relay4_DC_GPIO_Port GPIOE
#define Relay3_TX_LED_Pin GPIO_PIN_14
#define Relay3_TX_LED_GPIO_Port GPIOE
#define Relay3_RX_LED_Pin GPIO_PIN_15
#define Relay3_RX_LED_GPIO_Port GPIOE
#define Relay3_ST_LED_Pin GPIO_PIN_12
#define Relay3_ST_LED_GPIO_Port GPIOB
#define Relay3_DC_Pin GPIO_PIN_13
#define Relay3_DC_GPIO_Port GPIOB
#define Relay2_TX_LED_Pin GPIO_PIN_8
#define Relay2_TX_LED_GPIO_Port GPIOD
#define Relay2_RX_LED_Pin GPIO_PIN_9
#define Relay2_RX_LED_GPIO_Port GPIOD
#define Relay2_ST_LED_Pin GPIO_PIN_10
#define Relay2_ST_LED_GPIO_Port GPIOD
#define Relay2_DC_Pin GPIO_PIN_11
#define Relay2_DC_GPIO_Port GPIOD
#define Relay1_TX_LED_Pin GPIO_PIN_12
#define Relay1_TX_LED_GPIO_Port GPIOD
#define Relay1_RX_LED_Pin GPIO_PIN_13
#define Relay1_RX_LED_GPIO_Port GPIOD
#define Relay1_ST_LED_Pin GPIO_PIN_14
#define Relay1_ST_LED_GPIO_Port GPIOD
#define Relay1_DC_Pin GPIO_PIN_15
#define Relay1_DC_GPIO_Port GPIOD
#define UI_485_DC_Pin GPIO_PIN_8
#define UI_485_DC_GPIO_Port GPIOA
#define UI_485_TX_LED_Pin GPIO_PIN_15
#define UI_485_TX_LED_GPIO_Port GPIOA
#define UI_485_RX_LED_Pin GPIO_PIN_10
#define UI_485_RX_LED_GPIO_Port GPIOC
#define UI_485_ST_LED_Pin GPIO_PIN_11
#define UI_485_ST_LED_GPIO_Port GPIOC
#define DIP_ADD7_Pin GPIO_PIN_0
#define DIP_ADD7_GPIO_Port GPIOD
#define DIP_ADD6_Pin GPIO_PIN_1
#define DIP_ADD6_GPIO_Port GPIOD
#define DIP_ADD5_Pin GPIO_PIN_2
#define DIP_ADD5_GPIO_Port GPIOD
#define DIP_ADD4_Pin GPIO_PIN_3
#define DIP_ADD4_GPIO_Port GPIOD
#define DIP_ADD3_Pin GPIO_PIN_4
#define DIP_ADD3_GPIO_Port GPIOD
#define DIP_ADD2_Pin GPIO_PIN_5
#define DIP_ADD2_GPIO_Port GPIOD
#define DIP_ADD1_Pin GPIO_PIN_6
#define DIP_ADD1_GPIO_Port GPIOD
#define DIP_ADD0_Pin GPIO_PIN_7
#define DIP_ADD0_GPIO_Port GPIOD
#define Relay8_TX_LED_Pin GPIO_PIN_4
#define Relay8_TX_LED_GPIO_Port GPIOB
#define Relay8_RX_LED_Pin GPIO_PIN_7
#define Relay8_RX_LED_GPIO_Port GPIOB
#define Relay8_ST_LED_Pin GPIO_PIN_8
#define Relay8_ST_LED_GPIO_Port GPIOB
#define Relay8_DC_Pin GPIO_PIN_9
#define Relay8_DC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

//#define Group_Max_Number  32
#define Group_Max_Number  8
#define SUB_Group_Max_Number  8

#define Repeater_Header_Number  6
#define Repeater_Number         220
//#define Repeater_Data_Number    6
#define Repeater_Data_Number    5
#define Repeater_Crc_Number     2
#define Repeater_End_Number     2
//#define Repeater_Data_Total     1260
#define Repeater_Data_Total     1110

#define Group_Register_Data_Number  39

#define Group_Charge_Register_Number  440

#define Group_Charge_Time_Number  9

#define Pow_Bod_Max_Number 8

#define Pow_Bod_Header_Number  6
#define Pow_Bod_Data_Number   6
#define Pow_Bod_CkSum_Number  1
#define Pow_Bod_End_Number     2
#define Pow_Bod_Data_Total  15


#define LED_On  1
#define LED_Off 0


//Array to store sub-64 system information, located in sdram2 (0x30000000)
// Group_Data[8][8][1110]
extern uint8_t Group_Data[Group_Max_Number][SUB_Group_Max_Number][Repeater_Header_Number +(Repeater_Number * Repeater_Data_Number) + Repeater_Crc_Number + Repeater_End_Number];


//Array to store lower 8 relay panel power board information
//Pow_Bod_Data[8][16]
extern uint8_t Pow_Bod_Data[Pow_Bod_Max_Number][Pow_Bod_Header_Number + Pow_Bod_Data_Number + Pow_Bod_CkSum_Number + Pow_Bod_End_Number];

//Array to store sub-64 system registration information
//Group_Regster[64][39]
extern uint8_t Group_Regster[Group_Max_Number][Group_Register_Data_Number];

//Array to store the charge information of the lower 64 systems
//Group_Charge_Regster[8][8][440]
extern uint8_t Group_Charge_Regster[Group_Max_Number][SUB_Group_Max_Number][Group_Charge_Register_Number];

//Array to store accumulation time information for lower 64 systems, does not operate if time is 0
//Group_Charge_Time[64][9]
extern uint8_t Group_Charge_Time[Group_Max_Number][Group_Charge_Time_Number];


//Array that stores system information to be reported to the parent, located in sdram3 (0x38000000).
//Group_Rep_Group_Data[508]
extern uint8_t Rep_Group_Data[Repeater_Header_Number +(Repeater_Number * Repeater_Data_Number) + Repeater_Crc_Number + Repeater_End_Number];

//Array that sto;;res information on the relay board power board to be reported to the upper level, located in sdram3 (0x38000000).
//Rep_Pow_Bod_Data[16]
extern uint8_t Rep_Pow_Bod_Data[Pow_Bod_Header_Number + Pow_Bod_Data_Number + Pow_Bod_CkSum_Number + Pow_Bod_End_Number];

//Array Repeater accumulation setting
#define REPEATER_Acc_Set_Num 229
#define REPEATER_Acc_OnOff_Num 10
extern uint8_t REPEATER_Acc_Set_Data[Group_Max_Number][SUB_Group_Max_Number][REPEATER_Acc_Set_Num];

/*
#define Set_Command_T_Num  256
#define Set_Command_T_Lan  640
extern uint8_t Set_Command_Num , Set_Command_Num_tmp;
extern uint8_t Set_Command_Data[Set_Command_T_Num][Set_Command_T_Lan], Set_Command_Data_tmp[Set_Command_T_Num][Set_Command_T_Lan];
extern uint8_t Set_Command_Data_Ck[Set_Command_T_Lan];
*/
//array to store addresses
extern uint8_t DIP_Value;

#define Max_Wate_udelay	25
#define Max_Wate_Recever_Board	25*(1000 / Max_Wate_udelay) // under 100, Set to multiples of 8
#define Max_Wate_Recever_4CH_Board	60*(1000 / Max_Wate_udelay) // under 100, Set to multiples of 8
#define Max_Wate_Repearter_Board	30*(1000 / Max_Wate_udelay) // under 100, Set to multiples of 8

#define Max_ccu_Err_Cnt	0
extern uint8_t ccu_Err_Cnt[8];

//Define UI uart receiving array
#define UI_UART_buf_len 2048
extern uint8_t UI_UART_Tx_buf[UI_UART_buf_len];
extern uint8_t UI_UART_RX_buf[UI_UART_buf_len];
extern uint8_t UI_UART_Tx_buf_tmp[UI_UART_buf_len];
extern uint8_t UI_UART_RX_buf_tmp[UI_UART_buf_len];
extern uint8_t UI_UART_buf_tmp;
extern uint8_t UART_RX_buf_tmp_o;
extern uint8_t UI_UART_State ;					// Define reception start state
extern int UI_UART_buf_count;					// Save the length of received data after starting reception
extern int UI_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
extern uint8_t UI_UART_Receive_complete;		// Variable indicating that reception has been completed
extern int UI_UART_RX_buf_Lan;

#define UART_buf_len 2048
#define UART_POW_buf_len 32

#define Recever_Board		0
#define Repearter_Board		1

extern uint8_t Tx_Mode;
extern uint8_t CM_Board;

#define UI_UART_Run_Cnt_Max 3
extern uint8_t UI_UART_Run_Clear, UI_UART_Run_Cnt;
extern uint8_t Read_Start_Sub_Com, Read_Start_Sub_Com_Time;

extern uint8_t SUB_UART_TX_buf[8][UART_buf_len];
extern uint8_t SUB_UART_RX_buf[8][UART_buf_len];
extern uint8_t SUB_UART_RX_buf_DMA_tmp[8][UART_buf_len];

extern uint8_t SUB_UART_POW_RX_buf[8][UART_POW_buf_len];
extern uint8_t SUB_UART_POW_RX_DMA_buf[8][UART_POW_buf_len];


extern uint8_t SUB_UART_State[8];					// Define reception start state
extern int SUB_UART_buf_count[8];					// Save the length of received data after starting reception
extern uint8_t SUB_UART_Receive_Command[8];
extern uint8_t SUB_UART_Receive_complete[8];			// Variable indicating that reception has been completed
extern uint8_t SUB_UART_Receive_Data_complete[8];
extern uint8_t SUB_UART_Transmit_complete[8];
extern uint64_t SUB_Tx_Cnt[8], SUB_Rx_Cnt[8];

extern uint8_t SUB_UART_Tx_Comp[8];
extern uint8_t SUB_UART_Rx_Comp[8];

extern uint8_t SUB_UART_Tx_Command[8];

#define UART_Com_A_len 1260

extern uint8_t Save_Info_Data[32][456];

extern uint8_t Save_Com_Version_Data[9][6];

#define Com_Version_Data_Number 72
extern uint8_t Com_Version_Data[Com_Version_Data_Number];

#define Rep_Version_Data_Number 1557
extern uint8_t Rep_Version_Data[Group_Max_Number][SUB_Group_Max_Number][Rep_Version_Data_Number];

extern uint8_t Sub_Version_Read_Cnt;

extern uint8_t Group_Tmp_Data[Group_Max_Number][SUB_Group_Max_Number][Repeater_Header_Number +(Repeater_Number * Repeater_Data_Number) + Repeater_Crc_Number + Repeater_End_Number];
extern uint8_t Group_Set_Info[Group_Max_Number][SUB_Group_Max_Number][456];

extern uint8_t Group_Port_Output[Group_Max_Number][SUB_Group_Max_Number][Group_Charge_Register_Number];
extern uint8_t Analog_Led_Mode[24][8];

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
