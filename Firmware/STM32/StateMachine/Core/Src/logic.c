/*
 * logic.c
 *
 *  Created on: Mar 7, 2025
 *      Author: Krzysztof Tomicki
 */

#include "logic.h"
#include "main.h"
#include "stdbool.h"

static SystemState currentState = STATE_INIT;

static float finalTemperature = 0;

void change_state(SystemState newState)
{
	currentState = newState;
}

void state_machine_run(void)
{
	switch (currentState)
	{
	case STATE_INIT: state_init(); break; //screen that waits for user first input (button click)
	case STATE_REG_TYPE: state_reg_type(); break; //screen that show different algorithm types for regulation
	case STATE_BANG_BANG_TEMP_CONF: state_bang_bang_conf(); break; //set coniguration for the bang bang regulation - here temperature and offset
	}
}

void state_init()
{
	static uint32_t lastBlinkTime = 0;
	static uint8_t textVisible = 1;

	//write first line of text
	LCD_SetCursor(0, 2);
	LCD_SendString("TEMP CONTROL");

	LCD_SetCursor(1, 2);

	//count time to change visibility of the second time
	if (HAL_GetTick() - lastBlinkTime >= 1000)
	{
		lastBlinkTime = HAL_GetTick();
		textVisible = !textVisible;
	}

	//write second line of text
	if (textVisible)
	{
		LCD_SendString("CLICK START");
	}
	else
	{
		LCD_SendString("           ");
	}

	//change state if action button is pressed
	if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == 1)
	{
		change_state(STATE_REG_TYPE);
		LCD_Clear();
	}
}

void state_reg_type()
{
	static char pressedKey = '\0';
	static uint16_t showTime = 0;

	HAL_GPIO_WritePin(CONFIG_MODE_GPIO_Port, CONFIG_MODE_Pin, 1);

	//write text on sreen
	LCD_SetCursor(0, 0);
	LCD_SendString("1: BANG BANG");
	LCD_SetCursor(1, 0);
	LCD_SendString("2: PID");

	//wait for input from the user
	while (pressedKey == '\0')
	{
		pressedKey = Keyboard_readKey();
	}

	if (pressedKey == '1')
	{
		currentState = STATE_BANG_BANG_TEMP_CONF;
		LCD_Clear();
	}
	else if (pressedKey == '2')
	{
		currentState = STATE_PID_CONF;
		LCD_Clear();
	}
	else if (pressedKey != '\0') //wrong input from the user
	{
		//show string WRONG NUMBER! for 2 seconds
		LCD_Clear();
		uint32_t show_time = 0;
		showTime = HAL_GetTick();
		while (HAL_GetTick() - showTime <= 2000)
		{
			LCD_SetCursor(0, 1);
			LCD_SendString("WRONG NUMBER!");
		}
		LCD_Clear();
		pressedKey = '\0';
	}
}

void state_bang_bang_conf()
{
	static uint32_t enterTime = 0;
	static bool delayStarted = false;
	static bool keyReleased = true;
	static uint8_t length = 0;
	static char writtenTemperature[6] = {0};
	static bool dotInserted = false;


	LCD_SetCursor(0, 0);
	LCD_SendString("CHOOSE TEMP: ");

	//one time delay to not get the 1 from the previous state
	if (!delayStarted)
	{
		enterTime = HAL_GetTick();
		delayStarted = true;
	}

	if (HAL_GetTick() - enterTime >= 500)
	{
		//read the clicked number
		char currentKey = Keyboard_readKey();

		//checking if the key is released
		if (currentKey == '\0')
		{
			keyReleased = true;
		}

		//if the key was pressed and released
		if (currentKey != '\0' && keyReleased)
		{
			keyReleased = false;

			length = strlen(writtenTemperature);
			//checking if there is still place in the table
            if (length < sizeof(writtenTemperature) - 1)
            {
                //automatically insert a dot after the second digit
                if (length == 2 && !dotInserted)
                {
                    writtenTemperature[length] = '.';
                    writtenTemperature[length + 1] = '\0';
                    dotInserted = true;
                    length++;  //increase length since we added a character
                }

                //add the new digit if there's still space
                if (length < sizeof(writtenTemperature) - 1)
                {
                    writtenTemperature[length] = currentKey;
                    writtenTemperature[length + 1] = '\0';
                }
            }
		}
	}

	LCD_SetCursor(1, 0);
	LCD_SendString(writtenTemperature);

	//accepting written temperature
	if ((HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == 1) && (length == sizeof(writtenTemperature) - 1))
	{
		finalTemperature = atof(writtenTemperature);
		memset(writtenTemperature, 0, strlen(writtenTemperature)); //clear the table
		delayStarted = false;

		currentState = STATE_BANG_BANG_OFFSET_CONF;
	}
}







