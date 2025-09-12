NAME := minishell

SRC_DIR := ./src
BUILD_DIR := ./build
LIBS_DIR := ./libs

FTLIBC_DIR := $(LIBS_DIR)/ftlibc
FTLIBC := $(FTLIBC_DIR)/ftlibc.a

HEADERS := $(shell find $(SRC_DIR) -type f -name "*.h")
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

INCLUDES := -I$(SRC_DIR)/include \
			-I$(LIBS_DIR)/ftlibc/include

CFLAGS := -Wall -Wextra -Werror
LDLIBS := -lreadline

all: $(NAME)

bonus: all

$(NAME): $(FTLIBC) $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(FTLIBC) -o $(NAME) $(LDLIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FTLIBC): $(shell find -L $(FTLIBC_DIR) -name '*.[ch]')
	make -C $(FTLIBC_DIR) "CFLAGS := $(CFLAGS)"

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	make -C $(FTLIBC_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FTLIBC_DIR) fclean

print-%:
	@echo $($*)
