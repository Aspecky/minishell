BUILD_DIR := ./build
DEBUG_DIR := $(BUILD_DIR)/Debug
NAME := debug

BIN_DIR := ../source
BIN := $(shell make -C $(BIN_DIR) -s print-NAME)
BIN_BONUS := $(BIN)_bonus

CFLAGS := -Wall -Wextra -fsanitize=address -ggdb3 -O0

all: $(BUILD_DIR) $(DEBUG_DIR)
	make all -s -C $(BIN_DIR) "CFLAGS = $(CFLAGS)" "DDEBUG = 1"
	cp $(BIN_DIR)/$(BIN) $(NAME)

bonus: $(BUILD_DIR) $(DEBUG_DIR)
	make bonus -C $(BIN_DIR) "CFLAGS = $(CFLAGS)"
	cp $(BIN_DIR)/$(BIN_BONUS) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEBUG_DIR):
	mkdir -p $(DEBUG_DIR)

val:
	make all "CFLAGS = $(filter-out -fsanitize=address,$(CFLAGS))"

clean:
	make clean -C $(BIN_DIR)
	rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C $(BIN_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

print-%:
	@echo $($*)
