CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -I./cJSON-1.7.15
LIBS = -lm ./cJSON-1.7.15/cJSON.o
SRC = main.c catalogo.c estoque.c
OBJ = $(SRC:.c=.o)
PROG = myprogram

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(PROG)
