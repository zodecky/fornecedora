CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lcjson

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = $(SRC_DIR)/obj
TEST_DIR = tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Main target
all: main makelib

makelib:
	cd ../lib/cJSON/
	sudo make install
	cd ../../src/

# Main executable
main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main $(LIBS)

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
clean:
	rm -f main $(OBJS) $(TEST_OBJS)

# Tests
test: $(TEST_OBJS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	$(CC) $(CFLAGS) $(TEST_OBJS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) -o test $(LIBS)
	./test

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
