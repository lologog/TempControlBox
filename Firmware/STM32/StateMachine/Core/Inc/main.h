/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
<<<<<<< HEAD
=======
#define ENC1_BTN_Pin GPIO_PIN_14
#define ENC1_BTN_GPIO_Port GPIOC
#define ENC2_BTN_Pin GPIO_PIN_15
#define ENC2_BTN_GPIO_Port GPIOC
#define ENC3_BTN_Pin GPIO_PIN_0
#define ENC3_BTN_GPIO_Port GPIOD
#define BTN2_Pin GPIO_PIN_4
#define BTN2_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_5
#define BTN1_GPIO_Port GPIOA
#define STM_RUNNING_Pin GPIO_PIN_11
#define STM_RUNNING_GPIO_Port GPIOA
#define CONFIG_MODE_Pin GPIO_PIN_12
#define CONFIG_MODE_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define REG_MODE_Pin GPIO_PIN_15
#define REG_MODE_GPIO_Port GPIOA
#define LCD_SCL_Pin GPIO_PIN_6
#define LCD_SCL_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOB
>>>>>>> dev

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
