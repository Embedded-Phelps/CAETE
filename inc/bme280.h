/*
 * bme280.h
 *
 *  Created on: Apr 10, 2017
 *      Author: shuting
 */

#ifndef INC_BME280_H_
#define INC_BME280_H_

#include <limits.h>

/* Find correct data type for signed/unsigned 16 bit variables by
	checking max of unsigned variant */
#if USHRT_MAX == 0xFFFF
		/* 16 bit achieved with short */
		#define BME280_U16_t unsigned short
		#define BME280_S16_t signed short
#elif UINT_MAX == 0xFFFF
		/* 16 bit achieved with int */
		#define BME280_U16_t unsigned int
		#define BME280_S16_t signed int
#else
		#error BME280_U16_t and BME280_S16_t could not be defined automatically, please do so manually
#endif

/* Find correct data type for 32 bit variables */
#if INT_MAX == 0x7FFFFFFF
		/* 32 bit achieved with int */
		#define BME280_U32_t unsigned int
		#define BME280_S32_t signed int
#elif LONG_MAX == 0x7FFFFFFF
		/* 32 bit achieved with long int */
		#define BME280_U32_t unsigned long int
		#define BME280_S32_t signed long int
#else
		#error BME280_S32_t and BME280_U32_t could not be defined automatically, please do so manually
#endif

/* Find correct data type for 64 bit variables */
#if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
	#define BME280_S64_t long int
	#define BME280_64BITSUPPORT_PRESENT
#elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
	#define BME280_S64_t long long int
	#define BME280_64BITSUPPORT_PRESENT
#else
	#warning Either the correct data type for signed 64 bit \
		integer could not be found, or 64 bit integers are \
		not supported in your environment.
	#warning The API will only offer 32 bit pressure calculation. \
		This will slightly impede accuracy(noise of ~1 Pa RMS \
		will be added to output).
	#warning If 64 bit integers are supported on your platform, \
		please set BME280_S64_t manually and
		#define BME280_64BITSUPPORT_PRESENT manually.
#endif

#define SHIFT_RIGHT_4_POSITION				 4
#define SHIFT_LEFT_2_POSITION                2
#define SHIFT_LEFT_4_POSITION                4
#define SHIFT_LEFT_5_POSITION                5
#define SHIFT_LEFT_8_POSITION                8
#define SHIFT_LEFT_12_POSITION               12
#define SHIFT_LEFT_16_POSITION               16

#define BME280_I2C_ADDR0		(0x76)
#define BME280_I2C_ADDR1		(0X77)
#define BME280_I2C_ADDR			(BME280_I2C_ADDR0)

#define BME280_POWER_PORT		(gpioPortD)
#define BME280_POWER_PIN		(0U)

#define BME280_I2C				(I2C1)
#define BME280_I2C_IO_LOCATION	(0)
#define BME280_I2C_SDA_PORT		(I2C1_SDA_PORT)
#define BME280_I2C_SDA_PIN		(I2C1_SDA_PIN)
#define BME280_I2C_SCL_PORT		(I2C1_SCL_PORT)
#define BME280_I2C_SCL_PIN		(I2C1_SCL_PIN)

#define BME280_SLEEP_MODE                    0x00
#define BME280_FORCED_MODE                   0x01
#define BME280_NORMAL_MODE                   0x03

#define BME280_OVERSAMPLING_SKIPPED          0x00
#define BME280_OVERSAMPLING_1X               0x01
#define BME280_OVERSAMPLING_2X               0x02
#define BME280_OVERSAMPLING_4X               0x03
#define BME280_OVERSAMPLING_8X               0x04
#define BME280_OVERSAMPLING_16X              0x05

#define T_INIT_MAX							20
				/* 20/16 = 1.25 ms */
#define T_MEASURE_PER_OSRS_MAX				37
				/* 37/16 = 2.3125 ms*/
#define T_SETUP_PRESSURE_MAX				10
				/* 10/16 = 0.625 ms */


#define BME280_DIG_T1_LSB_REG                (0x88)
#define BME280_DIG_T1_MSB_REG                (0x89)
#define BME280_DIG_T2_LSB_REG                (0x8A)
#define BME280_DIG_T2_MSB_REG                (0x8B)
#define BME280_DIG_T3_LSB_REG                (0x8C)
#define BME280_DIG_T3_MSB_REG                (0x8D)
#define BME280_DIG_P1_LSB_REG                (0x8E)
#define BME280_DIG_P1_MSB_REG                (0x8F)
#define BME280_DIG_P2_LSB_REG                (0x90)
#define BME280_DIG_P2_MSB_REG                (0x91)
#define BME280_DIG_P3_LSB_REG                (0x92)
#define BME280_DIG_P3_MSB_REG              	 (0x93)
#define BME280_DIG_P4_LSB_REG                (0x94)
#define BME280_DIG_P4_MSB_REG                (0x95)
#define BME280_DIG_P5_LSB_REG                (0x96)
#define BME280_DIG_P5_MSB_REG                (0x97)
#define BME280_DIG_P6_LSB_REG                (0x98)
#define BME280_DIG_P6_MSB_REG                (0x99)
#define BME280_DIG_P7_LSB_REG                (0x9A)
#define BME280_DIG_P7_MSB_REG                (0x9B)
#define BME280_DIG_P8_LSB_REG                (0x9C)
#define BME280_DIG_P8_MSB_REG                (0x9D)
#define BME280_DIG_P9_LSB_REG                (0x9E)
#define BME280_DIG_P9_MSB_REG                (0x9F)

#define BME280_CHIP_ID_REG                   (0xD0)  /* Chip ID Register */
#define BME280_RST_REG                       (0xE0)  /* Softreset Register */
#define BME280_STATUS_REG                    (0xF3)  /* Status Register */
#define BME280_CTRL_MEAS_REG                 (0xF4)  /* Ctrl Measure Register */
#define BME280_CONFIG_REG                    (0xF5)  /* Configuration Register */
#define BME280_PRESSURE_MSB_REG              (0xF7)  /* Pressure MSB Register */
#define BME280_PRESSURE_LSB_REG              (0xF8)  /* Pressure LSB Register */
#define BME280_PRESSURE_XLSB_REG             (0xF9)  /* Pressure XLSB Register */
#define BME280_TEMPERATURE_MSB_REG           (0xFA)  /* Temperature MSB Reg */
#define BME280_TEMPERATURE_LSB_REG           (0xFB)  /* Temperature LSB Reg */
#define BME280_TEMPERATURE_XLSB_REG          (0xFC)  /* Temperature XLSB Reg */

/* Status Register */
#define BME280_STATUS_REG_MEASURING__POS           3
#define BME280_STATUS_REG_MEASURING__MSK           0x08
#define BME280_STATUS_REG_MEASURING__LEN           1
#define BME280_STATUS_REG_MEASURING__REG           BME280_STATUS_REG

#define BME280_STATUS_REG_IMUPDATE__POS            0
#define BME280_STATUS_REG_IMUPDATE__MSK            0x01
#define BME280_STATUS_REG_IMUPDATE__LEN            1
#define BME280_STATUS_REG_IMUPDATE__REG            BME280_STATUS_REG

/* Control Measurement Register */
#define BME280_CTRLMEAS_REG_OSRST__POS             5
#define BME280_CTRLMEAS_REG_OSRST__MSK             0xE0
#define BME280_CTRLMEAS_REG_OSRST__LEN             3
#define BME280_CTRLMEAS_REG_OSRST__REG             BME280_CTRL_MEAS_REG

#define BME280_CTRLMEAS_REG_OSRSP__POS             2
#define BME280_CTRLMEAS_REG_OSRSP__MSK             0x1C
#define BME280_CTRLMEAS_REG_OSRSP__LEN             3
#define BME280_CTRLMEAS_REG_OSRSP__REG             BME280_CTRL_MEAS_REG

#define BME280_CTRLMEAS_REG_MODE__POS              0
#define BME280_CTRLMEAS_REG_MODE__MSK              0x03
#define BME280_CTRLMEAS_REG_MODE__LEN              2
#define BME280_CTRLMEAS_REG_MODE__REG              BME280_CTRL_MEAS_REG

/* Configuration Register */
#define BME280_CONFIG_REG_TSB__POS                 5
#define BME280_CONFIG_REG_TSB__MSK                 0xE0
#define BME280_CONFIG_REG_TSB__LEN                 3
#define BME280_CONFIG_REG_TSB__REG                 BME280_CONFIG_REG

#define BME280_CONFIG_REG_FILTER__POS              2
#define BME280_CONFIG_REG_FILTER__MSK              0x1C
#define BME280_CONFIG_REG_FILTER__LEN              3
#define BME280_CONFIG_REG_FILTER__REG              BME280_CONFIG_REG

#define BME280_CONFIG_REG_SPI3WEN__POS             0
#define BME280_CONFIG_REG_SPI3WEN__MSK             0x01
#define BME280_CONFIG_REG_SPI3WEN__LEN             1
#define BME280_CONFIG_REG_SPI3WEN__REG             BME280_CONFIG_REG

/* Data Register */
#define BME280_PRESSURE_XLSB_REG_DATA__POS         4
#define BME280_PRESSURE_XLSB_REG_DATA__MSK         0xF0
#define BME280_PRESSURE_XLSB_REG_DATA__LEN         4
#define BME280_PRESSURE_XLSB_REG_DATA__REG         BME280_PRESSURE_XLSB_REG

#define BME280_TEMPERATURE_XLSB_REG_DATA__POS      4
#define BME280_TEMPERATURE_XLSB_REG_DATA__MSK      0xF0
#define BME280_TEMPERATURE_XLSB_REG_DATA__LEN      4
#define BME280_TEMPERATURE_XLSB_REG_DATA__REG      BME280_TEMPERATURE_XLSB_REG

#define BME280_PowerOn()   	(GPIO_PinOutSet(BME280_POWER_PORT, BME280_POWER_PIN))
#define BME280_PowerOff()	(GPIO_PinOutClear(BME280_POWER_PORT, BME280_POWER_PIN))

/** this structure holds all device specific calibration parameters */
struct bme280_calibration_param_t{
	BME280_U16_t dig_T1;
	BME280_S16_t dig_T2;
	BME280_S16_t dig_T3;
	BME280_U16_t dig_P1;
	BME280_S16_t dig_P2;
	BME280_S16_t dig_P3;
	BME280_S16_t dig_P4;
	BME280_S16_t dig_P5;
	BME280_S16_t dig_P6;
	BME280_S16_t dig_P7;
	BME280_S16_t dig_P8;
	BME280_S16_t dig_P9;

	BME280_S32_t t_fine;
};
/** BME280 image registers data structure */
struct bme280_t
{
	struct bme280_calibration_param_t cal_param;

	uint8_t chip_id;
	uint8_t dev_addr;

	uint8_t osrs_t;
	uint8_t osrs_p;
};

typedef enum bme280_state
{
	ERROR = -1,
	SUCCESS = 0
}bme280_state_e;

void bme280_enable(struct bme280_t *bme280);
bme280_state_e bme280_get_forced_uput(void);
double bme280_compensate_T_double(BME280_S32_t adc_T);
double bme280_compensate_P_double(BME280_S32_t adc_P);
#endif /* INC_BME280_H_ */
