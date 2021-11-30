/*
 * @file: tone_to_sample.h
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @credits: Collaboration with Taher Ujjainwala for the implementation
 * of this function
 */

#ifndef TONE_TO_SAMPLE_H_
#define TONE_TO_SAMPLE_H_

#include "common.h"

size_t Tone_To_Samples(int freq_note, uint16_t *buffer, uint32_t buf_size);

#endif /* TONE_TO_SAMPLE_H_ */
