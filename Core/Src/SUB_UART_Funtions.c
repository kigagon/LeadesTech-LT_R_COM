/*
 * SUB_UART_Funtions.c
 *
 *  Created on: Nov 25, 2024
 *      Author: root
 */


#include "main.h"
#include "SUB_UART_Funtions.h"
#include "UI_UART_Funtions.h"

void Sub_Cmd_TX_LED_On(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_TX_LED_GPIO_Port, Relay1_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_TX_LED_GPIO_Port, Relay2_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_TX_LED_GPIO_Port, Relay3_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_TX_LED_GPIO_Port, Relay4_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_TX_LED_GPIO_Port, Relay5_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_TX_LED_GPIO_Port, Relay6_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_TX_LED_GPIO_Port, Relay7_TX_LED_Pin , LED_On);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_TX_LED_GPIO_Port, Relay8_TX_LED_Pin , LED_On);
	}
}

void Sub_Cmd_TX_LED_Off(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_TX_LED_GPIO_Port, Relay1_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_TX_LED_GPIO_Port, Relay2_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_TX_LED_GPIO_Port, Relay3_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_TX_LED_GPIO_Port, Relay4_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_TX_LED_GPIO_Port, Relay5_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_TX_LED_GPIO_Port, Relay6_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_TX_LED_GPIO_Port, Relay7_TX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_TX_LED_GPIO_Port, Relay8_TX_LED_Pin , LED_Off);
	}
}

void Sub_Cmd_RX_LED_On(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_RX_LED_GPIO_Port, Relay1_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_RX_LED_GPIO_Port, Relay2_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_RX_LED_GPIO_Port, Relay3_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_RX_LED_GPIO_Port, Relay4_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_RX_LED_GPIO_Port, Relay5_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_RX_LED_GPIO_Port, Relay6_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_RX_LED_GPIO_Port, Relay7_RX_LED_Pin , LED_On);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_RX_LED_GPIO_Port, Relay8_RX_LED_Pin , LED_On);
	}
}

void Sub_Cmd_RX_LED_Off(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_RX_LED_GPIO_Port, Relay1_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_RX_LED_GPIO_Port, Relay2_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_RX_LED_GPIO_Port, Relay3_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_RX_LED_GPIO_Port, Relay4_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_RX_LED_GPIO_Port, Relay5_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_RX_LED_GPIO_Port, Relay6_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_RX_LED_GPIO_Port, Relay7_RX_LED_Pin , LED_Off);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_RX_LED_GPIO_Port, Relay8_RX_LED_Pin , LED_Off);
	}
}

void Sub_Cmd_ST_LED_On(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_ST_LED_GPIO_Port, Relay1_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_ST_LED_GPIO_Port, Relay2_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_ST_LED_GPIO_Port, Relay3_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_ST_LED_GPIO_Port, Relay4_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_ST_LED_GPIO_Port, Relay5_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_ST_LED_GPIO_Port, Relay6_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_ST_LED_GPIO_Port, Relay7_ST_LED_Pin , LED_On);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_ST_LED_GPIO_Port, Relay8_ST_LED_Pin , LED_On);
	}
}

void Sub_Cmd_ST_LED_Off(uint8_t LED_Num){
	if(LED_Num == 1){
		LED_Control(Relay1_ST_LED_GPIO_Port, Relay1_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 2){
		LED_Control(Relay2_ST_LED_GPIO_Port, Relay2_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 3){
		LED_Control(Relay3_ST_LED_GPIO_Port, Relay3_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 4){
		LED_Control(Relay4_ST_LED_GPIO_Port, Relay4_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 5){
		LED_Control(Relay5_ST_LED_GPIO_Port, Relay5_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 6){
		LED_Control(Relay6_ST_LED_GPIO_Port, Relay6_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 7){
		LED_Control(Relay7_ST_LED_GPIO_Port, Relay7_ST_LED_Pin , LED_Off);
	}
	else if(LED_Num == 8){
		LED_Control(Relay8_ST_LED_GPIO_Port, Relay8_ST_LED_Pin , LED_Off);
	}
}


void Sub_Cmd_DC_On(uint8_t UART_Num){
	if(UART_Num == 1){
		HAL_GPIO_WritePin(Relay1_DC_GPIO_Port, Relay1_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 2){
		HAL_GPIO_WritePin(Relay2_DC_GPIO_Port, Relay2_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 3){
		HAL_GPIO_WritePin(Relay3_DC_GPIO_Port, Relay3_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 4){
		HAL_GPIO_WritePin(Relay4_DC_GPIO_Port, Relay4_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 5){
		HAL_GPIO_WritePin(Relay5_DC_GPIO_Port, Relay5_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 6){
		HAL_GPIO_WritePin(Relay6_DC_GPIO_Port, Relay6_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 7){
		HAL_GPIO_WritePin(Relay7_DC_GPIO_Port, Relay7_DC_Pin, GPIO_PIN_SET);
	}
	else if(UART_Num == 8){
		HAL_GPIO_WritePin(Relay8_DC_GPIO_Port, Relay8_DC_Pin, GPIO_PIN_SET);
	}
}

void Sub_Cmd_DC_Off(uint8_t UART_Num){
	if(UART_Num == 1){
		HAL_GPIO_WritePin(Relay1_DC_GPIO_Port, Relay1_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 2){
		HAL_GPIO_WritePin(Relay2_DC_GPIO_Port, Relay2_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 3){
		HAL_GPIO_WritePin(Relay3_DC_GPIO_Port, Relay3_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 4){
		HAL_GPIO_WritePin(Relay4_DC_GPIO_Port, Relay4_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 5){
		HAL_GPIO_WritePin(Relay5_DC_GPIO_Port, Relay5_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 6){
		HAL_GPIO_WritePin(Relay6_DC_GPIO_Port, Relay6_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 7){
		HAL_GPIO_WritePin(Relay7_DC_GPIO_Port, Relay7_DC_Pin, GPIO_PIN_RESET);
	}
	else if(UART_Num == 8){
		HAL_GPIO_WritePin(Relay8_DC_GPIO_Port, Relay8_DC_Pin, GPIO_PIN_RESET);
	}
}

void Sub_Cmd_TX_UART(uint8_t UART_Num,  const uint8_t *Uart_Tx_Data, uint16_t Size){

	if(UART_Num == 1){
		HAL_UART_Transmit(&huart6, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 2){
		HAL_UART_Transmit(&huart1, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 3){
		HAL_UART_Transmit(&huart3, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 4){
		HAL_UART_Transmit(&huart7, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 5){
		HAL_UART_Transmit(&huart2, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 6){
		HAL_UART_Transmit(&huart4, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 7){
		HAL_UART_Transmit(&huart8, Uart_Tx_Data, Size, 1000);
	}
	else if(UART_Num == 8){
		HAL_UART_Transmit(&huart5, Uart_Tx_Data, Size, 1000);
	}
}

void Sub_Cmd_TX_UART_DMA(uint8_t UART_Num,  const uint8_t *Uart_Tx_Data_tmp, uint16_t Size){

	if(UART_Num == 1){
		HAL_UART_Transmit_DMA(&huart6, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 2){
		HAL_UART_Transmit_DMA(&huart1, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 3){
		HAL_UART_Transmit_DMA(&huart3, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 4){
		HAL_UART_Transmit_DMA(&huart7, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 5){
		HAL_UART_Transmit_DMA(&huart2, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 6){
		HAL_UART_Transmit_DMA(&huart4, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 7){
		HAL_UART_Transmit_DMA(&huart8, Uart_Tx_Data_tmp, Size);
	}
	else if(UART_Num == 8){
		HAL_UART_Transmit_DMA(&huart5, Uart_Tx_Data_tmp, Size);
	}

}
void Sub_Cmd_RX_UART(uint8_t UART_Num,int Rx_Num){
	if(UART_Num == 1){
		HAL_UART_Receive_DMA(&huart6, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 2){
		HAL_UART_Receive_DMA(&huart1, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 3){
		HAL_UART_Receive_DMA(&huart3, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 4){
		HAL_UART_Receive_DMA(&huart7, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 5){
		HAL_UART_Receive_DMA(&huart2, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 6){
		HAL_UART_Receive_DMA(&huart4, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 7){
		HAL_UART_Receive_DMA(&huart8, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 8){
		HAL_UART_Receive_DMA(&huart5, SUB_UART_RX_buf_DMA_tmp[UART_Num-1], Rx_Num);
	}
}

void Sub_Cmd_RX_UART_Stop(uint8_t UART_Num){
	if(UART_Num == 1){
		HAL_UART_DMAStop(&huart6);
	}
	else if(UART_Num == 2){
		HAL_UART_DMAStop(&huart1);
	}
	else if(UART_Num == 3){
		HAL_UART_DMAStop(&huart3);
	}
	else if(UART_Num == 4){
		HAL_UART_DMAStop(&huart7);
	}
	else if(UART_Num == 5){
		HAL_UART_DMAStop(&huart2);
	}
	else if(UART_Num == 6){
		HAL_UART_DMAStop(&huart4);
	}
	else if(UART_Num == 7){
		HAL_UART_DMAStop(&huart8);
	}
	else if(UART_Num == 8){
		HAL_UART_DMAStop(&huart5);
	}
}

void Sub_Cmd_RX_UART_Abort(uint8_t UART_Num){
	if(UART_Num == 1){
		HAL_UART_Abort(&huart6);
	}
	else if(UART_Num == 2){
		HAL_UART_Abort(&huart1);
	}
	else if(UART_Num == 3){
		HAL_UART_Abort(&huart3);
	}
	else if(UART_Num == 4){
		HAL_UART_Abort(&huart7);
	}
	else if(UART_Num == 5){
		HAL_UART_Abort(&huart2);
	}
	else if(UART_Num == 6){
		HAL_UART_Abort(&huart4);
	}
	else if(UART_Num == 7){
		HAL_UART_Abort(&huart8);
	}
	else if(UART_Num == 8){
		HAL_UART_Abort(&huart5);
	}
}

void Sub_Cmd_Power_RX_UART(uint8_t UART_Num,int Rx_Num){

	if(UART_Num == 1){
		HAL_UART_Receive_DMA(&huart6, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 2){
		HAL_UART_Receive_DMA(&huart1, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 3){
		HAL_UART_Receive_DMA(&huart3, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 4){
		HAL_UART_Receive_DMA(&huart7, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 5){
		HAL_UART_Receive_DMA(&huart2, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 6){
		HAL_UART_Receive_DMA(&huart4, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 7){
		HAL_UART_Receive_DMA(&huart8, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
	else if(UART_Num == 8){
		HAL_UART_Receive_DMA(&huart5, SUB_UART_POW_RX_DMA_buf[UART_Num-1], Rx_Num);
	}
}

void Sub_Tx_Wait(uint8_t Board_type, uint8_t Ms){

	uint8_t Count_tmp;
	for(int i=0; i<(Ms * 100) ;i++){
		//Check_UI_UART_Receive(UI_UART_Receive_complete);
		delay_us(10);
		Count_tmp = 0;

		if(Board_type == Recever_Board){
			for(int j=0;j<4; j++){
				Count_tmp+= SUB_UART_Tx_Comp[j];
			}
			if(Count_tmp == 4){
				break;
			}
		}
		else if(Board_type == Repearter_Board){
			for(int j=0;j<8; j++){
				Count_tmp+= SUB_UART_Tx_Comp[j];
			}
			if(Count_tmp == 8){
				 break;
			}
		}
	}
	for(int i=1; i<8 ;i++){
		Sub_Cmd_TX_LED_Off(i);
		SUB_UART_Tx_Comp[i-1] = 0;
	}
}

void Sub_Rx_Wait(uint8_t Board_type, uint8_t Ms){

	uint8_t Count_tmp;
	for(int i=0; i<(Ms * 100) ;i++){
		Check_UI_UART_Receive(UI_UART_Receive_complete);
		delay_us(10);
		Count_tmp = 0;
		if(Board_type == Recever_Board){
			for(int j=0;j<4; j++){
				Count_tmp+= SUB_UART_Rx_Comp[j];
			}
			if(Count_tmp == 4){
				break;
			}
		}
		else if(Board_type == Repearter_Board){
			for(int j=0;j<8; j++){
				Count_tmp+= SUB_UART_Rx_Comp[j];
			}
			if(Count_tmp == 8){
				 break;
			}
		}
	}
	for(int i=1; i<8 ;i++){
		Sub_Cmd_RX_LED_Off(i);
		SUB_UART_Rx_Comp[i-1] = 0;
	}

}

void Sub_Cmd_RX_DMA_ST(uint8_t Num){
/*
	if(SUB_UART_Tx_Command[0]=='A'){
		Sub_Cmd_RX_UART(Num,UART_Com_A_len);
	}
	else if(SUB_UART_Tx_Command[0]=='P'){
		Sub_Cmd_Power_RX_UART(Num,15);
	}
	else if(SUB_UART_Tx_Command[0]=='V'){
		Sub_Cmd_RX_UART(Num,Rep_Version_Data_Number);
	}
	else if(SUB_UART_Tx_Command[0]=='v'){
		Sub_Cmd_RX_UART(Num,Com_Version_Data_Number);
	}
	*/

	if(SUB_UART_Tx_Command[Num-1]=='A'){
		Sub_Cmd_RX_UART(Num,UART_Com_A_len);
	}
	else if(SUB_UART_Tx_Command[Num-1]=='P'){
		Sub_Cmd_Power_RX_UART(Num,15);
	}
	else if(SUB_UART_Tx_Command[Num-1]=='V'){
		Sub_Cmd_RX_UART(Num,Rep_Version_Data_Number);
	}
	else if(SUB_UART_Tx_Command[Num-1]=='v'){
		Sub_Cmd_RX_UART(Num,Com_Version_Data_Number);
	}

}
// 'A' Repeater information request: Read all information of the requested Sub system.
void Sub_Cmd_Func_A(uint8_t Main_Group, uint8_t Sub_Group){

//	uint8_t Uart_Tx_Data[8];

	SUB_UART_TX_buf[Main_Group-1][0] = 0x53;
	SUB_UART_TX_buf[Main_Group-1][1] = 0x54;
	SUB_UART_TX_buf[Main_Group-1][2] = 0x55;
	SUB_UART_TX_buf[Main_Group-1][3] = 0x41;
	if(CM_Board == Recever_Board){
		SUB_UART_TX_buf[Main_Group-1][4] = Main_Group +(DIP_Value -1)*4;	// receiver
		SUB_UART_TX_buf[Main_Group-1][5] = Sub_Group;
	}
	else if(CM_Board == Repearter_Board){
//		SUB_UART_TX_buf[Main_Group-1][4] = Main_Group;	// receiver
//		SUB_UART_TX_buf[Main_Group-1][5] = Sub_Group;						// relay
		SUB_UART_TX_buf[Main_Group-1][4] = 1;	// receiver
		SUB_UART_TX_buf[Main_Group-1][5] = Main_Group;						// relay
	}

	SUB_UART_TX_buf[Main_Group-1][6] = SUB_UART_TX_buf[Main_Group-1][2]^SUB_UART_TX_buf[Main_Group-1][3]
									^SUB_UART_TX_buf[Main_Group-1][4]^SUB_UART_TX_buf[Main_Group-1][5];
	SUB_UART_TX_buf[Main_Group-1][7] = 0x45;
	SUB_UART_TX_buf[Main_Group-1][8] = 0x44;

	Sub_Cmd_RX_LED_Off(Main_Group);
	Sub_Cmd_TX_LED_On(Main_Group);
	Sub_Cmd_RX_UART_Abort(Main_Group);

	Sub_Cmd_DC_On(Main_Group);
	for(int i=0;i< UART_buf_len; i++){
		SUB_UART_RX_buf_DMA_tmp[Main_Group-1][i] = 0;
	}

	//Sub_Cmd_TX_UART(Main_Group, SUB_UART_TX_buf[Main_Group-1], 9);
	Sub_Cmd_TX_UART_DMA(Main_Group, SUB_UART_TX_buf[Main_Group-1], 9);

	SUB_UART_Tx_Command[Main_Group -1]='A';

}

void Sub_Cmd_Func_S(int num)
{

	uint8_t Main_Group=0;
	int Tx_data_Len;

	if(CM_Board == Recever_Board){
		Main_Group = Set_Command_Data[num][4];
	}
	else if(CM_Board == Repearter_Board){
		Main_Group = Set_Command_Data[num][5];					// relay
	}

//	if(Set_Command_Data[num][3] == 0x53){	//'S' Repeater settings: Repeater output settings
//		Tx_data_Len = 14;
//	}
//	else if(Set_Command_Data[num][3] == 0x43){	//'C' Delete repeater information
//
//	}
//	else if(Set_Command_Data[num][3] == 0x49){	//'I' Register repeater information
//
//	}
//	else if(Set_Command_Data[num][3] == 0x52){	//'R' Repeater recovery request
//
//	}
//	else if(Set_Command_Data[num][3] == 0x44){	//'D' Registering repeater accumulated information
//
//	}
//	else if(Set_Command_Data[num][3] == 0x47){	//'G' Repeater accumulation setting
//
//	}
//	else if(Set_Command_Data[num][3] == 0x47){	//'O' Repeater All Output Setting
//
//	}

	Tx_data_Len = 14;

	for(int i = 0; i<Tx_data_Len ; i++){
		SUB_UART_TX_buf[Main_Group-1][i] = Set_Command_Data[num][i];
	}

	if(CM_Board == Recever_Board){

	}
	else if(CM_Board == Repearter_Board){
	}

	Sub_Cmd_DC_On(Main_Group);
	Sub_Cmd_RX_LED_Off(Main_Group);
	Sub_Cmd_TX_LED_On(Main_Group);

	HAL_Delay(1);

	//Sub_Cmd_TX_UART(Main_Group, SUB_UART_TX_buf[Main_Group-1], 1);

	Sub_Cmd_TX_UART(Main_Group, SUB_UART_TX_buf[Main_Group-1], Tx_data_Len);

	if(CM_Board  ==  Repearter_Board){
		HAL_Delay((Tx_data_Len/150)+1);
	}
	else{
		HAL_Delay((Tx_data_Len/20)+1);
	}
	Sub_Cmd_DC_Off(Main_Group);
	Sub_Cmd_TX_LED_Off(Main_Group);
	if(CM_Board  ==  Repearter_Board){
		HAL_Delay(10);
	}
	else{
		HAL_Delay(30);
	}

}

/* 'P' Request for power board information of the relay panel:
 * Read the requested power board information of the relay panel.*/
///*

void Sub_Cmd_Func_P(uint8_t Main_Group){

	uint8_t Uart_Tx_Data[9];

 	Uart_Tx_Data[0] = 0x53;
	Uart_Tx_Data[1] = 0x54;
	Uart_Tx_Data[2] = 0x55;
	Uart_Tx_Data[3] = 0x50;

	Uart_Tx_Data[4] = (DIP_Value - 1)*4 + Main_Group;

	Uart_Tx_Data[5] = 0;
	Uart_Tx_Data[6] = Uart_Tx_Data[2]^Uart_Tx_Data[3]^Uart_Tx_Data[4]^Uart_Tx_Data[5];
	Uart_Tx_Data[7] = 0x45;
	Uart_Tx_Data[8] = 0x44;

	Sub_Cmd_RX_LED_Off(Main_Group);
	Sub_Cmd_TX_LED_On(Main_Group);
	Sub_Cmd_RX_UART_Abort(Main_Group);

	for(int i=0;i< UART_buf_len; i++){
		SUB_UART_RX_buf_DMA_tmp[Main_Group-1][i] = 0;
	}
	if(Main_Group == 3){
		Sub_Cmd_DC_On(Main_Group);
	}
	Sub_Cmd_DC_On(Main_Group);
	HAL_Delay(1);


	//Sub_Cmd_TX_UART(Main_Group, SUB_UART_TX_buf[Main_Group-1], 9);

	//Sub_Cmd_TX_UART_DMA(Main_Group, Uart_Tx_Data, 9);

	Sub_Cmd_TX_UART(Main_Group, Uart_Tx_Data, 9);
////
//	HAL_Delay(10);
	Sub_Cmd_DC_Off(Main_Group);
	Sub_Cmd_TX_LED_Off(Main_Group);

	SUB_UART_Receive_complete[Main_Group-1] = 0;
	SUB_UART_Receive_Command[Main_Group-1] = 'P';
//	Sub_Cmd_Power_RX_UART(Main_Group,UART_POW_buf_len);
	SUB_UART_Tx_Command[Main_Group -1]='P';
	Sub_Cmd_RX_DMA_ST(Main_Group);
}


/* 'T' Request : repeater powerboard battery test command*/
///*
void Sub_Cmd_Func_T(uint8_t Main_Group){

	uint8_t Uart_Tx_Data[9];

	Uart_Tx_Data[0] = 0x53;
	Uart_Tx_Data[1] = 0x54;
	Uart_Tx_Data[2] = 0x55;
	Uart_Tx_Data[3] = 0x54;
	Uart_Tx_Data[4] = Main_Group;
	Uart_Tx_Data[5] = 0x01;
	Uart_Tx_Data[6] = Uart_Tx_Data[2]^Uart_Tx_Data[3]^Uart_Tx_Data[4]^Uart_Tx_Data[5];
	Uart_Tx_Data[7] = 0x45;
	Uart_Tx_Data[8] = 0x44;

	Sub_Cmd_RX_LED_Off(Main_Group - (DIP_Value -1) * 4);
	Sub_Cmd_TX_LED_On(Main_Group - (DIP_Value -1) * 4);
	Sub_Cmd_DC_On(Main_Group - (DIP_Value -1) * 4);
	Sub_Cmd_TX_UART(Main_Group - (DIP_Value -1) * 4, Uart_Tx_Data, 9);
	Sub_Cmd_DC_Off(Main_Group - (DIP_Value -1) * 4);
	Sub_Cmd_TX_LED_Off(Main_Group - (DIP_Value -1) * 4);
}



/*
uint16_t cal_crc16 = 0;
uint16_t cal_crc16_tmp = 0;
uint8_t Crc_Data[Repeater_Data_Total - 6];
void Check_Sub_UART_ComA_Receive(uint8_t Sub_Group){



	uint8_t Main_Group_tmp, Sub_Group_tmp;

	uint8_t SUB_UART_RX_buf_tmp[Repeater_Data_Total];

	cal_crc16 = 0;
	cal_crc16_tmp = 0;

	if(CM_Board == Recever_Board){
		for(int i=0; i< 4 ; i++){

			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][0] == 'T')){

			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					 SUB_UART_RX_buf_DMA_tmp[i][j] = SUB_UART_RX_buf_tmp[j];
				}
				SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total -1] = 'D';
			}

			if((DIP_Value%2) ==1){
				Main_Group_tmp = i;
			}
			else if((DIP_Value%2) == 0){
				Main_Group_tmp = i+4;
			}

			Sub_Group_tmp = Sub_Group -1;

			for(int j=0; j< (Repeater_Data_Total - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_DMA_tmp[i][j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);


				Sub_Group_tmp = SUB_UART_RX_buf_DMA_tmp[i][5] - 1;


				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_DMA_tmp[i][j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}


	}
	else if(CM_Board == Repearter_Board){
		for(int i=0; i< 8 ; i++){

			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][0] == 'T')){

			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					 SUB_UART_RX_buf_DMA_tmp[i][j] = SUB_UART_RX_buf_tmp[j];
				}
				SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total -1] = 'D';
			}

			Main_Group_tmp = i;
			Sub_Group_tmp = 0;

			for(int j=0; j< (Repeater_Data_Total - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_DMA_tmp[i][j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_DMA_tmp[i][Repeater_Data_Total - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);

				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_DMA_tmp[i][j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Group_Data[Main_Group_tmp][Sub_Group_tmp][4] = DIP_Value;
				Group_Data[Main_Group_tmp][Sub_Group_tmp][5] = SUB_UART_RX_buf_DMA_tmp[i][4];
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}
	}
}

*/



void Check_Sub_UART_ComA_Receive(uint8_t Sub_Group){

	uint16_t cal_crc16 = 0;
	uint16_t cal_crc16_tmp = 0;
	uint8_t Crc_Data[Repeater_Data_Total - 6];
	uint8_t SUB_UART_RX_buf_tmp[Repeater_Data_Total];

	uint8_t Main_Group_tmp, Sub_Group_tmp;

	cal_crc16 = 0;
	cal_crc16_tmp = 0;

	if(CM_Board == Recever_Board){
		for(int i=0; i< 4 ; i++){

			for(int j=0; j<(Repeater_Data_Total -1); j++){
				SUB_UART_RX_buf_tmp[j] = 0;
			}
			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
				for(int j=0; j<(Repeater_Data_Total ); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j];
				}
			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}

				SUB_UART_RX_buf_tmp[Repeater_Data_Total -1] = 'D';
			}

			if((DIP_Value%2) ==1){
				Main_Group_tmp = i;
			}
			else if((DIP_Value%2) == 0){
				Main_Group_tmp = i+4;
			}

			Sub_Group_tmp = Sub_Group -1;

			for(int j=0; j< (Repeater_Data_Total - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, Repeater_Data_Total - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Repeater_Data_Total - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_tmp[Repeater_Data_Total - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);


				Sub_Group_tmp = SUB_UART_RX_buf_tmp[5] - 1;


				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}

	}
	else if(CM_Board == Repearter_Board){
		for(int i=0; i< 8 ; i++){

			for(int j=0; j<(Repeater_Data_Total -1); j++){
				SUB_UART_RX_buf_tmp[j] = 0;
			}
			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
				for(int j=0; j<(Repeater_Data_Total); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j];
				}
			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Repeater_Data_Total -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}

				SUB_UART_RX_buf_tmp[Repeater_Data_Total -1] = 'D';
			}

			Main_Group_tmp = i;
			Sub_Group_tmp = 0;

			for(int j=0; j< (Repeater_Data_Total - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, Repeater_Data_Total - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Repeater_Data_Total - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_tmp[Repeater_Data_Total - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);

				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Group_Data[Main_Group_tmp][Sub_Group_tmp][5] = SUB_UART_RX_buf_tmp[5];
				Group_Data[Main_Group_tmp][Sub_Group_tmp][4] = DIP_Value;
				//Group_Data[Main_Group_tmp][Sub_Group_tmp][5] = SUB_UART_RX_buf_DMA_tmp[i][4];
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Repeater_Data_Total ; j++){
					Group_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}
	}
}

void Check_Sub_UART_ComP_Receive(void){
	uint8_t Crc_Data = 0;

	uint8_t Group_Num_tmp = 0;


	if(CM_Board == Recever_Board){
		for(int i=0; i< 4 ; i++){

			Crc_Data = 0;
			Crc_Data = SUB_UART_POW_RX_DMA_buf[i][2]^SUB_UART_POW_RX_DMA_buf[i][3]^SUB_UART_POW_RX_DMA_buf[i][4]^
					SUB_UART_POW_RX_DMA_buf[i][5]^SUB_UART_POW_RX_DMA_buf[i][6]^SUB_UART_POW_RX_DMA_buf[i][7]^
					SUB_UART_POW_RX_DMA_buf[i][8]^SUB_UART_POW_RX_DMA_buf[i][9]^SUB_UART_POW_RX_DMA_buf[i][10]^
					SUB_UART_POW_RX_DMA_buf[i][11];

			if(Crc_Data == SUB_UART_POW_RX_DMA_buf[i][12]){
				Sub_Cmd_RX_LED_On(i+1);

				if((DIP_Value%2) ==1){
					Group_Num_tmp = i;
				}
				else if((DIP_Value%2) == 0){
					Group_Num_tmp = i+4;
				}



				for(int j=0; j<Pow_Bod_Data_Total ; j++){
					Pow_Bod_Data[Group_Num_tmp][j] = SUB_UART_POW_RX_DMA_buf[i][j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Pow_Bod_Data_Total ; j++){
					Pow_Bod_Data[Group_Num_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}


	}
	else if(CM_Board == Repearter_Board){

	}
}

void Check_Sub_POW_UART_Receive(void){

	int l;
	uint8_t Crc_Data = 0;

	uint8_t Receive_Cnt = 0;
	uint8_t Group_Num_tmp = 0;

	if(CM_Board == Repearter_Board){
		Receive_Cnt = 4;
	}
	else{
		Receive_Cnt = 8;
	}

	for(int i=0; i<8 ; i++){
		Sub_Cmd_RX_UART_Abort(i);
	}
	for(int i=0; i<Receive_Cnt ; i++){
		l = 0;
		for(int j=2; j<UART_POW_buf_len; j++){
			if((SUB_UART_POW_RX_buf[i][j-2] == 0x53) & (SUB_UART_POW_RX_buf[i][j-1] == 0x54)){
				l = j;
			}
		}
		for(int j=0; j<UART_POW_buf_len - l; j++){
			SUB_UART_POW_RX_buf[i][j] = SUB_UART_POW_RX_buf[i][j+l - 2];
		}

		for(int k=0; k<15 ; k++){
			Pow_Bod_Data[i][k] = 0;
		}

		Crc_Data = 0;
		Crc_Data = SUB_UART_POW_RX_buf[i][2]^SUB_UART_POW_RX_buf[i][3]^SUB_UART_POW_RX_buf[i][4]^
				SUB_UART_POW_RX_buf[i][5]^SUB_UART_POW_RX_buf[i][6]^SUB_UART_POW_RX_buf[i][7]^
				SUB_UART_POW_RX_buf[i][8]^SUB_UART_POW_RX_buf[i][9]^SUB_UART_POW_RX_buf[i][10]^
				SUB_UART_POW_RX_buf[i][11];
		if((Crc_Data == SUB_UART_POW_RX_buf[i][12]) & (SUB_UART_POW_RX_buf[i][0] == 0x53)){
			Sub_Cmd_RX_LED_On(i+1);

			if((DIP_Value == 1)|(DIP_Value == 2)){
				Group_Num_tmp = SUB_UART_POW_RX_buf[i][4]-1;
			}
			else if((DIP_Value == 3)|(DIP_Value == 4)){
				Group_Num_tmp = SUB_UART_POW_RX_buf[i][4]-1 - 8;
			}
			else if((DIP_Value == 5)|(DIP_Value == 6)){
				Group_Num_tmp = SUB_UART_POW_RX_buf[i][4]-1 - 16;
			}

			for(int k=0; k<15 ; k++){
				Pow_Bod_Data[Group_Num_tmp][k] = SUB_UART_POW_RX_buf[i][k];
				SUB_UART_Receive_Data_complete[i] = 1;
			}
			Sub_Cmd_RX_LED_Off(i+1);
		}
		else{
			if(CM_Board == Repearter_Board){
				if( (DIP_Value % 2) == 1){
					for(int k=0; k<15 ; k++){
						Pow_Bod_Data[i][k] = 0;
					}
				}
				else{
					for(int k=0; k<15 ; k++){
						Pow_Bod_Data[i+4][k] = 0;
					}
				}
			}
		}
		Check_UI_UART_Receive(UI_UART_Receive_complete);
	}


}


void Sub_UART_Rx_Com(uint8_t uart_num, uint8_t Rx_Data){

	  SUB_UART_RX_buf[uart_num][SUB_UART_buf_count[uart_num]] = Rx_Data;
	  SUB_UART_buf_count[uart_num]++;

	  if(SUB_UART_State[uart_num] == 0){
		  if((SUB_UART_RX_buf[uart_num][SUB_UART_buf_count[uart_num]-2] == 0x53) &&(SUB_UART_RX_buf[uart_num][SUB_UART_buf_count[uart_num]-1] == 0x54)){

			  SUB_UART_RX_buf[uart_num][0] = 0x53;
			  SUB_UART_RX_buf[uart_num][1] = 0x54;
			  SUB_UART_buf_count[uart_num] = 2;
			  SUB_UART_State[uart_num] = 1;
		  }
	  }
	  else{
		  if((SUB_UART_RX_buf[uart_num][SUB_UART_buf_count[uart_num] - 2 ] == 0x45) &&(SUB_UART_RX_buf[uart_num][SUB_UART_buf_count[uart_num] - 1] == 0x44)) {
			  SUB_UART_State[uart_num] = 0;
			  SUB_UART_buf_count[uart_num] = 0;
			  SUB_UART_Receive_complete[uart_num] = 1;
			  SUB_Rx_Cnt[uart_num]++;
			}
	  }



	  if(SUB_UART_buf_count[0] > UI_UART_buf_len){

		  SUB_UART_State[0] = 0;
		  SUB_UART_buf_count[0] = 0;
		  SUB_UART_Receive_complete[0] = 0;
	  }

}

void Sub_Cmd_Func_V(uint8_t Main_Group, uint8_t Sub_Group){

//	uint8_t Uart_Tx_Data[8];

	SUB_UART_TX_buf[Main_Group-1][0] = 0x53;
	SUB_UART_TX_buf[Main_Group-1][1] = 0x54;
	SUB_UART_TX_buf[Main_Group-1][2] = 0x55;
	SUB_UART_TX_buf[Main_Group-1][3] = 0x56;
	if(CM_Board == Recever_Board){
		SUB_UART_TX_buf[Main_Group-1][4] = Main_Group +(DIP_Value -1)*4;	// receiver
		SUB_UART_TX_buf[Main_Group-1][5] = Sub_Group;
	}
	else if(CM_Board == Repearter_Board){
//		SUB_UART_TX_buf[Main_Group-1][4] = Main_Group;	// receiver
//		SUB_UART_TX_buf[Main_Group-1][5] = Sub_Group;						// relay
		SUB_UART_TX_buf[Main_Group-1][4] = 1;	// receiver
		SUB_UART_TX_buf[Main_Group-1][5] = Main_Group;						// relay
	}

	SUB_UART_TX_buf[Main_Group-1][6] = SUB_UART_TX_buf[Main_Group-1][2]^SUB_UART_TX_buf[Main_Group-1][3]
									^SUB_UART_TX_buf[Main_Group-1][4]^SUB_UART_TX_buf[Main_Group-1][5];
	SUB_UART_TX_buf[Main_Group-1][7] = 0x45;
	SUB_UART_TX_buf[Main_Group-1][8] = 0x44;

	Sub_Cmd_RX_LED_Off(Main_Group);
	Sub_Cmd_TX_LED_On(Main_Group);
	Sub_Cmd_RX_UART_Abort(Main_Group);

	Sub_Cmd_DC_On(Main_Group);
	for(int i=0;i< UART_buf_len; i++){
		SUB_UART_RX_buf_DMA_tmp[Main_Group-1][i] = 0;
	}

	//Sub_Cmd_TX_UART(Main_Group, SUB_UART_TX_buf[Main_Group-1], 9);
	Sub_Cmd_TX_UART_DMA(Main_Group, SUB_UART_TX_buf[Main_Group-1], 9);

	if(Sub_Group == 0){
		SUB_UART_Tx_Command[Main_Group -1]='v';
	}
	else{
		SUB_UART_Tx_Command[Main_Group -1]='V';
	}
}

void Check_Sub_UART_ComV_Receive(uint8_t Sub_Group){

	uint16_t cal_crc16 = 0;
	uint16_t cal_crc16_tmp = 0;
	uint8_t Crc_Data[Rep_Version_Data_Number - 6];
	uint8_t Crc_Data1[Com_Version_Data_Number - 6];
	uint8_t SUB_UART_RX_buf_tmp[Rep_Version_Data_Number];
//	uint8_t SUB_UART_RX_buf_tmp1[Com_Version_Data_Number];

	uint8_t Main_Group_tmp, Sub_Group_tmp;

	int l;
	cal_crc16 = 0;
	cal_crc16_tmp = 0;

	if(Sub_Group == 0){
		if(CM_Board == Recever_Board){

			for(int i=1 ; i< 9; i++){
				for(int j=0; j<6; j++){
					Save_Com_Version_Data[i][j] = 0;
				}
			}
			for(int i=0; i< 4 ; i++){
				for(int j=0; j<(Com_Version_Data_Number -1); j++){
//					SUB_UART_RX_buf_tmp1[j] = 0;
				}

				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = 0;
				}

				if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
					for( l=0; l<(Rep_Version_Data_Number); l++){
						SUB_UART_RX_buf_tmp[l] = SUB_UART_RX_buf_DMA_tmp[i][l];
					}
				}
				else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
					for(int j=0; j<(Rep_Version_Data_Number -1); j++){
						SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
					}

					SUB_UART_RX_buf_tmp[Rep_Version_Data_Number -1] = 'D';
				}

				for(int j=0; j< (Com_Version_Data_Number - 6); j++){
					Crc_Data1[j] = SUB_UART_RX_buf_tmp[j+2];
				}

				cal_crc16 = 0;
				cal_crc16 = CRC16(Crc_Data1, Com_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

				cal_crc16_tmp = 0;
				cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Com_Version_Data_Number - 4]<<8 )&0xff00)
						| (SUB_UART_RX_buf_tmp[Com_Version_Data_Number - 3]&0x00ff));
				if(cal_crc16 == cal_crc16_tmp){
					if(cal_crc16 == 0){
						for(int j=0; j<6;j++){
							Save_Com_Version_Data[i+1][j] = 0;
						}
					}
					else{
						Sub_Cmd_RX_LED_On(i+1);
						for(int j=0; j<6;j++){
							Save_Com_Version_Data[i+1][j] = SUB_UART_RX_buf_tmp[6+j];
						}
					}
				}
			}
		}
		else{

		}
	}
	else{
		if(CM_Board == Recever_Board){
			for(int i=0; i< 4 ; i++){

				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = 0;
				}

				if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
					for(int j=0; j<(Rep_Version_Data_Number); j++){
						SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j];
					}
				}
				else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
					for(int j=0; j<(Rep_Version_Data_Number -1); j++){
						SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
					}

					SUB_UART_RX_buf_tmp[Rep_Version_Data_Number -1] = 'D';
				}

				if((DIP_Value%2) ==1){
					Main_Group_tmp = i;
				}
				else if((DIP_Value%2) == 0){
					Main_Group_tmp = i+4;
				}

				Sub_Group_tmp = Sub_Group -1;

				for(int j=0; j< (Rep_Version_Data_Number - 6); j++){
					Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
				}

				cal_crc16 = 0;
				cal_crc16 = CRC16(Crc_Data, Rep_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

				cal_crc16_tmp = 0;
				cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 4]<<8 )&0xff00)
						| (SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 3]&0x00ff));


				if(cal_crc16 == cal_crc16_tmp){

					if(cal_crc16 == 0){
						for(int j=0; j<Rep_Version_Data_Number ; j++){
							Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
						}
						SUB_UART_Receive_Data_complete[i] = 0;
					}
					else{
						Sub_Cmd_RX_LED_On(i+1);

						Sub_Group_tmp = SUB_UART_RX_buf_DMA_tmp[i][5] - 1;

						for(int j=0; j<Rep_Version_Data_Number ; j++){
							Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
						}
						SUB_UART_Receive_Data_complete[i] = 1;
						Sub_Cmd_RX_LED_Off(i+1);
					}
				}
				else{
					for(int j=0; j<Rep_Version_Data_Number ; j++){
						Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
						SUB_UART_Receive_Data_complete[i] = 1;
					}
				}
				if(i==1){
					if(SUB_UART_RX_buf_DMA_tmp[1][0] ==0 )
					HAL_Delay(1);
				}
			}

		}
		else if(CM_Board == Repearter_Board){
			for(int i=0; i< 8 ; i++){

				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = 0;
				}
				if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
					for(int j=0; j<(Rep_Version_Data_Number); j++){
						SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j];
					}
				}
				else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
					for(int j=0; j<(Rep_Version_Data_Number -1); j++){
						SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
					}

					SUB_UART_RX_buf_tmp[Rep_Version_Data_Number -1] = 'D';
				}

				Main_Group_tmp = i;
				Sub_Group_tmp = 0;

				for(int j=0; j< (Rep_Version_Data_Number - 6); j++){
					Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
				}

				cal_crc16 = 0;
				cal_crc16 = CRC16(Crc_Data, Rep_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

				cal_crc16_tmp = 0;
				cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 4]<<8 )&0xff00)
						| (SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 3]&0x00ff));
				if(cal_crc16 == cal_crc16_tmp){
					Sub_Cmd_RX_LED_On(i+1);

					SUB_UART_RX_buf_tmp[4] = DIP_Value;
					SUB_UART_RX_buf_tmp[5] = SUB_UART_RX_buf_tmp[5];

					for(int j=0; j< (Rep_Version_Data_Number - 6); j++){
						Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
					}

					cal_crc16 = 0;
					cal_crc16 = CRC16(Crc_Data, Rep_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

					SUB_UART_RX_buf_tmp[Rep_Version_Data_Number- 4] = (cal_crc16 >> 8)& 0xff;
					SUB_UART_RX_buf_tmp[Rep_Version_Data_Number- 3] = (cal_crc16 >> 0)& 0xff;

					for(int j=0; j<Rep_Version_Data_Number ; j++){
						Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
						SUB_UART_Receive_Data_complete[i] = 1;
					}
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][5] = SUB_UART_RX_buf_tmp[5];
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][4] = DIP_Value;

					Sub_Cmd_RX_LED_Off(i+1);
				}
				else{
					for(int j=0; j<Rep_Version_Data_Number ; j++){
						Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
						SUB_UART_Receive_Data_complete[i] = 1;
					}
				}

			}
		}
	}
}

/*
void Check_Sub_UART_ComV_Receive(uint8_t Sub_Group){

	uint16_t cal_crc16 = 0;
	uint16_t cal_crc16_tmp = 0;
	uint8_t Crc_Data[Rep_Version_Data_Number - 6];
	uint8_t SUB_UART_RX_buf_tmp[Rep_Version_Data_Number];

	uint8_t Main_Group_tmp, Sub_Group_tmp;

	int l;
	cal_crc16 = 0;
	cal_crc16_tmp = 0;

	if(CM_Board == Recever_Board){
		for(int i=0; i< 4 ; i++){

			for(int j=0; j<(Rep_Version_Data_Number -1); j++){
				SUB_UART_RX_buf_tmp[j] = 0;
			}

			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
				for( l=0; l<(Rep_Version_Data_Number -1); l++){
					SUB_UART_RX_buf_tmp[l] = SUB_UART_RX_buf_DMA_tmp[i][l];
				}
			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}

				SUB_UART_RX_buf_tmp[Rep_Version_Data_Number -1] = 'D';
			}

			if((DIP_Value%2) ==1){
				Main_Group_tmp = i;
			}
			else if((DIP_Value%2) == 0){
				Main_Group_tmp = i+4;
			}

			Sub_Group_tmp = Sub_Group -1;

			for(int j=0; j< (Rep_Version_Data_Number - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, Rep_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);


				Sub_Group_tmp = SUB_UART_RX_buf_DMA_tmp[i][5] - 1;


				for(int j=0; j<Rep_Version_Data_Number ; j++){
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Rep_Version_Data_Number ; j++){
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}

	}
	else if(CM_Board == Repearter_Board){
		for(int i=0; i< 8 ; i++){

			for(int j=0; j<(Rep_Version_Data_Number -1); j++){
				SUB_UART_RX_buf_tmp[j] = 0;
			}
			if((SUB_UART_RX_buf_DMA_tmp[i][0] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][1] == 'T')){
				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j];
				}
			}
			else if((SUB_UART_RX_buf_DMA_tmp[i][1] == 'S')&(SUB_UART_RX_buf_DMA_tmp[i][2] == 'T')){
				for(int j=0; j<(Rep_Version_Data_Number -1); j++){
					SUB_UART_RX_buf_tmp[j] = SUB_UART_RX_buf_DMA_tmp[i][j+1];
				}

				SUB_UART_RX_buf_tmp[Rep_Version_Data_Number -1] = 'D';
			}

			Main_Group_tmp = i;
			Sub_Group_tmp = 0;

			for(int j=0; j< (Rep_Version_Data_Number - 6); j++){
				Crc_Data[j] = SUB_UART_RX_buf_tmp[j+2];
			}

			cal_crc16 = 0;
			cal_crc16 = CRC16(Crc_Data, Rep_Version_Data_Number - 6); //sizeof(Crc_Data)/sizeof(uint8_t));

			cal_crc16_tmp = 0;
			cal_crc16_tmp = ( ((SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 4]<<8 )&0xff00)
					| (SUB_UART_RX_buf_tmp[Rep_Version_Data_Number - 3]&0x00ff));
			if(cal_crc16 == cal_crc16_tmp){
				Sub_Cmd_RX_LED_On(i+1);

				for(int j=0; j<Rep_Version_Data_Number ; j++){
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = SUB_UART_RX_buf_tmp[j];
					SUB_UART_Receive_Data_complete[i] = 1;
				}
				Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][5] = SUB_UART_RX_buf_tmp[5];
				Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][4] = DIP_Value;

				Sub_Cmd_RX_LED_Off(i+1);
			}
			else{
				for(int j=0; j<Rep_Version_Data_Number ; j++){
					Rep_Version_Data[Main_Group_tmp][Sub_Group_tmp][j] = 0;
					SUB_UART_Receive_Data_complete[i] = 1;
				}
			}

		}
	}
}
*/
///////////////UART interrupt operation function terminated///////////////////


