/*
 * gyroscope.c
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "gyroscope.h"

void gyroscope_init(Gyroscope *accelero)
{
	vector_clear(&accelero->raw_data);
	vector_clear(&accelero->rotation_radians_per_second);
	vector_clear(&accelero->rotation_degrees_per_second);
}

void gyroscope_set_raw_data(Gyroscope *gyro, const Vector *new_raw_data)
{
	gyro->raw_data = *new_raw_data;
}


