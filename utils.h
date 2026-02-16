#ifndef UTILS_H_
#define UTILS_H_

#define MAX_USER_INPUT_BUFFER_SIZE 32

enum buffered_types {
        CHAR,
        BID_T,
        CARD_T
};

typedef enum buffered_types buffered_type_t;

void    allocate_buffer(buffered_type_t, void*, size_t, size_t);
void    free_allocated_buffer(buffered_type_t, void*);
void    cast_allocated_buffer(buffered_type_t, void*);
void    get_user_input(const char*, char*, size_t);
void    quit(const char*);

#endif

