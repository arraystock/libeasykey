# Makefile
# Copyright (c) 2019 Jonathan Archer

TARGET := example.out

SRCS := main.c
OBJS := $(filter %.o, $(patsubst %.c, %.o, $(SRCS)))

CPPFLAGS := -Wall -Wextra

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -leasykey

all: $(TARGET)

clean:
	-@rm -rf $(TARGET) $(OBJS)