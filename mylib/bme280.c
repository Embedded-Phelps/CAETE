/*
 * bme280.c
 * This driver refer to the official API documents provided by Bosch. Inc
 *
 *  Created on: Apr 10, 2017
 *      Author: shuting
 */

#include "LG_system.h"

struct bme280_t *p_bme280;

void bme280_enable(struct bme280_t *bme280);
bme280_state_e bme280_init(struct bme280_t *bme280);
bme280_state_e bme280_get_calib_param(void);
bme280_state_e bme280_set_osrs_t(uint8_t value);
bme280_state_e bme280_set_osrs_p(uint8_t value);
bme280_state_e bme280_get_forced_uput(void);
bme280_state_e bme280_compute_wait_time(uint8_t *v_delaytime_u8r);
bme280_state_e bme280_read_uput(BME280_S32_t *upressure, BME280_S32_t *utemperature);
double bme280_compensate_T_double(BME280_S32_t adc_T);
double bme280_compensate_P_double(BME280_S32_t adc_P);
bme280_state_e BME280_I2CWriteByte(uint8_t address, uint8_t data);
bme280_state_e BME280_I2CRead(uint8_t address, uint8_t * reg_data, uint8_t cnt);
void bme280_RTCCallback(RTCDRV_TimerID_t id);

void bme280_enable(struct bme280_t *bme280)
{
	uint8_t i;

	// SDA/SCL pin mode configuration
	GPIO_PinModeSet(BME280_I2C_SCL_PORT, BME280_I2C_SCL_PIN, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(BME280_I2C_SDA_PORT, BME280_I2C_SDA_PIN, gpioModeWiredAnd, 1);

	// Reset the I2C bus
	for(i=0;i<9;i++)
	{
		GPIO_PinOutClear(BME280_I2C_SCL_PORT, BME280_I2C_SCL_PIN);
        GPIO_PinOutSet(BME280_I2C_SCL_PORT, BME280_I2C_SCL_PIN);
	}

	// Initialize the device
	bme280_init(bme280);
	bme280_set_osrs_t(BME280_OVERSAMPLING_1X);
	bme280_set_osrs_p(BME280_OVERSAMPLING_8X);

	bme280_get_forced_uput();
}

bme280_state_e bme280_init(struct bme280_t *bme280)
{
	bme280_state_e rc = SUCCESS;
	p_bme280 = bme280;                         /* assign BMP280 ptr */
	p_bme280->dev_addr = BME280_I2C_ADDR;   /* preset BMP280 I2C_addr */
	if (SUCCESS != BME280_I2CRead(BME280_CHIP_ID_REG, &(p_bme280->chip_id), 1)) /* read Chip Id */
	{
		rc = ERROR;
	}
	if (SUCCESS != bme280_get_calib_param())
	{
		rc = ERROR; /* readout bmp280 calibparam structure */
	}
	return rc;
}

bme280_state_e bme280_get_calib_param(void)
{
	bme280_state_e rc = SUCCESS;
	uint8_t a_data_u8r[26] = {0};
	if (p_bme280 == NULL)
	{
		rc = ERROR;
	}
	else
	{
		if(SUCCESS != BME280_I2CRead(BME280_DIG_T1_LSB_REG, a_data_u8r, 24))
		{
			rc = ERROR;
		}
		else
		{
			p_bme280->cal_param.dig_T1 = (BME280_U16_t)((((BME280_U16_t)((unsigned char)a_data_u8r[1])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[0]);
			p_bme280->cal_param.dig_T2 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[3])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[2]);
			p_bme280->cal_param.dig_T3 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[5])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[4]);
			p_bme280->cal_param.dig_P1 = (BME280_U16_t)((((BME280_U16_t)((unsigned char)a_data_u8r[7])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[6]);
			p_bme280->cal_param.dig_P2 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[9])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[8]);
			p_bme280->cal_param.dig_P3 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[11])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[10]);
			p_bme280->cal_param.dig_P4 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[13])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[12]);
			p_bme280->cal_param.dig_P5 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[15])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[14]);
			p_bme280->cal_param.dig_P6 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[17])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[16]);
			p_bme280->cal_param.dig_P7 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[19])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[18]);
			p_bme280->cal_param.dig_P8 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[21])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[20]);
			p_bme280->cal_param.dig_P9 = (BME280_S16_t)((((BME280_S16_t)((signed char)a_data_u8r[23])) << SHIFT_LEFT_8_POSITION) | a_data_u8r[22]);
		}
	}
	return rc;
}

bme280_state_e bme280_set_osrs_t(uint8_t value)
{
	bme280_state_e rc = SUCCESS;
	uint8_t v_data_u8r = 0;
	if (p_bme280 == NULL)
	{
		rc = ERROR;
	}
	else
	{
		if(SUCCESS != BME280_I2CRead(BME280_CTRLMEAS_REG_OSRST__REG, &v_data_u8r, 1))
		{
			rc = ERROR;
		}
		v_data_u8r = (v_data_u8r & ~BME280_CTRLMEAS_REG_OSRST__MSK) | ((value << BME280_CTRLMEAS_REG_OSRST__POS) & BME280_CTRLMEAS_REG_OSRST__MSK);
		if(SUCCESS != BME280_I2CWriteByte(BME280_CTRLMEAS_REG_OSRST__REG, v_data_u8r))
		{
			rc = ERROR;
		}
		else
		{
			p_bme280->osrs_t = value;
		}
	}
	return rc;
}

bme280_state_e bme280_set_osrs_p(uint8_t value)
{
	bme280_state_e rc = SUCCESS;
	uint8_t v_data_u8r = 0;
	if (p_bme280 == NULL)
	{
		rc = ERROR;
	}
	else
	{
		if(SUCCESS != BME280_I2CRead(BME280_CTRLMEAS_REG_OSRSP__REG, &v_data_u8r, 1))
		{
			rc = ERROR;
		}
		v_data_u8r = (v_data_u8r & ~BME280_CTRLMEAS_REG_OSRSP__MSK) | ((value << BME280_CTRLMEAS_REG_OSRSP__POS) & BME280_CTRLMEAS_REG_OSRSP__MSK);
		if(SUCCESS != BME280_I2CWriteByte(BME280_CTRLMEAS_REG_OSRSP__REG, v_data_u8r))
		{
			rc = ERROR;
		}
		else
		{
			p_bme280->osrs_p = value;
		}
	}
	return rc;
}

bme280_state_e bme280_get_forced_uput(void)
{
	bme280_state_e rc = SUCCESS;
	uint8_t v_data_u8r = 0;
	uint8_t v_waittime_u8r = 0;
	if (p_bme280 == NULL)
	{
		rc = ERROR;
	}
	else
	{
		v_data_u8r = (p_bme280->osrs_t << BME280_CTRLMEAS_REG_OSRST__POS) + (p_bme280->osrs_p << BME280_CTRLMEAS_REG_OSRSP__POS) + BME280_FORCED_MODE;
		if (SUCCESS != BME280_I2CWriteByte(BME280_CTRL_MEAS_REG, v_data_u8r))
		{
			rc = ERROR;
		}
		else
		{
			bme280_compute_wait_time(&v_waittime_u8r);
			RTCDRV_StartTimer(rtc_ID, rtcdrvTimerTypeOneshot, v_waittime_u8r, bme280_RTCCallback, NULL);
		}
	}
	return rc;
}

bme280_state_e bme280_compute_wait_time(uint8_t *v_delaytime_u8r) ///???????
{
	bme280_state_e rc = SUCCESS;

	*v_delaytime_u8r = (T_INIT_MAX + T_MEASURE_PER_OSRS_MAX * \
		(((1 << p_bme280->osrs_t) >> 1) + ((1 << p_bme280->osrs_p) >> 1)) \
		+ (p_bme280->osrs_p ? T_SETUP_PRESSURE_MAX : 0) + 15) / 16;
	return rc;
}

bme280_state_e bme280_read_uput(BME280_S32_t *upressure, BME280_S32_t *utemperature)
{
	bme280_state_e rc = SUCCESS;
	uint8_t a_data_u8r[6] = {0};
	if (p_bme280 == NULL)
	{
		rc = ERROR;
	}
	else
	{
		if(SUCCESS != BME280_I2CRead(BME280_PRESSURE_MSB_REG, a_data_u8r, 6))
		{
			rc = ERROR;
		}
		else
		{
			/* Pressure */
			*upressure = (BME280_S32_t)((((BME280_U32_t)(a_data_u8r[0])) << SHIFT_LEFT_12_POSITION) | \
					 	 (((BME280_U32_t)(a_data_u8r[1])) << SHIFT_LEFT_4_POSITION) | \
						 ((BME280_U32_t)a_data_u8r[2] >>SHIFT_RIGHT_4_POSITION));

			/* Temperature */
			*utemperature = (BME280_S32_t)((((BME280_U32_t) (a_data_u8r[3])) << SHIFT_LEFT_12_POSITION) | \
							(((BME280_U32_t)(a_data_u8r[4])) << SHIFT_LEFT_4_POSITION) | \
							((BME280_U32_t)a_data_u8r[5] >> SHIFT_RIGHT_4_POSITION));
		}
	}
	return rc;
}

double bme280_compensate_T_double(BME280_S32_t adc_T)
{
	double v_x1_u32r = 0;
	double v_x2_u32r = 0;
	double temperature = 0;

	v_x1_u32r  = (((double)adc_T) / 16384.0 - \
		((double)p_bme280->cal_param.dig_T1) / 1024.0) * \
		((double)p_bme280->cal_param.dig_T2);
	v_x2_u32r  = ((((double)adc_T) / 131072.0 - \
		((double)p_bme280->cal_param.dig_T1) / 8192.0) * \
		(((double)adc_T) / 131072.0 - \
		((double)p_bme280->cal_param.dig_T1) / 8192.0)) * \
		((double)p_bme280->cal_param.dig_T3);
	p_bme280->cal_param.t_fine = (BME280_S32_t)(v_x1_u32r + v_x2_u32r);
	temperature  = (v_x1_u32r + v_x2_u32r) / 5120.0;
	return temperature;
}

double bme280_compensate_P_double(BME280_S32_t adc_P)
{
	double v_x1_u32r = 0;
	double v_x2_u32r = 0;
	double pressure = 0;

	v_x1_u32r = ((double)p_bme280->cal_param.t_fine/2.0) - 64000.0;
	v_x2_u32r = v_x1_u32r * v_x1_u32r * ((double)p_bme280->cal_param.dig_P6) / 32768.0;
	v_x2_u32r = v_x2_u32r + v_x1_u32r * ((double)p_bme280->cal_param.dig_P5) * 2.0;
	v_x2_u32r = (v_x2_u32r / 4.0) + (((double)p_bme280->cal_param.dig_P4) * 65536.0);
	v_x1_u32r = (((double)p_bme280->cal_param.dig_P3) * v_x1_u32r * v_x1_u32r / 524288.0 + ((double)p_bme280->cal_param.dig_P2) * v_x1_u32r) / 524288.0;
	v_x1_u32r = (1.0 + v_x1_u32r / 32768.0) * ((double)p_bme280->cal_param.dig_P1);

	if (v_x1_u32r == 0.0)
	{
		return 0; /* Avoid exception caused by division by zero */
	}
	pressure = 1048576.0 - (double)adc_P;
	pressure = (pressure - (v_x2_u32r / 4096.0)) * 6250.0 / v_x1_u32r;
	v_x1_u32r = ((double)p_bme280->cal_param.dig_P9) * pressure * pressure / 2147483648.0;
	v_x2_u32r = pressure * ((double)p_bme280->cal_param.dig_P8) / 32768.0;
	pressure = pressure + (v_x1_u32r + v_x2_u32r + ((double)p_bme280->cal_param.dig_P7)) / 16.0;

	return pressure;
}

bme280_state_e BME280_I2CWriteByte(uint8_t address, uint8_t data)
{
	bme280_state_e rc = SUCCESS;
	BME280_I2C->TXDATA = BME280_I2C_ADDR << 1 | I2C_WRITE;
	BME280_I2C->CMD = I2C_CMD_START;

	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;

	BME280_I2C->TXDATA = address;
	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;

	BME280_I2C->TXDATA = data;
	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;

	BME280_I2C->CMD = I2C_CMD_STOP;
	return rc;
}

bme280_state_e BME280_I2CRead(uint8_t address, uint8_t * reg_data, uint8_t cnt)
{
	bme280_state_e rc = SUCCESS;
	uint8_t i;

	BME280_I2C->TXDATA = BME280_I2C_ADDR << 1 | I2C_WRITE;
	BME280_I2C->CMD = I2C_CMD_START;

	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;

	BME280_I2C->TXDATA = address;
	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;

	BME280_I2C->CMD = I2C_CMD_START;
	BME280_I2C->TXDATA = BME280_I2C_ADDR << 1 | I2C_READ;
	while((BME280_I2C->IF & I2C_IF_ACK) == 0);
	BME280_I2C->IFC = I2C_IFC_ACK;
	for (i = 0; i < cnt; i++)
	{
		while(!(BME280_I2C->STATUS & I2C_STATUS_RXDATAV));
		reg_data[i] = BME280_I2C->RXDATA;
		if (i != cnt-1)
		{
			BME280_I2C->CMD = I2C_CMD_ACK;
		}
	}
	BME280_I2C->CMD = I2C_CMD_NACK;
	BME280_I2C->CMD = I2C_CMD_STOP;
	return rc;
}

void bme280_RTCCallback(RTCDRV_TimerID_t id)
{
	BME280_S32_t upressure, utemperature;
	double cal_upressure, cal_utemperature;

	bme280_read_uput(&upressure, &utemperature);
	cal_utemperature = bme280_compensate_T_double(utemperature);
	cal_upressure = bme280_compensate_P_double(upressure);
	BME280_PowerOff();
	//send out value.
	if(data_upload_flag == DATA_UPLOAD_ENABLED)
	{
		serial_SendPacket(TEMPERATURE, &cal_utemperature);
		serial_SendPacket(BAROMETRIC_PRESSURE, &cal_upressure);
	}
}
