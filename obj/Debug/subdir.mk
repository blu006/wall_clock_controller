################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: C:/Users/bklu/Projects/wall_clock_controller/Debug/debug.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

