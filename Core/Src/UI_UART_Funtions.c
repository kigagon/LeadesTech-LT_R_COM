
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : UI_UART_Funtions.c
  * @brief          : UI_UART_Funtions
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */


#include "main.h"

#include "UI_UART_Funtions.h"
#include "SUB_UART_Funtions.h"

#include "Compile_Data.h"
#include "ReadWriteFlash.h"

void Check_UI_UART_Receive(int check_val)
{
	if(check_val == 1)
	{
	    uint8_t Uart2_crc = 0;
	    uint8_t Uart2_crc_o = 0xFF;

	    uint8_t Crc_Data_D[456 - 6];

	    uint16_t cal_crc16_D = 0, Uart2_crc16_o = 0;

	    uint8_t CRC_Mode = 0  , CRC_Ex_Mode = 1 , CRC16_Mode = 2 ;

	    if((UI_UART_RX_buf[3] == 0x53)){
	    	Uart2_crc = 0;
	    }

	    if(UI_UART_RX_buf[2] == 'U'){

	    	if(UI_UART_RX_buf[3] == 'A'){		//중계기 정보 요청  : 요청한 계통의 모든 정보를 읽는다.
	    		CRC_Mode = CRC_Ex_Mode;
	    	}
	    	else if(UI_UART_RX_buf[3] == 'S'){	//중계기 설정  : 중계기의 출력 설정 중계기별로 설정
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'V'){	// 버전 정보 요청
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'I'){	//등록정보 저장
	    		CRC_Mode = CRC16_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'D'){	//축적정보 저장
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'G'){	//축적정보 전체 설정
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'P'){	//중계반 파워보드 정보 요청  : 요청한 중계반의 파워보드 정보를 읽는다.
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'i'){	//등록 정보 종료
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'R'){	// ccu 리셋
	    		CRC_Mode = CRC_Ex_Mode;
			}
	    	else if(UI_UART_RX_buf[3] == 'l'){	// 아날로그 LED제어
				CRC_Mode = CRC_Ex_Mode;
			}

	    	if (CRC_Mode == CRC_Ex_Mode){
	    		Uart2_crc = 0;
				for(int i=2; i< (UI_UART_RX_buf_Lan - 3) ; i++){
					Uart2_crc = Uart2_crc ^ UI_UART_RX_buf[i];
				}
				Uart2_crc_o = UI_UART_RX_buf[UI_UART_RX_buf_Lan - 3];
	    	}
	    	else if (CRC_Mode == CRC16_Mode){
	    		for(int i=0; i< (UI_UART_RX_buf_Lan - 6); i++){
	    			Crc_Data_D[i] = UI_UART_RX_buf[i+2];
				}
	    		cal_crc16_D = CRC16(Crc_Data_D, sizeof(Crc_Data_D)/sizeof(uint8_t));
	    		Uart2_crc16_o = (((UI_UART_RX_buf[UI_UART_RX_buf_Lan - 4])<<8)&0xff00)
	    				|((UI_UART_RX_buf[UI_UART_RX_buf_Lan - 3])&0x00ff);
	    	}

			if((Uart2_crc == Uart2_crc_o) | (cal_crc16_D == Uart2_crc16_o))
			{
				UI_UART_buf_count_tmp = UI_UART_buf_count;

				UI_Cmd_Func();

				UI_UART_Receive_complete = 0;
				UI_UART_buf_count_tmp = 0;
				UI_UART_State = 0;
				UI_UART_buf_count = 0;
				for(int i = 0; i < UI_UART_buf_len; i++){
					UI_UART_RX_buf[i] = 0;
				}
			}
			else
			{
				UI_UART_Receive_complete = 0;
				UI_UART_buf_count_tmp = 0;
				UI_UART_State = 0;
				UI_UART_buf_count = 0;
				for(int i = 0; i < UI_UART_buf_len ; i++){
					UI_UART_RX_buf[i] = 0;
				}
			}
			HAL_GPIO_WritePin(SYS_LED2_GPIO_Port, SYS_LED2_Pin,GPIO_PIN_SET);
	    }

	    UI_UART_Receive_complete = 0;
	}
	else{

	}
}

void UI_Cmd_Func(void){

	// relay
	if(UI_UART_RX_buf[3] == 0x50 || UI_UART_RX_buf[3] == 0x54)
	{
		if(CM_Board == Recever_Board){
			if((UI_UART_RX_buf[4] >= ((DIP_Value - 1)*4 + 1)) & (UI_UART_RX_buf[4] <= ((DIP_Value - 1)*4 + 4))){
				if(UI_UART_RX_buf[3] == 0x50){	//'P' Request for relay board power board information
					HAL_Delay(1);
					UI_Cmd_Func_P();
				}
				else if(UI_UART_RX_buf[3] == 0x54){	//'T' Repeater power board battery test command
					HAL_Delay(1);
					UI_Cmd_Func_T();
				}
			}
		}
	}
	else
	{
		int Board_Address_Check = 0;
		if(CM_Board == Recever_Board){
			if((UI_UART_RX_buf[4] >= ((DIP_Value - 1)*4 + 1)) & (UI_UART_RX_buf[4] <= ((DIP_Value - 1)*4 + 4))){  // receiver
				Board_Address_Check = 1;
			}
			else if((UI_UART_RX_buf[4]== 0)&(UI_UART_RX_buf[5]== 0)){
				if((UI_UART_RX_buf[3] == 0x52)|(UI_UART_RX_buf[3] == 0x47)|(UI_UART_RX_buf[3] == 0x6C)){
					Board_Address_Check = 1;
				}
			}
			else{
				Board_Address_Check = 0;
			}
		}
		else if(CM_Board == Repearter_Board){
//			if((UI_UART_RX_buf[4] >= ((DIP_Value - 1)*8 + 1)) & (UI_UART_RX_buf[4] <= ((DIP_Value - 1)*8 + 8))){	   // relay
//				Board_Address_Check = 1;
//			}
			if(UI_UART_RX_buf[4] == DIP_Value){
//			if((UI_UART_RX_buf[4] >= 1) & (UI_UART_RX_buf[4] <= 8)){
				Board_Address_Check = 1;
			}
			else{
				Board_Address_Check = 0;
			}
		}

		if(Board_Address_Check == 0){
			if(UI_UART_RX_buf[3] == 'i'){
				Board_Address_Check = 1;
			}
		}

		if(Board_Address_Check == 1){

			 if(UI_UART_RX_buf[3] == 0x41){		// 'A' Repeater information request: Read all information of the requested system.
				 UI_Cmd_Func_A();
			 }
			 else if(UI_UART_RX_buf[3] == 0x53){	//'S' Repeater settings: Repeater output settings
				 UI_Cmd_Func_S();
				 //UI_Cmd_Func_S_Save();
			 }
			 else if(UI_UART_RX_buf[3] == 0x43){	//'C' Delete repeater information
//				 UI_Cmd_Func_C();
			 }
			 else if(UI_UART_RX_buf[3] == 0x49){	//'I' Register repeater information
				 UI_Cmd_Func_I();
			 }
			 else if(UI_UART_RX_buf[3] == 0x52){	//'R' Repeater recovery request
				 UI_Cmd_Func_R();
				 Init_Group_Data();
			 }
			 else if(UI_UART_RX_buf[3] == 0x44){	//'D' Registering repeater accumulated setting
				 UI_Cmd_Func_D();
			 }
			 else if(UI_UART_RX_buf[3] == 0x47){	//'G' Repeater accumulation On Off
				 UI_Cmd_Func_G();
				 Init_Group_Data();
			 }
			 else if(UI_UART_RX_buf[3] == 0x56){	//'V' Repeater Version information request
				 UI_Cmd_Func_V();
			 }
			 else if(UI_UART_RX_buf[3] == 0x47){	//'O' Repeater All Output Setting
//				 UI_Cmd_Func_O();
			 }
			 else if(UI_UART_RX_buf[3] == 0x69){	//I' 등록 정보 전송 완
				 UI_Cmd_Func_I_End();
			 }
			 else if(UI_UART_RX_buf[3] == 0x6C){	//I' 등록 정보 전송 완
				 UI_Com_Func_Anal_LED_Set();
				 Init_Group_Data();
			 }
		}
	}

	for(int i=0 ; i<UI_UART_buf_len ; i++){
		UI_UART_RX_buf_tmp[i] = 0;
	}
}

// 'A' Repeater information request: Read all information of the requested system.
void UI_Cmd_Func_A(void)
{
	uint8_t Crc_Data[Repeater_Data_Total - 6];
	uint16_t cal_crc16 = 0;

	uint16_t Group_Num = 0;
	uint16_t Sub_Group_Num = 0;
//
//	for(int i=0; i< Repeater_Data_Total; i++){
//
//		if(CM_Board == Recever_Board){
//			if((DIP_Value == 1) | (DIP_Value == 2)){
//				Group_Num = UI_UART_RX_buf[4];
//			}
//			else if((DIP_Value == 3) | (DIP_Value == 4)){
//				Group_Num = UI_UART_RX_buf[4] - 8;
//			}
//			else if((DIP_Value == 5) | (DIP_Value == 6)){
//				Group_Num = UI_UART_RX_buf[4] - 16;
//			}
//			Sub_Group_Num = UI_UART_RX_buf[5];
//			Rep_Group_Data[i] = Group_Data[Group_Num-1][Sub_Group_Num-1][i];	// receiver
//		}
//		else if(CM_Board == Repearter_Board){
//			//Group_Num = UI_UART_RX_buf[4] ;
//			//Sub_Group_Num = UI_UART_RX_buf[5];
//			Group_Num = UI_UART_RX_buf[5] -1 ;
//			Sub_Group_Num = 0;
//			Rep_Group_Data[i] = Group_Data[Group_Num][Sub_Group_Num][i];	// relay
//		}
//	}

	if(CM_Board == Recever_Board){
		if((DIP_Value == 1) | (DIP_Value == 2)){
			Group_Num = UI_UART_RX_buf[4];
		}
		else if((DIP_Value == 3) | (DIP_Value == 4)){
			Group_Num = UI_UART_RX_buf[4] - 8;
		}
		else if((DIP_Value == 5) | (DIP_Value == 6)){
			Group_Num = UI_UART_RX_buf[4] - 16;
		}
		Sub_Group_Num = UI_UART_RX_buf[5];
	}
	else if(CM_Board == Repearter_Board){
		//Group_Num = UI_UART_RX_buf[4] ;
		//Sub_Group_Num = UI_UART_RX_buf[5];
		Group_Num = UI_UART_RX_buf[5] ;
		Sub_Group_Num = 1;
	}

	for(int i=0; i< Repeater_Data_Total; i++){

		Rep_Group_Data[i] = Group_Data[Group_Num-1][Sub_Group_Num-1][i];	// receiver
	}

	Rep_Group_Data[0] = 0x53;
	Rep_Group_Data[1] = 0x54;
	if(CM_Board == Recever_Board){
		if(Rep_Group_Data[2] == 0x0){
			Rep_Group_Data[2] = 0x63;
		}
		else{
			Rep_Group_Data[2] = Rep_Group_Data[2];
		}
	}
	else if(CM_Board == Repearter_Board){
		if(Rep_Group_Data[2] == 0x0){
			Rep_Group_Data[2] = 0x72;
		}
		else{
			Rep_Group_Data[2] = Rep_Group_Data[2];
		}
	}
	Rep_Group_Data[3] = 0x72;
	Rep_Group_Data[4] = UI_UART_RX_buf[4];
	Rep_Group_Data[5] = UI_UART_RX_buf[5] ;

	if(Rep_Group_Data[5] == 2){
		Rep_Group_Data[5] = UI_UART_RX_buf[5] ;
	}

	Rep_Group_Data[Repeater_Data_Total- 2] = 0x45;
	Rep_Group_Data[Repeater_Data_Total- 1] = 0x44;

	for(int i=0 ; i<Repeater_Number ; i++ ){
		Rep_Group_Data[6+ (i*5)]= i+1;
	}

	for(int i=0; i< (Repeater_Data_Total - 6); i++){
		Crc_Data[i] = Rep_Group_Data[i+2];
	}
	cal_crc16 = CRC16(Crc_Data, sizeof(Crc_Data)/sizeof(uint8_t));

	Rep_Group_Data[Repeater_Data_Total- 4] = (cal_crc16 >> 8)& 0xff;
	Rep_Group_Data[Repeater_Data_Total- 3] = (cal_crc16 >> 0)& 0xff;
	HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
	LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
	//HAL_Delay(1);
	Tx_Mode = 0x41;

	//HAL_UART_Transmit_DMA(&hlpuart1, Rep_Group_Data, Repeater_Data_Total);
	//HAL_UART_Transmit_IT(&hlpuart1, Rep_Group_Data, Repeater_Data_Total);

	HAL_UART_Transmit(&hlpuart1, Rep_Group_Data, Repeater_Data_Total,1000);

	HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
	LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);


	if(CM_Board == Repearter_Board){

		if(Tx_Mode == 0x41){
			if(Rep_Group_Data[5]== 8)
			{
				Read_Start_Sub_Com = 1;
			}
		}
	}

	///////////If the DMA UART is malfunctioning, change th e reception mode to an interrupt./////
}
// 'A' Repeater information request: Read all information of the requested system.



void UI_Cmd_Func_S(void){

	uint8_t Crc_Data = 0;
	uint8_t Main_Group=0 , Send_Main;
	int Tx_data_Len = 14;

	for(int i=2 ; i< 11 ; i++){
		Crc_Data = Crc_Data ^ UI_UART_RX_buf[i];
	}

	if(Crc_Data == UI_UART_RX_buf[11]){

		if(CM_Board == Recever_Board){
			Main_Group = UI_UART_RX_buf[4];
		}
		else if(CM_Board == Repearter_Board){
			Main_Group = UI_UART_RX_buf[5];					// relay
		}

		for(int i = 0; i<Tx_data_Len ; i++){
			SUB_UART_TX_buf[Main_Group-1][i] = UI_UART_RX_buf[i];
		}
		if(CM_Board == Recever_Board){
			Send_Main = Main_Group - (DIP_Value -1) * 4;
		}
		else if(CM_Board == Repearter_Board){
			Send_Main = Main_Group;
		}

		Sub_Cmd_DC_On(Send_Main);
		Sub_Cmd_RX_LED_Off(Send_Main);
		Sub_Cmd_TX_LED_On(Send_Main);

		HAL_Delay(1);

		Sub_Cmd_TX_UART(Send_Main, SUB_UART_TX_buf[Main_Group-1], Tx_data_Len);

		if(CM_Board  ==  Repearter_Board){
			HAL_Delay((Tx_data_Len/150)+1);
		}
		else{
			HAL_Delay((Tx_data_Len/20)+1);
		}
		Sub_Cmd_DC_Off(Send_Main);
		Sub_Cmd_TX_LED_Off(Send_Main);
		if(CM_Board  ==  Repearter_Board){
			HAL_Delay(10);
		}
		else{
			HAL_Delay(30);
		}

	}
}

void UI_Cmd_Func_S_N(void)
{

	uint8_t R_Type, Output_Data;

	if(CM_Board == Recever_Board){
		if( (((DIP_Value - 1) * 4 + 1) >=  UI_UART_RX_buf[4] ) & (((DIP_Value) * 4 + 1) <  UI_UART_RX_buf[4]) ){

		}
	}
	else if(CM_Board == Repearter_Board){
		if(Rep_Group_Data[2] == 0x0){
			Rep_Group_Data[2] = 0x72;
		}
		else{
			Rep_Group_Data[2] = Rep_Group_Data[2];
		}
	}

	for(int i=0;i<Set_Command_Num; i++){

		R_Type = Group_Data[ Set_Command_Data[i][4] - 1 ][ Set_Command_Data[i][5] - 1 ][7+((Set_Command_Data[i][6] - 1)*5) ] ;
		Output_Data = Group_Data[ Set_Command_Data[i][4] - 1 ][ Set_Command_Data[i][5] - 1 ][9+((Set_Command_Data[i][6] - 1)*5) ] ;

		if( (R_Type == 0xA0)|(R_Type == 0x40)|(R_Type == 0x44) ){
			if(Output_Data == Set_Command_Data[i][8]){
				Set_Command_Data_Ck[i]=0;
			}
			else{
				Set_Command_Data_Ck[i]=1;
				Sub_Cmd_Func_S(i);
				for(int j=0; j<Set_Command_T_Lan ; j++){
					Set_Command_Data_tmp[Set_Command_Num_tmp][j] = Set_Command_Data[i][j];
					Set_Command_Num_tmp++;
				}
			}
		}
		else{
			if(Set_Command_Data[i][8] == 0){

			}
			else{
				Set_Command_Data_Ck[i]=1;
				for(int j=0; j<Set_Command_T_Lan ; j++){
					Set_Command_Data_tmp[Set_Command_Num_tmp][j] = Set_Command_Data[i][j];
					Set_Command_Num_tmp++;
				}
			}
		}

	}

	Set_Command_Num_tmp = 0;

	for(int i=0;i<Set_Command_Num; i++){
		if(Set_Command_Data_Ck[i]==1){

			for(int j=0; j<Set_Command_T_Num ; j++){
				 Set_Command_Data_tmp[Set_Command_Num_tmp][j] = Set_Command_Data[i][j];

			}
			Set_Command_Num_tmp++;
		}
		else{

		}
	}

	for(int i=0;i<Set_Command_T_Num; i++){
		for(int j=0; j<Set_Command_T_Lan ; j++){
			Set_Command_Data[i][j] = 0;
		}
	}

	for(int i=0;i<Set_Command_Num_tmp; i++){
		for(int j=0; j<Set_Command_T_Lan ; j++){
			Set_Command_Data[i][j] = Set_Command_Data_tmp[i][j];
		}
	}

	Set_Command_Num = Set_Command_Num_tmp;

}

void UI_Cmd_Func_C(void)
{


}


void UI_Cmd_Func_R(void)
{
	Def_Send_Data();
}


void UI_Cmd_Func_G(void)
{
	Def_Send_Data();

}

void UI_Com_Func_Anal_LED_Set(void)
{
	Def_Send_Data();
}

void Def_Send_Data(void){
	uint8_t Tx_Data_tmp[20], Tx_data_Len = UI_UART_RX_buf_Lan, Main_Group = 0 , Send_Main = 0;
	uint8_t Crc_Data = 0;

	for(int i = 0; i<Tx_data_Len ; i++){
		Tx_Data_tmp[i] = UI_UART_RX_buf[i];
	}

	if((Tx_Data_tmp[4] == 0)&(Tx_Data_tmp[5] == 0)){
		for(int j=1; j< 9 ;j++){
			for(int i=1; i<5; i++){


				Tx_Data_tmp[4] = (DIP_Value - 1)*4 + i;

				//Tx_Data_tmp[5] = j;


				if(CM_Board == Recever_Board){
					Main_Group = (DIP_Value - 1)*4 + i;
				}
				else if(CM_Board == Repearter_Board){
					Main_Group = j;				// relay
				}

				if(CM_Board == Recever_Board){
					Send_Main = Main_Group - (DIP_Value -1) * 4;
				}
				else if(CM_Board == Repearter_Board){
					Send_Main = Main_Group;
				}

				Crc_Data = 0;
				for(int i=2 ; i< (Tx_data_Len - 3) ; i++){
					Crc_Data = Crc_Data ^ Tx_Data_tmp[i];
				}
				Tx_Data_tmp[Tx_data_Len - 3] = Crc_Data;

				Sub_Cmd_DC_On(Send_Main);
				Sub_Cmd_RX_LED_Off(Send_Main);
				Sub_Cmd_TX_LED_On(Send_Main);

				HAL_Delay(1);

				Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

				if(CM_Board  ==  Repearter_Board){
					HAL_Delay((Tx_data_Len/150)+1);
				}
				else{
					HAL_Delay((Tx_data_Len/20)+1);
				}
				Sub_Cmd_DC_Off(Send_Main);
				Sub_Cmd_TX_LED_Off(Send_Main);
				if(CM_Board  ==  Repearter_Board){
					HAL_Delay(10);
				}
				else{
					HAL_Delay(30);
				}
			}
		}
	}
	else if((Tx_Data_tmp[4] != 0)&(Tx_Data_tmp[5] == 0)){

		for(int j=1; j< 9 ;j++){

			Tx_Data_tmp[5] = j;

			if(CM_Board == Recever_Board){
				Main_Group = Tx_Data_tmp[4];
			}
			else if(CM_Board == Repearter_Board){
				Main_Group = Tx_Data_tmp[5];					// relay
			}

			if(CM_Board == Recever_Board){
				Send_Main = Main_Group - (DIP_Value -1) * 4;
			}
			else if(CM_Board == Repearter_Board){
				Send_Main = Main_Group;
			}

			Crc_Data = 0;
			for(int i=2 ; i< (Tx_data_Len - 3) ; i++){
				Crc_Data = Crc_Data ^ Tx_Data_tmp[i];
			}
			Tx_Data_tmp[Tx_data_Len - 3] = Crc_Data;

			Sub_Cmd_DC_On(Send_Main);
			Sub_Cmd_RX_LED_Off(Send_Main);
			Sub_Cmd_TX_LED_On(Send_Main);

			HAL_Delay(1);

			Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

			if(CM_Board  ==  Repearter_Board){
				HAL_Delay((Tx_data_Len/150)+1);
			}
			else{
				HAL_Delay((Tx_data_Len/20)+1);
			}
			Sub_Cmd_DC_Off(Send_Main);
			Sub_Cmd_TX_LED_Off(Send_Main);
			if(CM_Board  ==  Repearter_Board){
				HAL_Delay(10);
			}
			else{
				HAL_Delay(30);
			}
		}
	}
	if((Tx_Data_tmp[4] != 0)&(Tx_Data_tmp[5] != 0)){

		if(CM_Board == Recever_Board){
			Main_Group = Tx_Data_tmp[4];
		}
		else if(CM_Board == Repearter_Board){
			Main_Group = Tx_Data_tmp[5];					// relay
		}

		if(CM_Board == Recever_Board){
			Send_Main = Main_Group - (DIP_Value -1) * 4;
		}
		else if(CM_Board == Repearter_Board){
			Send_Main = Main_Group;
		}

		Sub_Cmd_DC_On(Send_Main);
		Sub_Cmd_RX_LED_Off(Send_Main);
		Sub_Cmd_TX_LED_On(Send_Main);

		HAL_Delay(1);

		Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

		if(CM_Board  ==  Repearter_Board){
			HAL_Delay((Tx_data_Len/150)+1);
		}
		else{
			HAL_Delay((Tx_data_Len/20)+1);
		}
		Sub_Cmd_DC_Off(Send_Main);
		Sub_Cmd_TX_LED_Off(Send_Main);
		if(CM_Board  ==  Repearter_Board){
			HAL_Delay(10);
		}
		else{
			HAL_Delay(30);
		}
	}

}
/*
void UI_Cmd_Func_R(void)
{

	uint8_t Tx_Data_tmp[9], Tx_data_Len = 9, Main_Group = 0 , Send_Main;
	uint8_t Crc_Data = 0;

	for(int i=2 ; i< 6 ; i++){
		Crc_Data = Crc_Data ^ UI_UART_RX_buf[i];
	}

	if(Crc_Data == UI_UART_RX_buf[6]){

		for(int i = 0; i<Tx_data_Len ; i++){
			Tx_Data_tmp[i] = UI_UART_RX_buf[i];
		}

		if((Tx_Data_tmp[4] == 0)&(Tx_Data_tmp[5] == 0)){

			for(int j=1; j< 9 ;j++){

				for(int i=1; i<5; i++){

					Tx_Data_tmp[4] = (DIP_Value - 1)*4 + i;
					Tx_Data_tmp[5] = j;

					if(CM_Board == Recever_Board){
						Main_Group = Tx_Data_tmp[4];
					}
					else if(CM_Board == Repearter_Board){
						Main_Group = Tx_Data_tmp[5];					// relay
					}

					if(CM_Board == Recever_Board){
						Send_Main = Main_Group - (DIP_Value -1) * 4;
					}
					else if(CM_Board == Repearter_Board){
						Send_Main = Main_Group;
					}

					Crc_Data = 0;
					for(int i=2 ; i< 6 ; i++){
						Crc_Data = Crc_Data ^ Tx_Data_tmp[i];
					}
					Tx_Data_tmp[6] = Crc_Data;

					Sub_Cmd_DC_On(Send_Main);
					Sub_Cmd_RX_LED_Off(Send_Main);
					Sub_Cmd_TX_LED_On(Send_Main);

					HAL_Delay(1);

					Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

					if(CM_Board  ==  Repearter_Board){
						HAL_Delay((Tx_data_Len/150)+1);
					}
					else{
						HAL_Delay((Tx_data_Len/20)+1);
					}
					Sub_Cmd_DC_Off(Send_Main);
					Sub_Cmd_TX_LED_Off(Send_Main);
					if(CM_Board  ==  Repearter_Board){
						HAL_Delay(10);
					}
					else{
						HAL_Delay(30);
					}
				}
			}
		}
		else if((Tx_Data_tmp[4] != 0)&(Tx_Data_tmp[5] == 0)){

			for(int j=1; j< 9 ;j++){

				Tx_Data_tmp[5] = j;

				if(CM_Board == Recever_Board){
					Main_Group = Tx_Data_tmp[4];
				}
				else if(CM_Board == Repearter_Board){
					Main_Group = Tx_Data_tmp[5];					// relay
				}

				if(CM_Board == Recever_Board){
					Send_Main = Main_Group - (DIP_Value -1) * 4;
				}
				else if(CM_Board == Repearter_Board){
					Send_Main = Main_Group;
				}

				Crc_Data = 0;
				for(int i=2 ; i< 6 ; i++){
					Crc_Data = Crc_Data ^ Tx_Data_tmp[i];
				}
				Tx_Data_tmp[6] = Crc_Data;

				Sub_Cmd_DC_On(Send_Main);
				Sub_Cmd_RX_LED_Off(Send_Main);
				Sub_Cmd_TX_LED_On(Send_Main);

				HAL_Delay(1);

				Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

				if(CM_Board  ==  Repearter_Board){
					HAL_Delay((Tx_data_Len/150)+1);
				}
				else{
					HAL_Delay((Tx_data_Len/20)+1);
				}
				Sub_Cmd_DC_Off(Send_Main);
				Sub_Cmd_TX_LED_Off(Send_Main);
				if(CM_Board  ==  Repearter_Board){
					HAL_Delay(10);
				}
				else{
					HAL_Delay(30);
				}
			}
		}
		if((Tx_Data_tmp[4] != 0)&(Tx_Data_tmp[5] != 0)){

			if(CM_Board == Recever_Board){
				Main_Group = Tx_Data_tmp[4];
			}
			else if(CM_Board == Repearter_Board){
				Main_Group = Tx_Data_tmp[5];					// relay
			}

			if(CM_Board == Recever_Board){
				Send_Main = Main_Group - (DIP_Value -1) * 4;
			}
			else if(CM_Board == Repearter_Board){
				Send_Main = Main_Group;
			}

			Sub_Cmd_DC_On(Send_Main);
			Sub_Cmd_RX_LED_Off(Send_Main);
			Sub_Cmd_TX_LED_On(Send_Main);

			HAL_Delay(1);

			Sub_Cmd_TX_UART(Send_Main, Tx_Data_tmp, Tx_data_Len);

			if(CM_Board  ==  Repearter_Board){
				HAL_Delay((Tx_data_Len/150)+1);
			}
			else{
				HAL_Delay((Tx_data_Len/20)+1);
			}
			Sub_Cmd_DC_Off(Send_Main);
			Sub_Cmd_TX_LED_Off(Send_Main);
			if(CM_Board  ==  Repearter_Board){
				HAL_Delay(10);
			}
			else{
				HAL_Delay(30);
			}
		}
	}
}
*/
/*

void UI_Cmd_Func_G(void)
{

	uint8_t Group_Num = 0 , Sub_Group_Num = 0 , Send_Main;

	uint8_t Crc_Data = 0, End_Num = REPEATER_Acc_OnOff_Num - 3 ;

	for(int i=2 ; i < End_Num ;i++){
		Crc_Data = Crc_Data ^ UI_UART_RX_buf[i];
	}

	if(Crc_Data == UI_UART_RX_buf[End_Num]){

		if(CM_Board == Recever_Board){
			Group_Num = UI_UART_RX_buf[4];
		}
		else if(CM_Board == Repearter_Board){
			Group_Num = UI_UART_RX_buf[5];					// relay
		}

		if(CM_Board == Recever_Board){
			Send_Main = Group_Num - (DIP_Value -1) * 4;
		}
		else if(CM_Board == Repearter_Board){
			Send_Main = Group_Num;
		}


		Sub_Cmd_DC_On(Send_Main);
		Sub_Cmd_RX_LED_Off(Send_Main);
		Sub_Cmd_TX_LED_On(Send_Main);

		HAL_Delay(1);

		Sub_Cmd_TX_UART(Send_Main, UI_UART_RX_buf, REPEATER_Acc_OnOff_Num);

		if(CM_Board  ==  Repearter_Board){
			HAL_Delay((REPEATER_Acc_OnOff_Num/150)+1);
		}
		else{
			HAL_Delay((REPEATER_Acc_OnOff_Num/20)+1);
		}
		Sub_Cmd_DC_Off(Send_Main);
		Sub_Cmd_TX_LED_Off(Send_Main);
		if(CM_Board  ==  Repearter_Board){
			HAL_Delay(10);
		}
		else{
			HAL_Delay(30);
		}

		HAL_Delay(1);
	}
}

*/

// receiver
void UI_Cmd_Func_P(void){
	uint8_t num = 0, Rse_Data = 0;
	if(UI_UART_RX_buf[4] % 8 == 0)
	{
		num = 7;
	}
	else
	{
		num = (UI_UART_RX_buf[4] % 8) - 1;
	}

	if( (DIP_Value % 2) == 1){
		if( (num >= 0) & (num < 4)){
			Rse_Data = 1;
		}
		else{
			Rse_Data = 0;
		}
	}
	else{
		if( (num >= 0) & (num < 4)){
			Rse_Data = 0;
		}
		else{
			Rse_Data = 1;
		}
	}

	if(Rse_Data == 1){
		for(int i=0; i< Pow_Bod_Data_Total; i++){
			Rep_Pow_Bod_Data[i] = Pow_Bod_Data[num][i];
		}

		uint8_t Crc_Val = 0;
		Rep_Pow_Bod_Data[0] = 0x53;
		Rep_Pow_Bod_Data[1] = 0x54;
		if(Rep_Pow_Bod_Data[2] == 0){
			Rep_Pow_Bod_Data[2] = 0x63;
		}
		Rep_Pow_Bod_Data[3] = 0x72;
		Rep_Pow_Bod_Data[4] = UI_UART_RX_buf[4];
		Rep_Pow_Bod_Data[5] = 0;


		Rep_Pow_Bod_Data[Pow_Bod_Data_Total-2] = 0x45;
		Rep_Pow_Bod_Data[Pow_Bod_Data_Total-1] = 0x44;


		for(int i = 0 ; i < (Pow_Bod_Data_Total - 5) ; i++){
			Crc_Val = Crc_Val^Rep_Pow_Bod_Data[i+2];
		}
		Rep_Pow_Bod_Data[Pow_Bod_Data_Total-3] = Crc_Val;

		LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
		//HAL_Delay(1);
		HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
		Tx_Mode = 0x50;
		//HAL_UART_Transmit_IT(&hlpuart1, Rep_Pow_Bod_Data, Pow_Bod_Data_Total);
		HAL_UART_Transmit(&hlpuart1, Rep_Pow_Bod_Data, Pow_Bod_Data_Total,1000);
		HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
		LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);

		if(Rep_Pow_Bod_Data[4] == DIP_Value * 4)
		{
			Read_Start_Sub_Com = 1;
		}


	}
//
//	HAL_Delay(1);
}

// receiver
void UI_Cmd_Func_T(void){
//	Sub_Cmd_Func_T(UI_UART_UI_UART_buf_countRX_buf[4]%8);

	Sub_Cmd_Func_T(UI_UART_RX_buf[4]);
	//HAL_Delay(10);
}


void UI_Cmd_Func_S_Save(void){

	for(int  i=0 ; i < Set_Command_T_Lan; i++){
		if(UI_UART_RX_buf_Lan > i){
			Set_Command_Data[Set_Command_Num][i] = UI_UART_RX_buf[i];
		}
		else{
			Set_Command_Data[Set_Command_Num][i] = 0;
		}
	}
	Set_Command_Num++;
}

void UI_Cmd_Func_D(void)
{
	uint8_t Main_Group = 0 , Send_Main = 0;
	uint8_t Crc_Data = 0, End_Num = UI_UART_RX_buf_Lan - 3 ;


	for(int i=2 ; i < End_Num ;i++){
		Crc_Data = Crc_Data ^ UI_UART_RX_buf[i];
	}

	if(Crc_Data == UI_UART_RX_buf[End_Num]){


		if(CM_Board == Recever_Board){
			Main_Group = UI_UART_RX_buf[4];
		}
		else if(CM_Board == Repearter_Board){
			Main_Group = UI_UART_RX_buf[5];					// relay
		}

		for(int i = 0; i<UI_UART_RX_buf_Lan ; i++){
			SUB_UART_TX_buf[Main_Group-1][i] = UI_UART_RX_buf[i];
		}
		if(CM_Board == Recever_Board){
			Send_Main = Main_Group - (DIP_Value -1) * 4;
		}
		else if(CM_Board == Repearter_Board){
			Send_Main = Main_Group;
		}

		Sub_Cmd_DC_On(Send_Main);
		Sub_Cmd_RX_LED_Off(Send_Main);
		Sub_Cmd_TX_LED_On(Send_Main);

		HAL_Delay(1);

		Sub_Cmd_TX_UART(Send_Main, SUB_UART_TX_buf[Main_Group-1], UI_UART_RX_buf_Lan);

		if(CM_Board  ==  Repearter_Board){
			HAL_Delay((UI_UART_RX_buf_Lan/150)+1);
		}
		else{
			HAL_Delay((UI_UART_RX_buf_Lan/20)+1);
		}
		Sub_Cmd_DC_Off(Send_Main);
		Sub_Cmd_TX_LED_Off(Send_Main);
		if(CM_Board  ==  Repearter_Board){
			HAL_Delay(10);
		}
		else{
			HAL_Delay(30);
		}
	}

}

void UI_Cmd_Func_I(void)
{
	uint8_t Main_Group=0 , Send_Main = 0;
	uint8_t Save_Num = 0;

	if(CM_Board == Recever_Board){
		Main_Group = UI_UART_RX_buf[4];
	}
	else if(CM_Board == Repearter_Board){
		Main_Group = UI_UART_RX_buf[5];					// relay
	}

	for(int i = 0; i<UI_UART_RX_buf_Lan ; i++){
		SUB_UART_TX_buf[Main_Group-1][i] = UI_UART_RX_buf[i];
	}
	if(CM_Board == Recever_Board){
		Send_Main = Main_Group - (DIP_Value -1) * 4;
	}
	else if(CM_Board == Repearter_Board){
		Send_Main = Main_Group;
	}

	if(CM_Board == Recever_Board){
		Save_Num = ((UI_UART_RX_buf[4] - ((DIP_Value-1)*4))-1)*8 + UI_UART_RX_buf[5];
	}
	else if(CM_Board == Repearter_Board){
		Save_Num = Main_Group;
	}

	for(int i = 0; i<UI_UART_RX_buf_Lan ; i++){
		Save_Info_Data[Save_Num-1][i] = SUB_UART_TX_buf[Main_Group-1][i];
	}

	if(Write_Regi_data(Save_Num, UI_UART_RX_buf,UI_UART_RX_buf_Lan) == 1){

		for(int i = 0; i<UI_UART_RX_buf_Lan ; i++){
			Save_Info_Data[Save_Num-1][i] = SUB_UART_TX_buf[Main_Group-1][i];
		}
		Sub_Cmd_DC_On(Send_Main);
		Sub_Cmd_RX_LED_Off(Send_Main);
		Sub_Cmd_TX_LED_On(Send_Main);

		HAL_Delay(1);

		Sub_Cmd_TX_UART(Send_Main, SUB_UART_TX_buf[Main_Group-1], UI_UART_RX_buf_Lan);

		if(CM_Board  ==  Repearter_Board){
			HAL_Delay((UI_UART_RX_buf_Lan/150)+1);
		}
		else{
			HAL_Delay((UI_UART_RX_buf_Lan/20)+1);
		}

		Sub_Cmd_DC_Off(Send_Main);
		Sub_Cmd_TX_LED_Off(Send_Main);
		if(CM_Board  ==  Repearter_Board){
			HAL_Delay(10);
		}
		else{
			HAL_Delay(30);
		}
	}

}


void UI_Cmd_Func_I_End(void){

	uint8_t Save_tmp_Array[456], Save_tmp_Sec[32], End_Data_tmp[10];
	uint8_t Main_Group=0 , Send_Main = 0;
	uint16_t Send_Data_Lan = 456 ,Send_End_Data_Lan = 10;


	if(CM_Board == Recever_Board){
		for(int i=0;i<32;i++){
			for(int j=0; j<456; j++){
				Save_tmp_Array[j] = Save_Info_Data[i][j];
			}
			Save_tmp_Sec[i] = Write_Regi_data(1, Save_tmp_Array,256) ;
			if(Save_tmp_Sec[i] == 1){

				if(CM_Board == Recever_Board){
					Main_Group = Save_tmp_Array[4];
				}
				else if(CM_Board == Repearter_Board){
					Main_Group = Save_tmp_Array[5];					// relay
				}

				if(CM_Board == Recever_Board){
					Send_Main = Main_Group - (DIP_Value -1) * 4;
				}
				else if(CM_Board == Repearter_Board){
					Send_Main = Main_Group;
				}

				Sub_Cmd_DC_On(Send_Main);
				Sub_Cmd_RX_LED_Off(Send_Main);
				Sub_Cmd_TX_LED_On(Send_Main);

				HAL_Delay(1);

				if(Main_Group == 0){

				}
				else{
					Sub_Cmd_TX_UART(Send_Main, Save_tmp_Array, Send_Data_Lan);
				}
				Sub_Cmd_DC_Off(Send_Main);
				Sub_Cmd_TX_LED_Off(Send_Main);
	/*
				if(CM_Board  ==  Repearter_Board){
					HAL_Delay(10);
				}
				else{
					HAL_Delay(30);
				}
	*/

				if( ((i+1)% 8) == 0 ){

					for(int j=0; j<Send_End_Data_Lan; j++){
						End_Data_tmp[j] = UI_UART_RX_buf[j];
					}
					Sub_Cmd_DC_On(Send_Main);
					Sub_Cmd_RX_LED_Off(Send_Main);
					Sub_Cmd_TX_LED_On(Send_Main);

					HAL_Delay(1);

					Sub_Cmd_TX_UART(Send_Main, End_Data_tmp, Send_End_Data_Lan);

					Sub_Cmd_DC_Off(Send_Main);
					Sub_Cmd_TX_LED_Off(Send_Main);
				}
			}
		}
	}
	else if(CM_Board == Repearter_Board){
		for(int i=0;i<8;i++){
			for(int j=0; j<456; j++){
				Save_tmp_Array[j] = Save_Info_Data[i][j];
			}
			Save_tmp_Sec[i] = Write_Regi_data(1, Save_tmp_Array,256) ;
			if(Save_tmp_Sec[i] == 1){

				if(CM_Board == Recever_Board){
					Main_Group = Save_tmp_Array[4];
				}
				else if(CM_Board == Repearter_Board){
					Main_Group = Save_tmp_Array[5];					// relay
				}

				if(CM_Board == Recever_Board){
					Send_Main = Main_Group - (DIP_Value -1) * 4;
				}
				else if(CM_Board == Repearter_Board){
					Send_Main = Main_Group;
				}


				Sub_Cmd_DC_On(Send_Main);
				Sub_Cmd_RX_LED_Off(Send_Main);
				Sub_Cmd_TX_LED_On(Send_Main);

				HAL_Delay(1);

				Sub_Cmd_TX_UART(Send_Main, Save_Info_Data[Main_Group-1], Send_Data_Lan);

				Sub_Cmd_DC_Off(Send_Main);
				Sub_Cmd_TX_LED_Off(Send_Main);

				/*
				if(CM_Board  ==  Repearter_Board){
					HAL_Delay(10);
				}
				else{
					HAL_Delay(30);
				}
				*/
			}

		}
	}

	HAL_Delay(10);

}

void UI_Cmd_Func_V(void){

	uint8_t Com_Crc_Data[Com_Version_Data_Number - 6];
	uint8_t Rep_Crc_Data[Rep_Version_Data_Number - 6];
	uint16_t cal_crc16 = 0;

	uint8_t Com_Num = 0, Sub_Num = 0, Ccu_Num = 0, Save_Num = 0;

	if(CM_Board == Recever_Board){

		if(UI_UART_RX_buf[5] == 0){
			Com_Version_Data[0] = 0x53;
			Com_Version_Data[1] = 0x54;
			Com_Version_Data[2] = 0x63;
			Com_Version_Data[3] = 0x76;
			Com_Version_Data[4] = DIP_Value;

			Com_Crc_Data[0] = Com_Version_Data[2];
			Com_Crc_Data[1] = Com_Version_Data[3];
			Com_Crc_Data[2] = Com_Version_Data[4];

			for(int i = 0; i< 9; i++){
				Com_Crc_Data[3+i*7] = i;
				for(int j=0; j<6; j++){
					Com_Crc_Data[4 + i*7 +j] = Save_Com_Version_Data[i][j];
				}
			}

			for(int i=0; i< (Com_Version_Data_Number - 6); i++){
				Com_Version_Data[2+i] = Com_Crc_Data[i];
			}

			cal_crc16 = CRC16(Com_Crc_Data, sizeof(Com_Crc_Data)/sizeof(uint8_t));

			Com_Version_Data[Com_Version_Data_Number- 4] = (cal_crc16 >> 8)& 0xff;
			Com_Version_Data[Com_Version_Data_Number- 3] = (cal_crc16 >> 0)& 0xff;

			Com_Version_Data[Com_Version_Data_Number- 2] = 0x45;
			Com_Version_Data[Com_Version_Data_Number- 1] = 0x44;

			HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
			LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
			//HAL_Delay(1);
			Tx_Mode = 0x41;

			HAL_UART_Transmit(&hlpuart1, Com_Version_Data, Com_Version_Data_Number,1000);

			HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
			LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);

			//Read_Sub_Version();
			Sub_Version_Read_Cnt = 1;
		}
		else if((UI_UART_RX_buf[5] > 0)&(UI_UART_RX_buf[5] < 9)){

			HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
			LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
			//HAL_Delay(1);
			Tx_Mode = 0x56;

			Com_Num = DIP_Value;
			Sub_Num = UI_UART_RX_buf[4];
			Ccu_Num = UI_UART_RX_buf[5];

			//Save_Num = Sub_Num - ((Com_Num*2) - 1) * 8 - 1;

			if((Com_Num == 1)|(Com_Num == 2)){
				Save_Num = Sub_Num - 1;
			}
			else if((Com_Num == 3)|(Com_Num == 4)){
				Save_Num = Sub_Num - (1*8) -1;
			}
			else if((Com_Num == 5)|(Com_Num == 6)){
				Save_Num = Sub_Num - (2*8) -1;
			}

			if(Rep_Version_Data[Save_Num][Ccu_Num-1][0] == 0){
				Rep_Version_Data[Save_Num][Ccu_Num-1][0] = 0x53;
				Rep_Version_Data[Save_Num][Ccu_Num-1][1] = 0x54;
				Rep_Version_Data[Save_Num][Ccu_Num-1][2] = 0x63;
				Rep_Version_Data[Save_Num][Ccu_Num-1][3] = 0x76;
				Rep_Version_Data[Save_Num][Ccu_Num-1][4] = UI_UART_RX_buf[4];
				Rep_Version_Data[Save_Num][Ccu_Num-1][5] = UI_UART_RX_buf[5];

				Rep_Crc_Data[0] = Rep_Version_Data[Save_Num][Ccu_Num-1][2];
				Rep_Crc_Data[1] = Rep_Version_Data[Save_Num][Ccu_Num-1][3];
				Rep_Crc_Data[2] = Rep_Version_Data[Save_Num][Ccu_Num-1][4];
				Rep_Crc_Data[3] = Rep_Version_Data[Save_Num][Ccu_Num-1][5];

				for(int i = 0; i< 221; i++){
					Rep_Crc_Data[4+i*7] = i;
				}

				for(int i = 0; i< Rep_Version_Data_Number - 6; i++){
					Rep_Version_Data[Save_Num][Ccu_Num-1][2+i] = Rep_Crc_Data[i];
				}

				cal_crc16 = CRC16(Rep_Crc_Data, sizeof(Rep_Crc_Data)/sizeof(uint8_t));

				Rep_Version_Data[Save_Num][Ccu_Num-1][Rep_Version_Data_Number- 4] = (cal_crc16 >> 8)& 0xff;
				Rep_Version_Data[Save_Num][Ccu_Num-1][Rep_Version_Data_Number- 3] = (cal_crc16 >> 0)& 0xff;

				Rep_Version_Data[Save_Num][Ccu_Num-1][Rep_Version_Data_Number-2] = 0x45;
				Rep_Version_Data[Save_Num][Ccu_Num-1][Rep_Version_Data_Number-1] = 0x44;
			}

			HAL_UART_Transmit(&hlpuart1, Rep_Version_Data[Save_Num][Ccu_Num-1], Rep_Version_Data_Number,1000);

			HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
			LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);
		}
	}

	else{
		if(UI_UART_RX_buf[4] == DIP_Value){
			if(UI_UART_RX_buf[5] == 0){
				Com_Version_Data[0] = 0x53;
				Com_Version_Data[1] = 0x54;
				Com_Version_Data[2] = 0x63;
				Com_Version_Data[3] = 0x76;
				Com_Version_Data[4] = DIP_Value;

				Com_Crc_Data[0] = Com_Version_Data[2];
				Com_Crc_Data[1] = Com_Version_Data[3];
				Com_Crc_Data[2] = Com_Version_Data[4];

				for(int i = 0; i< 9; i++){
					Com_Crc_Data[3+i*7] = i;
					for(int j=0; j<6; j++){
						Com_Crc_Data[4 + i*7 +j] = Save_Com_Version_Data[i][j];
					}
				}

				for(int i=0; i< (Com_Version_Data_Number - 6); i++){
					Com_Version_Data[2+i] = Com_Crc_Data[i];
				}

				cal_crc16 = CRC16(Com_Crc_Data, sizeof(Com_Crc_Data)/sizeof(uint8_t));

				Com_Version_Data[Com_Version_Data_Number- 4] = (cal_crc16 >> 8)& 0xff;
				Com_Version_Data[Com_Version_Data_Number- 3] = (cal_crc16 >> 0)& 0xff;

				Com_Version_Data[Com_Version_Data_Number- 2] = 0x45;
				Com_Version_Data[Com_Version_Data_Number- 1] = 0x44;

				HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
				LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
				//HAL_Delay(1);
				Tx_Mode = 0x56;

				HAL_UART_Transmit(&hlpuart1, Com_Version_Data, Com_Version_Data_Number,1000);

				HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
				LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);

				Sub_Version_Read_Cnt = 1;
			}
			else if((UI_UART_RX_buf[5] > 0)&(UI_UART_RX_buf[5] < 9)){

				HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_SET); // sp3485EN-L is tx mode
				LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_On);
				//HAL_Delay(1);
				Tx_Mode = 0x56;

				Com_Num = DIP_Value;
				Sub_Num = UI_UART_RX_buf[4];
				Ccu_Num = UI_UART_RX_buf[5];

				Save_Num = Ccu_Num - 1;


				if(Rep_Version_Data[Save_Num][0][0] == 0){
					Rep_Version_Data[Save_Num][0][0] = 0x53;
					Rep_Version_Data[Save_Num][0][1] = 0x54;
					Rep_Version_Data[Save_Num][0][2] = 0x63;
					Rep_Version_Data[Save_Num][0][3] = 0x76;
					Rep_Version_Data[Save_Num][0][4] = UI_UART_RX_buf[4];
					Rep_Version_Data[Save_Num][0][5] = UI_UART_RX_buf[5];

					Rep_Crc_Data[0] = Rep_Version_Data[Save_Num][0][2];
					Rep_Crc_Data[1] = Rep_Version_Data[Save_Num][0][3];
					Rep_Crc_Data[2] = Rep_Version_Data[Save_Num][0][4];
					Rep_Crc_Data[3] = Rep_Version_Data[Save_Num][0][5];

					for(int i = 0; i< 221; i++){
						Rep_Crc_Data[4+i*7] = i;
					}

					for(int i = 0; i< Rep_Version_Data_Number - 6; i++){
						Rep_Version_Data[Save_Num][0][2+i] = Rep_Crc_Data[i];
					}

					cal_crc16 = CRC16(Rep_Crc_Data, sizeof(Rep_Crc_Data)/sizeof(uint8_t));

					Rep_Version_Data[Save_Num][0][Rep_Version_Data_Number- 4] = (cal_crc16 >> 8)& 0xff;
					Rep_Version_Data[Save_Num][0][Rep_Version_Data_Number- 3] = (cal_crc16 >> 0)& 0xff;

					Rep_Version_Data[Save_Num][0][Rep_Version_Data_Number-2] = 0x45;
					Rep_Version_Data[Save_Num][0][Rep_Version_Data_Number-1] = 0x44;
				}

				HAL_UART_Transmit(&hlpuart1, Rep_Version_Data[Save_Num][0], Rep_Version_Data_Number,1000);

				HAL_GPIO_WritePin(UI_485_DC_GPIO_Port, UI_485_DC_Pin, GPIO_PIN_RESET); // rx mode
				LED_Control(UI_485_TX_LED_GPIO_Port, UI_485_TX_LED_Pin , LED_Off);
			}
		}
	}
}

void Init_Group_Data(void){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			for(int k=0; k<1110; k++){
				Group_Data[i][j][k] = 0;
			}
		}
	}
}
