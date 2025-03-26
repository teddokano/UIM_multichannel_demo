################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/SoftPWM/ServoMotor.cpp \
../source/SoftPWM/SoftPWM.cpp \
../source/SoftPWM/SoftPWM_base.cpp 

CPP_DEPS += \
./source/SoftPWM/ServoMotor.d \
./source/SoftPWM/SoftPWM.d \
./source/SoftPWM/SoftPWM_base.d 

OBJS += \
./source/SoftPWM/ServoMotor.o \
./source/SoftPWM/SoftPWM.o \
./source/SoftPWM/SoftPWM_base.o 


# Each subdirectory must supply rules for building sources it contributes
source/SoftPWM/%.o: ../source/SoftPWM/%.cpp source/SoftPWM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++20 -DPRINTF_FLOAT_ENABLE=1 -DSCANF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSCANF_ADVANCED_ENABLE=1 -D__NEWLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DTARGET_A153 -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/z_demo_SG_FRDM_MCXA153/source" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/board" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/source/r01lib" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/source/r01device" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/component/lists" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/drivers" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/CMSIS" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/device" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/utilities" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxa153/component/uart" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-SoftPWM

clean-source-2f-SoftPWM:
	-$(RM) ./source/SoftPWM/ServoMotor.d ./source/SoftPWM/ServoMotor.o ./source/SoftPWM/SoftPWM.d ./source/SoftPWM/SoftPWM.o ./source/SoftPWM/SoftPWM_base.d ./source/SoftPWM/SoftPWM_base.o

.PHONY: clean-source-2f-SoftPWM

