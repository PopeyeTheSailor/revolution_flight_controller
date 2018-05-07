/*
 * allan_variance.h
 *
 *  Created on: 05.05.2018
 *      Author: Popeye
 */

#ifndef FCM_PACKAGES_ALGORITHMS_ALLAN_VARIANCE_H_
#define FCM_PACKAGES_ALGORITHMS_ALLAN_VARIANCE_H_

#define NUMBER_OF_INTERVALS_TO_PROCESS 100

#include "vector.h"
#include <stdlib.h>

typedef struct {

	uint16_t sampling_freq_hz;
	uint16_t interval_length_ms;
	uint16_t num_intervals_to_process;

	uint16_t num_samples_in_interval;
	uint16_t interval_count;
	uint16_t num_samples_added;

	Vector *data_sum;
	Vector *allan_variance_last_updated;
	Vector *data_average[NUMBER_OF_INTERVALS_TO_PROCESS];
	Vector *allan_variance[NUMBER_OF_INTERVALS_TO_PROCESS];
} Allan_Variance;

/**
 *
 */
void allan_variance_init(
		Allan_Variance *av,
		uint16_t sampling_freq_hz,
		uint16_t interval_length_ms,
		uint16_t num_intervals_to_process
		);

void allan_variance_deinit(Allan_Variance *av);

uint8_t allan_variance_update(Allan_Variance *av, Vector *new_data);

Vector *allan_variance_get_allan_variance_all(const Allan_Variance *av);

Vector allan_variance_get_last_computed_allan_variance(const Allan_Variance *av);



#endif /* FCM_PACKAGES_ALGORITHMS_ALLAN_VARIANCE_H_ */
