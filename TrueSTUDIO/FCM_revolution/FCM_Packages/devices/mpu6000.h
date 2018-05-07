/*
 * mpu6000.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_DEVICES_MPU6000_H_
#define FCM_PACKAGES_DEVICES_MPU6000_H_

#include "fcm_spi.h"
#include "vector.h"

#define PWR_MGMT_1 0x6B
#define SIGNAL_PATH_RESET 0x68

#define CONFIG 0x1A
#define DLPF_CFG_94Hz (1<<1) // Digital Low Pass Filter: 94Hz

#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B

#define ACCEL_XOUT_HIGH 0x3B
#define ACCEL_XOUT_HIGH_READ (ACCEL_XOUT_HIGH | (1 << 7))
#define GYRO_XOUT_HIGH 0x43

#define ACCELEROMETER_RESOLUTION 4096.0
#define GYROSCOPE_RESOLUTION 32.8

#define MPU_INIT_TRANSMISSION_DELAY_MS 5

#define GRAVITY_ACCELERATION 9.81f

/**
 * Reads accelerometer and gyroscope data
 */
HAL_StatusTypeDef mpu_6000_read_raw_data(
		Vector *accelerometer_raw_data, Vector *gyroscope_raw_data);

/**
 * Sends initialization messages to mpu6000
 */
HAL_StatusTypeDef mpu_6000_init();

#endif /* FCM_PACKAGES_DEVICES_MPU6000_H_ */
