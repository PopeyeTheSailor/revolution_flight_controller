/*
 * imu.h
 *
 *  Created on: 06.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_MODULES_IMU_H_
#define FCM_PACKAGES_MODULES_IMU_H_

#include "gyroscope.h"
#include "accelerometer.h"
#include "mpu6000.h"

typedef struct {

	Gyroscope gyro;
	Accelerometer accelero;

	Vector orientation;

} Imu;

void imu_init(Imu *imu);
void imu_set_raw_data(Imu *imu, Vector *raw_acc, Vector *raw_gyro, Vector *raw_mag);

#endif /* FCM_PACKAGES_MODULES_IMU_H_ */
