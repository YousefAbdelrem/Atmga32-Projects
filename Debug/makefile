################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include RTOS/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/Keybad/subdir.mk
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
Protect_app.lss \

FLASH_IMAGE += \
Protect_app.hex \

EEPROM_IMAGE += \
Protect_app.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Protect_app.elf secondary-outputs

# Tool invocations
Protect_app.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Protect_app.map -mmcu=atmega32 -o "Protect_app.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Protect_app.lss: Protect_app.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Protect_app.elf  >"Protect_app.lss"
	@echo 'Finished building: $@'
	@echo ' '

Protect_app.hex: Protect_app.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Protect_app.elf  "Protect_app.hex"
	@echo 'Finished building: $@'
	@echo ' '

Protect_app.eep: Protect_app.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Protect_app.elf  "Protect_app.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Protect_app.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Protect_app.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Protect_app.elf
	@echo 'Invoking: AVRDude'
	D:\Computer_Science\Embeded_SYSTEMS\IMT\SDK\IMT_SDK_Win_64\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -Pusb -Uflash:w:Protect_app.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Protect_app.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
