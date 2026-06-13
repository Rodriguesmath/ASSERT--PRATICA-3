/******************************************************************************/
/**
 * @file Bsp.c
 * @addtogroup BSP
 * @brief Interface de baixo nivel com timer, ADC e saida serial.
 * @author Rodrigues
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE.
 *
 * \n <b>Dependencias:</b>
 * - STM32 HAL.
 *
 * \n <b>Observacoes:</b>
 * - Concentra o acesso direto ao TIM6, ADC1 e printf.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "Bsp.h"
#include "adc.h"
#include <stdio.h>
#include "tim.h"

/*******************************************************************************
 * DEFINES LOCAIS (fixos, apenas auxiliar para calculos)
 ******************************************************************************/

/// Tempo maximo de espera pela conversao do ADC.
#define dBSP_ADC_POLL_TIMEOUT_MS    10U    // [ms]

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/
// Nao ha constantes locais.

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

/// Variaveis internas do BSP.
typedef struct
{
    /// Flag de estouro do TIM6.
    volatile bool timer6Elapsed;
} bsp_t;

/// Instancia interna do BSP.
static bsp_t bsp;

/*******************************************************************************
 * PROTOTIPOS LOCAIS
 ******************************************************************************/
static void Bsp_StartTimerInterrupt(void);

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief Inicializa as variaveis internas do BSP.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Init(void)
{
    bsp.timer6Elapsed = false;
    Bsp_StartTimerInterrupt();
}

/******************************************************************************/
/** @brief Verifica se o TIM6 sinalizou estouro.
 * @param Nenhum.
 * @retval true: o timer sinalizou estouro.
 * @retval false: o timer nao sinalizou estouro.
 ******************************************************************************/
bool Bsp_TimerHasElapsed(void)
{
    return bsp.timer6Elapsed;
}

/******************************************************************************/
/** @brief Limpa a flag interna de estouro do TIM6.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_ClearTimerFlag(void)
{
    bsp.timer6Elapsed = false;
}

/******************************************************************************/
/** @brief Realiza uma leitura do ADC por polling.
 * @param Nenhum.
 * @retval Valor bruto lido do ADC.
 ******************************************************************************/
uint16_t Bsp_ReadAdcPolling(void)
{
    uint16_t adcValue = 0U;

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, dBSP_ADC_POLL_TIMEOUT_MS) == HAL_OK)
    {
        adcValue = (uint16_t)HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);

    return adcValue;
}

/******************************************************************************/
/** @brief Imprime os dados calculados do sensor de nivel.
 * @param average: media dos valores brutos do ADC.
 * @param millivolts: tensao calculada em milivolts.
 * @param percent: percentual calculado do nivel.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_PrintLevelData(uint16_t average, uint16_t millivolts, uint8_t percent)
{
    printf("Media ADC: %u | Tensao: %u mV | Nivel: %u%%\r\n",
           average,
           millivolts,
           percent);
}

/******************************************************************************/
/** @brief Callback de estouro dos timers da HAL.
 * @param htim: ponteiro para o timer que gerou a interrupcao.
 * @retval Nenhum.
 ******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        bsp.timer6Elapsed = true;
    }
}

/*******************************************************************************
 * FUNCOES LOCAIS
 ******************************************************************************/

/******************************************************************************/
/** @brief Inicia o TIM6 em modo de interrupcao.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
static void Bsp_StartTimerInterrupt(void)
{
    HAL_TIM_Base_Start_IT(&htim6);
}

/** @} DOXYGEN GROUP TAG END OF FILE */
