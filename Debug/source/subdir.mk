################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/analysis.c \
../source/autocorrelate.c \
../source/dac.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sin.c \
../source/systick.c \
../source/test_sin.c \
../source/tone_to_sample.c 

OBJS += \
./source/adc.o \
./source/analysis.o \
./source/autocorrelate.o \
./source/dac.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sin.o \
./source/systick.o \
./source/test_sin.o \
./source/tone_to_sample.o 

C_DEPS += \
./source/adc.d \
./source/analysis.d \
./source/autocorrelate.d \
./source/dac.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sin.d \
./source/systick.d \
./source/test_sin.d \
./source/tone_to_sample.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\board" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\source" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\drivers" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\CMSIS" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\utilities" -I"C:\Users\hwsin\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Getting_In_Tune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


