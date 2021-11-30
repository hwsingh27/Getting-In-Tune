/*
 * @file: adc.h
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

#ifndef ADC_H_
#define ADC_H_

#define ADC_SAMPLE_RATE (96000)
#define SYS_CLOCK	(48E6)

void TPM1_Init(int sample);
void ADC_Init();
void ADC_Buffer(uint16_t *buffer, uint32_t sample_count);

#endif /* ADC_H_ */
