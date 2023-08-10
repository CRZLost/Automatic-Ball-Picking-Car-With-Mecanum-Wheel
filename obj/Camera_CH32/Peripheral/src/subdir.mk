################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Camera_CH32/Peripheral/src/ch32v10x_adc.c \
../Camera_CH32/Peripheral/src/ch32v10x_bkp.c \
../Camera_CH32/Peripheral/src/ch32v10x_crc.c \
../Camera_CH32/Peripheral/src/ch32v10x_dbgmcu.c \
../Camera_CH32/Peripheral/src/ch32v10x_dma.c \
../Camera_CH32/Peripheral/src/ch32v10x_exti.c \
../Camera_CH32/Peripheral/src/ch32v10x_flash.c \
../Camera_CH32/Peripheral/src/ch32v10x_gpio.c \
../Camera_CH32/Peripheral/src/ch32v10x_i2c.c \
../Camera_CH32/Peripheral/src/ch32v10x_iwdg.c \
../Camera_CH32/Peripheral/src/ch32v10x_misc.c \
../Camera_CH32/Peripheral/src/ch32v10x_pwr.c \
../Camera_CH32/Peripheral/src/ch32v10x_rcc.c \
../Camera_CH32/Peripheral/src/ch32v10x_rtc.c \
../Camera_CH32/Peripheral/src/ch32v10x_spi.c \
../Camera_CH32/Peripheral/src/ch32v10x_tim.c \
../Camera_CH32/Peripheral/src/ch32v10x_usart.c \
../Camera_CH32/Peripheral/src/ch32v10x_usb.c \
../Camera_CH32/Peripheral/src/ch32v10x_usb_host.c \
../Camera_CH32/Peripheral/src/ch32v10x_wwdg.c 

OBJS += \
./Camera_CH32/Peripheral/src/ch32v10x_adc.o \
./Camera_CH32/Peripheral/src/ch32v10x_bkp.o \
./Camera_CH32/Peripheral/src/ch32v10x_crc.o \
./Camera_CH32/Peripheral/src/ch32v10x_dbgmcu.o \
./Camera_CH32/Peripheral/src/ch32v10x_dma.o \
./Camera_CH32/Peripheral/src/ch32v10x_exti.o \
./Camera_CH32/Peripheral/src/ch32v10x_flash.o \
./Camera_CH32/Peripheral/src/ch32v10x_gpio.o \
./Camera_CH32/Peripheral/src/ch32v10x_i2c.o \
./Camera_CH32/Peripheral/src/ch32v10x_iwdg.o \
./Camera_CH32/Peripheral/src/ch32v10x_misc.o \
./Camera_CH32/Peripheral/src/ch32v10x_pwr.o \
./Camera_CH32/Peripheral/src/ch32v10x_rcc.o \
./Camera_CH32/Peripheral/src/ch32v10x_rtc.o \
./Camera_CH32/Peripheral/src/ch32v10x_spi.o \
./Camera_CH32/Peripheral/src/ch32v10x_tim.o \
./Camera_CH32/Peripheral/src/ch32v10x_usart.o \
./Camera_CH32/Peripheral/src/ch32v10x_usb.o \
./Camera_CH32/Peripheral/src/ch32v10x_usb_host.o \
./Camera_CH32/Peripheral/src/ch32v10x_wwdg.o 

C_DEPS += \
./Camera_CH32/Peripheral/src/ch32v10x_adc.d \
./Camera_CH32/Peripheral/src/ch32v10x_bkp.d \
./Camera_CH32/Peripheral/src/ch32v10x_crc.d \
./Camera_CH32/Peripheral/src/ch32v10x_dbgmcu.d \
./Camera_CH32/Peripheral/src/ch32v10x_dma.d \
./Camera_CH32/Peripheral/src/ch32v10x_exti.d \
./Camera_CH32/Peripheral/src/ch32v10x_flash.d \
./Camera_CH32/Peripheral/src/ch32v10x_gpio.d \
./Camera_CH32/Peripheral/src/ch32v10x_i2c.d \
./Camera_CH32/Peripheral/src/ch32v10x_iwdg.d \
./Camera_CH32/Peripheral/src/ch32v10x_misc.d \
./Camera_CH32/Peripheral/src/ch32v10x_pwr.d \
./Camera_CH32/Peripheral/src/ch32v10x_rcc.d \
./Camera_CH32/Peripheral/src/ch32v10x_rtc.d \
./Camera_CH32/Peripheral/src/ch32v10x_spi.d \
./Camera_CH32/Peripheral/src/ch32v10x_tim.d \
./Camera_CH32/Peripheral/src/ch32v10x_usart.d \
./Camera_CH32/Peripheral/src/ch32v10x_usb.d \
./Camera_CH32/Peripheral/src/ch32v10x_usb_host.d \
./Camera_CH32/Peripheral/src/ch32v10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Camera_CH32/Peripheral/src/%.o: ../Camera_CH32/Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Debug" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Core" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\User" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

