/******************************************************************************/
/**
 * @file Bsp.h
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#ifndef INC_BSP_H_
#define INC_BSP_H_

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONFIGURACOES
 ******************************************************************************/
// Nao ha configuracoes publicas.

/*******************************************************************************
 * DEFINES PUBLICOS
 ******************************************************************************/
// Nao ha defines publicos.

/*******************************************************************************
 * TIPOS DE DADOS PUBLICOS
 ******************************************************************************/
// Nao ha tipos de dados publicos.

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

/******************************************************************************/
/** @brief Inicializa as variaveis internas do BSP.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Init(void);

/******************************************************************************/
/** @brief Verifica se o TIM6 sinalizou estouro.
 * @param Nenhum.
 * @retval true: o timer sinalizou estouro.
 * @retval false: o timer nao sinalizou estouro.
 ******************************************************************************/
bool Bsp_TimerHasElapsed(void);

/******************************************************************************/
/** @brief Limpa a flag interna de estouro do TIM6.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_ClearTimerFlag(void);

/******************************************************************************/
/** @brief Realiza uma leitura do ADC por polling.
 * @param Nenhum.
 * @retval Valor bruto lido do ADC.
 ******************************************************************************/
uint16_t Bsp_ReadAdcPolling(void);

/******************************************************************************/
/** @brief Imprime os dados calculados do sensor de nivel.
 * @param average: media dos valores brutos do ADC.
 * @param millivolts: tensao calculada em milivolts.
 * @param percent: percentual calculado do nivel.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_PrintLevelData(uint16_t average, uint16_t millivolts, uint8_t percent);

#endif /* INC_BSP_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
