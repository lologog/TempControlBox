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

static float finalTemperature = 0;

void changeState(SystemState newState)
{
	currentState = newState;
}

void stateMachine(void)
{
	LCD_SetCursor(0, 0);
	LCD_SendString("State Machine");
}