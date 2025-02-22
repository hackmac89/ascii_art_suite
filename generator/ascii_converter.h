#ifndef __ASCII_CONVERTER_H__
#define __ASCII_CONVERTER_H__

#include <stdint.h>
#include <stdio.h>
#include "external/stb/stb_image.h" // Gets injected into the project as a submodule while Makefile "installation"

typedef struct {
    int width;
    int height;
    unsigned char **ascii_data;   // 2D interpretation of ASCII Art
} aart_matrix_t;

// Function prototypes
aart_matrix_t* convert_to_ascii_array(const char *, uint8_t);
void free_ascii_matrix(aart_matrix_t *);
void print_ascii_matrix(aart_matrix_t *);

#endif
