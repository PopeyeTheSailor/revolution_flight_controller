/*
 * accelerometer.h
 *
 *  Created on: 06.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_MODULES_ACCELEROMETER_H_
#define FCM_PACKAGES_MODULES_ACCELEROMETER_H_


#include "vector.h"

typedef struct {
	Vector raw_data;
	Vector acceleration_g;
	Vector acceleration_meters_per_second2;
} Accelerometer;

void accelerometer_init(Accelerometer *accelero);
void accelerometer_set_raw_data(Accelerometer *accelero, const Vector *new_raw_data);


#endif /* FCM_PACKAGES_MODULES_ACCELEROMETER_H_ */
