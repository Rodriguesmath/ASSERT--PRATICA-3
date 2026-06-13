/*
 * bsp.h
 *
 *  Created on: 13 de jun. de 2026
 *      Author: Rodrigues
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

void Bsp_Init();

void Bsp_StartTimerInterrupt();

void Bsp_ClearTimerFlag();

int Bsp_ReadAdcPolling();

#endif /* INC_BSP_H_ */
