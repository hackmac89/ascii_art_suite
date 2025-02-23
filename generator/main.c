#define _GNU_SOURCE
#include <string.h>
#include "file_header.h"
#include "ascii_converter.h"

// This function is used to print the usage of the program.
void print_usage(void) {
    printf("Usage: ./ascii_art_generator <input_image> <scale_factor>\n");
    printf("Example:\n\t./ascii_art_generator test.png 3\n");
}

// This function is used to remove the file extension from a filename.
char *remove_file_extension(const char *filename) {
    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        char *result = (char *)malloc(strlen(filename) + 1);
        if (result) {
            strcpy(result, filename);
        }
        return result;
    }
    size_t len = dot - filename;
    char *result = (char *)malloc(len + 1);
    if (result) {
        strncpy(result, filename, len);
        result[len] = '\0';
    }
    return result;
}

// This function is used to extract the filename from a path.
char *extract_filename(const char *path) {
    char *slash = strrchr(path, '/');
    if (!slash || slash == path) {
        char *result = (char *)malloc(strlen(path) + 1);
        if (result) {
            strcpy(result, path);
        }
        return result;
    }
    char *result = (char *)malloc(strlen(slash + 1) + 1);
    if (result) {
        strcpy(result, slash + 1);
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *input_image_file = argv[1];
    uint8_t scale_factor = atoi(argv[2]);
    char *output_filename = remove_file_extension(extract_filename(input_image_file));

    aart_matrix_t *ascii_array = convert_to_ascii_array(input_image_file, scale_factor);
    aart_file_t *new_aart_file = aart_file_new(ascii_array->ascii_data, ascii_array->height, ascii_array->width);

    if (new_aart_file == NULL) {
        return EXIT_FAILURE;
    }

    aart_file_save(new_aart_file, strcat(output_filename, ".aart"));

    puts("ASCII representation:");
    puts("--------------------");
    print_ascii_matrix(ascii_array);

    free_ascii_matrix(ascii_array);
    aart_file_free(new_aart_file);

    return EXIT_SUCCESS;
}
