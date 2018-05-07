/*
 * imu.c
 *
 *  Created on: 06.05.2018
 *      Author: Bartek Kurosz
 */


#include "imu.h"

void imu_init(Imu *imu)
{
	gyroscope_init(&imu->gyro);
	accelerometer_init(&imu->accelero);
	vector_clear(&imu->orientation);
	mpu_6000_init();
}

void imu_set_raw_data(Imu *imu, Vector *raw_acc, Vector *raw_gyro, Vector *raw_mag)
{
	accelerometer_set_raw_data(&imu->accelero, raw_acc);
	gyroscope_set_raw_data(&imu->gyro, raw_gyro);
}
