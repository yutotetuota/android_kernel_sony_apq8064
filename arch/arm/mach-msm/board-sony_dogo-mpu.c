/* arch/arm/mach-msm/board-sony_dogo-mpu.c
 *
 * Copyright (C) 2011 Sony Ericsson Mobile Communications AB.
 * Copyright (C) 2012-2013 Sony Mobile Communications AB.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <mach/board.h>
#include <mach/irqs.h>
#include "devices.h"
#include "devices-msm8x60.h"
#ifdef CONFIG_SENSORS_MPU3050
#include <linux/mpu.h>
#endif
#ifdef CONFIG_INV_MPU_IIO
#include <linux/iio_mpu.h>
#endif
#include "gyro-semc_common.h"

#define GYRO_ORIENTATION {  0,  1,  0,  1,  0,  0,  0,  0, -1 }
#define ACCEL_ORIENTATION { -1,  0,  0,  0,  1,  0,  0,  0, -1 }
#define COMPASS_ORIENTATION {  0,  0,  1,  0,  1,  0, -1,  0,  0 }
#define PRESSURE_ORIENTATION {  1,  0,  0,  0,  1,  0,  0,  0,  1 }

#ifdef CONFIG_SENSORS_MPU3050

struct mpu3050_platform_data mpu_data = {
	.int_config  = BIT_INT_ANYRD_2CLEAR,
	.orientation = GYRO_ORIENTATION,
	.accel = {
		 .get_slave_descr = get_accel_slave_descr,
		 .adapt_num   = 2,
		 .bus         = EXT_SLAVE_BUS_SECONDARY,
		 .address     = (0x30 >> 1),
		 .orientation = ACCEL_ORIENTATION,
		 .bypass_state = mpu3050_bypassmode,
		 .check_sleep_status = check_bma250_sleep_state,
		 .vote_sleep_status = vote_bma250_sleep_state,
	 },
	.compass = {
		 .get_slave_descr = get_compass_slave_descr,
		 .adapt_num   = 2,
		 .bus         = EXT_SLAVE_BUS_PRIMARY,
		 .address     = (0x18 >> 1),
		 .orientation = COMPASS_ORIENTATION,
	 },
	.pressure = {
		 .get_slave_descr = NULL,
		 .adapt_num   = 0,
		 .bus         = EXT_SLAVE_BUS_INVALID,
		 .address     = 0,
		 .orientation = PRESSURE_ORIENTATION,
	 },
	.setup   = mpu3050_gpio_setup,
	.hw_config  = mpu3050_power_mode,
};
#endif

#ifdef CONFIG_INV_MPU_IIO
struct mpu_platform_data mpu_data = {
	.int_config  = 0x10,
	.level_shifter = 0,
	.orientation = GYRO_ORIENTATION,
	.sec_slave_type = SECONDARY_SLAVE_TYPE_ACCEL,
	.sec_slave_id   = ACCEL_ID_BMA250,
	.secondary_i2c_addr = 0x18,
	.secondary_orientation = ACCEL_ORIENTATION,
	.power_supply = mpu_power_supply,
	.secondary_power_supply = acc_power_supply,
	.gpio = 28,
};

struct mpu_platform_data compass_data = {
	.orientation = COMPASS_ORIENTATION,
	.power_supply = compass_power_supply,
};
#endif
