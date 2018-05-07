/*
 * allan_variance.c
 *
 *  Created on: 05.05.2018
 *      Author: Popeye
 */

#include "allan_variance.h"

uint8_t allan_variance_update(Allan_Variance *av, Vector *new_data)
{
	//TODO Something does not work here, only one axis (axis[1] - Roll) nicely goes to
	// asymptote
	Vector average_difference;
	Vector average_difference_squared;
	Vector allan_variance;
	vector_clear(&average_difference);
	vector_clear(&average_difference_squared);
	vector_clear(&allan_variance);

	// sum ALLAN_VARIANCE_SAMPLES_NUMBER measurements
	*av->data_sum = vector_add(av->data_sum, new_data);

	av->num_samples_added++;

	if (av->num_samples_added == av->num_samples_in_interval) {
		av->num_samples_added = 0;
		// Compute average of previous interval
		*av->data_average[av->interval_count] = vector_divide(av->data_sum, av->num_samples_in_interval);
		vector_clear(av->data_sum);

		if (av->interval_count > 0) {
			if (av->interval_count > av->num_intervals_to_process) {
				// suspend task
				return 0;
			} else {

				// Compute: sum((x(t,k) - x(t,k-1))^2)     for k=1 to N
				for(uint8_t interval = 1; interval <= av->interval_count; interval++) {
					average_difference = vector_subtract(av->data_average[interval], av->data_average[interval-1]);
					average_difference_squared = vector_power(&average_difference, 2);
					allan_variance = vector_add(&allan_variance, &average_difference_squared);
				}
				allan_variance = vector_divide(&allan_variance, 2*av->interval_count);
				*av->allan_variance[av->interval_count] = allan_variance;
				*av->allan_variance_last_updated = allan_variance;
			}
		}
		av->interval_count++;
		return 1;
	}
	return 0;
}

void allan_variance_init(
		Allan_Variance *av,
		uint16_t sampling_freq_hz,
		uint16_t interval_length_ms,
		uint16_t num_intervals_to_process
		)
{
	av->sampling_freq_hz = sampling_freq_hz;
	av->interval_length_ms = interval_length_ms;
	av->num_intervals_to_process = num_intervals_to_process;

	av->num_samples_in_interval = av->sampling_freq_hz * av->interval_length_ms;
	av->interval_count = 0;
	av->num_samples_added = 0;

	av->data_sum = vector_new(0);
	av->allan_variance_last_updated = vector_new(0);

	for (uint16_t i = 0; i < NUMBER_OF_INTERVALS_TO_PROCESS; i++) {
		av->data_average[i] = vector_new(0);
		av->allan_variance[i] = vector_new(0);
	}
}

void allan_variance_deinit(Allan_Variance *av)
{
	for (uint16_t i = 0; i < NUMBER_OF_INTERVALS_TO_PROCESS; i++) {
		free(av->data_average[i]);
		free(av->allan_variance[i]);
	}
	free(av->data_sum);
	free(av->allan_variance_last_updated);
}

Vector *allan_variance_get_allan_variance_all(const Allan_Variance *av)
{
	return *av->allan_variance;
}

Vector allan_variance_get_last_computed_allan_variance(const Allan_Variance *av)
{
	return *av->allan_variance_last_updated;
}
