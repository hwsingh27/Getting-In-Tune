/*
 * @file: test_sin.c
 *
 * @author: Howdy Pierce
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Provided by the Prof. Howdy Pierce
 */

#include "common.h"

void Test_Sine()
{
	double act_sin;
	double exp_sin;
	double err;
	double sum_sq = 0;
	double max_err = 0;
	int i= 0;
	for (i=-TWO_PI; i <= TWO_PI; i++)
	{
		exp_sin = sin( (double)i / SCALE_FACTOR) * SCALE_FACTOR;
		act_sin = Compute_sin_value(i);
		err = act_sin - exp_sin;
		if (err < 0)
		{
			err = -err;
		}
		if (err > max_err)
		{
			max_err = err;
		}
		sum_sq += err*err;
	}
	PRINTF("Maximum Error=%d Sum of Square=%d\r\n",(int)max_err,(int)sum_sq);
}
