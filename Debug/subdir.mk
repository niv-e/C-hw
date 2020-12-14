################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Airline.c \
../Airport.c \
../AirportManager.c \
../Date.c \
../Flight.c \
../Functions.c \
../clock.c \
../exe.c \
../main.c 

OBJS += \
./Airline.o \
./Airport.o \
./AirportManager.o \
./Date.o \
./Flight.o \
./Functions.o \
./clock.o \
./exe.o \
./main.o 

C_DEPS += \
./Airline.d \
./Airport.d \
./AirportManager.d \
./Date.d \
./Flight.d \
./Functions.d \
./clock.d \
./exe.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


