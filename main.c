#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "cards.h"

int main() {
        deck_t*         deck;
        const char*     di;

        printf("Hello Bridge Player!\n");
        
        deck = init_deck();
        di = deck_info(deck);
        printf("%s\n", di);

        free_deck(deck);
        deck = NULL;
        di = NULL;        

        return 0;
}
