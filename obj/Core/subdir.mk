################################################################################
# MRS Version: 1.9.1
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
Core/core_riscv.o: C:/Users/Brandon.DESKTOP-NJOEOTV/Projects/wall_clock_controller/I2C/wall_clock_controller/Core/core_riscv.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Brandon.DESKTOP-NJOEOTV\Projects\wall_clock_controller\I2C\wall_clock_controller\Debug" -I"C:\Users\Brandon.DESKTOP-NJOEOTV\Projects\wall_clock_controller\I2C\wall_clock_controller\Core" -I"C:\Users\Brandon.DESKTOP-NJOEOTV\Projects\wall_clock_controller\I2C\wall_clock_controller\User" -I"C:\Users\Brandon.DESKTOP-NJOEOTV\Projects\wall_clock_controller\I2C\wall_clock_controller\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

