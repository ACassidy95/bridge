#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_USER_INPUT_BUFFER_SIZE 32

void allocate_buffer(buffered_type_t type, void* buffer, size_t elem_size, size_t len) {
        if (!elem_size) {
                quit("allocate_buffer: Provided element size 0. Cannot allocate buffer for elements of unknown size.");
        }

        if (!len) {
                fprintf(stderr, "allocate_buffer: Provided len value 0. Setting to 1");
                len += 1;
        }

        buffer = malloc(elem_size * len);
        if (!buffer) {
                quit("allocate_buffer: Buffer allocation faied.");   
        }

        cast_allocated_buffer(type, buffer);
}

void cast_allocated_buffer(buffered_type_t type, void* buffer) {
        switch(type) {
        case CHAR:
                (char*)buffer;
                break;
        case BID_T:
                (bid_t*)buffer;
                break;
        case CARD_T:
                (card_t*)buffer;
                break;
        default:
                fprintf(stderr, "Invalid buffer type. No cast performed.\n");
                break;
        }

        return;
}

void free_allocated_buffer(buffered_type_t type, void* buffer) {
        cast_allocated_buffer(type, buffer);        
        free(buffer);
        buffer = NULL;
}

const char* get_user_input(const char* template) {
        char* buffer;

        buffer = (char*)malloc(MAX_USER_INPUT_BUFFER_SIZE + 1);
        if (buffer == NULL) {
                quit("Error allocating using user input buffer");
        }

        printf("%s", template);

        while (1) {
                int c = getchar();
                if (c == EOF) {
                        break;
                }

                if (!isspace(c)) {
                        unget(c, stdin);
                        break;
                }
        }

        int i = 0;
        while (1) {
                int c = getchar();
                if (c == '\n' || c == EOF) {
                        buffer[i] = '\0';
                        break;
                }
                if (i == MAX_USER_INPUT_BUFFER_SIZE - 1) {
                        buffer[i] = '\0';
                        break
                }
                buffer[i] = c;
                ++i;
        }

        return buffer;
}

void quit(const char* err) {
        fprintf(stderr, "%s\n", err);
        exit(1);
}

 input_error:
