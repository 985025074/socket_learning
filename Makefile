# Makefile for hserver project

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Target executable
TARGET = hserver hclient

LIB_NAME = check_lib

# Source files

#check_lib

check_lib_src += ./checkLib/*.c
check_lib_include += ./checkLib
SRCS = ./src
OUTPUT =./output
INCLUDE = ${check_lib_include}
LIBSRC = $(CURDIR)/output


# Default target (compile the program)
all: $(TARGET)

# Rule to compile the target executable
# rpath 不能用相对路径，想想也是合情合理的，因为连接器目录在特定位置
hserver:  check_lib
	$(CC) $(CFLAGS) -o ${OUTPUT}/$@ ${SRCS}/hserver.c -L${LIBSRC} -l${LIB_NAME} -I${INCLUDE} -Wl,-rpath=${LIBSRC}
hclient:  check_lib
	$(CC) $(CFLAGS) -o ${OUTPUT}/$@ ${SRCS}/hclient.c -L${LIBSRC} -l${LIB_NAME} -I${INCLUDE} -Wl,-rpath=${LIBSRC}

check_lib :
	$(CC) $(CCFLAGS) -shared -fPIC -o $(LIBSRC)/libcheck_lib.so ${check_lib_src} -I./checkLib/

# Rule to run the program
run:$(TARGET)
	LD_LIBRARY_PATH=$(LIBSRC):$$LD_LIBRARY_PATH ./$(OUTPUT)/hserver
	LD_LIBRARY_PATH=$(LIBSRC):$$LD_LIBRARY_PATH ./$(OUTPUT)/hclinet
	

# Rule to clean up compiled files
# clean:

# 	rm -f $(TARGET)

# Rule to clean up and recompile
# rebuild: clean all
