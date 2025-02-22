#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "types.h"

// Function prototypes
aart_file_t *create_header(void);
void free_header(aart_file_t *);
bool populate_header(aart_file_t *, FILE *, char *);
void check_valid_header(char *);
void print_header(aart_file_t *);
// Quick - and Dirty implementation of the decode function, which just prints the payload
//  One could also implement a function to write the payload to string buffer, without just using printf
void decode_payload(aart_file_t *);
void print_ascii_matrix(aart_file_t *);

#endif
