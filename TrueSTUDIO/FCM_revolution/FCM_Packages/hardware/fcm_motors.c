/*
 * fcm_motors.c
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "fcm_motors.h"

void motors_set_speed(motor_enum_t motor, int16_t speed)
{
	if (speed < 0)
		speed = 0;
	if (speed > 1000)
		speed = 1000;
	speed += 1000;

	if (motor == MOTOR_ALL) {
		uint8_t i;
		for (i = 0; i < 4; i++) {
			__HAL_TIM_SET_COMPARE((motor_timer[i]), motor_channel[i], speed);
		}
	} else {
		__HAL_TIM_SET_COMPARE((motor_timer[motor]), motor_channel[motor], speed);
	}
}

void motors_stop()
{
	motors_set_speed(MOTOR_ALL, 0);
}

void motors_start_safe_initial_rotation()
{
	motors_set_speed(MOTOR_ALL, MOTOR_LOWEST_ROTATION_SPEED);
}

Status motors_init()
{
	motor_timer[0] = &htim3;
	motor_timer[1] = &htim3;
	motor_timer[2] = &htim9;
	motor_timer[3] = &htim9;

	motor_channel[0] = TIM_CHANNEL_3;
	motor_channel[1] = TIM_CHANNEL_4;
	motor_channel[2] = TIM_CHANNEL_1;
	motor_channel[3] = TIM_CHANNEL_2;

	uint8_t i;
	Status status;
	for (i = 0; i < 4; i++) {
		status = HAL_TIM_PWM_Start(motor_timer[i], motor_channel[i]);
		if (status != HAL_OK) {
			return status;
		}
	}
	motors_stop();
	return status;
}
