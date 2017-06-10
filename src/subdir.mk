################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Archer.cpp \
../src/Arrow.cpp \
../src/Character.cpp \
../src/Explosion.cpp \
../src/GameComponent.cpp \
../src/GameManager.cpp \
../src/HUDElement.cpp \
../src/InGameComp.cpp \
../src/Main.cpp \
../src/Minion.cpp \
../src/Object.cpp \
../src/Player.cpp \
../src/ResourceManager.cpp \
../src/Room.cpp \
../src/SceneGraph.cpp \
../src/Sword.cpp \
../src/Swordman.cpp \
../src/TextElement.cpp \
../src/Wizard.cpp \
../src/toolbox.cpp 

OBJS += \
./src/Archer.o \
./src/Arrow.o \
./src/Character.o \
./src/Explosion.o \
./src/GameComponent.o \
./src/GameManager.o \
./src/HUDElement.o \
./src/InGameComp.o \
./src/Main.o \
./src/Minion.o \
./src/Object.o \
./src/Player.o \
./src/ResourceManager.o \
./src/Room.o \
./src/SceneGraph.o \
./src/Sword.o \
./src/Swordman.o \
./src/TextElement.o \
./src/Wizard.o \
./src/toolbox.o 

CPP_DEPS += \
./src/Archer.d \
./src/Arrow.d \
./src/Character.d \
./src/Explosion.d \
./src/GameComponent.d \
./src/GameManager.d \
./src/HUDElement.d \
./src/InGameComp.d \
./src/Main.d \
./src/Minion.d \
./src/Object.d \
./src/Player.d \
./src/ResourceManager.d \
./src/Room.d \
./src/SceneGraph.d \
./src/Sword.d \
./src/Swordman.d \
./src/TextElement.d \
./src/Wizard.d \
./src/toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


