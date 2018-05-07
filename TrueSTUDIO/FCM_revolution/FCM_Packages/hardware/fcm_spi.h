/*
 * fcm_spi.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_HARDWARE_FCM_SPI_H_
#define FCM_PACKAGES_HARDWARE_FCM_SPI_H_

#include "fcm_types.h"
#include "spi.h"

#define TRANSMIT_TIMEOUT 100 // units?
#define RECEIVE_TIMEOUT 100 // units?

/**
 * Initializes SPI data lines
 */
void fcm_spi_init();

/**
 * Transmits data through hardware SPI peripheral
 *
 * @param spi_handle
 * @param data_to_transmit
 * @param num_bytes_to_transmit
 */
Status fcm_spi_transmit(SPI_HandleTypeDef *spi_handle,
		uint8_t *data_to_transmit, uint8_t num_bytes_to_transmit);

/**
 * Receives data through hardware SPI peripheral
 */
Status fcm_spi_receive(SPI_HandleTypeDef *spi_handle,
		uint8_t address_to_read_from, uint8_t *received_data,
		uint8_t num_bytes_to_receive);

/**
 * Transmits data to MPU through hardware SPI peripheral
 */
Status spi_transmit_mpu(uint8_t *data_to_transmit,
		uint8_t num_bytes_to_transmit);

/**
 * Receives data from MPU through hardware SPI peripheral
 */
Status spi_receive_mpu(uint8_t address_to_read_from,
		uint8_t *received_data, uint8_t num_bytes_to_receive);

/**
 * Transmits data to M25P16 flash memory through hardware SPI peripheral
 */
Status spi_transmit_flash_memory(uint8_t *data_to_transmit,
		uint8_t num_bytes_to_transmit);

/**
 * Receives data from M25P16 flash memory through hardware SPI peripheral
 */
Status spi_receive_flash_memory(uint8_t command, uint8_t *address,
		uint8_t *received_data, uint8_t num_bytes_to_receive);

/**
 * Transmits data to RFM22 through hardware SPI peripheral
 */
Status spi_transmit_rfm22(uint8_t *dataToTransmit,
		uint8_t numberOfTransmittedData);

/**
 * Receives data from RFM22 through hardware SPI peripheral
 */
Status spi_receive_rfm22(uint8_t address_to_read_from, uint8_t *received_data,
		uint8_t num_bytes_to_receive);

#endif /* FCM_PACKAGES_HARDWARE_FCM_SPI_H_ */
