/*
 * LevelSensor.c
 *
 *  Created on: 13 de jun. de 2026
 *      Author: Rodrigues
 */

#include "LevelSensor.h"

typedef struct
{
    uint32_t accumulator;
    uint8_t sampleCount;
} LevelSensor_t;

static LevelSensor_t levelSensor = {0U, 0U};
