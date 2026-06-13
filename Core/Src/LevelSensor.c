/**
 * @file LevelSensor.c
 * @brief Implementação do módulo de sensor de nível.
 *
 * Este módulo é responsável por acumular amostras brutas do ADC,
 * verificar quando a quantidade desejada de amostras foi atingida,
 * calcular a média aritmética e converter valores brutos para
 * milivolts e percentual.
 *
 * Created on: 13 de jun. de 2026
 * Author: Rodrigues
 */

/* Includes ------------------------------------------------------------------*/
#include "LevelSensor.h"

/* Private typedefs ----------------------------------------------------------*/

/**
 * @brief Estrutura interna do módulo LevelSensor.
 *
 * Agrupa todas as variáveis internas usadas para o cálculo da média.
 */
typedef struct
{
    uint32_t accumulator; /**< Acumulador das amostras brutas do ADC. */
    uint8_t sampleCount; /**< Quantidade de amostras acumuladas. */
} LevelSensor_t;

/* Private variables ---------------------------------------------------------*/

/**
 * @brief Instância interna do módulo LevelSensor.
 */
static LevelSensor_t levelSensor = {0, 0};

/* Public functions ----------------------------------------------------------*/

/**
 * @brief Acumula uma nova amostra bruta do ADC.
 *
 * A amostra é somada ao acumulador interno enquanto a quantidade de
 * amostras ainda for menor que dLEVEL_SENSOR_NUMBER.
 *
 * @param rawValue Valor bruto lido do ADC.
 */
void LevelSensor_NewSample(uint16_t rawValue)
{
    if (levelSensor.sampleCount < dLEVEL_SENSOR_NUMBER)
    {
        levelSensor.accumulator += rawValue;
        levelSensor.sampleCount++;
    }
}

/**
 * @brief Verifica se o módulo já possui amostras suficientes.
 *
 * @return 1 se a quantidade de amostras atingiu dLEVEL_SENSOR_NUMBER,
 *         0 caso contrário.
 */
int LevelSensor_IsReady(void)
{
    return levelSensor.sampleCount >= dLEVEL_SENSOR_NUMBER;
}

/**
 * @brief Calcula a média aritmética das amostras acumuladas.
 *
 * Caso nenhuma amostra tenha sido acumulada, a função retorna 0 para
 * evitar divisão por zero.
 *
 * @return Média dos valores brutos do ADC.
 */
uint16_t LevelSensor_GetAverage(void)
{
    if (levelSensor.sampleCount == 0)
    {
        return 0;
    }

    return levelSensor.accumulator / levelSensor.sampleCount;
}

/**
 * @brief Reinicia o estado interno do módulo.
 *
 * Zera o acumulador e a quantidade de amostras, permitindo iniciar
 * um novo ciclo de aquisição.
 */
void LevelSensor_Reset(void)
{
    levelSensor.accumulator = 0;
    levelSensor.sampleCount = 0;
}

/**
 * @brief Converte um valor bruto do ADC para milivolts.
 *
 * A conversão considera a resolução máxima definida por
 * dLEVEL_SENSOR_ADC_MAX e a tensão de referência definida por
 * dLEVEL_SENSOR_ADC_REF_MV.
 *
 * @param rawValue Valor bruto lido do ADC.
 *
 * @return Valor convertido em milivolts.
 */
uint16_t LevelSensor_RawToMilliVolts(uint16_t rawValue)
{
    return rawValue * dLEVEL_SENSOR_ADC_REF_MV / dLEVEL_SENSOR_ADC_MAX;
}

/**
 * @brief Converte um valor bruto do ADC para percentual.
 *
 * O valor bruto é convertido para uma escala de 0 a 100%.
 *
 * @param rawValue Valor bruto lido do ADC.
 *
 * @return Valor percentual correspondente.
 */
uint8_t LevelSensor_RawToPercent(uint16_t rawValue)
{
    return rawValue * 100U / dLEVEL_SENSOR_ADC_MAX;
}
