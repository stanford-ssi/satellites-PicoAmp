################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./picoamp/source/adc.obj" \
"./picoamp/source/can.obj" \
"./picoamp/source/crc.obj" \
"./picoamp/source/dabort.obj" \
"./picoamp/source/dcc.obj" \
"./picoamp/source/ecap.obj" \
"./picoamp/source/eqep.obj" \
"./picoamp/source/esm.obj" \
"./picoamp/source/etpwm.obj" \
"./picoamp/source/gio.obj" \
"./picoamp/source/het.obj" \
"./picoamp/source/i2c.obj" \
"./picoamp/source/lin.obj" \
"./picoamp/source/mibspi.obj" \
"./picoamp/source/notification.obj" \
"./picoamp/source/pinmux.obj" \
"./picoamp/source/rti.obj" \
"./picoamp/source/sci.obj" \
"./picoamp/source/spi.obj" \
"./picoamp/source/sys_core.obj" \
"./picoamp/source/sys_dma.obj" \
"./picoamp/source/sys_intvecs.obj" \
"./picoamp/source/sys_main.obj" \
"./picoamp/source/sys_mpu.obj" \
"./picoamp/source/sys_pcr.obj" \
"./picoamp/source/sys_phantom.obj" \
"./picoamp/source/sys_pmm.obj" \
"./picoamp/source/sys_pmu.obj" \
"./picoamp/source/sys_selftest.obj" \
"./picoamp/source/sys_startup.obj" \
"./picoamp/source/sys_vim.obj" \
"./picoamp/source/system.obj" \
"../picoamp/source/sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-lrtsv7R4_T_be_v3D16_eabi.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include picoamp/source/subdir_vars.mk
-include picoamp/source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
picoamp.out \

EXE_OUTPUTS__QUOTED += \
"picoamp.out" \

BIN_OUTPUTS += \
picoamp.hex \

BIN_OUTPUTS__QUOTED += \
"picoamp.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "picoamp.out"

# Tool invocations
picoamp.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi -z -m"picoamp.map" --heap_size=0x800 --stack_size=0x800 -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/lib" -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="picoamp_linkInfo.xml" --rom_model --be32 -o "picoamp.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

picoamp.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armhex"  -o "picoamp.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "picoamp/source/adc.obj" "picoamp/source/can.obj" "picoamp/source/crc.obj" "picoamp/source/dabort.obj" "picoamp/source/dcc.obj" "picoamp/source/ecap.obj" "picoamp/source/eqep.obj" "picoamp/source/esm.obj" "picoamp/source/etpwm.obj" "picoamp/source/gio.obj" "picoamp/source/het.obj" "picoamp/source/i2c.obj" "picoamp/source/lin.obj" "picoamp/source/mibspi.obj" "picoamp/source/notification.obj" "picoamp/source/pinmux.obj" "picoamp/source/rti.obj" "picoamp/source/sci.obj" "picoamp/source/spi.obj" "picoamp/source/sys_core.obj" "picoamp/source/sys_dma.obj" "picoamp/source/sys_intvecs.obj" "picoamp/source/sys_main.obj" "picoamp/source/sys_mpu.obj" "picoamp/source/sys_pcr.obj" "picoamp/source/sys_phantom.obj" "picoamp/source/sys_pmm.obj" "picoamp/source/sys_pmu.obj" "picoamp/source/sys_selftest.obj" "picoamp/source/sys_startup.obj" "picoamp/source/sys_vim.obj" "picoamp/source/system.obj" 
	-$(RM) "picoamp/source/adc.d" "picoamp/source/can.d" "picoamp/source/crc.d" "picoamp/source/dcc.d" "picoamp/source/ecap.d" "picoamp/source/eqep.d" "picoamp/source/esm.d" "picoamp/source/etpwm.d" "picoamp/source/gio.d" "picoamp/source/het.d" "picoamp/source/i2c.d" "picoamp/source/lin.d" "picoamp/source/mibspi.d" "picoamp/source/notification.d" "picoamp/source/pinmux.d" "picoamp/source/rti.d" "picoamp/source/sci.d" "picoamp/source/spi.d" "picoamp/source/sys_dma.d" "picoamp/source/sys_main.d" "picoamp/source/sys_pcr.d" "picoamp/source/sys_phantom.d" "picoamp/source/sys_pmm.d" "picoamp/source/sys_selftest.d" "picoamp/source/sys_startup.d" "picoamp/source/sys_vim.d" "picoamp/source/system.d" 
	-$(RM) "picoamp/source/dabort.d" "picoamp/source/sys_core.d" "picoamp/source/sys_intvecs.d" "picoamp/source/sys_mpu.d" "picoamp/source/sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

