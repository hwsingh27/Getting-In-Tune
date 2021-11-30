/*
 * @file: autocorrelate.h
 *
 * @author: Howdy Pierce
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Provided by the Prof. Howdy Pierce
 */

#ifndef AUTOCORRELATE_H_
#define AUTOCORRELATE_H_

#include "common.h"

typedef enum {
  kAC_12bps_unsigned,   // 12 bits per sample, unsigned samples (stored in 16 bits)
  kAC_16bps_unsigned,   // 16 bits per sample, unsigned samples
  kAC_12bps_signed,     // 12 bits per sample, signed samples (stored in 16 bits)
  kAC_16bps_signed      // 16 bits per sample, signed samples
} autocorrelate_sample_format_t;


/*
 * Determine the fundamental period of a waveform using
 * autocorrelation
 *
 * Parameters:
 *   samples   Array of samples
 *   nsamp     Number of samples
 *   format    The format for the samples (see above)
 *
 * Returns:
 *   The recovered fundamental period of the waveform, expressed in
 *   number of samples, or -1 if no correlation was found
 */
int autocorrelate_detect_period(void *samples, uint32_t nsamp,
    autocorrelate_sample_format_t format);

#endif /* AUTOCORRELATE_H_ */
