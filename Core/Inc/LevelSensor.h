/*
 * LevelSensor.h
 *
 *  Created on: 13 de jun. de 2026
 *      Author: Rodrigues
 */

#ifndef INC_LEVELSENSOR_H_
#define INC_LEVELSENSOR_H_


#include "Bsp.h"

void LevelSensor_NewSample(int raw);
void LevelSensor_IsReady(void);
uint16_t LevelSensor_GetAverage(void);
uint16_t LevelSensor_RawToMilliVolts(uint16_t raw);
uint8_t LevelSensor_RawToPercent(uint16_t raw);

#endif /* INC_LEVELSENSOR_H_ */
