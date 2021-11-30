/*
 * @file: adc.c
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with
 * Arm Cortex-M based Microcontrollers (Textbook)
 * by Alexander G.Dean, GitHub repo
 * and KL25Z Reference Manual.
 *
 */

#include "common.h"

/**
 * @brief: TPM initialization function, configuring the required registers
 *
 * @para: sample rate at which the TPM1 triggers the ADC
 * @return: NULL
 */
void TPM1_Init(int sample_rate)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	//Clear the status and control register
	TPM1->SC = 0;

	//MOD is loaded with the module value
	TPM1->MOD = TPM_MOD_MOD(SYS_CLOCK/sample_rate);

	//Clear the CNT register
	TPM1->CNT = 0;

	//Setting the prescaler factor by dividing with '1' and LPTPM counter is made to operate in up counting mode
	TPM1->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0);
}

/**
 * @brief: ADC initialization function, configuring the required registers
 *
 * @para: NULL
 * @return: NULL
 */
void ADC_Init()
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	/*
	 * Working with normal power configuration, set the divide ratio '1' and the clock rate is input clock,
	 * configured as short sample time, 16-bit conversion, using input clock as Bus clock
	 */
	ADC0->CFG1 = ADC_CFG1_ADLPC(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	//Clear the configuration_2 register
	ADC0->CFG2 = 0;

	/*
	 * Hardware trigger is enabled, compare function is disabled, DMA is disabled, external pins
	 * are used to voltage reference
	 */
	ADC0->SC2 = ADC_SC2_ADTRG(1) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);

	/*
	 * Conversion complete interrupt is disabled, single ended conversion and input channels are selected,
	 * AD23 is selected as input
	 */
	ADC0->SC1[0] = ADC_SC1_AIEN(0) | ADC_SC1_DIFF(0) | ADC_SC1_ADCH(23);

	/*
	 * Alternate trigger is selected for AD0
	 * ADC0 is triggered when TPM1 overflow
	 */
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9);
}

/**
 * @brief: stores the samples into the buffer to be analyzed
 *
 * @para: buffer in which samples are stored through the ADC and the number of samples to be stored
 * @return: NULL
 */
void ADC_Buffer(uint16_t *buffer, uint32_t sample_count)
{
	int i=0;

	//Turning ON the TPM
	TPM1->SC |= TPM_SC_CMOD(1);

	//Loop for filling the ADC buffer
	while(i<sample_count)
	{
		while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK)==0); //wait for the conversion to be done
		buffer[i] = ADC0->R[0]; //if conversion is completed, store the result in the result register
		i++;
	}

	//Turning OFF the TPM
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
}
