/*
 * hmc5883.c
 *
 *  Created on: 04.05.2018
 *      Author: Popeye
 */

#include "hmc5883.h"

Status hmc_5883l_init()
{
	Status transmission_status;
	uint8_t data_to_write = (1 << 3) | (1 << 4); // FIXME magic number!
	transmission_status = i2c_memory_write(
			HMC5883L_ADDRESS, HMC5883L_CONFIGURATION_REGISTER_A, &data_to_write, 1);
	if (transmission_status != HAL_OK) {
		//TODO create transmission error message
		return transmission_status;
	}

	data_to_write = 0x00; // set continuous conversion mode
	transmission_status = i2c_memory_write(HMC5883L_ADDRESS, HMC5883L_MODE_REGISTER, &data_to_write, 1);
	if (transmission_status != HAL_OK) {
		//TODO create transmission error message
		return transmission_status;
	}
	return transmission_status;
}

Status hmc_5883l_read_raw_data(Vector *magnetometer_data)
{
	Status transmission_status;
	uint8_t raw_data_bytes[6];
	transmission_status = i2c_memory_read(HMC5883L_ADDRESS, HMC5883L_DATA_OUTPUT_X_MSB_REGISTER, raw_data_bytes, 6);
	if (transmission_status != HAL_OK) {
		//TODO create transmission error message
		return transmission_status;
	}
	for(uint8_t i = 0; i < 3; i++) {
		magnetometer_data->data[i] = (raw_data_bytes[2*i] << 8) | raw_data_bytes[2*i+1];
	}
	return transmission_status;
}
