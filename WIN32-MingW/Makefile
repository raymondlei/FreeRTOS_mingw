# Build directory
BUILD_DIR := ../build_full
PARALLEL_JOBS ?= $(if $(NUMBER_OF_PROCESSORS),$(NUMBER_OF_PROCESSORS),4)
MAKEFLAGS += -j$(PARALLEL_JOBS)

BLINKY_DEMO ?= 0
EXAMPLE004_DEMO ?= 0
EXAMPLE013_DEMO ?= 0
EXAMPLE010_DEMO ?= 0
EXAMPLE011_DEMO ?= 0
EXAMPLE016_DEMO ?= 0
EXAMPLE020_DEMO ?= 0
EXAMPLE024_DEMO ?= 0
SANDBOX_DEMO ?= 0

# Compiler - Note this expects you are using MinGW version of GCC
CC := gcc
CFLAGS := -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -Wcast-qual -Wno-error=return-mismatch -D_WIN32_WINNT=0x0601

ifeq ($(SANDBOX_DEMO),1)
ifneq ($(filter 1,$(BLINKY_DEMO) $(EXAMPLE004_DEMO) $(EXAMPLE010_DEMO) $(EXAMPLE011_DEMO) $(EXAMPLE013_DEMO) $(EXAMPLE016_DEMO) $(EXAMPLE020_DEMO) $(EXAMPLE024_DEMO)),)
$(error SANDBOX_DEMO cannot be combined with another demo)
endif
endif

ifeq ($(BLINKY_DEMO),1)
ifeq ($(EXAMPLE004_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE004_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE013_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE013_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE010_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE010_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE011_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE011_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE016_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE016_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE024_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE020_DEMO),1)
$(error BLINKY_DEMO and EXAMPLE020_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE004_DEMO),1)
ifeq ($(EXAMPLE013_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE013_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE010_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE010_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE011_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE011_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE016_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE016_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE024_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE020_DEMO),1)
$(error EXAMPLE004_DEMO and EXAMPLE020_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE013_DEMO),1)
ifeq ($(EXAMPLE010_DEMO),1)
$(error EXAMPLE013_DEMO and EXAMPLE010_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE011_DEMO),1)
$(error EXAMPLE013_DEMO and EXAMPLE011_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE016_DEMO),1)
$(error EXAMPLE013_DEMO and EXAMPLE016_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE024_DEMO),1)
$(error EXAMPLE013_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE020_DEMO),1)
$(error EXAMPLE013_DEMO and EXAMPLE020_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE010_DEMO),1)
ifeq ($(EXAMPLE011_DEMO),1)
$(error EXAMPLE010_DEMO and EXAMPLE011_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE016_DEMO),1)
$(error EXAMPLE010_DEMO and EXAMPLE016_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE024_DEMO),1)
$(error EXAMPLE010_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
ifeq ($(EXAMPLE020_DEMO),1)
$(error EXAMPLE010_DEMO and EXAMPLE020_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE011_DEMO),1)
ifeq ($(EXAMPLE016_DEMO),1)
$(error EXAMPLE011_DEMO and EXAMPLE016_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE016_DEMO),1)
ifeq ($(EXAMPLE024_DEMO),1)
$(error EXAMPLE016_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE020_DEMO),1)
ifeq ($(EXAMPLE024_DEMO),1)
$(error EXAMPLE020_DEMO and EXAMPLE024_DEMO cannot both be 1)
endif
endif

ifeq ($(EXAMPLE016_DEMO),1)
ifeq ($(EXAMPLE020_DEMO),1)
$(error EXAMPLE016_DEMO and EXAMPLE020_DEMO cannot both be 1)
endif
endif

ifeq ($(BLINKY_DEMO),1)
	BUILD_DIR := ../build_blinky
	CFLAGS += -DmainCREATE_SIMPLE_BLINKY_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE004_DEMO),1)
	BUILD_DIR := ../build_functional
	CFLAGS += -DmainCREATE_FUNCTIONAL_EXAMPLE_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE013_DEMO),1)
	BUILD_DIR := ../build_example013
	CFLAGS += -DmainCREATE_EXAMPLE013_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE010_DEMO),1)
	BUILD_DIR := ../build_example010
	CFLAGS += -DmainCREATE_EXAMPLE010_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE011_DEMO),1)
	BUILD_DIR := ../build_example011
	CFLAGS += -DmainCREATE_EXAMPLE011_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE020_DEMO),1)
	BUILD_DIR := ../build_example020
	CFLAGS += -DmainCREATE_EXAMPLE020_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE024_DEMO),1)
	BUILD_DIR := ../build_example024
	CFLAGS += -DmainCREATE_EXAMPLE024_DEMO_ONLY=1
endif

ifeq ($(EXAMPLE016_DEMO),1)
	BUILD_DIR := ../build_example016
	CFLAGS += -DmainCREATE_EXAMPLE016_DEMO_ONLY=1
endif

ifeq ($(SANDBOX_DEMO),1)
	BUILD_DIR := ../build_sandbox
	CFLAGS += -DmainCREATE_SANDBOX_DEMO_ONLY=1
endif

ifeq ($(COVERAGE_TEST),1)
  CFLAGS += -DprojCOVERAGE_TEST=1
else
  CFLAGS += -DprojCOVERAGE_TEST=0
endif

# Linker - Note this expects you are using MinGW version of GCC
LD :=  ${CC}
LDFLAGS := -Xlinker -Map=$(BUILD_DIR)/rtosdemo.map

# Executable Targets
EXE := $(BUILD_DIR)/RTOSDemo.exe
ifeq ($(SANDBOX_DEMO),1)
	EXE := $(BUILD_DIR)/sandbox_demo.exe
endif

# FreeRTOS Kernel
FREERTOS_KERNEL_DIR := $(abspath ../FreeRTOS-Kernel)
FREERTOS_KERNEL_INCLUDES :=
FREERTOS_KERNEL_SOURCES :=
FREERTOS_KERNEL_INCLUDE_DIRS :=
FREERTOS_KERNEL_OBJS :=
FREERTOS_KERNEL_BUILD_DIR := $(BUILD_DIR)/FreeRTOS-Kernel

## FreeRTOS Kernel includes
FREERTOS_KERNEL_INCLUDES += $(wildcard $(FREERTOS_KERNEL_DIR)/include/*.h)
FREERTOS_KERNEL_INCLUDE_DIRS += -I $(FREERTOS_KERNEL_DIR)/include

## FreeRTOS Kernel sources
FREERTOS_KERNEL_SOURCES += $(wildcard $(FREERTOS_KERNEL_DIR)/*.c)
FREERTOS_KERNEL_SOURCES += $(FREERTOS_KERNEL_DIR)/portable/MemMang/heap_5.c

## FreeRTOS Kernel Windows port includes
FREERTOS_KERNEL_INCLUDES += $(FREERTOS_KERNEL_DIR)/portable/MSVC-MingW/portmacro.h
FREERTOS_KERNEL_INCLUDE_DIRS += -I $(FREERTOS_KERNEL_DIR)/portable/MSVC-MingW

## FreeRTOS Kernel Windows port sources
FREERTOS_KERNEL_SOURCES += $(FREERTOS_KERNEL_DIR)/portable/MSVC-MingW/port.c

## FreeRTOS Kernel configuration includes
FREERTOS_KERNEL_INCLUDES += ./FreeRTOSConfig.h
FREERTOS_KERNEL_INCLUDE_DIRS += -I .

# FreeRTOS Kernel objects
FREERTOS_KERNEL_SOURCES_NAMES :=$(notdir $(FREERTOS_KERNEL_SOURCES))
FREERTOS_KERNEL_OBJS := $(FREERTOS_KERNEL_SOURCES_NAMES:%.c=$(FREERTOS_KERNEL_BUILD_DIR)/%.o)

# Trace Recorder
FREERTOS_PLUS_TRACE_DIR := $(abspath ../FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace)
FREERTOS_PLUS_TRACE_INCLUDES :=
FREERTOS_PLUS_TRACE_SOURCES :=
FREERTOS_PLUS_TRACE_INCLUDE_DIRS :=
FREERTOS_PLUS_TRACE_OBJS :=
FREERTOS_PLUS_TRACE_BUILD_DIR := $(BUILD_DIR)/FreeRTOS-Plus-Trace

## Trace Recorder includes
FREERTOS_PLUS_TRACE_INCLUDES += $(wildcard $(FREERTOS_PLUS_TRACE_DIR)/include/*.h)
FREERTOS_PLUS_TRACE_INCLUDE_DIRS += -I $(FREERTOS_PLUS_TRACE_DIR)/include
FREERTOS_PLUS_TRACE_INCLUDES += $(wildcard $(FREERTOS_PLUS_TRACE_DIR)/kernelports/FreeRTOS/include/*.h)
FREERTOS_PLUS_TRACE_INCLUDE_DIRS += -I $(FREERTOS_PLUS_TRACE_DIR)/kernelports/FreeRTOS/include

## Trace Recorder sources
FREERTOS_PLUS_TRACE_SOURCES += $(wildcard $(FREERTOS_PLUS_TRACE_DIR)/*.c)
FREERTOS_PLUS_TRACE_SOURCES += $(wildcard $(FREERTOS_PLUS_TRACE_DIR)/kernelports/FreeRTOS/*.c)

## Trace Recorder configuration includes
FREERTOS_PLUS_TRACE_INCLUDES += $(wildcard ./Trace_Recorder_Configuration/*.h)
FREERTOS_PLUS_TRACE_INCLUDE_DIRS += -I ./Trace_Recorder_Configuration

# Trace Recoder objects
FREERTOS_PLUS_TRACE_SOURCES_NAMES :=$(notdir $(FREERTOS_PLUS_TRACE_SOURCES))
FREERTOS_PLUS_TRACE_OBJS := $(FREERTOS_PLUS_TRACE_SOURCES_NAMES:%.c=$(FREERTOS_PLUS_TRACE_BUILD_DIR)/%.o)

# Demos
FREERTOS_DEMOS_DIR := $(abspath ../FreeRTOS/FreeRTOS/Demo/Common/Minimal)
FREERTOS_DEMOS_INCLUDES :=
FREERTOS_DEMOS_SOURCES :=
FREERTOS_DEMOS_INCLUDE_DIRS :=
FREERTOS_DEMOS_OBJS :=
FREERTOS_DEMOS_BUILD_DIR := $(BUILD_DIR)/FreeRTOS-Demos

## Demos includes
FREERTOS_DEMOS_INCLUDES := $(wildcard $(FREERTOS_DEMOS_DIR)/../include/*.h)
FREERTOS_DEMOS_INCLUDE_DIRS := -I $(FREERTOS_DEMOS_DIR)/../include

## Demos sources
FREERTOS_DEMOS_SOURCES += $(wildcard $(FREERTOS_DEMOS_DIR)/*.c)

### Filter out unsupported demos
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/comtest_strings.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/comtest.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/flash_timer.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/flash.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/IntQueue.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/recmutex.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES += ./DemosModifiedForLowTickRate/recmutex.c
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/sp_flop.c, $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_SOURCES := $(filter-out $(FREERTOS_DEMOS_DIR)/TaskNotifyArray.c, $(FREERTOS_DEMOS_SOURCES))

## Demos objects
FREERTOS_DEMOS_SOURCES_NAMES :=$(notdir $(FREERTOS_DEMOS_SOURCES))
FREERTOS_DEMOS_OBJS := $(FREERTOS_DEMOS_SOURCES_NAMES:%.c=$(FREERTOS_DEMOS_BUILD_DIR)/%.o)

# Main
MAIN_DIR := .
MAIN_INCLUDES :=
MAIN_SOURCES :=
MAIN_INCLUDE_DIRS :=
MAIN_BUILD_DIR := $(BUILD_DIR)/main
SANDBOX_DIR := $(abspath ../ECE422_sandbox)

## Main includes
ifeq ($(SANDBOX_DEMO),1)
MAIN_INCLUDES += $(wildcard $(SANDBOX_DIR)/app/*.h)
MAIN_INCLUDE_DIRS += -I $(SANDBOX_DIR)/app
endif

## Main sources
MAIN_SOURCES += $(wildcard $(MAIN_DIR)/*.c)
ifeq ($(SANDBOX_DEMO),1)
MAIN_SOURCES += $(SANDBOX_DIR)/main_sandbox.c
MAIN_SOURCES += $(wildcard $(SANDBOX_DIR)/app/*.c)
endif

## Main objects
MAIN_SOURCES_NAMES :=$(notdir $(MAIN_SOURCES))
MAIN_OBJS := $(MAIN_SOURCES_NAMES:%.c=$(MAIN_BUILD_DIR)/%.o)

$(EXE) : $(MAIN_OBJS) $(FREERTOS_KERNEL_OBJS) $(FREERTOS_DEMOS_OBJS) $(FREERTOS_PLUS_TRACE_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ -lwinmm

# Main objects rules
$(MAIN_OBJS): %.o: $(MAIN_SOURCES) $(MAIN_INCLUDES) $(FREERTOS_KERNEL_INCLUDES) $(FREERTOS_PLUS_TRACE_INCLUDES) $(FREERTOS_DEMOS_INCLUDES)
	if not exist "$(@D)" mkdir "$(@D)" 2>NUL || ver >NUL
	$(CC) $(CFLAGS) $(MAIN_INCLUDE_DIRS) $(FREERTOS_KERNEL_INCLUDE_DIRS) $(FREERTOS_PLUS_TRACE_INCLUDE_DIRS) $(FREERTOS_DEMOS_INCLUDE_DIRS) -o $@ $(filter $(notdir $(patsubst %.o, %.c, $@)) %/$(notdir $(patsubst %.o, %.c, $@)), $^)

# FreeRTOS Kernel objects rules
$(FREERTOS_KERNEL_OBJS): %.o: $(FREERTOS_KERNEL_SOURCES) $(FREERTOS_KERNEL_INCLUDES) $(FREERTOS_PLUS_TRACE_INCLUDES)
	if not exist "$(@D)" mkdir "$(@D)" 2>NUL || ver >NUL
	$(CC) $(CFLAGS) $(FREERTOS_KERNEL_INCLUDE_DIRS) $(FREERTOS_PLUS_TRACE_INCLUDE_DIRS) -o $@ $(filter %$(notdir $(patsubst %.o, %.c, $@)), $^)

# FreeRTOS Demos objects rules
$(FREERTOS_DEMOS_OBJS): %.o: $(FREERTOS_DEMOS_SOURCES) $(FREERTOS_DEMOS_INCLUDES) $(FREERTOS_KERNEL_INCLUDES) $(FREERTOS_PLUS_TRACE_INCLUDES)
	if not exist "$(@D)" mkdir "$(@D)" 2>NUL || ver >NUL
	$(CC) $(CFLAGS) $(FREERTOS_DEMOS_INCLUDE_DIRS) $(FREERTOS_KERNEL_INCLUDE_DIRS) $(FREERTOS_PLUS_TRACE_INCLUDE_DIRS) -o $@ $(filter %$(notdir $(patsubst %.o, %.c, $@)), $^)

# Trace Recorder object filess
$(FREERTOS_PLUS_TRACE_OBJS): %.o: $(FREERTOS_PLUS_TRACE_SOURCES) $(FREERTOS_PLUS_TRACE_INCLUDES) $(FREERTOS_KERNEL_INCLUDES)
	if not exist "$(@D)" mkdir "$(@D)" 2>NUL || ver >NUL
	$(CC) $(CFLAGS) $(FREERTOS_PLUS_TRACE_INCLUDE_DIRS) $(FREERTOS_KERNEL_INCLUDE_DIRS) -o $@ $(filter %$(notdir $(patsubst %.o, %.c, $@)), $^)

# Clean rule
clean:
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

