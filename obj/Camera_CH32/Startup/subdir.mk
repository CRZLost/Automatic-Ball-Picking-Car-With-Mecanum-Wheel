################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Camera_CH32/Startup/startup_ch32v10x.S 

OBJS += \
./Camera_CH32/Startup/startup_ch32v10x.o 

S_UPPER_DEPS += \
./Camera_CH32/Startup/startup_ch32v10x.d 


# Each subdirectory must supply rules for building sources it contributes
Camera_CH32/Startup/%.o: ../Camera_CH32/Startup/%.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Startup" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\Hardware" -I"C:\Users\Lost\Desktop\智能小车\Codes\CH32V103_Vice_Control\System" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

