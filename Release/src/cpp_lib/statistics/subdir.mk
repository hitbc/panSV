################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cpp_lib/statistics/StatsManager.cpp \
../src/cpp_lib/statistics/StatsTracker.cpp 

OBJS += \
./src/cpp_lib/statistics/StatsManager.o \
./src/cpp_lib/statistics/StatsTracker.o 

CPP_DEPS += \
./src/cpp_lib/statistics/StatsManager.d \
./src/cpp_lib/statistics/StatsTracker.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpp_lib/statistics/%.o: ../src/cpp_lib/statistics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -I../src/htslib -Ipthread -Im -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


