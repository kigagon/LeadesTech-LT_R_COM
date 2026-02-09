/*
 * ReadWriteFlash.c
 *
 *  Created on: Sep 19, 2025
 *      Author: root
 */

/*
 *
 * Sector Size : 4096byte
 * Sector 0 : 시스템 정보 예약
 *
 * Sector 1 : 중계기 1 등록정보
 * Sector 2 : 중계기 2 등록정보
 * ....
 * Sector 31 : 중계기 31 등록정보
 * Sector 32 : 중계기 32 등록정보
 *
 *
 */

#include "main.h"
#include "w25qxx.h"
#include "w25qxxConf.h"
#include "ReadWriteFlash.h"
#include "Compile_Data.h"

uint8_t Info_Version_Year;
uint8_t Info_Version_Month;
uint8_t Info_Version_Day;
uint8_t Info_Version_Hour;
uint8_t Info_Version_Min;
uint8_t Info_Version_Sec;

uint8_t Repearter_Info_Data[8*2][10];
uint8_t CCU_Info_Data[8*8*2][10];

uint8_t Info_Data[146][10];


uint8_t Temp_Sector[4096];

void Info_Set(uint8_t CM_Board){

	int num ;

	if(CM_Board == Recever_Board){
		num = 0;
		Info_Data[num][0] = 'c';
		Info_Data[num][1] = DIP_Value;
		Info_Data[num][2] = 0;
		Info_Data[num][3] = 0;
		Info_Data[num][4] = F_Version_Year;
		Info_Data[num][5] = F_Version_Month;
		Info_Data[num][6] = F_Version_Day;
		Info_Data[num][7] = F_Version_Hour;
		Info_Data[num][8] = F_Version_Min;
		Info_Data[num][9] = F_Version_Sec;

		num = 1;
		Info_Data[num][0] = 'c';
		Info_Data[num][1] = DIP_Value;
		Info_Data[num][2] = 0;
		Info_Data[num][3] = 0;
		Info_Data[num][4] = Info_Version_Year;
		Info_Data[num][5] = Info_Version_Month;
		Info_Data[num][6] = Info_Version_Day;
		Info_Data[num][7] = Info_Version_Hour;
		Info_Data[num][8] = Info_Version_Min;
		Info_Data[num][9] = Info_Version_Sec;

		for(int i=0; i<16; i++ ){
			for(int j=0; j<10; j++){
				Info_Data[i+(2)][j] = Repearter_Info_Data[i][j];
			}
		}
		for(int i=0; i<(8*8*2); i++ ){
			for(int j=0; j<10; j++){
				Info_Data[i+(2+16)][j] = CCU_Info_Data[i][j];
			}
		}

	}
	else if(CM_Board == Repearter_Board){

	}

	for(int i=0;i<9;i++){


	}
	Write_Info_data(Info_Data,sizeof(Info_Data));
}

void Read_Info_data(uint8_t *arr, int size){

	W25qxx_ReadSector(Temp_Sector, 0, 0, 4096);

	for(int i=0; i<size; i++){
		arr[i] = Temp_Sector[i];
	}
}

int Write_Info_data(uint8_t *arr, int size){

	int Succsee = 1, Failure = 0 , Data_Check = 0, Num = 0;

	for(int i = 0; i< 4096; i++){
		Temp_Sector[i] = 0xff;
	}

	for(int i = 0; i< size; i++){
		Temp_Sector[i] = arr[i];
	}
	W25qxx_EraseSector(Num);
	W25qxx_WriteSector(arr, Num, 0, 4096);
	for(int i = 0; i< 4096; i++){
		Temp_Sector[i] = 0x00;
	}
	W25qxx_ReadSector(Temp_Sector, Num, 0, 4096);

	for(int i=0 ; i<size ; i++){
		if(Temp_Sector[i] == arr[i]){
			Data_Check = 1;
		}
		else{
			Data_Check = 0;
		}

		if(Data_Check == 0){
			break;
		}
	}

	if(Data_Check == 1){
		return Succsee;
	}
	else{
		return Failure;
	}
}

int Write_Regi_data(uint8_t Num, uint8_t *arr, int size){

	int Succsee = 1, Failure = 0 , Data_Check = 0;

	for(int i = 0; i< 4096; i++){
		Temp_Sector[i] = 0xff;
	}
	if((Num >= 33)|(Num == 0) ){
	}
	else{
		for(int i = 0; i< size; i++){
			Temp_Sector[i] = arr[i];
		}
		W25qxx_EraseSector(Num);
		W25qxx_WriteSector(Temp_Sector, Num, 0, 4096);
		for(int i = 0; i< 4096; i++){
			Temp_Sector[i] = 0x00;
		}
		W25qxx_ReadSector(Temp_Sector, Num, 0, 4096);
	}

	for(int i=0 ; i<size ; i++){
		if(Temp_Sector[i] == arr[i]){
			Data_Check = 1;
		}
		else{
			Data_Check = 0;
		}

		if(Data_Check == 0){
			break;
		}
	}

	if(Data_Check == 1){
		return Succsee;
	}
	else{
		return Failure;
	}
}
