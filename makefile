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

all: $(PROG)

$(PROG): $(OBJ) $(OMKALL)
	$(CC) $(OBJ) $(OMKALL) -o $(PROG) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(PROG)

testcatalogo: $(PROG)
$(PROG): $(OBJ) $(OMKTEST)
	$(CC) $(OBJ) $(OMKTEST) -o $(PROG) $(LIBS)
