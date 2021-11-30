/*
 * @file: sin.c
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @credits: Taher Ujjainwala and Gaurang Rane for the implementation of
 * this function
 */

#include "common.h"

/*
 * Sine lookup table with 33 elements (32 intervals).
 * Computed each value using the equation -> [scale_factor * sin((PI*x)/(2x32))]
 */
static const int16_t lookup_table[TABLE_STEPS+1] =
  {0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960, 1047,
   1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694, 1747,
   1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
   2037};


/*
 * @brief: computes the value of y0 coordinate using coordinate geometry equation (2-point form)
 *
 * @para: x0, (x1,y1) and (x2,y2) coordinates
 * @return: computed value of y0 coordination
 */
int32_t Interpolation(int32_t x0, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	//Mathematical equation to find the value of y0 coordinate if all other parameters are available
	return ((((x2-x1)/2)+((x0-x1)*(y2-y1))) / (x2-x1)+y1);
}

/*
 * @brief: computes the value of sine using the interpolation method if required
 *
 * @para: value in radian
 * @return: computed value of sine mapped with the sine lookup table
 */
int32_t Compute_sin_value(int32_t rad)
{

	int32_t index;
	int flag = 1; //Keeping track of the sign of value

	//Checking the value of 'rad', if rad<-PI, keep adding 2*pi to bring 'rad' between -PI to PI
	while(rad< -PI)
	{
		rad += TWO_PI;
	}

	//Checking the value of 'rad', if rad>PI, keep subtracting 2*pi to bring 'rad' between -PI to PI
	while (rad > PI)
	{
		rad -= TWO_PI;
	}

	//Using the relation sin(-x)=-sin(x), if rad<0, change -rad to +rad and set the flag to -1
	if(rad<0)
	{
		rad = -rad;
		flag = -1;
	}

	//Change rad to (PI-rad) using sin(x)=sin(PI-x) if x>(PI/2)
	if(rad>HALF_PI)
	{
		rad=PI-rad;
	}

	/*
	 * For using the lookup table, you need to calculate the index that matches the input sample as suggested
	 * in White chapter-9.
	 * To achieve this, the lowest value should be subtracted from 'rad' and divided by step size (lowest value is 0)
	 */
	index = rad/TABLE_STEP_SIZE;
	int32_t x1 = index*TABLE_STEP_SIZE;

	//Compare x1 with rad, if they are equal then no interpolation is required
	if (x1 == rad)
	{
		return flag * lookup_table[index];
	}

	//If x1 is not equal to rad then interpolation is performed to return y0 coordinate
	int32_t x2 = (index+1) * TABLE_STEP_SIZE;
	int32_t y0 = Interpolation(rad, x1, lookup_table[index], x2, lookup_table[index+1]);

	return (flag*y0);
}
