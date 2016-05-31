/*
 *  led.c
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, P.BH.P
 */

#include "led.h"





void led_init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  // GPIO Ports Clock Enable
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  // Configure GPIO pin Output Level
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);

  // Configure GPIO pin : PB7
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PI1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

void led_on( uint8_t ch )
{
  switch( ch )
  {
	case 0:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);   break;
	case 1:  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);     break;
  }
}

void led_off( uint8_t ch )
{
  switch( ch )
  {
	case 0:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);   break;
	case 1:  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);     break;
  }
}

void led_toggle( uint8_t ch )
{
  switch( ch )
  {
	case 0:      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);      break;
	case 1:      HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);      break;
  }
}

