# update per change V0004
# get project settings
include src/Makefile.mk
# get platform settings
include platform/$(MCU).mk

INCLUDES += -Iplatform
LIBDIR += -L"./ld"
ALIBS +=
RLIBS += 
DLIBS += 
RLIBDIR +=
DLIBDIR +=

# Toolchain settings
MAKE = make
MKDIR = mkdir
RM = rm
C_COMPILER = gcc
CXX_COMPILER = g++
GDB = gdb
TOOLCHAIN_PREFIX = arm-none-eabi-
SIZE = size
AR = ar
OBJDUMP = objdump
OBJCOPY = objcopy

# Toolchain flags
COMPILE_C_FLAGS +=  
COMPILE_CXX_FLAGS +=  
COMPILE_ASM_FLAGS += 
DEFINES += -DMCU_$(MCU)
DEFINES_RELEASE = -DNDEBUG
DEFINES_DEBUG = -DDEBUG
C_RELEASE_COMPILE_FLAGS = -Os -g  
C_DEBUG_COMPILE_FLAGS = -Og -g3 
CXX_RELEASE_COMPILE_FLAGS = -Os -g 
CXX_DEBUG_COMPILE_FLAGS = -Og -g3
ASM_RELEASE_COMPILE_FLAGS = 
ASM_DEBUG_COMPILE_FLAGS = -g3

LINK_FLAGS += -flto -nostdlib -Xlinker --gc-sections -Xlinker -print-memory-usage
LINK_FLAGS_RELEASE =
LINK_FLAGS_DEBUG =
LDSCRIPT = -T"ld/$(MCU).ld"

# Clear built-in rules
.SUFFIXES:

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Combine compiler and linker flags
release: export CFLAGS := $(COMPILE_C_FLAGS) $(C_RELEASE_COMPILE_FLAGS) $(DEFINES_RELEASE) $(DEFINES)
release: export CXXFLAGS := $(COMPILE_CXX_FLAGS) $(CXX_RELEASE_COMPILE_FLAGS) $(DEFINES_RELEASE) $(DEFINES)
release: export ASMFLAGS := $(COMPILE_ASM_FLAGS) $(ASM_RELEASE_COMPILE_FLAGS) $(DEFINES_RELEASE) $(DEFINES)
release: export LDFLAGS := $(LINK_FLAGS) $(LINK_FLAGS_RELEASE) $(LIBDIR) $(RLIBDIR) $(LDSCRIPT)
release: export LIBS := $(ALIBS) $(RLIBS)
debug: export CFLAGS := $(COMPILE_C_FLAGS) $(C_DEBUG_COMPILE_FLAGS) $(DEFINES_DEBUG) $(DEFINES)
debug: export CXXFLAGS := $(COMPILE_CXX_FLAGS) $(CXX_DEBUG_COMPILE_FLAGS) $(DEFINES_DEBUG) $(DEFINES)
debug: export ASMFLAGS := $(COMPILE_ASM_FLAGS) $(ASM_DEBUG_COMPILE_FLAGS) $(DEFINES_DEBUG) $(DEFINES)
debug: export LDFLAGS := $(LINK_FLAGS) $(LINK_FLAGS_DEBUG) $(LIBDIR) $(DLIBDIR) $(LDSCRIPT)
debug: export LIBS := $(ALIBS) $(DLIBS)

# Build and output paths
release: export BUILD_PATH := build/release
release: export BIN_PATH := bin/release
debug: export BUILD_PATH := build/debug
debug: export BIN_PATH := bin/debug

# export what target we are building, used for size logs
release: export BUILD_TARGET := release
debug: export BUILD_TARGET := debug

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(C_SOURCES:%.c=$(BUILD_PATH)/%.c.o)
OBJECTS += $(CXX_SOURCES:%.cpp=$(BUILD_PATH)/%.cpp.o)
OBJECTS += $(S_SOURCES:%.s=$(BUILD_PATH)/%.s.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# Standard, non-optimized release build
release: dirs
	# make lpc_chip library if needed
	$(MAKE) all --no-print-directory

# Debug build for gdb debugging
debug: dirs
	$(MAKE) all --no-print-directory

# Create the directories used in the build
dirs:
	$(MKDIR) -p $(BUILD_PATH)
	$(MKDIR) -p $(BIN_PATH)

# Removes all build files
clean_debug:
clean_release:
clean:
	$(RM) -r build
	$(RM) -r bin

# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME).elf

# create the executable
$(BIN_PATH)/$(BIN_NAME).elf: $(OBJECTS)
	$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(LDFLAGS) $(OBJECTS) -Xlinker -Map="$@.map" -o $@ $(LIBS)
	# dump size and log to file
	$(TOOLCHAIN_PREFIX)$(SIZE) -x --format=SysV $@ 
	date >> size$(BUILD_TARGET).log
	$(TOOLCHAIN_PREFIX)$(SIZE) $@ >> size$(BUILD_TARGET).log
	# create the various output files
	$(TOOLCHAIN_PREFIX)$(OBJCOPY) -R .stack -O binary $@ $(BIN_PATH)/$(BIN_NAME).bin
	$(TOOLCHAIN_PREFIX)$(OBJDUMP) -h -S "$@" > "$(BIN_PATH)/$(BIN_NAME).lss"

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
# if the source file is in a subdir, create this subdir in the build dir
# additional dependency on Makefile and more importantly the include in src
$(BUILD_PATH)/%.c.o: ./%.c Makefile ./src/Makefile.mk
	$(MKDIR) -p $(dir $@) 
	$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

$(BUILD_PATH)/%.cpp.o: ./%.cpp Makefile ./src/Makefile.mk
	$(MKDIR) -p $(dir $@) 
	$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

$(BUILD_PATH)/%.s.o: ./%.s Makefile ./src/Makefile.mk
	$(MKDIR) -p $(dir $@) 
	$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(ASMFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# debugging lines
gdbftdidebug: debug
	$(TOOLCHAIN_PREFIX)$(GDB) -x ./gdb_scripts/bmpFTDIdebug.txt

gdbftdirelease: release
	$(TOOLCHAIN_PREFIX)$(GDB) -x ./gdb_scripts/bmpFTDIrelease.txt

gdbusbdebug: debug
	$(TOOLCHAIN_PREFIX)$(GDB) -x ./gdb_scripts/bmpUSBdebug.txt

gdbusbrelease: debug
	$(TOOLCHAIN_PREFIX)$(GDB) -x ./gdb_scripts/bmpUSBrelease.txt


.PHONY: release debug dirs all clean clean_debug clean_release gdbftdidebug gdbftdirelease gdbusbdebug gdbusbrelease

