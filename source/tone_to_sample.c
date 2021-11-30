/*
 * @file: tone_to_sample.c
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @credits: Collaboration with Taher Ujjainwala for the implementation
 * of this function
 */

#include "common.h"

/**
 * @brief: function generates the samples for the given frequency and stores them in the buffer
 * which is then passed to the DAC over DMA to generate the waveform.
 *
 * @para: the frequency whose samples to be computed, buffer to store the samples, maximum size of the buffer
 * @return: the total number of samples in total number of cycles
 */
uint32_t Tone_To_Samples(int freq_note, uint16_t *buffer, uint32_t buf_size)
{
	int32_t val;
	int i=0;
	int samples_per_cycle = (DAC_SAMPLE_RATE+(freq_note/2))/freq_note; //Calculating the number of samples required for running one cycle
	int total_cycles = buf_size / samples_per_cycle; //Calculating the total number of cycles
	int total_samples = samples_per_cycle * total_cycles; //Calculating the total number of samples required for total number cycles

	//Filling the buffer with the computed samples for generating sine wave
	while(i<total_samples)
	{
		val = Compute_sin_value(i*TWO_PI/samples_per_cycle)+SCALE_FACTOR;
		buffer[i] = val;
		i++;
	}

	PRINTF("Generated %d samples at %d Hz; computed period=%d samples\r\n",
			total_samples, freq_note, samples_per_cycle);

	return total_samples;
}
