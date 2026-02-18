CC ?= gcc

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build
DATA_DIR := data

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := $(DATA_DIR)/vocaend

CFLAGS ?= -O2 -Wall
CFLAGS += -I$(INC_DIR) -fstack-protector-all -MMD -MP
LDFLAGS ?= -no-pie -lm -z lazy -s

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(DATA_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(DATA_DIR):
	mkdir -p $@

clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

-include $(DEPS)
