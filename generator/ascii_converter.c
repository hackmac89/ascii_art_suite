#define STB_IMAGE_IMPLEMENTATION
#include "ascii_converter.h"

/*  
    This function is used to convert an image to an ASCII representation
    and return it in a one dimensional array representation.
    The ASCII representation is created by using the greyscale values of the image.
    Parameters:
        filename: The filename of the image to be converted.
        scale: The scale factor to be used. 1 = 1:1, 2 = 1:2, 3 = 1:3, ...
*/
aart_matrix_t* convert_to_ascii_array(const char *filename, uint8_t scale) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 1); // 1 = greyscale
    if (data == NULL) {
        fprintf(stderr, "Error (convert_to_ascii_array): Could not load image file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    aart_matrix_t *ascii_matrix = malloc(sizeof(aart_matrix_t));
    ascii_matrix->height = height / scale;
    ascii_matrix->width = width / scale;
    ascii_matrix->ascii_data = (unsigned char **)malloc(ascii_matrix->height * sizeof(unsigned char *));
    if (ascii_matrix->ascii_data == NULL) {
        fprintf(stderr, "Error (convert_to_ascii_array): Could not allocate memory for the ASCII matrix\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ascii_matrix->height; i++) {
        ascii_matrix->ascii_data[i] = (unsigned char *)malloc(ascii_matrix->width * sizeof(unsigned char) + 1);
        if (ascii_matrix->ascii_data[i] == NULL) {
            fprintf(stderr, "Error (convert_to_ascii_array): Could not allocate memory for the ASCII matrix\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < ascii_matrix->width; j++) {
            unsigned char pixel = data[(i * scale * width) + (j * scale)];
            ascii_matrix->ascii_data[i][j] = pixel < 128 ? '#' : ' ';
        }
        ascii_matrix->ascii_data[i][ascii_matrix->width] = '\0';
    }

    stbi_image_free(data);
    return ascii_matrix;
}

// This function is used to free the memory allocated for the ASCII matrix.
void free_ascii_matrix(aart_matrix_t *ascii_matrix) {
    if (ascii_matrix->ascii_data != NULL) {
        for (int i = 0; i < ascii_matrix->height; i++) {
            free(ascii_matrix->ascii_data[i]);
        }
        free(ascii_matrix->ascii_data);
    }
    if (ascii_matrix != NULL) {
        free(ascii_matrix);
    }
}

// This function is used to print the ASCII matrix to the console.
void print_ascii_matrix(aart_matrix_t *ascii_matrix) {
    if (ascii_matrix == NULL) {
        fprintf(stderr, "Error (print_ascii_matrix): ASCII matrix is NULL\n");
        return;
    }

    for (int i = 0; i < ascii_matrix->height; i++) {
        for (int j = 0; j < ascii_matrix->width; j++) {
            if (ascii_matrix->ascii_data[i][j] != '\0') printf("%c", ascii_matrix->ascii_data[i][j]);
        }
        printf("\n");
    }
}
