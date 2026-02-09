/*
 * SUB_UART_Funtions.h
 *
 *  Created on: Nov 25, 2024
 *      Author: root
 */

#ifndef INC_SUB_UART_FUNTIONS_H_
#define INC_SUB_UART_FUNTIONS_H_



#endif /* INC_SUB_UART_FUNTIONS_H_ */


void Sub_Cmd_Func_A(uint8_t Main_Group, uint8_t Sub_Group);
void Sub_Cmd_Func_P(uint8_t Main_Group);
void Sub_Cmd_Func_V(uint8_t Main_Group, uint8_t Sub_Group);

void SUB_Receiver(uint8_t Main_Group);

void Sub_Cmd_TX_LED_On(uint8_t LED_Num);
void Sub_Cmd_TX_LED_Off(uint8_t LED_Num);
void Sub_Cmd_RX_LED_On(uint8_t LED_Num);
void Sub_Cmd_RX_LED_Off(uint8_t LED_Num);
void Sub_Cmd_ST_LED_On(uint8_t LED_Num);
void Sub_Cmd_ST_LED_Off(uint8_t LED_Num);
void Sub_Cmd_DC_On(uint8_t LED_Num);
void Sub_Cmd_DC_Off(uint8_t LED_Num);
void Sub_Cmd_TX_UART(uint8_t UART_Num,  const uint8_t *Uart_Tx_Data, uint16_t Size);
void Sub_Cmd_TX_UART_DMA(uint8_t UART_Num,  const uint8_t *Uart_Tx_Data, uint16_t Size);

void Sub_Cmd_RX_UART(uint8_t UART_Num,int Rx_Num);

void Sub_Cmd_RX_UART_Stop(uint8_t UART_Num);
void Sub_Cmd_RX_UART_Abort(uint8_t UART_Num);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void Sub_Cmd_RX_DMA_ST(uint8_t Num);

void Check_Sub_UART_ComA_Receive(uint8_t Sub_Group);
void Check_Sub_UART_ComP_Receive(void);
void Check_Sub_POW_UART_Receive(void);
void Sub_UART_Rx_Com(uint8_t Uart_Num, uint8_t Rx_Data);
void Sub_Cmd_Power_RX_UART(uint8_t UART_Num,int Rx_Num);

void Sub_Tx_Wait(uint8_t Board_type, uint8_t Ms);
void Sub_Rx_Wait(uint8_t Board_type, uint8_t Ms);
void Sub_Cmd_Func_S(int num);
void Sub_Cmd_Func_T(uint8_t Main_Group);

void Check_Sub_UART_ComV_Receive(uint8_t Sub_Group);


