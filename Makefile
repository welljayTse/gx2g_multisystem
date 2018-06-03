# Makefile
#
# Make of remote
#
# date 2016.05.03

# cross compile prefix
CROSS = /opt/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-

# compiler
CC = $(CROSS)gcc
CFLAGS = -O2

# linker
LD = $(CROSS)ld
LDFLAGS = #-elf2flat
LDLIBS = -lm# -lz

# strip
STRIP = $(CROSS)strip

# archive
AR = $(CROSS)ar cr
RANLIB = $(CROSS)ranlib


# target
GX4G = gx4g	#可执行文件
GX4G_OBJ = gx4g.o \
	   mysocketcan.o mygps.o my4gmodule.o myuart.o

### targets ###

all: 	$(GX4G)
	$(STRIP) $(GX4G)

$(GX4G): $(GX4G_OBJ)

clean:
	-rm -f *.o
	-rm -f $(GX4G)
	-rm -f $(TESTBULK)

.PHONY: all clean

