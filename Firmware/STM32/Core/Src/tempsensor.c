#include "tempsensor.h"

//variables to store callibration data to calculate temp in Celcius degrees
static uint16_t tempSensor_T1;
static int16_t tempSensor_T2, tempSensor_T3;

//Function that reads whole byte of chosen register via I2C from the sensor
uint8_t TempSensor_ReadRegister(I2C_HandleTypeDef *hi2c, uint8_t reg)
{
    uint8_t value;
    HAL_I2C_Mem_Read(hi2c, TEMPSENSOR_I2C_ADDR << 1, reg, 1, &value, 1, HAL_MAX_DELAY); // << 1 because I2C is using 7bit addressing
    return value;
}

//same as the function above but reads 2 bytes instead of one
uint16_t TempSensor_Read16(I2C_HandleTypeDef *hi2c, uint8_t reg) {
    uint8_t buf[2];
    HAL_I2C_Mem_Read(hi2c, TEMPSENSOR_I2C_ADDR << 1, reg, 1, buf, 2, HAL_MAX_DELAY);
    return (buf[1] << 8) | buf[0];
}

//Initialization function
uint8_t TempSensor_Init(I2C_HandleTypeDef *hi2c)
{
	//we want to check if sensor ID read from the sensor register matches ID from the datasheet
    uint8_t id = TempSensor_ReadRegister(hi2c, TEMPSENSOR_REG_ID);
    if (id != 0x58)
    {
    	return 0;
    }

    //read temperature calibration data
    tempSensor_T1 = TempSensor_Read16(hi2c, TEMPSENSOR_REG_DIG_T1);
    tempSensor_T2 = (int16_t)TempSensor_Read16(hi2c, TEMPSENSOR_REG_DIG_T2);
    tempSensor_T3 = (int16_t)TempSensor_Read16(hi2c, TEMPSENSOR_REG_DIG_T3);

    //configure TempSensor: Temperature x1, Pressure x1, Normal mode
    uint8_t config = (1 << 5) | (1 << 2) | 3;
    HAL_I2C_Mem_Write(hi2c, TEMPSENSOR_I2C_ADDR << 1, TEMPSENSOR_REG_CTRL_MEAS, 1, &config, 1, HAL_MAX_DELAY);

    return 1;
}

//read 20bit raw temperature data and converts it into Celcius degrees
float TempSensor_ReadTemp(I2C_HandleTypeDef *hi2c)
{
    int32_t raw_temp;

    //read temperature registers (20-bit value)
    uint8_t msb = TempSensor_ReadRegister(hi2c, TEMPSENSOR_REG_TEMP_MSB);
    uint8_t lsb = TempSensor_ReadRegister(hi2c, TEMPSENSOR_REG_TEMP_LSB);
    uint8_t xlsb = TempSensor_ReadRegister(hi2c, TEMPSENSOR_REG_TEMP_XLSB);

    raw_temp = (msb << 12) | (lsb << 4) | (xlsb >> 4);

    //temperature calibration formula
    int32_t var1, var2, t_fine;
    var1 = ((((raw_temp >> 3) - ((int32_t)tempSensor_T1 << 1))) * ((int32_t)tempSensor_T2)) >> 11;
    var2 = (((((raw_temp >> 4) - ((int32_t)tempSensor_T1)) * ((raw_temp >> 4) - ((int32_t)tempSensor_T1))) >> 12) * ((int32_t)tempSensor_T3)) >> 14;

    t_fine = var1 + var2;
    float temperature = (t_fine * 5 + 128) >> 8;

    return temperature / 100.0;
}
