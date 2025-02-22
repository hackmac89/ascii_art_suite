#include "types.h"
#include "functions.h"

int main(int argc, char **argv) {
    // Print basic usage information
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file in binary reading mode
    char *filename = argv[1];
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Create header struct
    aart_file_t *header = create_header();
    if (header == NULL) {
        printf("Could not create header struct\n");
        return EXIT_FAILURE;
    }

    // Populate header struct
    if ( populate_header(header, f, filename) != EXIT_SUCCESS ) {
        printf("Could not populate header struct\n");
        return EXIT_FAILURE;
    }

    // Check if magic number is valid
    check_valid_header(header->magic_number);   // Only "aart" is valid

    // Output header and payload for information purposes
    print_header(header);

    // Decode payload
    decode_payload(header);
    //print_ascii_matrix(header);

    // Closing file and freeing memory
    fclose(f);
    free_header(header);
    return EXIT_SUCCESS;
}
