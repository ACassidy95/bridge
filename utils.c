#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_USER_INPUT_BUFFER_SIZE 32

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
