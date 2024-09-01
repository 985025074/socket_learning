# makefile

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# some target which have been perfectly done
DEFUALT_TARGET = hserver hclient file_client file_server select_exp

LIB_NAME = check_lib
# 注意 -l接的库名 去掉前后缀
NORMAL_RULE = $(CC) $(CFLAGS) -o ${OUTPUT}/$@ ${SRCS}/$@.c -L${LIBSRC} -l${LIB_NAME} -I${INCLUDE} -Wl,-rpath=${LIBSRC}
# LIB_RULE = it is waiting to be finished
# definition of the path of source,include and other files 

check_lib_src += ./checkLib/*.c
check_lib_include += ./checkLib
SRCS = ./src
OUTPUT =./output
INCLUDE = ${check_lib_include}
LIBSRC = $(CURDIR)/output


# Already well-done target (compile the program)
all: $(DEFAULT_TARGET)
half_close_exp: file_client file_server
udp_exp: udp_client udp_server
opt_exp: set_get_socket_opt
# Rule to compile the target executable
# 可以使用 % 匹配所有任务目标
# rpath 不能用相对路径，想想也是合情合理的，因为连接器目录在特定位置
${DEFUALT_TARGET}:check_lib
	${NORMAL_RULE}	
check_lib :
	$(CC) $(CCFLAGS) -shared -fPIC -o $(LIBSRC)/lib$@.so ${check_lib_src} -I./checkLib/
pipe_exp:check_lib
	${NORMAL_RULE}
# Rule to run the program
# run:${DEFUALT_TARGET}
# 	LD_LIBRARY_PATH=$(LIBSRC):$$LD_LIBRARY_PATH ./$(OUTPUT)/hserver
# 	LD_LIBRARY_PATH=$(LIBSRC):$$LD_LIBRARY_PATH ./$(OUTPUT)/hclinet
	

# Rule to clean up compiled files
# clean:

# 	rm -f $(TARGET)

# Rule to clean up and recompile
# rebuild: clean all
