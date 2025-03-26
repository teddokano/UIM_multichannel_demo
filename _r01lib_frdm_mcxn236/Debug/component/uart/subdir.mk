################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_lpuart.c 

C_DEPS += \
./component/uart/fsl_adapter_lpuart.d 

OBJS += \
./component/uart/fsl_adapter_lpuart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DPRINTF_FLOAT_ENABLE=1 -DSCANF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSCANF_ADVANCED_ENABLE=1 -DCPU_MCXN236VDF -DCPU_MCXN236VDF_cm33 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DTARGET_N236 -DSDK_DELAY_USE_DWT -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/source" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/source/r01lib" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/source/r01device" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/board" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/drivers" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/device" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/utilities" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/component/uart" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/component/lists" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/CMSIS" -I"/Users/tedd/dev/mcuxpresso/UIM_multichannel_demo/_r01lib_frdm_mcxn236/startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_lpuart.d ./component/uart/fsl_adapter_lpuart.o

.PHONY: clean-component-2f-uart

