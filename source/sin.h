/*
 * @file: sin.h
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @credits: Taher Ujjainwala and Gaurang Rane for the implementation of
 * this function
 */

#ifndef SIN_H_
#define SIN_H_

#include "common.h"

#define SCALE_FACTOR	(2037)
#define HALF_PI			(3200)
#define PI 				(6399)
#define TWO_PI			(12799)
#define TABLE_STEPS 	(32)
#define TABLE_STEP_SIZE (HALF_PI/TABLE_STEPS)

int32_t Compute_sin_value(int32_t x);
int32_t Interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void ADC_Analysis(uint16_t *buffer, uint32_t count);

size_t Tone_To_Samples(int input_freq, uint16_t *buffer, size_t size);

#endif /* SIN_H_ */
