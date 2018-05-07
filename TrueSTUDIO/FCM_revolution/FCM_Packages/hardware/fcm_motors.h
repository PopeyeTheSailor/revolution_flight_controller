/*
 * motors.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_HARDWARE_FCM_MOTORS_H_
#define FCM_PACKAGES_HARDWARE_FCM_MOTORS_H_

#include "fcm_types.h"
#include "tim.h"

TIM_HandleTypeDef *motor_timer[4];
uint8_t motor_channel[4];

#define MOTOR_LOWEST_ROTATION_SPEED 180
typedef enum {
	MOTOR_FRONT_LEFT, MOTOR_FRONT_RIGHT, MOTOR_REAR_LEFT, MOTOR_REAR_RIGHT, MOTOR_ALL
} motor_enum_t;

/*
 * Set speed in range 0 - 1000
 */
void motors_set_speed(motor_enum_t motor, int16_t speed);

/**
 * Sets speed of all motors to 0
 */
void motors_stop();

/**
 * Sets speed of all motors to lowest speed, at which all motors starts proper rotation
 */
void motors_start_safe_initial_rotation();

/**
 * Initialize motor timers and set speeds to 0
 */
Status motors_init();

#endif /* FCM_PACKAGES_HARDWARE_FCM_MOTORS_H_ */
