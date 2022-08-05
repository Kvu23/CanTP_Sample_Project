#pragma once

#ifndef CANTP_SAMPLE_PROJECT_H
#define CANTP_SAMPLE_PROJECT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Send_Frame.h"

#define MAX_DATA_LENGTH 500U

/*extern variables */
extern uint8_t Sample_Data[MAX_DATA_LENGTH];
extern int No_Of_Bytes;
extern int No_Of_Blocks;
extern int ST_Min;

#endif // !CANTP_SAMPLE_PROJECT_H
