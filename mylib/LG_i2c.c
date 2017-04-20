/*
 * LG_i2c.c
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#include "LG_system.h"

void i2c_Setup(void)
{
	// I2C control registers initialization
	const I2C_Init_TypeDef i2c_Config =
	{
		.enable			= false,
		.master 		= true,
		.refFreq		= 0,
		.freq			= I2C_FREQ_STANDARD_MAX,
		.clhr			= i2cClockHLRStandard
	};

	I2C_Init(BME280_I2C, &i2c_Config);
	// Routing SDA/SCL to desired IO location
	BME280_I2C->ROUTE |= BME280_I2C_IO_LOCATION << _I2C_ROUTE_LOCATION_SHIFT;
	BME280_I2C->ROUTE |= I2C_ROUTE_SCLPEN | I2C_ROUTE_SDAPEN;
	// Reset I2C
	if(BME280_I2C->STATE & I2C_STATE_BUSY)
	{
		BME280_I2C->CMD = I2C_CMD_ABORT;
	}

	I2C_Enable(BME280_I2C, true);

	GPIO_PinModeSet(BME280_POWER_PORT, BME280_POWER_PIN, gpioModePushPull, 0);
}

