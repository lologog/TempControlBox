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

	if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == 1)
	{
		changeState(STATE_CONTROL_TYPE);
		LCD_Clear();
	}
}