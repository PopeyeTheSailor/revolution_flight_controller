/*
 * hmc5883.h
 *
 *  Created on: 04.05.2018
 *      Author: Bartek Kurosz
 */

#ifndef FCM_PACKAGES_DEVICES_HMC5883_H_
#define FCM_PACKAGES_DEVICES_HMC5883_H_

#include "vector.h"
#include "fcm_i2c.h"

#define HMC5883L_ADDRESS 0x3D
#define HMC5883L_CONFIGURATION_REGISTER_A 0x00
#define HMC5883L_CONFIGURATION_REGISTER_B 0x01
#define HMC5883L_MODE_REGISTER 0x02
#define HMC5883L_DATA_OUTPUT_X_MSB_REGISTER 0x03

#define MAGNETOMETER_RESOLUTION 1090.0

/**
 *
 */
Status hmc_5883l_init();

/**
 *
 */
Status hmc_5883l_read_raw_data();
#endif /* FCM_PACKAGES_DEVICES_HMC5883_H_ */
