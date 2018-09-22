################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/openings/book.cpp 

OBJS += \
./src/openings/book.o 

CPP_DEPS += \
./src/openings/book.d 


# Each subdirectory must supply rules for building sources it contributes
src/openings/%.o: ../src/openings/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/echo/code/sheila/src/events" -I"/home/echo/code/sheila/src/openings" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


