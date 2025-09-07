/*
 * LCD1602.c
 *
 *  Created on: Mar 4, 2025
 *      Author: Krzysztof Tomicki
 */

#include "lcd1602.h"

//external I2C configuration - change if using a different I2C
extern I2C_HandleTypeDef hi2c1;

/*
 * 		      	LCD 8 bit control
 * BIT      |P0|P1|P2|P3|   P4    |P5|P6|P7|
 * FUNCTION |D4|D5|D6|D7|Backlight|EN|RW|RS|
 *
 * RS -> Mode (1 - data, 0 - cmd)
 * RW -> Read/Write (0 - write)
 * EN -> Activate LCD (impulse 1->0)
 * D7-D4 -> 4 data bits
 *
 * Based on Hitachi HD44780U datasheet
 */

//need to use 4 bit mode because of the i2C to LCD converter
void LCD_SendCommand(uint8_t cmd)
{
	uint8_t data_u, data_l;
	uint8_t data_t[4];

	data_u = (cmd & 0xF0); //upper 4 bits of cmd
	data_l = ((cmd << 4) & 0xF0); // lower 4 bits of cmd (left shift)

	data_t[0] = data_u | 0x0C; // EN = 1, RS = 0, backlight = 1;
	data_t[1] = data_u | 0x08; // EN = 0, RS = 0, Backlight = 1;
	data_t[2] = data_l | 0x0C;
	data_t[3] = data_l | 0x08;

	//send 4-byte sequence to LCD
	HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data_t, 4, 100);
}

void LCD_Init(I2C_HandleTypeDef *hi2c)
{
	HAL_Delay(50); //wait for LCD to power up ~ 40ms

	//Set LCD into 4bit mode (8 bit default)
	LCD_SendCommand(0x30); // 8-bit mode
	HAL_Delay(1);
	LCD_SendCommand(0x30); // confirmation
	HAL_Delay(1);
	LCD_SendCommand(0x30); // one more confirmation to make sure
	HAL_Delay(1);
	LCD_SendCommand(0x20); // change to 4 bit mode

	// Function set: 4-bit, 2-line, 5x8 font
	LCD_SendCommand(0x28);
	HAL_Delay(1);

	// Turn off screen to avoid blinking while configurating
	LCD_SendCommand(0x08);
	HAL_Delay(1);

	//Clear display
	LCD_SendCommand(0x01);
	HAL_Delay(2); // must be 2ms

	//cursor configuration to shift right after every character, no shift of the screen
	LCD_SendCommand(0x06);
	HAL_Delay(1);

	//Turn on screen, cursor off
	LCD_SendCommand(0x0C);
}

void LCD_SendChar(char data)
{
	// almost same as send command
	uint8_t data_u, data_l;
	uint8_t data_t[4];

	data_u = (data & 0xF0);
	data_l = ((data << 4) & 0xF0);

	data_t[0] = data_u | 0x0D; //EN = 1, RS = 1, backlight = 1;
	data_t[1] = data_u | 0x09; //EN = 0, RS = 1, backlight = 1;
	data_t[2] = data_l | 0x0D;
	data_t[3] = data_l | 0x09;

	HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS, data_t, 4, 100);
}

void LCD_SendString(char *str)
{
	while (*str) // loop unitl the null character (end of string) '\0' is found
	{
		LCD_SendChar(*str);
		str++;
	}
}

void LCD_Clear(void)
{
	LCD_SendCommand(0x01);
	HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
	// if row 0 then address 0x80 so first line, otherwise second line
	uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
	LCD_SendCommand(address);
}
