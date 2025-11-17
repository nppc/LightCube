################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/button.c \
../src/candle.c \
../src/gen.c \
../src/main.c \
../src/pwm.c \
../src/status_led.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/button.OBJ \
./src/candle.OBJ \
./src/gen.OBJ \
./src/main.OBJ \
./src/pwm.OBJ \
./src/status_led.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/button.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/button.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/status_led.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/candle.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/gen.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/InitDevice.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/status_led.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/button.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/pwm.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/candle.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/pwm.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/pwm.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/status_led.OBJ: C:/src/tennp/git/LightCube/Firmware/LightCube/src/main.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/status_led.h C:/src/tennp/git/LightCube/Firmware/LightCube/src/button.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8BB50/inc/SI_EFM8BB50_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h


