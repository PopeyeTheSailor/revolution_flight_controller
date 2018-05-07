/*
 * mpu6000.c
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#include "mpu6000.h"

Status mpu_6000_read_raw_data(
		Vector *accelerometer_data, Vector *gyroscope_data)
{
	uint8_t raw_data[14];
	Status transmission_status = spi_receive_mpu(ACCEL_XOUT_HIGH_READ, raw_data, 14);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}

	uint8_t raw_accelerometer_data[6];
	uint8_t raw_gyroscope_data[6];
	for (uint8_t i = 0; i < 6; i++) {
		raw_accelerometer_data[i] = raw_data[i];
		raw_gyroscope_data[i] = raw_data[i + 8];
	}
	for(uint8_t i = 0; i < 3; i++) {
		accelerometer_data->data[i] = (int16_t)(raw_accelerometer_data[2*i] << 8) | (int16_t)(raw_accelerometer_data[2*i+1]);
		gyroscope_data->data[i] = (int16_t)(raw_accelerometer_data[2*i] << 8) | (int16_t)(raw_gyroscope_data[2*i+1]);
	}
	return transmission_status;
}

Status mpu_6000_init()
{
	uint8_t transmitBuffer[2];
	Status transmission_status;

	// Device reset
	transmitBuffer[0] = PWR_MGMT_1;
	transmitBuffer[1] = 0x80;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

	// Analog Reset
	transmitBuffer[0] = SIGNAL_PATH_RESET;
	transmitBuffer[1] = 0x07;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

	// Set clock source to PLL with X axis gyroscope reference
	transmitBuffer[0] = PWR_MGMT_1;
	transmitBuffer[1] = 0x00;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

	// Configure Accelerometer to +/- 8g (4096 LSB/g)
	transmitBuffer[0] = ACCEL_CONFIG;
	transmitBuffer[1] = 0x10;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

	transmitBuffer[0] = CONFIG;
	transmitBuffer[1] = DLPF_CFG_94Hz;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

//	 Configure Gyroscope to +/- 1000deg (32.8 LSB/deg)
	transmitBuffer[0] = GYRO_CONFIG;
	transmitBuffer[1] = 0x10;
	transmission_status = spi_transmit_mpu(transmitBuffer, 2);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	HAL_Delay(MPU_INIT_TRANSMISSION_DELAY_MS);

	return transmission_status;
}
