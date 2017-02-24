################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Project\ 1.c 

OBJS += \
./src/Project\ 1.o 

C_DEPS += \
./src/Project\ 1.d 


# Each subdirectory must supply rules for building sources it contributes
src/Project\ 1.o: ../src/Project\ 1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Project 1.d" -MT"src/Project\ 1.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


