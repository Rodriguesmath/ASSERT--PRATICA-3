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

void LevelSensor_NewSample(uint16_t rawValue)
{
    if (levelSensor.sampleCount < dLEVEL_SENSOR_NUMBER)
    {
        levelSensor.accumulator += rawValue;
        levelSensor.sampleCount++;
    }
}

int LevelSensor_IsReady(void)
{
    return levelSensor.sampleCount >= dLEVEL_SENSOR_NUMBER;
}

uint16_t LevelSensor_GetAverage(void)
{
    if (levelSensor.sampleCount == 0U)
    {
        return 0U;
    }

    return levelSensor.accumulator / levelSensor.sampleCount;
}

void LevelSensor_Reset(void)
{
    levelSensor.accumulator = 0U;
    levelSensor.sampleCount = 0U;
}
