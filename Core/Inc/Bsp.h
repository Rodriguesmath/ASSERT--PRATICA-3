/**
 * @file Bsp.h
 * @brief Interface pública do módulo BSP.
 *
 * Este módulo encapsula o acesso ao hardware utilizado na prática:
 * timer, ADC e saída serial.
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
#include <stdio.h>

/* Defines -------------------------------------------------------------------*/
/* Não há defines públicos neste módulo. */

/* Public prototypes ---------------------------------------------------------*/

/**
 * @brief Inicializa as variáveis internas do BSP.
 */
void Bsp_Init(void);

/**
 * @brief Verifica se o TIM6 sinalizou estouro.
 * @return 1 se o timer sinalizou estouro, 0 caso contrário.
 */
int Bsp_TimerHasElapsed(void);

/**
 * @brief Inicia o TIM6 em modo de interrupção.
 */
void Bsp_StartTimerInterrupt(void);

/**
 * @brief Limpa a flag interna de estouro do TIM6.
 */
void Bsp_ClearTimerFlag(void);

/**
 * @brief Realiza uma leitura do ADC por polling.
 * @return Valor bruto lido do ADC.
 */
int Bsp_ReadAdcPolling(void);

/**
 * @brief Imprime os dados calculados do sensor de nível.
 * @param average Média dos valores brutos do ADC.
 * @param millivolts Tensão calculada em milivolts.
 * @param percent Percentual calculado do nível.
 */
void Bsp_PrintLevelData(uint16_t average, uint16_t millivolts, uint8_t percent);

#endif /* INC_BSP_H_ */
