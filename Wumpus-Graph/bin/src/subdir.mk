################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/A.I.cpp \
../src/Wumpus.cpp \
../src/cell.cpp \
../src/graph.cpp \
../src/map.cpp 

OBJS += \
./src/A.I.o \
./src/Wumpus.o \
./src/cell.o \
./src/graph.o \
./src/map.o 

CPP_DEPS += \
./src/A.I.d \
./src/Wumpus.d \
./src/cell.d \
./src/graph.d \
./src/map.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


