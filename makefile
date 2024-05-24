CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c error_handling.c shell_functions.c
OBJS = $(SRCS:.c=.o)
TARGET = program

CUSTOM_LIB_PATH = custom_lib
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))	

# cat
CAT_SRCS = cat/cat.c
CAT_OBJS = $(CAT_SRCS:.c=.o)
CAT_TARGET = $(CUSTOM_LIB_PATH)/cat

# ls
LS_SRCS = ls/ls.c
LS_OBJS = $(LS_SRCS:.c=.o)
LS_TARGET = $(CUSTOM_LIB_PATH)/ls

.PHONY: all clean cat ls

all: $(TARGET) $(CAT_TARGET) $(LS_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(CAT_TARGET): $(CAT_OBJS)
	mkdir -p $(CUSTOM_LIB_PATH)
	$(CC) $(CFLAGS) $(CAT_SRCS) -o $(CAT_TARGET)

$(LS_TARGET): $(LS_OBJS)
	mkdir -p $(CUSTOM_LIB_PATH)
	$(CC) $(CFLAGS) $(LS_SRCS) -o $(LS_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(CAT_OBJS) $(LS_OBJS)
	rm -rf $(CUSTOM_LIB_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@