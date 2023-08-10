################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Private Works\嵌入式比赛_捡球小车\报告部分\提交内容\Final_Codes\Final_Codes\Final_Codes\CH32V103_Vice_Control\Debug" -I"F:\Private Works\嵌入式比赛_捡球小车\报告部分\提交内容\Final_Codes\Final_Codes\Final_Codes\CH32V103_Vice_Control\Core" -I"F:\Private Works\嵌入式比赛_捡球小车\报告部分\提交内容\Final_Codes\Final_Codes\Final_Codes\CH32V103_Vice_Control\User" -I"F:\Private Works\嵌入式比赛_捡球小车\报告部分\提交内容\Final_Codes\Final_Codes\Final_Codes\CH32V103_Vice_Control\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

