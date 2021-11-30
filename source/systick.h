/*
 * @file: systick.h
 *
 * @author: Harshwardhan Singh
 * @date: November 29th 2021
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with
 * Arm Cortex-M based Microcontrollers (Textbook)
 * by Alexander G.Dean.
 */

#include "common.h"

#ifndef SYSTICK_H_
#define SYSTICK_H_

typedef uint32_t ticktime_t;

void Init_Systick();
ticktime_t Now();
void Reset_Timer();
ticktime_t Get_Timer();

#endif /* SYSTICK_H_ */
