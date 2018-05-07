/*
 * variance_magnitude.c
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#include "static_detector.h"

void static_detector_init(Static_Detector *sd, uint32_t max_buffer_size)
{
	buffer_init(&sd->data_buffer, max_buffer_size );
}

void static_detector_update_data(Static_Detector *sd, Vector *new_data)
{
}


void float_2_bytes(uint8_t *output_bytes, const float float_variable)
{
	union {
		float float_representation;
		uint8_t byte_representation[4];
	} converter;
	converter.float_representation = float_variable;
	memcpy(output_bytes, &converter.byte_representation, 4);
}

void bytes_2_float(float *output_float, const uint8_t *bytes_to_convert)
{
	union {
		float float_representation;
		uint8_t byte_representation[4];
	} converter;
	memcpy(converter.byte_representation, bytes_to_convert, 4);
	*output_float = converter.float_representation;
}

void vector_2_bytes(uint8_t* output_array, const Vector *vector)
{
	uint8_t tmp[4];
	for(uint8_t i = 0; i < 3; i++) {
		float_2_bytes(tmp, vector->data[i]);
		memcpy(output_array + 4*i, tmp, 4);
	}
}

void bytes_2_vector(Vector* output_vector, const uint8_t *bytes_to_convert)
{
	for(uint8_t i = 0; i < 3; i++) {
		bytes_2_float(&output_vector->data[i], bytes_to_convert + 4*i);
	}
}

