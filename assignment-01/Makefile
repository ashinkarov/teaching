# Simple makefile to build a square.c in the labs.

# Path to the OpenCL libraries.  In this case AMD SDK
# is being used, as system uses AMD graphics card.
OPENCL	:= /opt/AMDAPP

# C flags with strictest warnings.
CFLAGS	+= -Wall -Wextra  -std=c99

# Linker flags.

CC := clang

all: square

# Build a binary from C source.
square: square.c
	$(CC) -framework OpenCL $(CFLAGS) -std=c99 -o $@ $^ &&./square
	

# Remove the binary.
clean:
	$(RM) square
