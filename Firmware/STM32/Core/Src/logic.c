/*
 * logic.c
 *
 *  Created on: Mar 7, 2025
 *      Author: Krzysztof Tomicki
 */

#include "logic.h"
#include "main.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lcd1602.h"
#include "keyboard.h"

static SystemState currentState = STATE_INIT;

void changeState(SystemState newState)
{
	currentState = newState;
}

void stateMachine(void)
{
	switch (currentState)
	{
		case STATE_INIT: stateInitHandler(); break;
		case STATE_CONTROL_TYPE: stateControlTypeHandler(); break;
		default: break;
	}
}

void stateInitHandler(void)
{
	static uint32_t lastBlinkTime = 0;
	static uint8_t textVisible = 1;

	// Print welcome text in the middle of the first line
	LCD_SetCursor(0, 2);
	LCD_SendString("TEMP CONTROL");

	// Blinking "CLICK START" text at 1Hz
	if (HAL_GetTick() - lastBlinkTime >= 500)
	{
		lastBlinkTime = HAL_GetTick();
		textVisible = !textVisible;
	}

	LCD_SetCursor(1, 3);
	if (textVisible)
	{
		LCD_SendString("CLICK START");
	}
	else
	{
		LCD_SendString("           ");
	}

	// Check if START button is pressed to move to the next state
	if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == 1)
	{
		changeState(STATE_CONTROL_TYPE);
		LCD_Clear();
	}
}

void stateControlTypeHandler(void)
{
	static char keyPressed = '\0';
	static bool keyReleased = true;

	// Turn on config mode LED
	HAL_GPIO_WritePin(CONFIG_MODE_GPIO_Port, CONFIG_MODE_Pin, GPIO_PIN_SET);

	// Show possible control options to choose from on the screen
	LCD_SetCursor(0, 0);
	LCD_SendString("1-Relay Control");

	LCD_SetCursor(1, 0);
	LCD_SendString("2-PID Control");

	// Read keyboard input
	char currentKey = Keyboard_readKey();

	// Check if key has been released
	if (currentKey == '\0')
	{
		keyReleased = true;
	}

	// Handle key press
	if (currentKey != '\0' && keyReleased)
	{
		keyReleased = false;
		keyPressed = currentKey;

		// Handle selection
		if (keyPressed == '1')
		{
			HAL_GPIO_WritePin(REG_MODE_GPIO_Port, REG_MODE_Pin, GPIO_PIN_SET);
			changeState(STATE_ON_OFF_TEMP_CONF);
			LCD_Clear();
		}
		else if (keyPressed == '2')
		{
			HAL_GPIO_WritePin(REG_MODE_GPIO_Port, REG_MODE_Pin, GPIO_PIN_SET);
			changeState(STATE_PID_TEMP_CONF);
			LCD_Clear();
		}
		else
		{
			// Invalid choice
			LCD_Clear();
			LCD_SetCursor(0, 3);
			LCD_SendString("Wrong key!");
			
			// Wait for a bit to show the invalid key
			HAL_Delay(1000);
			LCD_Clear();
			
			// Reset for next input
			keyPressed = '\0';
		}
	}
}