#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

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
    uint64_t payload_size;
    unsigned char *payload;

    /* 
        One could also use function pointers here, to make the struct more modular
        and to allow for different decoding functions etc. pp.
        Example:
            void (*populate_header)(aart_file_t *self, FILE *f);
            void (*free)(aart_file_t *self);
        In our main.c file, we would then call the functions like this:
            header->populate_header(header, f);
            header->free(header);
        This would make it extremely clear,
        that these methods are directly operating on the "aart_file_t" struct
        and that these are not just random functions pieced together.
        I will skip this for now, to keep it as simple as needed without introducing more syntactic sugar.
        (This was just a heads up ;-), but I will not implement this here.)
        Just get back to me, if you are interested in this approach @Tobias Modrow aka. hardrockheinz.
    */
} aart_file_t;

#endif
