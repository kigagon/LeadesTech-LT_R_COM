/*
 * ReadWriteFlash.h
 *
 *  Created on: Sep 19, 2025
 *      Author: root
 */

#ifndef INC_READWRITEFLASH_H_
#define INC_READWRITEFLASH_H_

extern uint8_t Info_Version_Year;
extern uint8_t Info_Version_Month;
extern uint8_t Info_Version_Day;
extern uint8_t Info_Version_Hour;
extern uint8_t Info_Version_Min;
extern uint8_t Info_Version_Sec;

extern uint8_t Repearter_Info_Data[8*2][10];
extern uint8_t CCU_Info_Data[8*8*2][10];

extern uint8_t Info_Data[146][10];

void Info_Set(uint8_t CM_Board);
void Read_Info_data(uint8_t *arr, int size);
int Write_Info_data(uint8_t *arr, int size);
int Write_Regi_data(uint8_t Num, uint8_t *arr, int size);


#endif /* INC_READWRITEFLASH_H_ */
