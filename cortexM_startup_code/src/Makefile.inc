
# project name
BIN_NAME = cortexM_startup_code
MCU = LPC824
BOARD = 
C_SOURCES = 
CPP_SOURCES = src/startup.cpp src/main.cpp
S_SOURCES = 
INCLUDES = -Iinc
LIBDIR = 
LIBS = 
RLIBDIR = 
DEFINES = -mcpu=cortex-m0 -mthumb
COMPILE_CXX_FLAGS = -mcpu=cortex-m0 -mthumb
COMPILE_CPP_FLAGS = -mcpu=cortex-m0 -mthumb
COMPILE_ASM_FLAGS =
LINK_FLAGS = -mcpu=cortex-m0 -mthumb