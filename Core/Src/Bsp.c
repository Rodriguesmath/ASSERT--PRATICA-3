/*
 * Bsp.c
 *
 *  Created on: 13 de jun. de 2026
 *      Author: Rodrigues
 */
#include "Bsp.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim6;

static volatile int timer6_elapsed = 0;

void Bsp_Init(void)
{
    timer6_elapsed = 0;
}

int Bsp_TimerHasElapsed(void)
{
    return timer6_elapsed;
}

void Bsp_StartTimerInterrupt(void)
{
    HAL_TIM_Base_Start_IT(&htim6);
}
void Bsp_ClearTimerFlag(void)
{
    timer6_elapsed = 0;
}


int Bsp_ReadAdcPolling(void){}

void Bsp_UartPrintAverage(uint16_t average)
{
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        timer6_elapsed = 1;
    }
}
