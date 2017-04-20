/*
 * LG_lesense.h
 *
 *  Created on: Apr 19, 2017
 *      Author: shuting
 */

#ifndef INC_LG_LESENSE_H_
#define INC_LG_LESENSE_H_

#define	LIGHTNESS	(true)
#define DARKNESS	(false)

/* Upper voltage threshold. */
#define LESENSE_ACMP_VDD_SCALE    		(0x37U)
/* Upper voltage threshold */
#define CAPLESENSE_ACMP_VDD_SCALE      	(LESENSE_ACMP_VDD_SCALE)
#define CAPLESENSE_SENSITIVITY_OFFS    	(1U)

#define LESENSE_CHANNELS        		(16U)

#define AMBIENT_LIGHT_CHANNEL			(6U)
#define SLIDER_PART0_CHANNEL    		(8U)   /**< Touch slider channel Part 0 */
#define SLIDER_PART1_CHANNEL    		(9U)   /**< Touch slider channel Part 1 */
#define SLIDER_PART2_CHANNEL    		(10U)  /**< Touch slider channel Part 2 */
#define SLIDER_PART3_CHANNEL    		(11U)  /**< Touch slider channel Part 3 */

#define LESENSE_CHANNEL_INT        			(LESENSE_IF_CH6 | LESENSE_IF_CH8 | LESENSE_IF_CH9 | LESENSE_IF_CH10 | LESENSE_IF_CH11)
#define LESENSE_CHANNEL_INT_AMBIENT_LIGHT	(LESENSE_IF_CH6)
#define LESENSE_CHANNEL_INT_SLIDER			(LESENSE_CHANNEL_INT_SLIDER0 | LESENSE_CHANNEL_INT_SLIDER1 | LESENSE_CHANNEL_INT_SLIDER2 | LESENSE_CHANNEL_INT_SLIDER3)
#define LESENSE_CHANNEL_INT_SLIDER0			(LESENSE_IF_CH8)
#define LESENSE_CHANNEL_INT_SLIDER1			(LESENSE_IF_CH9)
#define LESENSE_CHANNEL_INT_SLIDER2			(LESENSE_IF_CH10)
#define LESENSE_CHANNEL_INT_SLIDER3			(LESENSE_IF_CH11)


#define LESENSE_CAPSENSE_CH_IN_USE {							\
/*  Ch0,   Ch1,   Ch2,   Ch3,   Ch4,   Ch5,   Ch6,   Ch7    */	\
  false, false, false, false, false, false, true, false,		\
/*  Ch8,   Ch9,   Ch10,  Ch11,  Ch12,  Ch13,  Ch14,  Ch15   */	\
  true,  true,  true,  true,  false, false, false, false		\
}

/* Configuration for capacitive sense channels. */
#define LESENSE_LIGHTSENSE_SENSOR_CH_CONF                     \
{                                                  \
	true,                      /* Enable scan channel. */    \
	false,                     /* Enable the assigned pin on scan channel. */ \
	true,                      /* Enable interrupts on channel. */ \
	lesenseChPinExHigh,        /* GPIO pin is high during the excitation period. */    \
	lesenseChPinIdleDis,       /* GPIO pin is low during the idle period. */ \
	true,                      /* Use alternate excitation pins for excitation. */    \
	false,                     /* Disabled to shift results from this channel to the decoder register. */ \
	false,                     /* Disabled to invert the scan result bit. */  \
	true,                      /* Enabled to store counter value in the result buffer. */   \
	lesenseClkLF,              /* Use the LF clock for excitation timing. */    \
	lesenseClkLF,              /* Use the LF clock for sample timing. */ \
	0x01U,                     /* Excitation time is set to 1(+1) excitation clock cycles. */    \
	0x01U,                     /* Sample delay is set to 1(+1) sample clock cycles. */ \
	0x00U,                     /* Measure delay is set to 0 excitation clock cycles.*/    \
	0x38U,                     /* ACMP threshold has been set to 0x38. */ \
	lesenseSampleModeACMP,     /* ACMP will be used in comparison. */    \
	lesenseSetIntNegEdge,      /* Interrupt is generated if the sensor triggers. */ \
	0x0000U,                   /* Counter threshold has been set to 0x00. */    \
	lesenseCompModeLess        /* Compare mode has been set to trigger interrupt on "less". */ \
}

/** Configuration for capacitive sense channels in sense mode. */
#define LESENSE_CAPSENSE_CH_CONF_SENSE                                                                   \
{                                                                                                      \
    true,                     /* Enable scan channel. */                                                 \
    true,                     /* Enable the assigned pin on scan channel. */                             \
    false,                    /* Disable interrupts on channel. */                                       \
    lesenseChPinExDis,        /* GPIO pin is disabled during the excitation period. */                   \
    lesenseChPinIdleDis,      /* GPIO pin is disabled during the idle period. */                         \
    false,                    /* Don't use alternate excitation pins for excitation. */                  \
    false,                    /* Disabled to shift results from this channel to the decoder register. */ \
    false,                    /* Disabled to invert the scan result bit. */                              \
    true,                     /* Enabled to store counter value in the result buffer. */                 \
    lesenseClkLF,             /* Use the LF clock for excitation timing. */                              \
    lesenseClkLF,             /* Use the LF clock for sample timing. */                                  \
    0x00U,                    /* Excitation time is set to 0 excitation clock cycles. */                 \
    0x0FU,                    /* Sample delay is set to 15(+1) sample clock cycles. */                   \
    0x00U,                    /* Measure delay is set to 0 excitation clock cycles.*/                    \
    LESENSE_ACMP_VDD_SCALE,   /* ACMP threshold has been set to LESENSE_ACMP_VDD_SCALE. */               \
    lesenseSampleModeCounter, /* ACMP will be used in comparison. */                                     \
    lesenseSetIntLevel,       /* Interrupt is generated if the sensor triggers. */                       \
    0x00U,                    /* Counter threshold has been set to 0x00. */                              \
    lesenseCompModeLess       /* Compare mode has been set to trigger interrupt on "less". */            \
}

#define LESENSE_CAPSENSE_CH_CONF_SLEEP                                                                   \
{                                                                                                      \
    true,                     /* Enable scan channel. */                                                 \
    true,                     /* Enable the assigned pin on scan channel. */                             \
    true,                     /* Enable interrupts on channel. */                                        \
    lesenseChPinExDis,        /* GPIO pin is disabled during the excitation period. */                   \
    lesenseChPinIdleDis,      /* GPIO pin is disabled during the idle period. */                         \
    false,                    /* Don't use alternate excitation pins for excitation. */                  \
    false,                    /* Disabled to shift results from this channel to the decoder register. */ \
    false,                    /* Disabled to invert the scan result bit. */                              \
    true,                     /* Enabled to store counter value in the result buffer. */                 \
    lesenseClkLF,             /* Use the LF clock for excitation timing. */                              \
    lesenseClkLF,             /* Use the LF clock for sample timing. */                                  \
    0x00U,                    /* Excitation time is set to 0 excitation clock cycles. */                 \
    0x01U,                    /* Sample delay is set to 1(+1) sample clock cycles. */                    \
    0x00U,                    /* Measure delay is set to 0 excitation clock cycles.*/                    \
    LESENSE_ACMP_VDD_SCALE,   /* ACMP threshold has been set to LESENSE_ACMP_VDD_SCALE. */               \
    lesenseSampleModeCounter, /* Counter will be used in comparison. */                                  \
    lesenseSetIntLevel,       /* Interrupt is generated if the sensor triggers. */                       \
    0x0EU,                    /* Counter threshold has been set to 0x0E. */                              \
    lesenseCompModeLess       /* Compare mode has been set to trigger interrupt on "less". */            \
}

#define LESENSE_DISABLED_CH_CONF                     \
{                                                  \
	false,                     /* Disable scan channel. */    \
	false,                     /* Disable the assigned pin on scan channel. */ \
	false,                     /* Disable interrupts on channel. */ \
	lesenseChPinExDis,         /* GPIO pin is disabled during the excitation period. */    \
	lesenseChPinIdleDis,       /* GPIO pin is disabled during the idle period. */ \
	false,                     /* Don't use alternate excitation pins for excitation. */    \
	false,                     /* Disabled to shift results from this channel to the decoder register. */ \
	false,                     /* Disabled to invert the scan result bit. */  \
	false,                     /* Disabled to store counter value in the result buffer. */   \
	lesenseClkLF,              /* Use the LF clock for excitation timing. */    \
	lesenseClkLF,              /* Use the LF clock for sample timing. */ \
	0x00U,                     /* Excitation time is set to 5(+1) excitation clock cycles. */    \
	0x00U,                     /* Sample delay is set to 7(+1) sample clock cycles. */ \
	0x00U,                     /* Measure delay is set to 0 excitation clock cycles.*/    \
	0x00U,                     /* ACMP threshold has been set to 0. */ \
	lesenseSampleModeCounter,  /* ACMP output will be used in comparison. */    \
	lesenseSetIntNone,         /* No interrupt is generated by the channel. */ \
	0x00U,                     /* Counter threshold has been set to 0x01. */    \
	lesenseCompModeLess        /* Compare mode has been set to trigger interrupt on "less". */ \
}

#define LESENSE_SCAN_CONF_WITH_CAPSENSE_SENSE                 				  \
{                                                     				  \
    {                                                    			  \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 0. */  \
		LESENSE_DISABLED_CH_CONF,       			/* Channel 1. */  \
		LESENSE_DISABLED_CH_CONF,       			/* Channel 2. */  \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 3. */  \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 4. */  \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 5. */  \
		LESENSE_LIGHTSENSE_SENSOR_CH_CONF,        	/* Channel 6. */  \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 7. */  \
		LESENSE_CAPSENSE_CH_CONF_SENSE, 			/* Channel 8. */  \
		LESENSE_CAPSENSE_CH_CONF_SENSE,  			/* Channel 9. */  \
		LESENSE_CAPSENSE_CH_CONF_SENSE,  			/* Channel 10. */ \
		LESENSE_CAPSENSE_CH_CONF_SENSE,  			/* Channel 11. */ \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 12. */ \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 13. */ \
		LESENSE_DISABLED_CH_CONF,        			/* Channel 14. */ \
		LESENSE_DISABLED_CH_CONF         			/* Channel 15. */ \
	}                                                    \
}

/** Configuration for scan in sleep mode. */
#define LESENSE_SCAN_CONF_WITH_CAPSENSE_SLEEP                \
{                                                     \
    {                                                    \
		LESENSE_DISABLED_CH_CONF,        /* Channel 0. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 1. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 2. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 3. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 4. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 5. */  \
		LESENSE_LIGHTSENSE_SENSOR_CH_CONF,        /* Channel 6. */  \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 7. */  \
	    LESENSE_CAPSENSE_CH_CONF_SLEEP,  /* Channel 8. */  \
	    LESENSE_CAPSENSE_CH_CONF_SLEEP,  /* Channel 9. */  \
	    LESENSE_CAPSENSE_CH_CONF_SLEEP,  /* Channel 10. */ \
	    LESENSE_CAPSENSE_CH_CONF_SLEEP,  /* Channel 11. */ \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 12. */ \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 13. */ \
	    LESENSE_DISABLED_CH_CONF,        /* Channel 14. */ \
	    LESENSE_DISABLED_CH_CONF         /* Channel 15. */ \
	}                                                    \
}

/* Default configuration for alternate excitation channel. */
#define LESENSE_LIGHTSENSE_ALTEX_CH_CONF                                       \
{                                                                              \
    true,                   /* Alternate excitation enabled.*/                  \
    lesenseAltExPinIdleDis, /* Alternate excitation pin is low in idle. */ \
    true                    /* Excite only for corresponding channel. */        \
}

/* Default configuration for alternate excitation channel. */
#define LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF                                   \
{                                                                              \
    false,                   /* Alternate excitation enabled.*/                  \
    lesenseAltExPinIdleDis,  /* Alternate excitation pin is disabled in idle. */ \
    false                    /* Excite only for corresponding channel. */        \
}

/* Default configuration for all alternate excitation channels. */
#define LESENSE_LIGHTSENSE_ALTEX_CONF                                          \
{                                                                              \
    lesenseAltExMapALTEX,                                                         \
    {                                                                            \
    	LESENSE_LIGHTSENSE_ALTEX_CH_CONF,     /* Alternate excitation channel 0. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 1. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 2. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 3. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 4. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 5. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF, /* Alternate excitation channel 6. */\
        LESENSE_LIGHTSENSE_ALTEX_DIS_CH_CONF  /* Alternate excitation channel 7. */\
    }                                                                            \
}

void lesense_Setup(bool sleep);
void lesense_SetupCallbacks(void (*scanCb)(void), void (*chCb)(uint32_t flag));
int32_t lesense_GetSliderPosition(void);
#endif /* INC_LG_LESENSE_H_ */
