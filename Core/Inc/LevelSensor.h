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

void LevelSensor_IsReady();
#endif /* INC_LEVELSENSOR_H_ */
