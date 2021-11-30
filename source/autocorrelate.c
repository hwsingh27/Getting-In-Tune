/*
 * @file: autocorrelate.c
 *
 * @author: Howdy Pierce
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Provided by the Prof. Howdy Pierce
 */

#include "common.h"


/*
 * See documentation in .h file
 */
int
autocorrelate_detect_period(void *samples, uint32_t nsamp,
    autocorrelate_sample_format_t format)
{
	int i=0, k=0;
  int32_t sum = 0;
  int prev_sum = 0;
  int32_t thresh = 0;
  bool slope_positive = false;

  int32_t s1 = 0;
  int32_t s2 = 0;

  sum = 0;
  for (i=0; i < nsamp; i++) {
    prev_sum = sum;
    sum = 0;

    for (k=0; k < nsamp - i; k++) {

      switch (format) {

      case kAC_12bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 11);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 11);
        sum += (s1 * s2) >> 12;
        break;

      case kAC_16bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 15);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 15);
        sum += (s1 * s2) >> 16;
        break;

      case kAC_12bps_signed:
      case kAC_16bps_signed:
        s1 = *((int16_t*)samples + k);
        s2 = *((int16_t*)samples + k+i);
        sum += (s1 * s2) >> (format == kAC_12bps_signed ? 12 : 16);
        break;
      }
    }

    if (i == 0) {
      thresh = sum / 2;

    } else if ((sum > thresh) && (sum - prev_sum > 0)) {
      // slope is positive, so now enter mode where we're looking for
      // negative slope
      slope_positive = true;

    } else if (slope_positive && (sum - prev_sum) <= 0) {
      // We have crested the peak and started down the other
      // side; actual peak was one sample back
      return i-1;
    }
  }

  // no correlation found
  return -1;
}
