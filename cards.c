#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

card_t init_card(uint8_t rank, char suit) {
        card_t c;

        c = card_default;

        c.rank = rank;
        c.suit = suit;

        return c;
}

const char* card_info(card_t card) {
        char* buffer;

        buffer = (char*)malloc(CARD_INFO_BUFFER_SIZE);
        if(buffer == NULL) {
                return NULL;
        }

        switch(card.rank) {
        case B_STD_MIN_CARD_RANK ... 10:
                sprintf(buffer, "|%2d\\%2c|", card.rank, card.suit);
                break;
        case 11:
                sprintf(buffer, "|%2c\\%2c|", 'J', card.suit);
                break;
        case 12:
                sprintf(buffer, "|%2c\\%2c|", 'Q', card.suit);
                break;
        case 13:
                sprintf(buffer, "|%2c\\%2c|", 'K', card.suit);
                break;
        case B_STD_MAX_CARD_RANK:
                sprintf(buffer, "|%2c\\%2c|", 'A', card.suit);
                break;
        default:
                return NULL;
        }

        return buffer;
}

      
