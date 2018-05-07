/*
 * fcm_spi.c
 *
 *  Created on: 04.05.2018
 *      Author: Popeye
 */

#include "fcm_spi.h"

void fcm_spi_init() {
	HAL_GPIO_WritePin(CS_MPU_GPIO_Port, CS_MPU_Pin, GPIO_PIN_SET); // Drive CS MPU high
	HAL_GPIO_WritePin(CS_RFM22_GPIO_Port, CS_RFM22_Pin, GPIO_PIN_SET); // Drive CS RFM22 high
	HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_SET); // Drive CS External flash memory high
}

Status fcm_spi_transmit(SPI_HandleTypeDef *spi_handle,
		uint8_t *data_to_transmit, uint8_t num_bytes_to_transmit)
{
	return HAL_SPI_Transmit(spi_handle, data_to_transmit,
			num_bytes_to_transmit, TRANSMIT_TIMEOUT);
}

Status fcm_spi_receive(
		SPI_HandleTypeDef *spi_handle,
		uint8_t address_to_read_from,
		uint8_t *received_data,
		uint8_t num_bytes_to_receive)
{
	Status transmission_status = HAL_SPI_Transmit(
			spi_handle, &address_to_read_from, 1, TRANSMIT_TIMEOUT);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	transmission_status = HAL_SPI_Receive(spi_handle, received_data,
			num_bytes_to_receive, 100);
	return transmission_status;
}

Status spi_transmit_mpu(uint8_t *data_to_transmit,
		uint8_t num_bytes_to_transmit)
{
	HAL_GPIO_WritePin(CS_MPU_GPIO_Port, CS_MPU_Pin, GPIO_PIN_RESET); // Drive CS low
	Status transmission_status = fcm_spi_transmit(&hspi1, data_to_transmit, num_bytes_to_transmit);
	HAL_GPIO_WritePin(CS_MPU_GPIO_Port, CS_MPU_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}

Status spi_receive_mpu(uint8_t address_to_read_from,
		uint8_t *received_data, uint8_t num_bytes_to_receive)
{
	HAL_GPIO_WritePin(CS_MPU_GPIO_Port, CS_MPU_Pin, GPIO_PIN_RESET); // Drive CS low
	Status transmission_status = fcm_spi_receive(
			&hspi1, address_to_read_from, received_data, num_bytes_to_receive);
	HAL_GPIO_WritePin(CS_MPU_GPIO_Port, CS_MPU_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}

Status spi_transmit_flash_memory(uint8_t *data_to_transmit,
		uint8_t num_bytes_to_transmit)
{
	HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_RESET); // Drive CS low
	Status transmission_status = fcm_spi_transmit(&hspi3, data_to_transmit, num_bytes_to_transmit);
	HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}

Status spi_receive_flash_memory(uint8_t command, uint8_t *address,
		uint8_t *received_data, uint8_t num_bytes_to_receive)
{
	uint8_t bytes_to_transmit[4];
	uint8_t num_bytesto_transmit = 1;

	bytes_to_transmit[0] = command;

	if (address != NULL) {
		bytes_to_transmit[1] = address[0];
		bytes_to_transmit[2] = address[1];
		bytes_to_transmit[3] = address[2];
		num_bytesto_transmit = 4;
	}

	HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_RESET); // Drive CS low

	// Transmit command code and address (if any)
	Status transmission_status = HAL_SPI_Transmit(
			&hspi3, bytes_to_transmit, num_bytesto_transmit, TRANSMIT_TIMEOUT);
	if (transmission_status != HAL_OK) {
		return transmission_status;
	}
	// Receive data bytes
	transmission_status = HAL_SPI_Receive(&hspi3, received_data,
			num_bytes_to_receive, 100);

	HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}

Status spi_transmit_rfm22(uint8_t *dataToTransmit,
		uint8_t numberOfTransmittedData)
{
	HAL_GPIO_WritePin(CS_RFM22_GPIO_Port, CS_RFM22_Pin, GPIO_PIN_RESET); // Drive CS low
	Status transmission_status = fcm_spi_transmit(&hspi3, dataToTransmit, numberOfTransmittedData);
	HAL_GPIO_WritePin(CS_RFM22_GPIO_Port, CS_RFM22_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}

Status spi_receive_rfm22(uint8_t address_to_read_from, uint8_t *received_data,
		uint8_t num_bytes_to_receive)
{
	HAL_GPIO_WritePin(CS_RFM22_GPIO_Port, CS_RFM22_Pin, GPIO_PIN_RESET); // Drive CS low
	Status transmission_status = fcm_spi_receive(
			&hspi3, address_to_read_from, received_data, num_bytes_to_receive);
	HAL_GPIO_WritePin(CS_RFM22_GPIO_Port, CS_RFM22_Pin, GPIO_PIN_SET); // Drive CS high
	return transmission_status;
}
