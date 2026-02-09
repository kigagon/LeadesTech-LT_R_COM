/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : UI_UART_Funtions.h
  * @brief          : UI_UART_Funtions
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */



void UI_Receiver(void);
void Check_UI_UART_Receive(int check_val);


void Check_Except4UI_UART_Receive(uint8_t tempNum);
void UI_Cmd_Func(void);
void UI_Cmd_Func_A(void);
void UI_Cmd_Func_P(void);
void UI_Cmd_Func_T(void);
void UI_Cmd_Func_S_Save(void);
void UI_Cmd_Func_S(void);
void UI_Cmd_Func_S_N(void);
void UI_Cmd_Func_R(void);
void UI_Cmd_Func_D(void);
void UI_Cmd_Func_G(void);
void UI_Cmd_Func_V(void);
void UI_Cmd_Func_I(void);
void UI_Cmd_Func_I_End(void);
void UI_Com_Func_Anal_LED_Set(void);

void Def_Send_Data(void);
void Init_Group_Data(void);
