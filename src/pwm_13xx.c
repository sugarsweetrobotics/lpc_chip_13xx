/*
 * @brief LPC13xx PWM chip driver for LPC13(47) families
 *
 * @note
 * Copyright(C) SUGAR SWEET ROBOTICS, CO., LTD.
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "clock_13xx.h"


#if defined(CHIP_LPC1347)


static inline int Chip_PWM32_Timer_Init(LPC_TIMER_T* pTimer, uint32_t channel, uint32_t frequency) {
	int retval = -1;
	if(pTimer == LPC_TIMER32_0) {
		Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT32B0);
		retval = 0;
	} else if (pTimer == LPC_TIMER32_1) {
		Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT32B1);
		retval = 1;
	} else {
		return retval;
	}

	pTimer->PR = 0;
	pTimer->MCR = (1 << 10); // MR3 Reset
	pTimer->MR[3] = SystemCoreClock/frequency;
	pTimer->CTCR = 0;
	pTimer->TC = 0;
	pTimer->TCR = 1;

	pTimer->PWMC |= (1 << channel);
	pTimer->MR[0] = 0xFFFFFFFF;

	return retval;
}

static inline bool Chip_PWM32_SetTimerDuty(LPC_TIMER_T* pTimer, uint16_t duty) {
	pTimer->MR[0] = pTimer->MR[3] - 1ULL*pTimer->MR[3]*duty/65536;
	return true;
}


int Chip_PWM_Init(uint8_t port, uint8_t pin, uint32_t frequency) {
	// Initializing PWM Controller

	if(port == 0) {
		switch(pin) {
		case 1:
			LPC_IOCON->PIO0[1] = (2 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 2, frequency);
		case 11:
			LPC_IOCON->PIO0[11] = (3 << 0) | (0 << 3) | (0 << 6) | (1 << 7) | (1 << 8);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 3, frequency);
		case 13:
			LPC_IOCON->PIO0[13] = (3 << 0) | (0 << 3) | (0 << 6) | (1 << 7) | (1 << 8);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 0, frequency);
		case 14:
			LPC_IOCON->PIO0[14] = (3 << 0) | (0 << 3) | (0 << 6) | (1 << 7) | (1 << 8);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 1, frequency);
		case 15:
			LPC_IOCON->PIO0[15] = (3 << 0) | (0 << 3) | (0 << 6) | (1 << 7) | (1 << 8);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 2, frequency);
		case 16:
			LPC_IOCON->PIO0[16] = (2 << 0) | (0 << 3) | (0 << 6) | (1 << 7) | (1 << 8);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 3, frequency);
		case 18:
			LPC_IOCON->PIO0[18] = (2 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 0, frequency);
		case 19:
			LPC_IOCON->PIO0[19] = (2 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 1, frequency);
		default:
			break;
		}

	} else if (port == 1) {
		switch(pin) {
		case 0:
			LPC_IOCON->PIO1[0] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 0, frequency);
		case 1:
			LPC_IOCON->PIO1[1] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 1, frequency);
		case 2:
			LPC_IOCON->PIO1[2] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 2, frequency);
		case 3:
			LPC_IOCON->PIO1[3] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_1, 3, frequency);
		case 24:
			LPC_IOCON->PIO1[24] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 0, frequency);
		case 25:
			LPC_IOCON->PIO1[25] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 1, frequency);
		case 26:
			LPC_IOCON->PIO1[26] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 2, frequency);
		case 27:
			LPC_IOCON->PIO1[27] = (1 << 0) | (0 << 3) | (0 << 6) | (0 << 7);
			return Chip_PWM32_Timer_Init(LPC_TIMER32_0, 3, frequency);
		default:
			break;
		}
	}
	return -1;
}

bool Chip_PWM_SetDuty(int handle, uint16_t duty) {
	if(handle == 0) {
		return Chip_PWM32_SetTimerDuty(LPC_TIMER32_0, duty);
	} else 	if(handle == 1) {
		return Chip_PWM32_SetTimerDuty(LPC_TIMER32_1, duty);
	}
	return false;
}




#endif
