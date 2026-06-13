/**
 * @file Bsp.c
 * @brief Implementação do módulo BSP.
 *
 * Este módulo concentra o acesso direto ao hardware utilizado na prática:
 * TIM6, ADC1 e saída serial via printf.
 */

/* Includes ------------------------------------------------------------------*/
#include "Bsp.h"

/* Private typedefs ----------------------------------------------------------*/

/**
 * @brief Estrutura interna do módulo BSP.
 */
typedef struct
{
    volatile int timer6Elapsed;
} Bsp_t;

/* Private variables ---------------------------------------------------------*/

static Bsp_t bsp = {0};

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim6;

/* Public functions ----------------------------------------------------------*/

/**
 * @brief Inicializa as variáveis internas do BSP.
 */
void Bsp_Init(void)
{
    bsp.timer6Elapsed = 0;
}

/**
 * @brief Verifica se o TIM6 sinalizou estouro.
 * @return 1 se o timer sinalizou estouro, 0 caso contrário.
 */
int Bsp_TimerHasElapsed(void)
{
    return bsp.timer6Elapsed;
}

/**
 * @brief Inicia o TIM6 em modo de interrupção.
 */
void Bsp_StartTimerInterrupt(void)
{
    HAL_TIM_Base_Start_IT(&htim6);
}

/**
 * @brief Limpa a flag interna de estouro do TIM6.
 */
void Bsp_ClearTimerFlag(void)
{
    bsp.timer6Elapsed = 0;
}

/**
 * @brief Realiza uma leitura do ADC por polling.
 * @return Valor bruto lido do ADC.
 */
int Bsp_ReadAdcPolling(void)
{
    uint32_t adcValue = 0U;

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10U) == HAL_OK)
    {
        adcValue = HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);

    return adcValue;
}

/**
 * @brief Imprime os dados calculados do sensor de nível.
 * @param average Média dos valores brutos do ADC.
 * @param millivolts Tensão calculada em milivolts.
 * @param percent Percentual calculado do nível.
 */
void Bsp_PrintLevelData(uint16_t average, uint16_t millivolts, uint8_t percent)
{
    printf("Media ADC: %u | Tensao: %u mV | Nivel: %u%%\r\n",
           average,
           millivolts,
           percent);
}

/**
 * @brief Callback de estouro dos timers da HAL.
 * @param htim Ponteiro para o timer que gerou a interrupção.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        bsp.timer6Elapsed = 1;
    }
}
