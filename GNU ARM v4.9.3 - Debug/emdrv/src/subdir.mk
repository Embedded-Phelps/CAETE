################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../emdrv/src/rtcdriver.c 

OBJS += \
./emdrv/src/rtcdriver.o 

C_DEPS += \
./emdrv/src/rtcdriver.d 


# Each subdirectory must supply rules for building sources it contributes
emdrv/src/rtcdriver.o: ../emdrv/src/rtcdriver.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DEFM32LG990F256=1' -I"/Users/shuting/Documents/ESE/ECEN_5023/Final_Project/inc" -I"/Users/shuting/Documents/ESE/ECEN_5023/Final_Project/inc" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32LG_STK3600/config" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32LG/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I/Users/shuting/Documents/ESE/ECEN_5023/Final_Project/emdrv/inc -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emdrv/src/rtcdriver.d" -MT"emdrv/src/rtcdriver.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


