/*
 * @file: dac.c
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

static uint16_t buf[MAX_SIZE]; //global buffer to store the samples
static uint32_t count = 0; //global variable to store the number of samples

#define ANALOG_PIN (30) //Setting analog pin to 30 as the output pin for oscilloscope

/**
 * @brief: DAC initialization function, configuring the required registers
 *
 * @para: NULL
 * @return: NULL
 */
void DAC_Init()
{

	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Select analog pin 30
	PORTE->PCR[ANALOG_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ANALOG_PIN] |= PORT_PCR_MUX(3);

	//Setting every bit of DAC register to '0'
    DAC0->C1 = 0;
    DAC0->C2 = 0;

    //Enabling the DAC system and selecting DACRFS_1 as the reference voltage
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

/**
 * @brief: DMA initialization function, configuring the required registers
 *
 * @para: NULL
 * @return: NULL
 */
void DMA_Init()
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	DMAMUX0->CHCFG[0] = 0x00;

	/*
	 * Enabling the interrupt signal, incrementing SAR, source size is 16-bits, destination size is 16-bits
	 * peripheral request is enabled, single read/write transfer is done for each request.
	 */
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
			DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	//Configuration for NVIC
	NVIC_SetPriority(DMA0_IRQn, 2); //Setting interrupt priority as '2'
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	//DMAMUX channel is enabled only when TPM0 overflow happens
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}

/**
 * @brief: TPM0 initialization function, configuring the required registers
 *
 * @para: NULL
 * @return: NULL
 */
void TPM0_Init()
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Using (MCGFLLCLK/2) clock source
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	TPM0->SC = 0;

	//Modulo value for the LPTPM counter is set to overflow after every 48kHz frequency
	TPM0->MOD = TPM_MOD_MOD(SYS_CLOCK / (SYS_CLOCK/1000));

	//Setting the counter value as 0
	TPM0->CNT = 0;

	/*
	 * Prescaler is taken as '1', counter operates in up counting mode,
	 * LPTPM counter is incremented on every LPTPM clock, DMA transfer is enabled
	 */
	TPM0->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0) | TPM_SC_CMOD(1) | TPM_SC_DMA_MASK;
}

/**
 * @brief: Copying the number of samples into count (global) and
 * and copying the samples into 'buf' buffer
 *
 * @para: buffer containing samples
 * 		  number of samples in that buffer
 * @return: NULL
 */
void DMA_Data(uint16_t *sample_buf, uint32_t sample_count) //change to DMA_Data
{
	//Disabling the LPTPM counter
	TPM0->SC &= ~TPM_SC_CMOD_MASK;

	//Storing the number of samples to 'count' to be used in other functions
	count = sample_count;

	//Copying the sample buffer to 'buf' to use it in other functions
	memcpy(buf, sample_buf, count*2);

	//Incrementing LPTPM counter on every LPTPM counter clock
	TPM0->SC |= TPM_SC_CMOD(1);
}

/**
 * @brief: transferring the samples into the DAC over DMA
 *
 * @para: NULL
 * @return: NULL
 */
void Transfer_To_DAC()
{
	//Source address register is used to transfer the samples from 'buf'
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buf);

	//Destination address register is used to transfer the data to the DAC
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	//Transferring of (count*2) bytes to the DAC
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(count * 2);

	//DONE is set when DMA transactions get completed
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;

	//Enabling the DMA channel
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}

/**
 * @brief: DMA handler in which DONE flag is getting cleared and Transfer_To_DAC() function is getting called.
 *
 * @para: NULL
 * @return: NULL
 */
void DMA0_IRQHandler(void)
{
	//Clearing the DONE flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	//Calling the function again to transfer the samples into the DAC
	Transfer_To_DAC();
}
