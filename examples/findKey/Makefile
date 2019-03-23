# Makefile
# Copyright (c) 2019 Jonathan Archer

TARGET := example

SRCS := main.c
OBJS := $(filter %.o, $(patsubst %.c, %.o, $(SRCS)))

CPPFLAGS := -Wall -Wextra -O2 \
			-I../../include

.PHONY: all clean clang-format

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L../../lib -leasykey

all: $(TARGET)

clean:
	-@rm -rf $(TARGET) $(PACKAGE) $(OBJS)

clang-format:
	clang-format -style=llvm -i $(SRCS)