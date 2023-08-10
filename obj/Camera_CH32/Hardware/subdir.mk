################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Camera_CH32/Hardware/Camera.c \
../Camera_CH32/Hardware/LED.c \
../Camera_CH32/Hardware/OLED.c \
../Camera_CH32/Hardware/PWM.c \
../Camera_CH32/Hardware/Servo.c \
../Camera_CH32/Hardware/Timer.c 

OBJS += \
./Camera_CH32/Hardware/Camera.o \
./Camera_CH32/Hardware/LED.o \
./Camera_CH32/Hardware/OLED.o \
./Camera_CH32/Hardware/PWM.o \
./Camera_CH32/Hardware/Servo.o \
./Camera_CH32/Hardware/Timer.o 

C_DEPS += \
./Camera_CH32/Hardware/Camera.d \
./Camera_CH32/Hardware/LED.d \
./Camera_CH32/Hardware/OLED.d \
./Camera_CH32/Hardware/PWM.d \
./Camera_CH32/Hardware/Servo.d \
./Camera_CH32/Hardware/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Camera_CH32/Hardware/%.o: ../Camera_CH32/Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Debug" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Core" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\User" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

