/*
 *  hal.c
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram, P.BH.P
 */

#include "hal.h"





void hal_init()
{
  bsp_init();

  led_init();
  button_init();
}

