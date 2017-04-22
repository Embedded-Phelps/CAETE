################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include mylib/subdir.mk
-include emlib/subdir.mk
-include emdrv/src/subdir.mk
-include CMSIS/EFM32LG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CAETE.axf

# Tool invocations
CAETE.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "CAETE.ld" -Xlinker --gc-sections -Xlinker -Map="CAETE.map" --specs=nano.specs -o CAETE.axf "./CMSIS/EFM32LG/startup_gcc_efm32lg.o" "./CMSIS/EFM32LG/system_efm32lg.o" "./emdrv/src/rtcdriver.o" "./emlib/em_acmp.o" "./emlib/em_adc.o" "./emlib/em_aes.o" "./emlib/em_assert.o" "./emlib/em_burtc.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_cryotimer.o" "./emlib/em_crypto.o" "./emlib/em_dac.o" "./emlib/em_dbg.o" "./emlib/em_dma.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpcrc.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_idac.o" "./emlib/em_int.o" "./emlib/em_lcd.o" "./emlib/em_ldma.o" "./emlib/em_lesense.o" "./emlib/em_letimer.o" "./emlib/em_leuart.o" "./emlib/em_mpu.o" "./emlib/em_msc.o" "./emlib/em_opamp.o" "./emlib/em_pcnt.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtc.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_vcmp.o" "./emlib/em_wdog.o" "./mylib/LG_acmp.o" "./mylib/LG_cmu.o" "./mylib/LG_i2c.o" "./mylib/LG_lesense.o" "./mylib/LG_letimer.o" "./mylib/LG_leuart.o" "./mylib/LG_sleep.o" "./mylib/bme280.o" "./mylib/board_led.o" "./mylib/pir.o" "./mylib/serial_BLE.o" "./src/LG_task.o" "./src/dmactrl.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: CAETE.hex'
	arm-none-eabi-objcopy -O ihex "CAETE.axf" "CAETE.hex"
	@echo ' '

	@echo 'Building bin file: CAETE.bin'
	arm-none-eabi-objcopy -O binary "CAETE.axf" "CAETE.bin"
	@echo ' '

	@echo 'Building s37 file: CAETE.s37'
	arm-none-eabi-objcopy -O srec "CAETE.axf" "CAETE.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "CAETE.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) CAETE.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
