#ifndef FCM_PACKAGES_TYPES_VECTOR_H_
#define FCM_PACKAGES_TYPES_VECTOR_H_
/*
 * vector.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "stdlib.h"
#include "fcm_types.h"


typedef float vector_base_type;

typedef struct {
	vector_base_type data[3];
} Vector;

Vector *vector_new(vector_base_type fill);
void vector_fill(Vector *vector, vector_base_type fill);
void vector_clear(Vector *vector);
Vector vector_copy(Vector *destination, const Vector *source);
Vector vector_add(const Vector *v1, const Vector *v2);
Vector vector_subtract(const Vector *v1, const Vector *v2);
Vector vector_divide(const Vector *vector, vector_base_type divider);
Vector vector_power(const Vector *vector, vector_base_type power);



#endif /* FCM_PACKAGES_TYPES_VECTOR_H_ */
