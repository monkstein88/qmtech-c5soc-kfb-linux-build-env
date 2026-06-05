#
TARGET = HPS_FPGA_LED_BLINK

ALT_DEVICE_FAMILY ?= soc_cv_av
HWLIBS_ROOT = ../../hwlib-socfpga/armv7a/hwlib

CROSS_COMPILE = arm-none-linux-gnueabihf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc

INCS = ./inc
SRCS = ./src/main.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -g -Wall -Werror \
	-I$(HWLIBS_ROOT)/include \
	-I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) \
	-I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY)/socal \
	-I$(INCS) \
	-D$(ALT_DEVICE_FAMILY)
LDFLAGS = -g -Wall -Werror


.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) *.a *~

