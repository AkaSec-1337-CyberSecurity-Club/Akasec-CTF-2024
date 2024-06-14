all: chall.z64
.PHONY: all

BUILD_DIR = build
D = 0
V = 1
include $(N64_INST)/include/n64.mk

CFLAGS+=-s

OBJS = $(BUILD_DIR)/src/main.o $(BUILD_DIR)/src/common.o

chall.z64: N64_ROM_TITLE = "chall"
chall.z64: $(BUILD_DIR)/sprites.dfs

$(BUILD_DIR)/chall.elf: $(OBJS)
$(BUILD_DIR)/sprites.dfs: $(wildcard filesystem/*)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)