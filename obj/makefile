################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
wall_clock_controller.hex \

SECONDARY_LIST += \
wall_clock_controller.lst \

SECONDARY_SIZE += \
wall_clock_controller.siz \


# All Target
all: wall_clock_controller.elf secondary-outputs

# Tool invocations
wall_clock_controller.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -flto -pedantic -Wunused -Wuninitialized -Wall -Wextra -Wfloat-equal  -g -T "C:\Users\bklu\Projects\wall_clock_controller\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"wall_clock_controller.map" --specs=nano.specs --specs=nosys.specs -o "wall_clock_controller.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
wall_clock_controller.hex: wall_clock_controller.elf
	@	riscv-none-elf-objcopy -O ihex "wall_clock_controller.elf"  "wall_clock_controller.hex"
	@	@
wall_clock_controller.lst: wall_clock_controller.elf
	@	riscv-none-elf-objdump --all-headers --demangle --disassemble -M xw "wall_clock_controller.elf" > "wall_clock_controller.lst"
	@	@
wall_clock_controller.siz: wall_clock_controller.elf
	@	riscv-none-elf-size --format=berkeley "wall_clock_controller.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) wall_clock_controller.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
