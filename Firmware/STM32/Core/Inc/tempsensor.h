#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "stm32f1xx_hal.h"

#define TEMPSENSOR_I2C_ADDR        0x76  //default I2C address
#define TEMPSENSOR_REG_ID          0xD0  //sensor ID register stored inside the sensor
#define TEMPSENSOR_REG_CTRL_MEAS   0xF4  //control register - where the settings are stored
#define TEMPSENSOR_REG_TEMP_MSB    0xFA  //MSB of temperature data
#define TEMPSENSOR_REG_TEMP_LSB    0xFB  //LSB of temperature data
#define TEMPSENSOR_REG_TEMP_XLSB   0xFC  //XLSB of temperature data

//temperature calibration registers
#define TEMPSENSOR_REG_DIG_T1      0x88
#define TEMPSENSOR_REG_DIG_T2      0x8A
#define TEMPSENSOR_REG_DIG_T3      0x8C

//function declarations
uint8_t TempSensor_Init(I2C_HandleTypeDef *hi2c);
float TempSensor_ReadTemp(I2C_HandleTypeDef *hi2c);

#endif
