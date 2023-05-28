CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -I./cJSON-1.7.15
LIBS = -lm ./cJSON-1.7.15/cJSON.o
SRC = catalogo.c estoque.c
MKALL = main.c
MKTEST = test_catalogo.c munit.c
OBJ = $(SRC:.c=.o)
OMKALL = $(MKALL:.c=.o)
OMKTEST = $(MKTEST:.c=.o)
PROG = myprogram

$(PROGTEST): $(OBJ) $(OMKTEST)
$(PROG): $(OBJ) $(OMKALL)

all: $(PROG)
	$(CC) $(OBJ) $(OMKALL) -o $(PROG) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(PROG)

testcatalogo: $(PROGTEST)
	$(CC) $(OBJ) $(OMKTEST) -o $(PROG) $(LIBS)
#make 2

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
	$(CC) $(CFLAGS) $(OBJS) obj/main.o -o main $(LIBS)

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
