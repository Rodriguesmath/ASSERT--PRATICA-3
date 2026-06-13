/*
 * bsp.h
 *
 *  Created on: 13 de jun. de 2026
 *      Author: Rodrigues
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "main.h"
#include <stdio.h>
#include <string.h>

void Bsp_Init(void);

int Bsp_TimerHasElapsed(void);

void Bsp_StartTimerInterrupt(void);

void Bsp_ClearTimerFlag(void);

int Bsp_ReadAdcPolling(void);

void Bsp_PrintLevelData(uint16_t average, uint16_t millivolts, uint8_t percent);


#endif /* INC_BSP_H_ */
