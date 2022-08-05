// CanTP_Sample_Project.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CanTP_Sample_Project.h"

/*Global variables to store Data*/
uint8_t Sample_Data[MAX_DATA_LENGTH];

/*variable to store No of Data bytes to send*/
int No_Of_Bytes = 0U;
int No_Of_Blocks = 0U;
int ST_Min = 0U;

int main(void)
{
	/*main loop to continuously Run programs*/
	while (1)
	{
		/*Reset variables first here*/
		Data_Counter = 0;
		No_of_Data_Bytes = 0U;
		frame_number = 0U;
		Temp_blockSize = 0U;

		printf("\n\nPlease Enter No of bytes to Send: ");
		(void)scanf_s("%d", &No_Of_Bytes);

		/*memset Data buffer*/
		memset(Sample_Data, 0x00, sizeof(Sample_Data));
#if 0
		/*check if number of bytes are less than or equal to 7*/
		if (No_Of_Bytes < 8)
		{
			;/*do nothing*/
		}
		else
		{
			printf("Please Enter No of Block Size: ");
			(void)scanf_s("%d", &No_Of_Blocks);
			Temp_blockSize = No_Of_Blocks;

			printf("Please Enter ST Min in milliSeconds: ");
			(void)scanf_s("%d", &ST_Min);
			printf("\n\n");
		}
#endif

		/*Check for input Data length here for MIN and MAX size*/
		if (No_Of_Bytes <= 0 || No_Of_Bytes > 4095U)
		{
			printf("No of bytes are %d then Exiting\n", No_Of_Bytes);
			exit(EXIT_FAILURE);
		}
		else
		{
			/*check if No of bytes are less then 7 then Send Single frame*/
			if (No_Of_Bytes < 8)
			{
				/*Call function to send Single frame*/
				Send_Single_Frame();
			}
			else/*greater than or equal to 8 bytes here*/
			{
				/*Ask user for input*/
				printf("Please Enter No of Block Size: ");
				(void)scanf_s("%d", &No_Of_Blocks);
				Temp_blockSize = No_Of_Blocks;

				printf("Please Enter ST Min in milliSeconds: ");
				(void)scanf_s("%d", &ST_Min);
				printf("\n\n");

				/*Call function to send first frame*/
				Send_First_Frame();
			}
		}
	}
	
	return 0;
}


