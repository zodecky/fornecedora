CC = gcc
CFLAGS = -Wall -Wextra -g 
LIBS = -lsqlite3

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

RELEASE_DIR = release
RELEASE_BIN_DIR = $(RELEASE_DIR)/bin
RELEASE_LIB_DIR = $(RELEASE_DIR)/lib

TEST_DIR = test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

all: release test

release: $(filter-out $(OBJ_DIR)/test.o, $(OBJS))
	mkdir -p $(RELEASE_BIN_DIR)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/test.o, $(OBJS)) -o $(RELEASE_BIN_DIR)/myprogram $(LIBS)
	cp -r $(LIB_DIR) $(RELEASE_LIB_DIR)

test: $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJS) -o $(BIN_DIR)/test $(LIBS)
	./$(BIN_DIR)/test

install:
	cp -r $(LIB_DIR) /usr/local/lib

run: release
	./$(RELEASE_BIN_DIR)/myprogram


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RELEASE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@