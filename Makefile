# Makefile
# Copyright (c) 2019 Jonathan Archer

TARGET := libeasykey.a
TARGET_DIR := lib

PACKAGE := libeasykey.zip

SRC_DIRS := source
INC_DIRS := include

SRCS := $(shell find $(SRC_DIRS) -name "*.c*")
OBJS := $(filter %.o, $(patsubst %.c, %.o, $(SRCS)))

CPPFLAGS := -std=gnu99 -Wall -Wextra -O2 \
			$(foreach dir, $(INC_DIRS), -I$(CURDIR)/$(dir)) \
			$(foreach dir, $(DATA_DIRS), -I$(CURDIR)/$(dir))

.PHONY: all package clean clang-format

$(TARGET_DIR)/$(TARGET): $(OBJS)
	-@mkdir $(TARGET_DIR)
	$(AR) -rcs $(TARGET_DIR)/$(TARGET) $(OBJS)

$(PACKAGE): all
	zip -r $(PACKAGE) ./

all: $(TARGET_DIR)/$(TARGET)

package: $(PACKAGE)

install: $(TARGET_DIR)/$(TARGET)
	cp $(TARGET_DIR)/$(TARGET) /usr/lib
	cp -rf include/** /usr/include/

uninstall:
	rm /usr/lib/$(TARGET)
	rm -rf /usr/include/easykey*

clean:
	-@rm -rf $(TARGET_DIR) $(PACKAGE) $(OBJS)

clang-format:
	clang-format -style=llvm -i $(SRCS) $(foreach DIR, $(INC_DIRS), $(DIR)/*.h* $(DIR)/**/*.h*)
