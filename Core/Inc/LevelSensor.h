/******************************************************************************/
/**
 * @file LevelSensor.h
 * @addtogroup LEVEL_SENSOR
 * @{
 ******************************************************************************/

#ifndef INC_LEVELSENSOR_H_
#define INC_LEVELSENSOR_H_

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
// Nao ha includes necessarios.

/*******************************************************************************
 * CONFIGURACOES
 ******************************************************************************/

/// Quantidade de amostras usadas no calculo da media.
/// Faixa aceita: 1 a 255 amostras.
#define dLEVEL_SENSOR_NUMBER       20U      // [amostras]

/// Valor bruto maximo produzido pelo ADC.
/// Faixa aceita: maior que zero.
#define dLEVEL_SENSOR_ADC_MAX      4095U    // [raw]

/// Tensao de referencia usada na conversao do ADC.
/// Faixa aceita: maior que zero.
#define dLEVEL_SENSOR_ADC_REF_MV   3300U    // [mV]

/*******************************************************************************
 * DEFINES PUBLICOS
 ******************************************************************************/
// Nao ha defines publicos alem das configuracoes.

/*******************************************************************************
 * TIPOS DE DADOS PUBLICOS
 ******************************************************************************/
// Nao ha tipos de dados publicos.

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

/******************************************************************************/
/** @brief Executa continuamente o processamento do sensor de nivel.
 * @param Nenhum.
 * @retval Nenhum.
 ******************************************************************************/
void LevelSensor_Handler(void);

#endif /* INC_LEVELSENSOR_H_ */

/** @} DOXYGEN GROUP TAG END OF FILE */
