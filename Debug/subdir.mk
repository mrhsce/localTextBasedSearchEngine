################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Document.cpp \
../FileNameManager.cpp \
../HashMap.cpp \
../Occurance.cpp \
../SimilarityMatrix.cpp \
../main.cpp 

OBJS += \
./Document.o \
./FileNameManager.o \
./HashMap.o \
./Occurance.o \
./SimilarityMatrix.o \
./main.o 

CPP_DEPS += \
./Document.d \
./FileNameManager.d \
./HashMap.d \
./Occurance.d \
./SimilarityMatrix.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


