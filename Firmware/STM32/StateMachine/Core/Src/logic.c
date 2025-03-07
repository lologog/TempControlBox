/*
 * logic.c
 *
 *  Created on: Mar 7, 2025
 *      Author: Krzysztof Tomicki
 */

#include "logic.h"
#include "main.h"

static SystemState currentState = STATE_INIT;

void change_state(SystemState newState)
{
	currentState = newState;
}

void state_machine_run(void)
{
	switch (currentState)
	{
	case STATE_INIT: state_init(); break; //screen that waits for user first input (button click)
	case STATE_REG_TYPE:break;
	}
}

void state_init()
{
	static uint32_t lastBlinkTime = 0;
	static uint8_t textVisible = 1;

	if (HAL_GetTick() - lastBlinkTime >= 1000)
	{
		lastBlinkTime = HAL_GetTick();
		textVisible = !textVisible;
	}

	LCD_SetCursor(0, 2);
	LCD_SendString("TEMP CONTROL");

	LCD_SetCursor(1, 2);

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
		change_state(STATE_REG_TYPE);
	}
}

