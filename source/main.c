/*
 * @file: main.c
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with
 * Arm Cortex-M based Microcontrollers (Textbook)
 * by Alexander G.Dean, GitHub repo
 * and KL25Z Reference Manual.
 */

#include "common.h"

#define A4 (440) //440Hz
#define D5 (587) //587Hz
#define E5 (659) //659Hz
#define A5 (880) //880Hz

#define ONE_SEC (100) //count value of 100 as 1 count = 10 msec, 100 counts = 1sec

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    int total_samples;
	int i=0;
    uint16_t out_buffer[MAX_SIZE];
    uint16_t in_buffer[MAX_SIZE];
    int notes[4] = {A4, D5, E5, A5};

    //Calling initialization functions
    Init_Systick();
    DAC_Init();
    DMA_Init();
    TPM0_Init();
    TPM1_Init(ADC_SAMPLE_RATE);
    ADC_Init();

    PRINTF("Sine Function Testing\r\n");
    Test_Sine(); //Testing sine wave error and sum of square error
    PRINTF("\r\n");

    Reset_Timer();

    //Keep track of 1sec time, when systick reaches 1sec, frequency changes
    while(1)
    {
    	if(Get_Timer()>ONE_SEC)
    	{
    		i++;
    		if(i==4)
    		{
    			i=0;
    		}
    		Reset_Timer();
    	}

        PRINTF("Frequency: %d Hz\r\n", notes[i]);
        total_samples = Tone_To_Samples(notes[i], out_buffer, MAX_SIZE);

        //DMA and DAC section
        DMA_Data(out_buffer,total_samples);
        Transfer_To_DAC();

        //ADC section
        ADC_Buffer(in_buffer, MAX_SIZE);
        ADC_Analysis(in_buffer, MAX_SIZE);
    }
    return 0 ;
}
