/*
 * @file: analysis.c
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @credits: Taher Ujjainwala and Gaurang Rane for the implementation of
 * this function
 */

#include "common.h"

#define FORMAT_SAMPLES (1) //For using 16 bits per sample (unsigned samples)

/**
 * @brief: function analyzes the sine waveform taken through the ADC
 *
 * @para: sample_err buffer with the number of samples to be analyzed
 * @return: the minimum, maximum, average, period and sample frequency of the analyzed sine waveform
 */
void ADC_Analysis(uint16_t *sample_arr, uint32_t num_samples)
{
	int i=0;
	uint32_t maximum=0;
	uint32_t total = 0;
	uint32_t minimum = 65536;

	//Check if 'i' is less than the number of samples to be analyzed
	while(i<num_samples)
	{
		if (sample_arr[i] > maximum)
		{
			maximum = sample_arr[i]; //Finds the maximum value from the samples_arr buffer to get the maximum amplitude of the sine wave
		}
		if (sample_arr[i] < minimum)
		{
			minimum = sample_arr[i]; //Finds the minimum value from the sample_arr buffer to get the minimum amplitude of the sine wave
		}

		total = total + sample_arr[i]; //This computation is used to find  the average
		i++;
	}

	uint32_t samples_per_cycle = autocorrelate_detect_period(sample_arr,num_samples,FORMAT_SAMPLES);
	PRINTF("min=%u max=%u avg=%u period=%d samples frequency=%d Hz\r\n\n",
	      minimum, maximum, total/num_samples, samples_per_cycle, ADC_SAMPLE_RATE/samples_per_cycle);
}
