/*
 * fcm_led.c
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#include "fcm_led.h"

void statusLedOn() {
	HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_RESET); // blue on
}

void statusLedOff() {
	HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET); // blue off
}

void statusLedToggle() {
	HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin); // blue toggle
}

void warningLedOn() {
	HAL_GPIO_WritePin(LED_WARNING_GPIO_Port, LED_WARNING_Pin, GPIO_PIN_RESET); // orange on
}

void warningLedOff() {
	HAL_GPIO_WritePin(LED_WARNING_GPIO_Port, LED_WARNING_Pin, GPIO_PIN_SET); // orange off
}

void warningLedToggle() {
	HAL_GPIO_TogglePin(LED_WARNING_GPIO_Port, LED_WARNING_Pin); // orange toggle
}
