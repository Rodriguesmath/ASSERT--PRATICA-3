/******************************************************************************/
/**
 * @file LevelSensor.c
 * @addtogroup LEVEL_SENSOR
 * @brief Processamento do sensor de nivel lido pelo ADC.
 * @author Rodrigues
 * @details
 * \n <b>Ferramentas:</b>
 * - STM32CubeIDE.
 *
 * \n <b>Dependencias:</b>
 * - Bsp.
 *
 * \n <b>Observacoes:</b>
 * - Acumula amostras brutas do ADC, calcula a media e converte o resultado para
 *   milivolts e percentual.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "LevelSensor.h"
#include "Bsp.h"
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * DEFINES LOCAIS (fixos, apenas auxiliar para calculos)
 ******************************************************************************/

/// Valor maximo da escala percentual.
#define dLEVEL_SENSOR_PERCENT_MAX              100U    // [%]

/// Valor maximo suportado pelo contador de amostras.
#define dLEVEL_SENSOR_SAMPLE_COUNTER_MAX       255U    // [amostras]

/// Valor usado para reiniciar acumuladores e contadores.
#define dLEVEL_SENSOR_RESET_VALUE              0U

// Verificacao de consistencia dos defines de configuracao.
#if (dLEVEL_SENSOR_NUMBER == 0U)
    #error "dLEVEL_SENSOR_NUMBER deve ser maior que zero."
#endif

#if (dLEVEL_SENSOR_NUMBER > dLEVEL_SENSOR_SAMPLE_COUNTER_MAX)
    #error "dLEVEL_SENSOR_NUMBER excede a capacidade do contador de amostras."
#endif

#if (dLEVEL_SENSOR_ADC_MAX == 0U)
    #error "dLEVEL_SENSOR_ADC_MAX deve ser maior que zero."
#endif

#if (dLEVEL_SENSOR_ADC_REF_MV == 0U)
    #error "dLEVEL_SENSOR_ADC_REF_MV deve ser maior que zero."
#endif

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/
// Nao ha constantes locais.

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

/// Variaveis internas do LevelSensor.
typedef struct
{
    /// Acumulador das amostras brutas do ADC.
    uint32_t accumulator;

    /// Quantidade de amostras acumuladas.
    uint8_t sampleCount;
} levelSensor_t;

/// Instancia interna do LevelSensor.
static levelSensor_t levelSensor;

/*******************************************************************************
 * PROTOTIPOS LOCAIS
 ******************************************************************************/
static void LevelSensor_NewSample(uint16_t rawValue);
static bool LevelSensor_IsReady(void);
static uint16_t LevelSensor_GetAverage(void);
static void LevelSensor_Reset(void);
static uint16_t LevelSensor_RawToMilliVolts(uint16_t rawValue);
static uint8_t LevelSensor_RawToPercent(uint16_t rawValue);

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief Executa continuamente o processamento do sensor de nivel.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void LevelSensor_Handler(void)
{
    while (true)
    {
        if (Bsp_TimerHasElapsed() == true)
        {
            Bsp_ClearTimerFlag();

            uint16_t rawValue = Bsp_ReadAdcPolling();

            LevelSensor_NewSample(rawValue);

            if (LevelSensor_IsReady() == true)
            {
                uint16_t average = LevelSensor_GetAverage();
                uint16_t millivolts = LevelSensor_RawToMilliVolts(average);
                uint8_t percent = LevelSensor_RawToPercent(average);

                Bsp_PrintLevelData(average, millivolts, percent);

                LevelSensor_Reset();
            }
        }
    }
}

/*******************************************************************************
 * FUNCOES LOCAIS
 ******************************************************************************/

/******************************************************************************/
/** @brief Acumula uma nova amostra bruta do ADC.
 * @param rawValue: valor bruto lido do ADC.
 * @retval Nenhum.
 * @details A amostra e somada ao acumulador interno enquanto a quantidade de
 *          amostras ainda for menor que dLEVEL_SENSOR_NUMBER.
 ******************************************************************************/
static void LevelSensor_NewSample(uint16_t rawValue)
{
    if (levelSensor.sampleCount < dLEVEL_SENSOR_NUMBER)
    {
        levelSensor.accumulator += rawValue;
        levelSensor.sampleCount++;
    }
}

/******************************************************************************/
/** @brief Verifica se o modulo ja possui amostras suficientes.
 * @param Nenhum.
 * @retval true: a quantidade de amostras atingiu dLEVEL_SENSOR_NUMBER.
 * @retval false: a quantidade de amostras ainda nao atingiu dLEVEL_SENSOR_NUMBER.
 ******************************************************************************/
static bool LevelSensor_IsReady(void)
{
    return levelSensor.sampleCount >= dLEVEL_SENSOR_NUMBER;
}

/******************************************************************************/
/** @brief Calcula a media aritmetica das amostras acumuladas.
 * @param Nenhum.
 * @retval Media dos valores brutos do ADC.
 * @details Caso nenhuma amostra tenha sido acumulada, a funcao retorna
 *          dLEVEL_SENSOR_RESET_VALUE para evitar divisao por zero.
 ******************************************************************************/
static uint16_t LevelSensor_GetAverage(void)
{
    if (levelSensor.sampleCount == dLEVEL_SENSOR_RESET_VALUE)
    {
        return dLEVEL_SENSOR_RESET_VALUE;
    }

    return levelSensor.accumulator / levelSensor.sampleCount;
}

/******************************************************************************/
/** @brief Reinicia o estado interno do modulo.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
static void LevelSensor_Reset(void)
{
    levelSensor.accumulator = dLEVEL_SENSOR_RESET_VALUE;
    levelSensor.sampleCount = dLEVEL_SENSOR_RESET_VALUE;
}

/******************************************************************************/
/** @brief Converte um valor bruto do ADC para milivolts.
 * @param rawValue: valor bruto lido do ADC.
 * @retval Valor convertido em milivolts.
 * @details A conversao considera dLEVEL_SENSOR_ADC_MAX e
 *          dLEVEL_SENSOR_ADC_REF_MV.
 ******************************************************************************/
static uint16_t LevelSensor_RawToMilliVolts(uint16_t rawValue)
{
    return rawValue * dLEVEL_SENSOR_ADC_REF_MV / dLEVEL_SENSOR_ADC_MAX;
}

/******************************************************************************/
/** @brief Converte um valor bruto do ADC para percentual.
 * @param rawValue: valor bruto lido do ADC.
 * @retval Valor percentual correspondente.
 ******************************************************************************/
static uint8_t LevelSensor_RawToPercent(uint16_t rawValue)
{
    return rawValue * dLEVEL_SENSOR_PERCENT_MAX / dLEVEL_SENSOR_ADC_MAX;
}

/** @} DOXYGEN GROUP TAG END OF FILE */
