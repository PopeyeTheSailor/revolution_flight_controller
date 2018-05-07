/*
 * fcm_buffer.c
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#include "fcm_buffer.h"

Buffer_Element *buffer_element_new()
{
	Buffer_Element *buf_elem = malloc(sizeof(Buffer_Element));
	buf_elem->data = vector_new(0);
	return buf_elem;
}

void buffer_element_delete(Buffer_Element *elem)
{
	if (elem != NULL) {
		if (elem->data != NULL) {
			free (elem->data);
		}
		free(elem);
	}
}


void buffer_init(Buffer *buf, uint32_t max_buffer_size)
{
	buf->first = NULL;
	buf->last = NULL;
	buf->size = 0;
	buf->max_buffer_size = max_buffer_size;

	buf->sum = vector_new(0);
	buf->mean = vector_new(0);
	buf->variance = vector_new(0);
}

void buffer_clean(Buffer *buf)
{
	if (buf->size == 1) {
		buf->size = 0;
		buffer_element_delete(buf->first);
		buf->first = NULL;
		buf->last = NULL;

	} else if (buf->size > 1) {
		Buffer_Element *e1 = buf->first;
		Buffer_Element *e2 = e1->next;
		do {
			buffer_element_delete(e1);
			e1 = e2;
			e2 = e2->next;
			buf->size--;
		} while (buf->size);

		buffer_element_delete(e1);
	}
}


void buffer_add(Buffer *buf, Vector data)
{
	Buffer_Element *buf_elem = buffer_element_new();
	*buf_elem->data =  data; // copy data
	buf_elem->next = NULL;

	// If buffer is empty
	if (buf->size == 0) {
		buf->first = buf_elem;
		buf->last = buf_elem;

	// If buffer is full
	} else if (buf->size == buf->max_buffer_size) {
		// update sum, so it does not have to be recalculated from scratch
		*buf->sum = vector_subtract(buf->sum, buf->first->data);
		*buf->sum = vector_add(buf->sum, &data);
		// update mean
		buffer_calculate_mean(buf);

		// update pointers
		buf->last->next = buf_elem;
		buf->last = buf_elem;
		Buffer_Element *tmp = buf->first;
		buf->first = buf->first->next;
		free(tmp);
		free(tmp);

	// If buffer is not empty nor full
	} else {
		buf->last->next = buf_elem;
		buf->last = buf_elem;
		buf->size++;
	}
}

Vector buffer_sum_all_elements(Buffer *buf)
{
	vector_clear(buf->sum);
	Buffer_Element *el = buf->first;

	while (el != NULL) {
		*buf->sum = vector_add(buf->sum, el->data);
		el = el->next;
	}
	return *buf->sum;
}

Vector buffer_calculate_mean(Buffer *buf)
{
	*buf->mean = vector_divide(buf->sum, buf->size);
	return *buf->mean;
}

Vector buffer_calculate_variance(Buffer *buf)
{
	Vector tmp;
	Vector variance_sum;

	vector_clear(&variance_sum);
	vector_clear(&tmp);
	vector_clear(buf->variance);

	Buffer_Element *el = buf->first;
	while (el != NULL) {
		tmp = vector_subtract(el->data, buf->mean); // X = Xi - Xm  (Xi - data point, Xm - mean)
		tmp = vector_power(&tmp, 2); // X = X^2
		variance_sum = vector_add(&variance_sum, &tmp); // Variance_sum += X
		el = el->next;
	}
	*buf->variance = vector_divide(&variance_sum, buf->size-1);
	return *buf->variance;
}

vector_base_type buffer_calculate_sigma(Buffer *buf)
{
	Vector variance = buffer_calculate_variance(buf);
	vector_base_type sigma = 0;
	for (uint8_t i = 0; i < 3; i++) {
		sigma += variance.data[i] * variance.data[i];
	}
	return sigma;
}

