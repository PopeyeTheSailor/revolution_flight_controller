/*
 * fcm_buffer.h
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#include "vector.h"
#include "stdlib.h"

#ifndef FCM_PACKAGES_TYPES_FCM_BUFFER_H_
#define FCM_PACKAGES_TYPES_FCM_BUFFER_H_


typedef struct buffer_element{

	Vector *data;
	struct buffer_element *next;

} Buffer_Element;

typedef struct {

	Buffer_Element *first;
	Buffer_Element *last;
	uint16_t size;
	uint16_t max_buffer_size;

	Vector *sum; // sum of all the elements in the buffer
	Vector *mean; // mean of all the elements in the buffer
	Vector *variance; // mean of all the elements in the buffer

} Buffer;


Buffer_Element *buffer_element_new();
void buffer_element_delete(Buffer_Element *elem);

void buffer_init(Buffer *buf, uint32_t max_buffer_size);
void buffer_clean(Buffer *buf);
void buffer_add(Buffer *buf, Vector data);
Vector buffer_sum_all_elements(Buffer *buf);
Vector buffer_calculate_mean(Buffer *buf);
Vector buffer_calculate_variance(Buffer *buf);

#endif /* FCM_PACKAGES_TYPES_FCM_BUFFER_H_ */
