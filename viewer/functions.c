#include "functions.h"

// Create header struct and allocate memory for its members
aart_file_t *create_header(void) {
    aart_file_t *header = (aart_file_t *)malloc(sizeof(aart_file_t));
    if (header == NULL) {
        printf("Could not allocate memory for header\n");
        exit(EXIT_FAILURE);
    }

    header->magic_number = (char *)malloc(HEADER_MAGIC_NUMBER_BYTES * sizeof(char));
    if (header->magic_number == NULL) {
        printf("Memory allocation for magic number failed\n");
        free(header);
        return NULL;
    }
    header->row_count = 0;
    header->column_count = 0;
    header->payload = NULL;

    return header;
}

// Free header struct and its members
void free_header(aart_file_t *header) {
    if (header != NULL) {
        free(header->magic_number);
        free(header->payload);
        free(header);
    }
}

// Populate header struct with data from a given file
bool populate_header(aart_file_t *header, FILE *f, char *filename) {
    // Obtain magic number
    if ( fread(header->magic_number, sizeof(char), HEADER_MAGIC_NUMBER_BYTES, f) != HEADER_MAGIC_NUMBER_BYTES ) {
        printf("Could not read magic number from file %s\n", filename);
        free_header(header);
        fclose(f);
        return EXIT_FAILURE;
    }

    // Obtain row count
    fseek(f, HEADER_ROW_COUNT_OFFSET, SEEK_SET);
    if ( fread(&header->row_count, sizeof(int), HEADER_ROW_COUNT_BYTES, f) != HEADER_ROW_COUNT_BYTES ) {
        printf("Could not read row count from file %s\n", filename);
        free_header(header);
        fclose(f);
        return EXIT_FAILURE;
    }

    // Obtain column count
    fseek(f, HEADER_COLUMN_COUNT_OFFSET, SEEK_SET);
    if ( fread(&header->column_count, sizeof(int), HEADER_COLUMN_COUNT_BYTES, f) != HEADER_COLUMN_COUNT_BYTES ) {
        printf("Could not read column count from file %s\n", filename);
        free_header(header);
        fclose(f);
        return EXIT_FAILURE;
    }

    // Allocate payload buffer
    header->payload_size = header->row_count * header->column_count;
    header->payload = (unsigned char *)malloc(header->payload_size * sizeof(unsigned char));
    if (header->payload == NULL) {
        printf("Memory allocation for payload failed\n");
        free_header(header);
        fclose(f);
        return EXIT_FAILURE;
    }

    // obtain/read payload
    fseek(f, HEADER_PAYLOAD_OFFSET, SEEK_SET);
    size_t bytes_read = 0;
    if ( (bytes_read = fread(header->payload, sizeof(unsigned char), header->payload_size, f)) != header->payload_size ) {
        printf("Could not read payload from file %s (%zu bytes read: %s)\n", filename, bytes_read, header->payload);
        free_header(header);
        fclose(f);
        return EXIT_FAILURE;
    }
    printf("Read %zu bytes of payload\n", bytes_read);

    return EXIT_SUCCESS;
}

// Check if magic number is valid and therefore the file is a valid aart file
void check_valid_header(char *magic_bytes) {
    if ( strncmp(magic_bytes, "aart", HEADER_MAGIC_NUMBER_BYTES) != 0 ) {
        printf("Invalid magic number (%s)\n", magic_bytes);
        exit(EXIT_FAILURE);
    }
}

// Print header information for debugging purposes
void print_header(aart_file_t *header) {
    printf("Magic number: %s\n", header->magic_number);
    printf("Row count: %d\n", header->row_count);
    printf("Column count: %d\n", header->column_count);
    printf("Payload size: %" PRIu64 "\n", header->payload_size);
    printf("Payload: %s\n", header->payload);
}

// Decode payload from most significant bit to least significant bit (Big Endian)
void decode_payload(aart_file_t *header) {
    for(uint32_t i = 0; i < header->row_count; i++) {
        for(uint32_t j = 0; j < header->column_count; j++) {
           char current_byte = header->payload[i * header->column_count + j];
           //putchar(current_byte);
           for (int k = 7; k >= 0; k--) { // MSB first
               // check, if bit is set
                if (current_byte & (1 << k)) {
                     printf("#");
                } else {
                     printf(" ");
                }
           }
        }
        printf("\n");
    }
}

void print_ascii_matrix(aart_file_t *ascii_matrix) {
    if (ascii_matrix == NULL) {
        fprintf(stderr, "Error (print_ascii_matrix): ASCII matrix is NULL\n");
        return;
    }

    for (uint32_t i = 0; i < ascii_matrix->row_count; i++) {
        for (uint32_t j = 0; j < ascii_matrix->column_count; j++) {
            printf("%c", ascii_matrix->payload[i * ascii_matrix->column_count + j]);
        }
        printf("\n");
    }
}
