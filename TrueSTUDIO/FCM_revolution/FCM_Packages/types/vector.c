/*
 * vector.c
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "vector.h"
#include "math.h"

Vector *vector_new(vector_base_type fill)
{
	Vector *vector = (Vector*)malloc(sizeof(Vector));
	for (uint8_t i = 0; i < 3; i++) {
		vector->data[i] = fill;
	}
	return vector;
}

void vector_fill(Vector *vector, vector_base_type fill)
{
	for (uint8_t i = 0; i < 3; i++) {
		vector->data[i] = fill;
	}
}

void vector_clear(Vector *vector)
{
	vector_fill(vector, 0);
}

Vector vector_copy(Vector *destination, const Vector *source)
{
	for (uint8_t i = 0; i < 3; i++) {
		destination->data[i] = source->data[i];
	}
	return *destination;
}

Vector vector_add(const Vector *v1, const Vector *v2)
{
	Vector retval;
	for (int i = 0; i < 3; i++) {
		retval.data[i] = v1->data[i] + v2->data[i];
	}
	return retval;
}

Vector vector_subtract(const Vector *v1, const Vector *v2)
{
	Vector retval;
	for (int i = 0; i < 3; i++) {
		retval.data[i] = v1->data[i] - v2->data[i];
	}
	return retval;
}

Vector vector_divide(const Vector *vector, vector_base_type divider)
{
	Vector retval;
	for (int i = 0; i < 3; i++) {
		retval.data[i] = vector->data[i] / divider;
	}
	return retval;
}

Vector vector_power(const Vector *vector, vector_base_type power)
{
	Vector retval;
	for (int i = 0; i < 3; i++) {
		retval.data[i] = (vector_base_type)pow((double)vector->data[i], (double)power);
	}
	return retval;
}
