  /* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "UI_UART_Funtions.h"
#include "SUB_UART_Funtions.h"
#include "Compile_Data.h"
#include "ReadWriteFlash.h"

//32M bit
//Page : 256 byte , 16384
//Sector : 4096byte , 1024 (16 page)
//Block: 65536byte, 64 (16 sector , 256page)

//128M bit
//Page : 256 byte , 65536
//Sector : 4096byte , 4096 (16 page * 4)
//Block: 65536byte, 256 (16*4 sector , 256*4page)


// 256(250):input X  256(250):Output X 1byte = 65536byte = 1Block , block add : 0
// 32 group : 32 block
//Ccu : 126kb , 3block, block add : 33
//Com : 164kb , 4block, block add : 37

#include "w25qxx.h"
#include "w25qxxConf.h"

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

IWDG_HandleTypeDef hiwdg1;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart7;
UART_HandleTypeDef huart8;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_lpuart1_tx;
DMA_HandleTypeDef hdma_lpuart1_rx;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart5_rx;
DMA_HandleTypeDef hdma_uart5_tx;
DMA_HandleTypeDef hdma_uart7_rx;
DMA_HandleTypeDef hdma_uart7_tx;
DMA_HandleTypeDef hdma_uart8_rx;
DMA_HandleTypeDef hdma_uart8_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim12;

/* USER CODE BEGIN PV */

//Array to store sub-64 system information, located in sdram2 (0x30000000)
// Group_Data[8][8][1110]
uint8_t Group_Data[Group_Max_Number][SUB_Group_Max_Number]
				   [Repeater_Header_Number +(Repeater_Number * Repeater_Data_Number) + Repeater_Crc_Number + Repeater_End_Number ] __attribute__((section(".d2_data"))) = {0};

//Array to store lower 8 relay panel power board information
//Pow_Bod_Data[8][16]
uint8_t Pow_Bod_Data[Pow_Bod_Max_Number][Pow_Bod_Header_Number + Pow_Bod_Data_Number + Pow_Bod_CkSum_Number + Pow_Bod_End_Number];

//Array to store sub-64 system registration information
//Group_Regster[64][39]
uint8_t Group_Regster[Group_Max_Number][Group_Register_Data_Number];

//Array to store the charge information of the lower 64 systems
//Group_Charge_Regster[64][508]
uint8_t Group_Charge_Regster[Group_Max_Number][Group_Charge_Register_Number];

//Array to store accumulation time information for lower 64 systems, does not operate if time is 0
//Group_Charge_Time[64][9]
uint8_t Group_Charge_Time[Group_Max_Number][Group_Charge_Time_Number];

//Array that stores system information to be reported to the parent, located in sdram3 (0x38000000).
//Group_Rep_Group_Data[1260]
uint8_t Rep_Group_Data[Repeater_Header_Number +(Repeater_Number * Repeater_Data_Number) + Repeater_Crc_Number + Repeater_End_Number] __attribute__((section(".d3_data"))) = {0};

//Array that stores information on the relay board power board to be reported to the upper level, located in sdram3 (0x38000000).
//Rep_Pow_Bod_Data[16]
uint8_t Rep_Pow_Bod_Data[Pow_Bod_Header_Number + Pow_Bod_Data_Number + Pow_Bod_CkSum_Number + Pow_Bod_End_Number] __attribute__((section(".d3_data"))) = {0};

//Array Repeater accumulation setting
uint8_t  REPEATER_Acc_Set_Data[Group_Max_Number][SUB_Group_Max_Number][REPEATER_Acc_Set_Num];

uint8_t Set_Command_Num = 0, Set_Command_Num_tmp = 0 ;
uint8_t Set_Command_Data[Set_Command_T_Num][Set_Command_T_Lan], Set_Command_Data_tmp[Set_Command_T_Num][Set_Command_T_Lan];
uint8_t Set_Command_Data_Ck[Set_Command_T_Lan];

//array to store addresses
uint8_t DIP_Value_tmp[8];
uint8_t DIP_Value;

uint8_t ccu_Err_Cnt[8];

//Define UI uart receiving array
uint8_t UI_UART_Tx_buf[UI_UART_buf_len];
uint8_t UI_UART_RX_buf[UI_UART_buf_len];
uint8_t UI_UART_Tx_buf_tmp[UI_UART_buf_len];
uint8_t UI_UART_RX_buf_tmp[UI_UART_buf_len];
uint8_t UI_UART_buf_tmp;
uint8_t UART_RX_buf_tmp_o;
uint8_t UI_UART_State ;					// Define reception start state
int UI_UART_buf_count;					// Save the length of received data after starting reception
int UI_UART_buf_count_tmp;				// Variable to store the length of the received data before initializing it when reception is completed
uint8_t UI_UART_Receive_complete;		// Variable indicating that reception has been completed
int UI_UART_RX_buf_Lan;

uint8_t Tx_Mode;
uint8_t CM_Board;
uint8_t Timer_Cnt;
int Com_Sleep_Cnt;
uint8_t UI_UART_Run_Clear, UI_UART_Run_Cnt;
uint8_t Read_Start_Sub_Com, Read_Start_Sub_Com_Time;

uint8_t SUB_UART_TX_buf[8][UART_buf_len];
uint8_t SUB_UART_RX_buf[8][UART_buf_len];
uint8_t SUB_UART_RX_buf_DMA_tmp[8][UART_buf_len];

uint8_t SUB_UART_POW_RX_buf[8][UART_POW_buf_len];
uint8_t SUB_UART_POW_RX_DMA_buf[8][UART_POW_buf_len];

uint8_t SUB_UART_State[8];					// Define reception start state
int SUB_UART_buf_count[8];					// Save the length of received data after starting reception
uint8_t SUB_UART_Receive_Command[8];
uint8_t SUB_UART_Receive_complete[8];			// Variable indicating that reception has been completed
uint8_t SUB_UART_Receive_Data_complete[8];
uint8_t SUB_UART_Transmit_complete[8];
uint64_t SUB_Tx_Cnt[8], SUB_Rx_Cnt[8];

uint8_t SUB_UART_Tx_Comp[8];
uint8_t SUB_UART_Rx_Comp[8];

uint8_t SUB_UART_Tx_Command[8];

uint32_t Flash_ID;
uint8_t Flash_Status;

uint8_t Serial_Num[7];

uint8_t Save_Info_Data[32][456];

uint8_t Sub_Version_Read_Cnt = 0;

// Save_Com_Version_Data[0]  : com board
// Save_Com_Version_Data[1~4]  : Sub board
// Save_Com_Version_Data[5~8]  : Pow board

uint8_t Save_Com_Version_Data[9][6];

uint8_t Com_Version_Data[Com_Version_Data_Number];
uint8_t Rep_Version_Data[Group_Max_Number][SUB_Group_Max_Number][Rep_Version_Data_Number];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_BDMA_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_UART4_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART7_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_UART5_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM12_Init(void);
static void MX_UART8_Init(void);
static void MX_SPI1_Init(void);
static void MX_IWDG1_Init(void);
/* USER CODE BEGIN PFP */

int t_cnt;
void delay_us(uint16_t time) {
	__HAL_TIM_SET_COUNTER(&htim12, 0);              // 타이머를 0으로 초기화

	while((__HAL_TIM_GET_COUNTER(&htim12))<time);   // 설정한 시간까지 대기
}

///////////////Start timer interrupt operation function///////////////////

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1)
  {
    HAL_GPIO_TogglePin(SYS_LED1_GPIO_Port, SYS_LED1_Pin);

    if(UI_UART_Run_Cnt > UI_UART_Run_Cnt_Max){
//    	HAL_UART_Receive_IT (&hlpuart1, &UI_UART_buf_tmp, 1);
    	UI_UART_Run_Cnt = 0;
    }
    else{
    	UI_UART_Run_Cnt++;
    }
    HAL_IWDG_Refresh(&hiwdg1);
    //Read_Start_Sub_Com = 1;

  }
  else if(htim->Instance == TIM2)
  {

  }
  else if(htim->Instance == TIM3)
  {

  }
  else if(htim->Instance == TIM4)
  {

  }
  else if(htim->Instance == TIM5)
  {

  }
  else if(htim->Instance == TIM8)
  {
	  Com_Sleep_Cnt++;
	  if(Com_Sleep_Cnt > 3){
//		  HAL_UART_Receive_IT (&hlpuart1, &UI_UART_buf_tmp, 1);
		  Com_Sleep_Cnt = 0;
	  }
  }
}
////////////////Timer interrupt operation function ends ///////////////////

int Pre_Com_Cnt;
int Del_Com_Cnt;
///////////////Start UART interrupt operation function///////////////////
///* receiver
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == LPUART1)
	{
		/*
		UI_UART_RX_buf_tmp[UI_UART_buf_count] = UI_UART_buf_tmp;

		UI_UART_buf_count++;

	  if((UI_UART_RX_buf_tmp[UI_UART_buf_count-3] == 0x53)&(UI_UART_RX_buf_tmp[UI_UART_buf_count-2] == 0x54)
	  		  &(UI_UART_RX_buf_tmp[UI_UART_buf_count-1] == 0x55))
		{
		  UI_UART_State = 1;
		  UI_UART_RX_buf_tmp[0] = 0x53;
		  UI_UART_RX_buf_tmp[1] = 0x54;
		  UI_UART_RX_buf_tmp[2] = 0x55;
		  UI_UART_buf_count = 3;
		  HAL_GPIO_WritePin(UI_485_RX_LED_GPIO_Port, UI_485_RX_LED_Pin, GPIO_PIN_RESET);
		}
		if((UI_UART_State == 1)&(UI_UART_RX_buf_tmp[UI_UART_buf_count -2 ] == 0x45)&(UI_UART_RX_buf_tmp[UI_UART_buf_count - 1] == 0x44)) {
		    UI_UART_State = 0;
		    UI_UART_RX_buf_Lan = UI_UART_buf_count;
		    UI_UART_buf_count = 0;
		    UI_UART_Receive_complete = 1;

		    for(int i=0; i<UI_UART_RX_buf_Lan; i++){
			  UI_UART_RX_buf[i] = UI_UART_RX_buf_tmp[i];
		    }
		    Com_Sleep_Cnt = 0;

		    HAL_GPIO_WritePin(UI_485_RX_LED_GPIO_Port, UI_485_RX_LED_Pin, GPIO_PIN_SET);
		  }

		if(UI_UART_buf_count >= UART_buf_len){
			UI_UART_State = 0;
			UI_UART_buf_count = 0;
			UI_UART_Receive_complete = 0;

		}
		UI_UART_Run_Cnt = 0;
		HAL_UART_Receive_IT (&hlpuart1, &UI_UART_buf_tmp, 1);
		*/

	}

	else if (huart->Instance == USART6)
	{
		Sub_Cmd_RX_LED_Off(1);
		SUB_UART_Rx_Comp[0] = 1;

	}

	else if (huart->Instance == USART1)
	{
		Sub_Cmd_RX_LED_Off(2);
		SUB_UART_Rx_Comp[1] = 1;
	}

	else if (huart->Instance == USART3)
	{
		Sub_Cmd_RX_LED_Off(3);
		SUB_UART_Rx_Comp[2] = 1;
	}

	else if (huart->Instance == UART7)
	{
		Sub_Cmd_RX_LED_Off(4);
		SUB_UART_Rx_Comp[3] = 1;
	}

	else if (huart->Instance == USART2)
	{
		Sub_Cmd_RX_LED_Off(5);
		SUB_UART_Rx_Comp[4] = 1;
	}

	else if (huart->Instance == UART4)
	{
		Sub_Cmd_RX_LED_Off(6);
		SUB_UART_Rx_Comp[5] = 1;
	}

	else if (huart->Instance == UART8)
	{
		Sub_Cmd_RX_LED_Off(7);
		SUB_UART_Rx_Comp[6] = 1;
	}

	else if (huart->Instance == UART5)
	{
		Sub_Cmd_RX_LED_Off(8);
		SUB_UART_Rx_Comp[7] = 1;
	}


}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	///////////If the DMA UART is malfunctioning, change the reception mode to an interrupt./////
	if (huart->Instance == LPUART1)
	{
		HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
		LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);

		if(CM_Board == Recever_Board){
//			if(DIP_Value % 2 == 1){
//				if(Tx_Mode == 0x41){
//					if((Rep_Group_Data[4] == DIP_Value * 4)&(Rep_Group_Data[5] == 8))
//					{
//						Read_Start_Sub_Com = 1;
//					}
//				}
//			}
//			else{
//				if(Tx_Mode == 0x50){
//					if(Rep_Pow_Bod_Data[4] == DIP_Value * 4)
//					{
//						Read_Start_Sub_Com = 1;
//					}
//				}
//			}
			if(Tx_Mode == 0x50){
					if(Rep_Pow_Bod_Data[4] == DIP_Value * 4)
					{
						Read_Start_Sub_Com = 1;
					}
				}

		}
		else if(CM_Board == Repearter_Board){

			if(Tx_Mode == 0x41){
				if(Rep_Group_Data[5]== 8)
				{
					Read_Start_Sub_Com = 1;
				}
			}
		}
	}
	else if (huart->Instance == USART6)
	{
		Sub_Cmd_DC_Off(1);
		Sub_Cmd_TX_LED_Off(1);
		SUB_UART_Tx_Comp[0] = 1;
		Sub_Cmd_RX_DMA_ST(1);
	}
	else if (huart->Instance == USART1)
	{
		Sub_Cmd_DC_Off(2);
		Sub_Cmd_TX_LED_Off(2);
		SUB_UART_Tx_Comp[1] = 1;
		Sub_Cmd_RX_DMA_ST(2);
	}
	else if (huart->Instance == USART3)
	{
		Sub_Cmd_DC_Off(3);
		Sub_Cmd_TX_LED_Off(3);
		SUB_UART_Tx_Comp[2] = 1;
		Sub_Cmd_RX_DMA_ST(3);
	}
	else if (huart->Instance == UART7)
	{
		Sub_Cmd_DC_Off(4);
		Sub_Cmd_TX_LED_Off(4);
		SUB_UART_Tx_Comp[3] = 1;
		Sub_Cmd_RX_DMA_ST(4);
	}
	else if (huart->Instance == USART2)
	{
		Sub_Cmd_DC_Off(5);
		Sub_Cmd_TX_LED_Off(5);
		SUB_UART_Tx_Comp[4] = 1;
		Sub_Cmd_RX_DMA_ST(5);
	}
	else if (huart->Instance == UART4)
	{
		Sub_Cmd_DC_Off(6);
		Sub_Cmd_TX_LED_Off(6);
		SUB_UART_Tx_Comp[5] = 1;
		Sub_Cmd_RX_DMA_ST(6);
	}
	else if (huart->Instance == UART8)
	{
		Sub_Cmd_DC_Off(7);
		Sub_Cmd_TX_LED_Off(7);
		SUB_UART_Tx_Comp[6] = 1;
		Sub_Cmd_RX_DMA_ST(7);
	}
	else if (huart->Instance == UART5)
	{
		Sub_Cmd_DC_Off(8);
		Sub_Cmd_TX_LED_Off(8);
		SUB_UART_Tx_Comp[7] = 1;
		Sub_Cmd_RX_DMA_ST(8);
	}
}
///////////////End UART interrupt operation function///////////////////

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_BDMA_Init();
  MX_LPUART1_UART_Init();
  MX_UART4_Init();
  MX_USART2_UART_Init();
  MX_UART7_Init();
  MX_USART3_UART_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_UART5_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_UART8_Init();
  MX_SPI1_Init();
//  MX_IWDG1_Init();
  /* USER CODE BEGIN 2 */

  ///////////////Start LED initialization//////////////////

  LED_Control(SYS_LED1_GPIO_Port, SYS_LED1_Pin , LED_Off);
  LED_Control(SYS_LED2_GPIO_Port, SYS_LED2_Pin , LED_Off);

  LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);
  LED_Control(UI_485_RX_LED_GPIO_Port, UI_485_RX_LED_Pin , LED_Off);
  LED_Control(UI_485_ST_LED_GPIO_Port, UI_485_ST_LED_Pin , LED_Off);

  LED_Control(Relay1_TX_LED_GPIO_Port, Relay1_TX_LED_Pin , LED_Off);
  LED_Control(Relay1_RX_LED_GPIO_Port, Relay1_RX_LED_Pin , LED_Off);
  LED_Control(Relay1_ST_LED_GPIO_Port, Relay1_ST_LED_Pin , LED_Off);

  LED_Control(Relay2_TX_LED_GPIO_Port, Relay2_TX_LED_Pin , LED_Off);
  LED_Control(Relay2_RX_LED_GPIO_Port, Relay2_RX_LED_Pin , LED_Off);
  LED_Control(Relay2_ST_LED_GPIO_Port, Relay2_ST_LED_Pin , LED_Off);

  LED_Control(Relay3_TX_LED_GPIO_Port, Relay3_TX_LED_Pin , LED_Off);
  LED_Control(Relay3_RX_LED_GPIO_Port, Relay3_RX_LED_Pin , LED_Off);
  LED_Control(Relay3_ST_LED_GPIO_Port, Relay3_ST_LED_Pin , LED_Off);

  LED_Control(Relay4_TX_LED_GPIO_Port, Relay4_TX_LED_Pin , LED_Off);
  LED_Control(Relay4_RX_LED_GPIO_Port, Relay4_RX_LED_Pin , LED_Off);
  LED_Control(Relay4_ST_LED_GPIO_Port, Relay4_ST_LED_Pin , LED_Off);

  LED_Control(Relay5_TX_LED_GPIO_Port, Relay5_TX_LED_Pin , LED_Off);
  LED_Control(Relay5_RX_LED_GPIO_Port, Relay5_RX_LED_Pin , LED_Off);
  LED_Control(Relay5_ST_LED_GPIO_Port, Relay5_ST_LED_Pin , LED_Off);

  LED_Control(Relay6_TX_LED_GPIO_Port, Relay6_TX_LED_Pin , LED_Off);
  LED_Control(Relay6_RX_LED_GPIO_Port, Relay6_RX_LED_Pin , LED_Off);
  LED_Control(Relay6_ST_LED_GPIO_Port, Relay6_ST_LED_Pin , LED_Off);

  LED_Control(Relay7_TX_LED_GPIO_Port, Relay7_TX_LED_Pin , LED_Off);
  LED_Control(Relay7_RX_LED_GPIO_Port, Relay7_RX_LED_Pin , LED_Off);
  LED_Control(Relay7_ST_LED_GPIO_Port, Relay7_ST_LED_Pin , LED_Off);

  LED_Control(Relay8_TX_LED_GPIO_Port, Relay8_TX_LED_Pin , LED_Off);
  LED_Control(Relay8_RX_LED_GPIO_Port, Relay8_RX_LED_Pin , LED_Off);
  LED_Control(Relay8_ST_LED_GPIO_Port, Relay8_ST_LED_Pin , LED_Off);
  ////////////////LED Initialization End//////////////////

  ///////////////Start reading address of board//////////////////
  DIP_Value_tmp[0] =  ~(HAL_GPIO_ReadPin(DIP_ADD0_GPIO_Port, DIP_ADD0_Pin)) & 0x01;
  DIP_Value_tmp[1] =  ~(HAL_GPIO_ReadPin(DIP_ADD1_GPIO_Port, DIP_ADD1_Pin)) & 0x01;
  DIP_Value_tmp[2] =  ~(HAL_GPIO_ReadPin(DIP_ADD2_GPIO_Port, DIP_ADD2_Pin)) & 0x01;
  DIP_Value_tmp[3] =  ~(HAL_GPIO_ReadPin(DIP_ADD3_GPIO_Port, DIP_ADD3_Pin)) & 0x01;
  DIP_Value_tmp[4] =  ~(HAL_GPIO_ReadPin(DIP_ADD4_GPIO_Port, DIP_ADD4_Pin)) & 0x01;
  DIP_Value_tmp[5] =  ~(HAL_GPIO_ReadPin(DIP_ADD5_GPIO_Port, DIP_ADD5_Pin)) & 0x01;
  DIP_Value_tmp[6] =  ~(HAL_GPIO_ReadPin(DIP_ADD6_GPIO_Port, DIP_ADD6_Pin)) & 0x01;
  DIP_Value_tmp[7] =  ~(HAL_GPIO_ReadPin(DIP_ADD7_GPIO_Port, DIP_ADD7_Pin)) & 0x01;

  /*
  DIP_Value = (DIP_Value_tmp[7] << 7)|(DIP_Value_tmp[6] << 6)|(DIP_Value_tmp[5] << 5)|(DIP_Value_tmp[4] << 4)
		  |(DIP_Value_tmp[3] << 3)|(DIP_Value_tmp[2] << 2)|(DIP_Value_tmp[1] << 1)|(DIP_Value_tmp[0] << 0);
*/

  DIP_Value = (DIP_Value_tmp[4] << 4)|(DIP_Value_tmp[3] << 3)|(DIP_Value_tmp[2] << 2)|(DIP_Value_tmp[1] << 1)|(DIP_Value_tmp[0] << 0);

  Compile_Date();

  Save_Com_Version_Data[0][0] = F_Version_Year;
  Save_Com_Version_Data[0][1] = F_Version_Month;
  Save_Com_Version_Data[0][2] = F_Version_Day;
  Save_Com_Version_Data[0][3] = F_Version_Hour;
  Save_Com_Version_Data[0][4] = F_Version_Min;
  Save_Com_Version_Data[0][5] = F_Version_Sec;
//  if((DIP_Value>0) &(DIP_Value<25)){
//
//  }
//  else{
//	  while(1){
//		  LED_Control(SYS_LED2_GPIO_Port, SYS_LED2_Pin , LED_On);
//		  HAL_Delay(1000);
//		  LED_Control(SYS_LED2_GPIO_Port, SYS_LED2_Pin , LED_Off);
//		  HAL_Delay(1000);
//	  }
//  }


  Flash_ID= W25qxx_ReadID();
  if(_MANUFACTURER_ID == ((Flash_ID >> 16) & 0xff)){
	  Flash_Status = 1;
	  W25qxx_Init();
  }

/*
  uint8_t W25Q_Page_Read_t[512];
  uint8_t W25Q_Page_Write_t[512];
  uint8_t Test_Block = 1;

  W25qxx_ReadBytes(W25Q_Page_Read_t, Test_Block, 256);

  W25qxx_ReadBytes(W25Q_Page_Read_t, Test_Block, 256);
  for(int i=0; i< 256 ; i++){
	  W25Q_Page_Write_t[i] = i;
    }


  W25qxx_EraseBlock(Test_Block);
  W25qxx_ReadPage(W25Q_Page_Read_t, Test_Block,0, 256);
  W25qxx_WritePage(W25Q_Page_Write_t,Test_Block ,0,256);
*/

  /*
  W25qxx_EraseSector(Test_Block);
  W25qxx_ReadSector(W25Q_Page_Read_t, Test_Block, 0, 512);
  W25qxx_WriteSector(W25Q_Page_Write_t, Test_Block, 0, 512);
  W25qxx_ReadSector(W25Q_Page_Read_t, Test_Block, 0, 512);

  W25qxx_ReadPage(W25Q_Page_Read_t, Test_Block, 0, 256);

  Write_Regi_data(Test_Block, W25Q_Page_Write_t, 256);
*/
  for(int i=0;i<8 ; i++){
	  for(int j = 0; j < UART_buf_len ; j++){
		  SUB_UART_TX_buf[i][j] = 0;
		  SUB_UART_RX_buf[i][j] = 0;
		  SUB_UART_RX_buf_DMA_tmp[i][j] = 0;
	  }
  }
  ///////////////End reading address of board//////////////////

  ///////////////Start Timer Interrupt Settings///////////////////

  // Timer1: 1 second cycle
  // Timer2: 0.5 second cycle
  // Timer3: 0.2 second cycle
  // Timer4: 0.1 second cycle
  // Timer5: 0.01 second cycle
  HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim4,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim5,TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim8,TIM_CHANNEL_1);

  HAL_TIM_Base_Start(&htim12);

  HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // sp3485EN-L is rx mode
  ///////////////End Timer Interrupt Settings///////////////////

  if(HAL_GPIO_ReadPin(COM_MODE_GPIO_Port, COM_MODE_Pin) == GPIO_PIN_SET){
	  CM_Board = Recever_Board;
	  if(HAL_GPIO_ReadPin(COM_4CH_SEL_GPIO_Port, COM_4CH_SEL_Pin) == GPIO_PIN_SET){
		  CM_Board = Recever_Board;
	  }
  }
  else{
	  CM_Board = Repearter_Board;

  }

  Board_Config(CM_Board);

  Info_Set(CM_Board);


/*
  while(1){

		// Enable the UART Error Interrupt: (Frame error, noise error, overrun error)
		__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_ERR);
		// Enable the UART Data Register not empty Interrupt
		__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE);

		  Check_UI_UART_Receive(UI_UART_Receive_complete);

		  Read_Sub_Version();
  }
*/


  Read_Start_Sub_Com = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_ERR);
	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE);

	  Check_UI_UART_Receive(UI_UART_Receive_complete);
//	  UI_Cmd_Func_S();
//	  Read_Start_Sub_Com = 1;

	  if(DIP_Value == 0){
		  Read_Start_Sub_Com = 1;
	  }

	  if(Read_Start_Sub_Com == 1){

		  for(int i=0; i<7 ; i++){
			  SUB_UART_Tx_Comp[i] = 0;
			  SUB_UART_Rx_Comp[i] = 0;
		  }
		  if(CM_Board == Recever_Board){

			  for(int k=0 ; k<1; k++){
				  for(int i=1; i<9;i++){
					  for(int j=1; j<5 ; j++){
						  Sub_Cmd_Func_A(j,i);
						  Check_UI_UART_Receive(UI_UART_Receive_complete);
					  }
					  if(DIP_Value_tmp[7] == 0){
						  Sub_Rx_Wait(CM_Board,80);
					  }
					  else{
						  Sub_Rx_Wait(CM_Board,30);
					  }


					  Check_Sub_UART_ComA_Receive(i);
				  }
			  }
			  for(int i=1; i<5;i++){
				  Sub_Cmd_Func_P(i);
			  }
			  Sub_Rx_Wait(CM_Board,2);
			  Check_Sub_UART_ComP_Receive();

		  }
		  else if(CM_Board == Repearter_Board){

			  for(int i=0; i<1;i++){
				  for(int j=1; j<9 ; j++){
					  Sub_Cmd_Func_A(j,1);
				  }
				  Sub_Rx_Wait(CM_Board,20);
				  Check_Sub_UART_ComA_Receive(1);
			  }

		  }


		  Read_Start_Sub_Com = 0;

	  }

	  if(Sub_Version_Read_Cnt == 1){

		  Read_Sub_Version();
		  Sub_Version_Read_Cnt = 0;

	  }


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief IWDG1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG1_Init(void)
{

  /* USER CODE BEGIN IWDG1_Init 0 */

  /* USER CODE END IWDG1_Init 0 */

  /* USER CODE BEGIN IWDG1_Init 1 */

  /* USER CODE END IWDG1_Init 1 */
  hiwdg1.Instance = IWDG1;
  hiwdg1.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg1.Init.Window = 4095;
  hiwdg1.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG1_Init 2 */

  /* USER CODE END IWDG1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 1500000;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 300000;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 300000;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart5, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart5, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief UART7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART7_Init(void)
{

  /* USER CODE BEGIN UART7_Init 0 */

  /* USER CODE END UART7_Init 0 */

  /* USER CODE BEGIN UART7_Init 1 */

  /* USER CODE END UART7_Init 1 */
  huart7.Instance = UART7;
  huart7.Init.BaudRate = 300000;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart7.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart7, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart7, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART7_Init 2 */

  /* USER CODE END UART7_Init 2 */

}

/**
  * @brief UART8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART8_Init(void)
{

  /* USER CODE BEGIN UART8_Init 0 */

  /* USER CODE END UART8_Init 0 */

  /* USER CODE BEGIN UART8_Init 1 */

  /* USER CODE END UART8_Init 1 */
  huart8.Instance = UART8;
  huart8.Init.BaudRate = 200000;
  huart8.Init.WordLength = UART_WORDLENGTH_8B;
  huart8.Init.StopBits = UART_STOPBITS_1;
  huart8.Init.Parity = UART_PARITY_NONE;
  huart8.Init.Mode = UART_MODE_TX_RX;
  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
  huart8.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart8.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart8.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart8, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart8, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart8) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART8_Init 2 */

  /* USER CODE END UART8_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 300000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 300000;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 300000;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 300000;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart6, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart6, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x0;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 23999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 23999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 23999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 23999;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 499;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 23999;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 99;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 23999;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 9999;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 239;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 65535;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim12, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim12, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_BDMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_BDMA_CLK_ENABLE();

  /* DMA interrupt init */
  /* BDMA_Channel0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BDMA_Channel0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(BDMA_Channel0_IRQn);
  /* BDMA_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BDMA_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(BDMA_Channel1_IRQn);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA1_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
  /* DMA2_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);
  /* DMA2_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Relay7_TX_LED_Pin|Relay7_RX_LED_Pin|Relay7_ST_LED_Pin|Relay7_DC_Pin
                          |Relay4_TX_LED_Pin|Relay4_RX_LED_Pin|Relay4_ST_LED_Pin|Relay4_DC_Pin
                          |Relay3_TX_LED_Pin|Relay3_RX_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SYS_LED2_Pin|SYS_LED1_Pin|Relay6_TX_LED_Pin|Relay6_RX_LED_Pin
                          |Relay6_ST_LED_Pin|Relay6_DC_Pin|Relay5_TX_LED_Pin|UI_485_RX_LED_Pin
                          |UI_485_ST_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(REPEATER_LED_GPIO_Port, REPEATER_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI_CS_Pin|UI_485_DC_Pin|UI_485_TX_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Relay5_RX_LED_Pin|Relay5_ST_LED_Pin|Relay5_DC_Pin|Relay3_ST_LED_Pin
                          |Relay3_DC_Pin|Relay8_TX_LED_Pin|Relay8_RX_LED_Pin|Relay8_ST_LED_Pin
                          |Relay8_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Relay2_TX_LED_Pin|Relay2_RX_LED_Pin|Relay2_ST_LED_Pin|Relay2_DC_Pin
                          |Relay1_TX_LED_Pin|Relay1_RX_LED_Pin|Relay1_ST_LED_Pin|Relay1_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Relay7_TX_LED_Pin Relay7_RX_LED_Pin Relay7_ST_LED_Pin Relay7_DC_Pin
                           Relay4_TX_LED_Pin Relay4_RX_LED_Pin Relay4_ST_LED_Pin Relay4_DC_Pin
                           Relay3_TX_LED_Pin Relay3_RX_LED_Pin */
  GPIO_InitStruct.Pin = Relay7_TX_LED_Pin|Relay7_RX_LED_Pin|Relay7_ST_LED_Pin|Relay7_DC_Pin
                          |Relay4_TX_LED_Pin|Relay4_RX_LED_Pin|Relay4_ST_LED_Pin|Relay4_DC_Pin
                          |Relay3_TX_LED_Pin|Relay3_RX_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : COM_4CH_SEL_Pin */
  GPIO_InitStruct.Pin = COM_4CH_SEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(COM_4CH_SEL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SYS_LED2_Pin SYS_LED1_Pin Relay6_TX_LED_Pin Relay6_RX_LED_Pin
                           Relay6_ST_LED_Pin Relay6_DC_Pin Relay5_TX_LED_Pin UI_485_RX_LED_Pin
                           UI_485_ST_LED_Pin */
  GPIO_InitStruct.Pin = SYS_LED2_Pin|SYS_LED1_Pin|Relay6_TX_LED_Pin|Relay6_RX_LED_Pin
                          |Relay6_ST_LED_Pin|Relay6_DC_Pin|Relay5_TX_LED_Pin|UI_485_RX_LED_Pin
                          |UI_485_ST_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : REPEATER_LED_Pin */
  GPIO_InitStruct.Pin = REPEATER_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(REPEATER_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : COM_MODE_Pin */
  GPIO_InitStruct.Pin = COM_MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(COM_MODE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_CS_Pin UI_485_DC_Pin UI_485_TX_LED_Pin */
  GPIO_InitStruct.Pin = SPI_CS_Pin|UI_485_DC_Pin|UI_485_TX_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay5_RX_LED_Pin Relay5_ST_LED_Pin Relay5_DC_Pin Relay3_ST_LED_Pin
                           Relay3_DC_Pin Relay8_TX_LED_Pin Relay8_RX_LED_Pin Relay8_ST_LED_Pin
                           Relay8_DC_Pin */
  GPIO_InitStruct.Pin = Relay5_RX_LED_Pin|Relay5_ST_LED_Pin|Relay5_DC_Pin|Relay3_ST_LED_Pin
                          |Relay3_DC_Pin|Relay8_TX_LED_Pin|Relay8_RX_LED_Pin|Relay8_ST_LED_Pin
                          |Relay8_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay2_TX_LED_Pin Relay2_RX_LED_Pin Relay2_ST_LED_Pin Relay2_DC_Pin
                           Relay1_TX_LED_Pin Relay1_RX_LED_Pin Relay1_ST_LED_Pin Relay1_DC_Pin */
  GPIO_InitStruct.Pin = Relay2_TX_LED_Pin|Relay2_RX_LED_Pin|Relay2_ST_LED_Pin|Relay2_DC_Pin
                          |Relay1_TX_LED_Pin|Relay1_RX_LED_Pin|Relay1_ST_LED_Pin|Relay1_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : DIP_ADD7_Pin DIP_ADD6_Pin DIP_ADD5_Pin DIP_ADD4_Pin
                           DIP_ADD3_Pin DIP_ADD2_Pin DIP_ADD1_Pin DIP_ADD0_Pin */
  GPIO_InitStruct.Pin = DIP_ADD7_Pin|DIP_ADD6_Pin|DIP_ADD5_Pin|DIP_ADD4_Pin
                          |DIP_ADD3_Pin|DIP_ADD2_Pin|DIP_ADD1_Pin|DIP_ADD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC2, SYSCFG_SWITCH_PC2_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC3, SYSCFG_SWITCH_PC3_CLOSE);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


unsigned short CRC16(unsigned char *crcdata, unsigned short usDataLen){

	unsigned short crc = 0xffff;

	for(int i=0;i<usDataLen ; i++){
		crc = crc^((*crcdata) << 8);
		crcdata++;
		for(int j=0;j<8;j++){
			if(crc & 0x8000){
				crc = (crc << 1) ^ 0x1021;
			}
			else{
				crc = crc << 1;
			}
		}
	}

	return crc;
}

void LED_Control(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin , uint16_t Staus){

  if(Staus == LED_On){
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
  }
  else if(Staus == LED_Off){
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
  }
}

void Board_Config(uint8_t Board){

	int High_Br = 1500000;
	int Low_Br = 200000;

	if(DIP_Value_tmp[7] == 0){
		Low_Br = 200000;
	}
	else if(DIP_Value_tmp[7] == 1){
		Low_Br = 400000;
	}

	if(Board == Recever_Board){

	  hlpuart1.Instance = LPUART1;
	  hlpuart1.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&hlpuart1) != HAL_OK){Error_Handler();}

	  huart6.Instance = USART6;
	  huart6.Init.BaudRate = Low_Br;
	  if (HAL_UART_Init(&huart6) != HAL_OK){Error_Handler();}

	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = Low_Br;
	  if (HAL_UART_Init(&huart1) != HAL_OK){Error_Handler();}

	  huart3.Instance = USART3;
	  huart3.Init.BaudRate = Low_Br;
	  if (HAL_UART_Init(&huart3) != HAL_OK){Error_Handler();}

	  huart7.Instance = UART7;
	  huart7.Init.BaudRate = Low_Br;
	  if (HAL_UART_Init(&huart7) != HAL_OK){Error_Handler();}


	  /*
	    PA2     ------> USART2_TX
		PA3     ------> USART2_RX

		PA0     ------> UART4_TX
		PA1     ------> UART4_RX

		PB5     ------> UART5_RX
		PB6     ------> UART5_TX

		PE0     ------> UART8_RX
		PE1     ------> UART8_TX.
		*/
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	}

	else if(Board == Repearter_Board){

	  hlpuart1.Instance = LPUART1;
	  hlpuart1.Init.BaudRate = Low_Br;
	  if (HAL_UART_Init(&hlpuart1) != HAL_OK){Error_Handler();}

	  huart6.Instance = USART6;
	  huart6.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart6) != HAL_OK){Error_Handler();}

	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart1) != HAL_OK){Error_Handler();}

	  huart3.Instance = USART3;
	  huart3.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart3) != HAL_OK){Error_Handler();}

	  huart7.Instance = UART7;
	  huart7.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart7) != HAL_OK){Error_Handler();}

	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart2) != HAL_OK){Error_Handler();}

	  huart4.Instance = UART4;
	  huart4.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart4) != HAL_OK){Error_Handler();}

	  huart8.Instance = UART8;
	  huart8.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart8) != HAL_OK){Error_Handler();}

	  huart5.Instance = UART5;
	  huart5.Init.BaudRate = High_Br;
	  if (HAL_UART_Init(&huart5) != HAL_OK){Error_Handler();}
	}
	//	HAL_Delay(100);
	/* hlpuart1 RX Interrupt  Enable */

//	/* Process Unlocked */
	__HAL_UNLOCK(&hlpuart1);
	/* Enable the UART Parity Error Interrupt */
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_PE);
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_ERR);
	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE);

//	HAL_UART_Receive_IT (&hlpuart1, &UI_UART_buf_tmp, 1);
}


void Read_Sub_Version(void){

	  if(CM_Board == Recever_Board){

		  for(int j=1; j<5 ; j++){
			  Sub_Cmd_Func_V(j,0);
			  Check_UI_UART_Receive(UI_UART_Receive_complete);
		  }
		  if(DIP_Value_tmp[7] == 0){
			  Sub_Rx_Wait(CM_Board,100);
		  }
		  else{
			  Sub_Rx_Wait(CM_Board,50);
		  }

		  Check_Sub_UART_ComV_Receive(0);

		  for(int k=0 ; k<1; k++){
			  for(int i=1; i<9;i++){
				  for(int j=1; j<5 ; j++){
					  Sub_Cmd_Func_V(j,i);
					  Check_UI_UART_Receive(UI_UART_Receive_complete);
				  }
				  if(DIP_Value_tmp[7] == 0){
					  Sub_Rx_Wait(CM_Board,100);
				  }
				  else{
					  Sub_Rx_Wait(CM_Board,50);
				  }

				  //HAL_Delay(300);
				  Check_Sub_UART_ComV_Receive(i);
			  }
		  }
		  HAL_Delay(500);
	  }
	  else if(CM_Board == Repearter_Board){
		  for(int i=0; i<1;i++){
			  for(int j=1; j<9 ; j++){
				  Sub_Cmd_Func_V(j,1);
			  }
			  Sub_Rx_Wait(CM_Board,20);
			  Check_Sub_UART_ComV_Receive(1);

			  //HAL_Delay(500);
			  /*
			  for(int i=0; i<500; i++){
				  Check_UI_UART_Receive(UI_UART_Receive_complete);
				  HAL_Delay(1);
			  }
			  */

		  }
	  }

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
