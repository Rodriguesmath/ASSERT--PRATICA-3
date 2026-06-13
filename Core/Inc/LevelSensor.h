/**
 * @file LevelSensor.h
 * @brief Interface pública do módulo de sensor de nível.
 *
 * Este módulo acumula amostras do ADC, calcula a média dos valores
 * brutos e realiza conversões para milivolts e percentual.
 */

#ifndef INC_LEVELSENSOR_H_
#define INC_LEVELSENSOR_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/
#define dLEVEL_SENSOR_NUMBER       20U
#define dLEVEL_SENSOR_ADC_MAX      4095U
#define dLEVEL_SENSOR_ADC_REF_MV   3300U

/* Public prototypes ---------------------------------------------------------*/

/**
 * @brief Acumula uma nova amostra do ADC.
 * @param rawValue Valor bruto lido do ADC.
 */
void LevelSensor_NewSample(uint16_t rawValue);

/**
 * @brief Verifica se o número de amostras necessárias foi atingido.
 * @return 1 se estiver pronto, 0 caso contrário.
 */
int LevelSensor_IsReady(void);

/**
 * @brief Retorna a média das amostras acumuladas.
 * @return Média dos valores brutos do ADC.
 */
uint16_t LevelSensor_GetAverage(void);

/**
 * @brief Reinicia o acumulador e a contagem de amostras.
 */
void LevelSensor_Reset(void);

/**
 * @brief Converte um valor bruto do ADC para milivolts.
 * @param rawValue Valor bruto do ADC.
 * @return Valor convertido em milivolts.
 */
uint16_t LevelSensor_RawToMilliVolts(uint16_t rawValue);

/**
 * @brief Converte um valor bruto do ADC para percentual.
 * @param rawValue Valor bruto do ADC.
 * @return Percentual correspondente entre 0 e 100.
 */
uint8_t LevelSensor_RawToPercent(uint16_t rawValue);

#endif /* INC_LEVELSENSOR_H_ */
