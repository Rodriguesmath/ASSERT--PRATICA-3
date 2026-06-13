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



int Bsp_ReadAdcPolling(void)
{
    uint32_t adc_value = 0;

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);

    return (int)adc_value;
}

void Bsp_UartPrintAverage(uint16_t average)
{
	 printf("Media ADC: %u\r\n", average);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        timer6_elapsed = 1;
    }
}
