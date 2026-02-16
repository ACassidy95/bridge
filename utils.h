#ifndef UTILS_H_
#define UTILS_H_

enum buffered_types {
        CHAR,
        BID_T,
        CARD_T
};

typedef enum buffered_types buffered_type_t;

void                    allocate_buffer(buffered_type_t, void*, size_t, size_t);
size_t                  size_buffered_type(buffered_type_t);
void                    free_allocated_buffer(buffered_type_t, void*);
void                    cast_allocated_buffer(buffered_type_t, void*);
const char*             get_user_input(const char*);
void                    quit(const char*);

#endif

