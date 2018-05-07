/*
 * accelerometer.c
 *
 *  Created on: 06.05.2018
 *      Author: Bartek Kurosz
 */

#include "accelerometer.h"

void accelerometer_init(Accelerometer *accelero)
{
	vector_clear(&accelero->raw_data);
	vector_clear(&accelero->acceleration_g);
	vector_clear(&accelero->acceleration_meters_per_second2);
}

void accelerometer_set_raw_data(Accelerometer *accelero, const Vector *new_raw_data)
{
	accelero->raw_data = *new_raw_data;
}
