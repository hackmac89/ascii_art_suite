OUTPUT=aart_viewer
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -g -O2
SRC=functions.c main.c
OBJ=$(SRC:.c=.o)
LDLIBS=-lm

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUTPUT) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUTPUT) > /dev/null 2>&1 || true
