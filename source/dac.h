/*
 * @file: dac.h
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

#ifndef DAC_H_
#define DAC_H_

#include "common.h"

#define MAX_SIZE (1024)
#define DAC_SAMPLE_RATE (48000)
#define SYS_CLOCK (48E6)

void DAC_Init();
void DMA_Init();
void TPM0_Init();
void DMA_Data(uint16_t *sample_buf, uint32_t sample_count);
void Transfer_To_DAC();

#endif /* DAC_H_ */
