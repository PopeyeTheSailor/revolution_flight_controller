/*
 * variance_magnitude.h
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_ALGORITHMS_STATIC_DETECTOR_H_
#define FCM_PACKAGES_ALGORITHMS_STATIC_DETECTOR_H_

#include "fcm_buffer.h"
#include "string.h"
#include "vector.h"

typedef struct {

	Buffer data_buffer;


} Static_Detector;

void static_detector_init(Static_Detector *sd, uint32_t max_buffer_size);

void static_detector_update_data(Static_Detector *sd, Vector *new_data);

void float_2_bytes(uint8_t *output_bytes, const float float_variable);
void bytes_2_float(float *output_float, const uint8_t *bytes_to_convert);
void vector_2_bytes(uint8_t* output_array, const Vector *vector);
void bytes_2_vector(Vector* output_vector, const uint8_t *bytes_to_convert);

#endif /* FCM_PACKAGES_ALGORITHMS_STATIC_DETECTOR_H_ */
