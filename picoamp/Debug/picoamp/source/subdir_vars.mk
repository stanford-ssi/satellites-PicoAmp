################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../picoamp/source/sys_link.cmd 

ASM_SRCS += \
../picoamp/source/dabort.asm \
../picoamp/source/sys_core.asm \
../picoamp/source/sys_intvecs.asm \
../picoamp/source/sys_mpu.asm \
../picoamp/source/sys_pmu.asm 

C_SRCS += \
../picoamp/source/adc.c \
../picoamp/source/can.c \
../picoamp/source/crc.c \
../picoamp/source/dcc.c \
../picoamp/source/ecap.c \
../picoamp/source/eqep.c \
../picoamp/source/esm.c \
../picoamp/source/etpwm.c \
../picoamp/source/gio.c \
../picoamp/source/het.c \
../picoamp/source/i2c.c \
../picoamp/source/lin.c \
../picoamp/source/mibspi.c \
../picoamp/source/notification.c \
../picoamp/source/pinmux.c \
../picoamp/source/rti.c \
../picoamp/source/sci.c \
../picoamp/source/spi.c \
../picoamp/source/sys_dma.c \
../picoamp/source/sys_main.c \
../picoamp/source/sys_pcr.c \
../picoamp/source/sys_phantom.c \
../picoamp/source/sys_pmm.c \
../picoamp/source/sys_selftest.c \
../picoamp/source/sys_startup.c \
../picoamp/source/sys_vim.c \
../picoamp/source/system.c 

C_DEPS += \
./picoamp/source/adc.d \
./picoamp/source/can.d \
./picoamp/source/crc.d \
./picoamp/source/dcc.d \
./picoamp/source/ecap.d \
./picoamp/source/eqep.d \
./picoamp/source/esm.d \
./picoamp/source/etpwm.d \
./picoamp/source/gio.d \
./picoamp/source/het.d \
./picoamp/source/i2c.d \
./picoamp/source/lin.d \
./picoamp/source/mibspi.d \
./picoamp/source/notification.d \
./picoamp/source/pinmux.d \
./picoamp/source/rti.d \
./picoamp/source/sci.d \
./picoamp/source/spi.d \
./picoamp/source/sys_dma.d \
./picoamp/source/sys_main.d \
./picoamp/source/sys_pcr.d \
./picoamp/source/sys_phantom.d \
./picoamp/source/sys_pmm.d \
./picoamp/source/sys_selftest.d \
./picoamp/source/sys_startup.d \
./picoamp/source/sys_vim.d \
./picoamp/source/system.d 

OBJS += \
./picoamp/source/adc.obj \
./picoamp/source/can.obj \
./picoamp/source/crc.obj \
./picoamp/source/dabort.obj \
./picoamp/source/dcc.obj \
./picoamp/source/ecap.obj \
./picoamp/source/eqep.obj \
./picoamp/source/esm.obj \
./picoamp/source/etpwm.obj \
./picoamp/source/gio.obj \
./picoamp/source/het.obj \
./picoamp/source/i2c.obj \
./picoamp/source/lin.obj \
./picoamp/source/mibspi.obj \
./picoamp/source/notification.obj \
./picoamp/source/pinmux.obj \
./picoamp/source/rti.obj \
./picoamp/source/sci.obj \
./picoamp/source/spi.obj \
./picoamp/source/sys_core.obj \
./picoamp/source/sys_dma.obj \
./picoamp/source/sys_intvecs.obj \
./picoamp/source/sys_main.obj \
./picoamp/source/sys_mpu.obj \
./picoamp/source/sys_pcr.obj \
./picoamp/source/sys_phantom.obj \
./picoamp/source/sys_pmm.obj \
./picoamp/source/sys_pmu.obj \
./picoamp/source/sys_selftest.obj \
./picoamp/source/sys_startup.obj \
./picoamp/source/sys_vim.obj \
./picoamp/source/system.obj 

ASM_DEPS += \
./picoamp/source/dabort.d \
./picoamp/source/sys_core.d \
./picoamp/source/sys_intvecs.d \
./picoamp/source/sys_mpu.d \
./picoamp/source/sys_pmu.d 

OBJS__QUOTED += \
"picoamp/source/adc.obj" \
"picoamp/source/can.obj" \
"picoamp/source/crc.obj" \
"picoamp/source/dabort.obj" \
"picoamp/source/dcc.obj" \
"picoamp/source/ecap.obj" \
"picoamp/source/eqep.obj" \
"picoamp/source/esm.obj" \
"picoamp/source/etpwm.obj" \
"picoamp/source/gio.obj" \
"picoamp/source/het.obj" \
"picoamp/source/i2c.obj" \
"picoamp/source/lin.obj" \
"picoamp/source/mibspi.obj" \
"picoamp/source/notification.obj" \
"picoamp/source/pinmux.obj" \
"picoamp/source/rti.obj" \
"picoamp/source/sci.obj" \
"picoamp/source/spi.obj" \
"picoamp/source/sys_core.obj" \
"picoamp/source/sys_dma.obj" \
"picoamp/source/sys_intvecs.obj" \
"picoamp/source/sys_main.obj" \
"picoamp/source/sys_mpu.obj" \
"picoamp/source/sys_pcr.obj" \
"picoamp/source/sys_phantom.obj" \
"picoamp/source/sys_pmm.obj" \
"picoamp/source/sys_pmu.obj" \
"picoamp/source/sys_selftest.obj" \
"picoamp/source/sys_startup.obj" \
"picoamp/source/sys_vim.obj" \
"picoamp/source/system.obj" 

C_DEPS__QUOTED += \
"picoamp/source/adc.d" \
"picoamp/source/can.d" \
"picoamp/source/crc.d" \
"picoamp/source/dcc.d" \
"picoamp/source/ecap.d" \
"picoamp/source/eqep.d" \
"picoamp/source/esm.d" \
"picoamp/source/etpwm.d" \
"picoamp/source/gio.d" \
"picoamp/source/het.d" \
"picoamp/source/i2c.d" \
"picoamp/source/lin.d" \
"picoamp/source/mibspi.d" \
"picoamp/source/notification.d" \
"picoamp/source/pinmux.d" \
"picoamp/source/rti.d" \
"picoamp/source/sci.d" \
"picoamp/source/spi.d" \
"picoamp/source/sys_dma.d" \
"picoamp/source/sys_main.d" \
"picoamp/source/sys_pcr.d" \
"picoamp/source/sys_phantom.d" \
"picoamp/source/sys_pmm.d" \
"picoamp/source/sys_selftest.d" \
"picoamp/source/sys_startup.d" \
"picoamp/source/sys_vim.d" \
"picoamp/source/system.d" 

ASM_DEPS__QUOTED += \
"picoamp/source/dabort.d" \
"picoamp/source/sys_core.d" \
"picoamp/source/sys_intvecs.d" \
"picoamp/source/sys_mpu.d" \
"picoamp/source/sys_pmu.d" 

C_SRCS__QUOTED += \
"../picoamp/source/adc.c" \
"../picoamp/source/can.c" \
"../picoamp/source/crc.c" \
"../picoamp/source/dcc.c" \
"../picoamp/source/ecap.c" \
"../picoamp/source/eqep.c" \
"../picoamp/source/esm.c" \
"../picoamp/source/etpwm.c" \
"../picoamp/source/gio.c" \
"../picoamp/source/het.c" \
"../picoamp/source/i2c.c" \
"../picoamp/source/lin.c" \
"../picoamp/source/mibspi.c" \
"../picoamp/source/notification.c" \
"../picoamp/source/pinmux.c" \
"../picoamp/source/rti.c" \
"../picoamp/source/sci.c" \
"../picoamp/source/spi.c" \
"../picoamp/source/sys_dma.c" \
"../picoamp/source/sys_main.c" \
"../picoamp/source/sys_pcr.c" \
"../picoamp/source/sys_phantom.c" \
"../picoamp/source/sys_pmm.c" \
"../picoamp/source/sys_selftest.c" \
"../picoamp/source/sys_startup.c" \
"../picoamp/source/sys_vim.c" \
"../picoamp/source/system.c" 

ASM_SRCS__QUOTED += \
"../picoamp/source/dabort.asm" \
"../picoamp/source/sys_core.asm" \
"../picoamp/source/sys_intvecs.asm" \
"../picoamp/source/sys_mpu.asm" \
"../picoamp/source/sys_pmu.asm" 


