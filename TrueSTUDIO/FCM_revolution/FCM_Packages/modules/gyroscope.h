/*
 * gyroscope.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_MODULES_GYROSCOPE_H_
#define FCM_PACKAGES_MODULES_GYROSCOPE_H_

#include "vector.h"

typedef struct {
	Vector raw_data;
	Vector rotation_radians_per_second;
	Vector rotation_degrees_per_second;
} Gyroscope;

void gyroscope_init(Gyroscope *gyro);
void gyroscope_set_raw_data(Gyroscope *gyro, const Vector *new_raw_data);

#endif /* FCM_PACKAGES_MODULES_GYROSCOPE_H_ */
