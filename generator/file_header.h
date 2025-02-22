#ifndef __FILE_HEADER_H__
#define __FILE_HEADER_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define HEADER_MAGIC_NUMBER_OFFSET 0
#define HEADER_MAGIC_NUMBER_BYTES 4
#define HEADER_ROW_COUNT_OFFSET 4
#define HEADER_ROW_COUNT_BYTES 1
#define HEADER_COLUMN_COUNT_OFFSET 8
#define HEADER_COLUMN_COUNT_BYTES 1
#define HEADER_PAYLOAD_OFFSET 12

typedef struct {
    char *magic_number;
    uint32_t row_count;
    uint32_t column_count;
    unsigned char *payload;
} aart_file_t;

// Function prototypes
aart_file_t *aart_file_new(unsigned char **, int, int);
void aart_file_free(aart_file_t *);
void set_bit(unsigned char *, int, int);
void encode_ascii_art(const char **, int, int, aart_file_t *);
void aart_file_save(aart_file_t *, char *);

#endif
