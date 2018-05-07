/*
 *  M25P16_flash.c
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#include "m25p16_flash.h"

HAL_StatusTypeDef flash_memory_send_command(uint8_t command)
{
	return spi_transmit_flash_memory(&command, 1);
}

void flash_memory_wait_for_write_access()
{
	uint8_t cmd = M25P16_CMD_READ_STATUS_REGISTER;
	uint8_t status_register;
//	uint16_t iter = 0;
	do {
		HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_RESET); // drive CS low
		HAL_SPI_Transmit(&hspi3, &cmd, 1, 1000);
		HAL_SPI_Receive(&hspi3, &status_register, 1, 1000);
		HAL_GPIO_WritePin(CS_FLASH_GPIO_Port, CS_FLASH_Pin, GPIO_PIN_SET); // drive CS high
		//TODO ADD TIMEOUT FOR THIS OPERATION
//		iter++;
//		if (iter == 10000) break;
	} while ((status_register & M25P16_STATUS_REGISTER_WIP_BIT));
}

HAL_StatusTypeDef flash_memory_full_erase()
{
	Status status;
	status = flash_memory_send_command(M25P16_CMD_WRITE_ENABLE);
	if (status != HAL_OK) {
		return status;
	}
	status = flash_memory_send_command(M25P16_CMD_BULK_ERASE);
	if (status != HAL_OK) {
		return status;
	}
	return status;
}

HAL_StatusTypeDef flash_memory_write(uint32_t address, uint8_t *data, uint8_t num_bytes)
{
	Status status;
	uint8_t address_segmented[3] = {address & 0x00FF0000, address & 0x0000FF00, address & 0x000000FF};

	uint8_t cmd_size = num_bytes + 4;
	uint8_t *cmd = (uint8_t*)malloc(sizeof(uint8_t) * cmd_size);
	cmd[0] = M25P16_CMD_PAGE_PROGRAM;
	memcpy(cmd+1, address_segmented, 3);
	memcpy(cmd+4, data, num_bytes);

	status = flash_memory_send_command(M25P16_CMD_WRITE_ENABLE);
	if (status != HAL_OK) {
		return status;
	}
	status = spi_transmit_flash_memory(cmd, cmd_size);
	free(cmd);
	if (status != HAL_OK) {
		return status;
	}
	return status;
}

HAL_StatusTypeDef flash_memory_read(uint32_t address, uint8_t *buffer, uint8_t num_bytes)
{
	Status status;
	uint8_t address_segmented[3] = {address & 0x00FF0000, address & 0x0000FF00, address & 0x000000FF};

	status = spi_receive_flash_memory(M25P16_CMD_READ_DATA_BYTES, address_segmented, buffer, num_bytes);
	if (status != HAL_OK) {
		return status;
	}
	return status;
}

HAL_StatusTypeDef flash_memory_init()
{
	Status status;
	flash_memory_wait_for_write_access();
	status = flash_memory_full_erase();
	if (status != HAL_OK) {
		return status;
	}
	return HAL_OK;
}

