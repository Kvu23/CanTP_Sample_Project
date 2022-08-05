#pragma once

#ifndef SEND_FRAME_H
#define SEND_FRAME_H
#include <time.h>
#include <Windows.h>
//#define EXTRACT_BIT_8TO10_MASK	((uint16_t)(0b111) << (8U))
#define EXTRACT_BIT_8TO10_MASK	(0x00000700)

extern int Data_Counter;
extern int No_of_Data_Bytes;
extern int frame_number;
extern int Temp_blockSize;

void Send_First_Frame(void);
void Send_Single_Frame(void);
void Send_FlowControl_Frame(void);
void Send_Consecutive_Frame(void);

#endif // !SEND_FRAME_H