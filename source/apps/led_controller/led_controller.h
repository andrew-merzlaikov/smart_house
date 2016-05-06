/*
 * control_led.h
 *
 *  Created on: 06 мая 2016 г.
 *      Author: Шундеев
 */

#ifndef CONTROL_LED_CONTROL_LED_H_
#define CONTROL_LED_CONTROL_LED_H_

#include <stdint.h>
#include <xdc/std.h>
#include <driverlib/gpio.h>

#define GREEN_PIN GPIO_PIN_4
#define YELLOW_PIN GPIO_PIN_7
#define RED_PIN GPIO_PIN_6


void led_toggle(uint8_t led_pin);
void pisiaheartBeatIdle(UArg arg0, UArg arg1);

#endif /* CONTROL_LED_CONTROL_LED_H_ */
