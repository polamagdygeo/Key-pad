################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
LSS += \
ProximitySensor.lss \

FLASH_IMAGE += \
ProximitySensor.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ProximitySensor.elf secondary-outputs

# Tool invocations
ProximitySensor.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ProximitySensor.map -mmcu=atmega32 -o "ProximitySensor.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ProximitySensor.lss: ProximitySensor.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ProximitySensor.elf  >"ProximitySensor.lss"
	@echo 'Finished building: $@'
	@echo ' '

ProximitySensor.hex: ProximitySensor.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ProximitySensor.elf  "ProximitySensor.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ProximitySensor.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ProximitySensor.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ProximitySensor.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
