/*
 * LCD1602.h
 *
 *  Created on: Mar 4, 2025
 *      Author: Krzysztof Tomicki
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

// for HAL functions
#include "stm32f1xx_hal.h"

//Function declarations

/*
 *  Initializes the LCD in 4-bit mode via I2C
 *  hi2c: pointer to the I2C_HandleTypeDef structure (e.g. &hi2c1)
 */
void LCD_Init(I2C_HandleTypeDef *hi2c);

/*
 * Sends a command to the LCD (e.g. clear screen, cursor movement)
 * cmd: command code (e.g. 0x01 for clearing screen)
 */
void LCD_SendCommand(uint8_t cmd);

/*
 * Sends a single character to the LCD at the current cursor position
 * data: ASCII character to display
 */
void LCD_SendChar(char data);

/*
 * Sends a string to the LCD from the current cursor position
 * str: pointer to a null-terminated string
 */
void LCD_SendString(char *str);

/*
 * Clears the LCD screen and sets the cursor to the home position (0,0)
 */
void LCD_Clear(void);

/*
 * Sets the cursor position on the LCD
 */
void LCD_SetCursor(uint8_t row, uint8_t col);


#endif /* INC_LCD1602_H_ */
