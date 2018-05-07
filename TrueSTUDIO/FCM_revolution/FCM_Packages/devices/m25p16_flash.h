/*
 *  M25P16_flash.h
 *
 *  Created on: 05.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_DEVICES_M25P16_FLASH_H_
#define FCM_PACKAGES_DEVICES_M25P16_FLASH_H_

#include "fcm_spi.h"
#include <stdlib.h>
#include <string.h>

#define M25P16_PAGE_SIZE 0xFFFF

#define M25P16_CMD_WRITE_ENABLE 0x06
#define M25P16_CMD_WRITE_DISABLE 0x04
#define M25P16_CMD_READ_IDENTIFICATION 0x9E
#define M25P16_CMD_READ_STATUS_REGISTER 0x05
#define M25P16_CMD_WRITE_STATUS_REGISTER 0x01
#define M25P16_CMD_READ_DATA_BYTES 0x03
#define M25P16_CMD_READ_DATA_BYTES_AT_HIGHER_SPEED 0x0B
#define M25P16_CMD_PAGE_PROGRAM 0x02
#define M25P16_CMD_SECTOR_ERASE 0xD8
#define M25P16_CMD_BULK_ERASE 0xC7
#define M25P16_CMD_DEEP_POWER_DOWN 0xB9
#define M25P16_CMD_RELEASE_FROM_DEEP_POWER_DOWN 0xAB

#define M25P16_STATUS_REGISTER_WIP_BIT (1<<0)
#define M25P16_STATUS_REGISTER_WEL_BIT (1<<1)

HAL_StatusTypeDef flash_memory_send_command(uint8_t command);
void flash_memory_wait_for_write_access();
HAL_StatusTypeDef flash_memory_full_erase();
HAL_StatusTypeDef flash_memory_write(uint32_t address, uint8_t *data, uint8_t num_bytes);
HAL_StatusTypeDef flash_memory_read(uint32_t address, uint8_t *buffer, uint8_t num_bytes);
HAL_StatusTypeDef flash_memory_init();


#endif /* FCM_PACKAGES_DEVICES_M25P16_FLASH_H_ */
