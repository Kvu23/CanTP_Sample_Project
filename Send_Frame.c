#include "CanTP_Sample_Project.h"
#include "Send_Frame.h"

/*Global Counter Variables */
int Data_Counter = 0U;
int No_of_Data_Bytes = 0U;
int frame_number = 0U;
int Temp_blockSize = 0U;

/*This function Send Single Frame*/
void Send_Single_Frame(void)
{
	/*Store number of byte in the counter */
	Data_Counter = No_Of_Bytes;
	No_of_Data_Bytes = No_Of_Bytes;

	/*create here first Field and frame types*/
	Sample_Data[0] = ((0x00 << 4) | No_of_Data_Bytes);
	printf("\nSF===> %x ", Sample_Data[0]);

	/*start for loop and get data in the buffer and display it*/
	for (size_t i = 1; i <= No_of_Data_Bytes; i++)
	{
		Sample_Data[i] = rand() % 0xFF;
		printf("%x ", Sample_Data[i]);
	}

	/*Reset the Data Buffer here*/
	memset(Sample_Data, 0x00, sizeof(Sample_Data));
}


/*This functions Send First Frame fromat*/
void Send_First_Frame(void)
{
	uint16_t Extracted_bits = 0U;

	/*Store number of byte in the counter */
	Data_Counter = No_Of_Bytes;
	No_of_Data_Bytes = No_Of_Bytes;

	/*create here first Field and frame types*/
	/*check if no of bytes are greater than 255*/
	if (No_of_Data_Bytes > 0xFF)
	{
		Extracted_bits = (No_of_Data_Bytes & EXTRACT_BIT_8TO10_MASK);
		//printf("Extracted bits: %x\n", Extracted_bits);
		Sample_Data[0] = ((0x1 << 4) | (uint8_t)(Extracted_bits >> 8U));
		Sample_Data[1] = (uint8_t)No_of_Data_Bytes;
	}
	else
	{
		/*Set frame type and DLC field*/
		Sample_Data[0] = (0x1 << 4);
		Sample_Data[1] = (uint8_t)No_of_Data_Bytes;
	}
	
	printf("FF===> %x %x ", Sample_Data[0], Sample_Data[1]);

	/*start for loop and get data in the buffer*/
	for (size_t i = 2; i <= 7U; i++)
	{
		Sample_Data[i] = rand() % 0xFF;
		printf("%x ", Sample_Data[i]);
		--Data_Counter;
	}

	/*Call function to send flow control frame first time*/
	Send_FlowControl_Frame();
	
	/*infinite loop start*/
	while (1) 
	{
		if (Data_Counter != 0)
		{
			/*Sleep for Up to ST Min time*/
			printf("\nSleeping for %d milliSeconds\n", ST_Min);
			/*Call sleep function for delay*/
			Sleep(ST_Min);

			/*Send Consecutive Frame here Call function*/
			Send_Consecutive_Frame();

			/*if temp block size is 0 then send Flow control frame */
			if (Temp_blockSize == 0U)
			{
				/*set block size to number of blocks again*/
				Temp_blockSize = No_Of_Blocks;

				/*Call function to send flow control frame*/
				Send_FlowControl_Frame();
			}
			else
			{
				;
			}
			
		}
		else
		{
			break;
		}
	}
	
	/*Reset the Data Buffer here*/
	memset(Sample_Data, 0x00, sizeof(Sample_Data));

}

/*This function Send Flow control frame*/
void Send_FlowControl_Frame(void)
{
	uint8_t i = 0U;
	/*Reset the Data Buffer here*/
	memset(Sample_Data, 0x00, sizeof(Sample_Data));
	Sample_Data[i++] = 0x30U;
	Sample_Data[i++] = No_Of_Blocks;
	//Sample_Data[i++] = ST_Min;

	printf("\nFC===> %x %x %x\n", Sample_Data[0], Sample_Data[1], ST_Min);
}

/*This function Send Consecutive frames*/
void Send_Consecutive_Frame(void)
{
	uint8_t i = 0U;
	
	/*Reset the Data Buffer here*/
	memset(Sample_Data, 0x00, sizeof(Sample_Data));

	/*check if Frame Number is reached to 0xF then roll over*/
	if (frame_number == 0x0F)
	{
		/*Set frame Number to 0 if it is greater than 0xF*/
		frame_number = 0x0U;
	}
	else
	{
		/*increment frame number*/
		frame_number++;
	}
	
	/*Set consecutive frame types and Number*/
	Sample_Data[0] = ((0x2 << 4) | frame_number);
	
	printf("\nCF===> %x ", Sample_Data[0]);
	
	for (size_t i = 1; i <= 7U; i++)
	{
		/*check if Data counter is Zero or not*/
		if (Data_Counter == 0)
		{
			/*break the loop if counter value is zero*/
			break;
		}
		else
		{
			/*generate data at randomly*/
			Sample_Data[i] = rand() % 0xFF;
		}

		/*Decrement Counter only if block size is not zero*/
		if (No_Of_Blocks == 0U)
		{
			;/*do nothing*/
		}
		else
		{
			/*decrement counter*/
			Data_Counter--;
		}
		
		/*Ptint Data here*/
		printf("%x ", Sample_Data[i]);
	}

	/*Decrement block size here*/
	--Temp_blockSize;
}
