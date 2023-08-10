################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Camera_CH32/Core/core_riscv.c 

OBJS += \
./Camera_CH32/Core/core_riscv.o 

C_DEPS += \
./Camera_CH32/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Camera_CH32/Core/%.o: ../Camera_CH32/Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Debug" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Core" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\User" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

