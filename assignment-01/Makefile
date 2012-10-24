# Simple makefile to build a square.c in the labs or on OSx

UNAME_S := $(shell uname -s)

# Path to the OpenCL libraries.  In this case AMD SDK
# is being used, as system uses AMD graphics card.
OPENCL	:= /opt/AMDAPP

#if OSx
ifeq ($(UNAME_S),Darwin)
	# C flags with strictest warnings.
	CFLAGS	+= -Wall -Wextra  -std=c99
endif

#if Linux
ifeq ($(UNAME_S),Linux)
	CFLAGS	+= -O3 -Wall -Wextra -I$(OPENCL)/include -std=c99
endif

#presuming most osx dont have gcc buy clang/llvm
# Linker flags.
ifeq ($(UNAME_S),Darwin)
	CC := clang
endif

all: square

# Build a binary from C source.
square: square.c
ifeq ($(UNAME_S),Darwin)
	$(CC) -framework OpenCL $(CFLAGS) -std=c99 -o $@ $^ &&./square
endif

ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) -std=c99 $(LDFLAGS) -o $@ $^
endif

# Remove the binary.
clean:
	$(RM) square


