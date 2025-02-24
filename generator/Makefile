OUTPUT=aart_generator
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -g -O2
SRC=ascii_converter.c file_header.c main.c
OBJ=$(SRC:.c=.o)
STB_DIR=external/stb
STB_HEADER=$(STB_DIR)/stb_image.h
LDLIBS=-lm

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUTPUT) $(LDLIBS)

%.o: %.c $(STB_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(STB_HEADER):
	@mkdir -p $(STB_DIR)
	@echo "Downloading stb_image.h..."
	@cd $(STB_DIR) && git init && git remote add origin https://github.com/nothings/stb.git
	@cd $(STB_DIR) && git config core.sparseCheckout true
	@echo "stb_image.h" > $(STB_DIR)/.git/info/sparse-checkout
	@cd $(STB_DIR) && git pull origin master

clean:
	rm -f $(OBJ) $(OUTPUT)
