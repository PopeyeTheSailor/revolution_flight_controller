/*
 * fcm_i2c.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_HARDWARE_FCM_I2C_H_
#define FCM_PACKAGES_HARDWARE_FCM_I2C_H_

#include "i2c.h"
#include "fcm_types.h"

/**
 * Writes specified message to the device over I2C bus
 */
Status i2c_memory_write(uint16_t device_address, uint16_t memory_address,
		uint8_t *data_to_transmit, uint8_t num_bytes_to_transmit);

/**
 * Reads specified register from the device over I2C bus
 */
Status i2c_memory_read(uint16_t device_address, uint16_t memory_address,
		uint8_t *received_data, uint8_t num_bytes_to_receive);

#endif /* FCM_PACKAGES_HARDWARE_FCM_I2C_H_ */
