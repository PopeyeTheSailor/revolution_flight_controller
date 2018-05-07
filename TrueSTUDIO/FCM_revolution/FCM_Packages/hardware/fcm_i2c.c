/*
 * fcm_i2c.c
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "fcm_i2c.h"

Status i2c_memory_write(uint16_t device_address, uint16_t memory_address,
		uint8_t *data_to_transmit, uint8_t num_bytes_to_transmit)
{
	return HAL_I2C_Mem_Write(&hi2c1, device_address, memory_address, 1,
			data_to_transmit, num_bytes_to_transmit, 100);
}

Status i2c_memory_read(uint16_t device_address, uint16_t memory_address,
		uint8_t *received_data, uint8_t num_bytes_to_receive)
{
	return HAL_I2C_Mem_Read(&hi2c1, device_address, memory_address, 1,
			received_data, num_bytes_to_receive, 100);
}
