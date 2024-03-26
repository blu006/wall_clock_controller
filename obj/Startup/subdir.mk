################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_ch32v00x.S 

OBJS += \
./Startup/startup_ch32v00x.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v00x.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v00x.o: C:/Users/bklu/Projects/wall_clock_controller/Startup/startup_ch32v00x.S
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"C:\Users\bklu\Projects\wall_clock_controller\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

