################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32v00x_adc.c \
../Peripheral/src/ch32v00x_dbgmcu.c \
../Peripheral/src/ch32v00x_dma.c \
../Peripheral/src/ch32v00x_exti.c \
../Peripheral/src/ch32v00x_flash.c \
../Peripheral/src/ch32v00x_gpio.c \
../Peripheral/src/ch32v00x_i2c.c \
../Peripheral/src/ch32v00x_iwdg.c \
../Peripheral/src/ch32v00x_misc.c \
../Peripheral/src/ch32v00x_opa.c \
../Peripheral/src/ch32v00x_pwr.c \
../Peripheral/src/ch32v00x_rcc.c \
../Peripheral/src/ch32v00x_spi.c \
../Peripheral/src/ch32v00x_tim.c \
../Peripheral/src/ch32v00x_usart.c \
../Peripheral/src/ch32v00x_wwdg.c 

OBJS += \
./Peripheral/src/ch32v00x_adc.o \
./Peripheral/src/ch32v00x_dbgmcu.o \
./Peripheral/src/ch32v00x_dma.o \
./Peripheral/src/ch32v00x_exti.o \
./Peripheral/src/ch32v00x_flash.o \
./Peripheral/src/ch32v00x_gpio.o \
./Peripheral/src/ch32v00x_i2c.o \
./Peripheral/src/ch32v00x_iwdg.o \
./Peripheral/src/ch32v00x_misc.o \
./Peripheral/src/ch32v00x_opa.o \
./Peripheral/src/ch32v00x_pwr.o \
./Peripheral/src/ch32v00x_rcc.o \
./Peripheral/src/ch32v00x_spi.o \
./Peripheral/src/ch32v00x_tim.o \
./Peripheral/src/ch32v00x_usart.o \
./Peripheral/src/ch32v00x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32v00x_adc.d \
./Peripheral/src/ch32v00x_dbgmcu.d \
./Peripheral/src/ch32v00x_dma.d \
./Peripheral/src/ch32v00x_exti.d \
./Peripheral/src/ch32v00x_flash.d \
./Peripheral/src/ch32v00x_gpio.d \
./Peripheral/src/ch32v00x_i2c.d \
./Peripheral/src/ch32v00x_iwdg.d \
./Peripheral/src/ch32v00x_misc.d \
./Peripheral/src/ch32v00x_opa.d \
./Peripheral/src/ch32v00x_pwr.d \
./Peripheral/src/ch32v00x_rcc.d \
./Peripheral/src/ch32v00x_spi.d \
./Peripheral/src/ch32v00x_tim.d \
./Peripheral/src/ch32v00x_usart.d \
./Peripheral/src/ch32v00x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32v00x_adc.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_adc.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_dbgmcu.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_dbgmcu.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_dma.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_dma.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_exti.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_exti.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_flash.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_flash.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_gpio.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_gpio.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_i2c.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_i2c.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_iwdg.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_iwdg.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_misc.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_misc.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_opa.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_opa.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_pwr.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_pwr.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_rcc.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_rcc.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_spi.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_spi.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_tim.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_tim.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_usart.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_usart.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v00x_wwdg.o: C:/Users/bklu/Projects/wall_clock_controller/Peripheral/src/ch32v00x_wwdg.c
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -Wunused -Wuninitialized -Wall -Wfloat-equal  -g -I"C:\Users\bklu\Projects\wall_clock_controller\Debug" -I"C:\Users\bklu\Projects\wall_clock_controller\Core" -I"C:\Users\bklu\Projects\wall_clock_controller\User" -I"C:\Users\bklu\Projects\wall_clock_controller\Peripheral\inc" -std=gnu99 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

