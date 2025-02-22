#include "file_header.h"
#include <string.h>

// This function is used to create a new aart_file.
aart_file_t *aart_file_new(unsigned char **payload, int height, int width) {
    aart_file_t *aart_file = (aart_file_t *)malloc(sizeof(aart_file_t));
    if (aart_file == NULL) {
        fprintf(stderr, "Error (aart_file_new): Can't create an aart_file.\n");
        return NULL;
    }

    aart_file->magic_number = "aart";
    aart_file->row_count = height;
    aart_file->column_count = (width + 7) / 8; // Rounding to whole bytes
    aart_file->payload = (unsigned char *)calloc(aart_file->row_count * aart_file->column_count, sizeof(unsigned char));
    if (aart_file->payload == NULL) {
        fprintf(stderr, "Error (aart_file_new): Can't allocate memory for the payload.\n");
        free(aart_file);
        return NULL;
    }

    // Encode payload
    encode_ascii_art((const char **)(payload), height, width, aart_file);

    return aart_file;
}

// This function is used to free the memory allocated for the aart_file.
void aart_file_free(aart_file_t *aart_file) {
    if (aart_file == NULL) {
        fprintf(stderr, "Error (aart_file_free): Can't free an uninitialized aart_file.\n");
        return;
    }

    if (aart_file->payload != NULL) {
        free(aart_file->payload);
    }

    free(aart_file);
}

void set_bit(unsigned char *byte, int bit_pos, int value) {
    if (value) {
        *byte |= (1 << (7 - bit_pos)); // MSB first
    }
}

void encode_ascii_art(const char **matrix, int height, int width, aart_file_t *aart_file) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int byte_index = i * aart_file->column_count + j / 8;
            int bit_pos = j % 8;
            if (matrix[i][j] == '#') {
                set_bit(&aart_file->payload[byte_index], bit_pos, 1);
            }
        }
    }
}

// This function is used to save the aart_file to a file.
void aart_file_save(aart_file_t *aart_file, char *filename) {
    if (aart_file == NULL) {
        fprintf(stderr, "Error (aart_file_save): The aart_file is not initialized, yet.\n");
        return;
    }

    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "Error (aart_file_save): Could not create the output file %s\n", filename);
        return;
    }

    // write aart header
    fseek(f, HEADER_MAGIC_NUMBER_OFFSET, SEEK_SET);
    fwrite(aart_file->magic_number, HEADER_MAGIC_NUMBER_BYTES, 1, f);
    fseek(f, HEADER_ROW_COUNT_OFFSET, SEEK_SET);
    fwrite(&aart_file->row_count, HEADER_ROW_COUNT_BYTES, 1, f);
    fseek(f, HEADER_COLUMN_COUNT_OFFSET, SEEK_SET);
    fwrite(&aart_file->column_count, HEADER_COLUMN_COUNT_BYTES, 1, f);
    fseek(f, HEADER_PAYLOAD_OFFSET, SEEK_SET);
    fwrite(aart_file->payload, sizeof(unsigned char), aart_file->row_count * aart_file->column_count, f);

    fclose(f);
}
