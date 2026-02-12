#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

card_t* init_card(uint8_t rank, const char* suit) {
        card_t* c;

        c = (card_t*)malloc(sizeof(card_t));
        if(c == NULL) {
                return NULL;
        }
        *c = card_default;

        c->rank = rank;
        c->suit = suit;
        c->str = card_info(*c);
        if(c->str == "" || c->str == NULL) {
                return NULL;
        }

        return c;
}

void free_card(card_t* card) {
        free((char*)card->suit);
        free((char*)card->str);
        card->suit = NULL;
        card->str = NULL;
        
        return; 
}

const char* card_info(card_t card) {
        char* buffer;

        buffer = (char*)malloc(CARD_INFO_BUFFER_SIZE);
        if(buffer == NULL) {
                return "";
        }

        switch(card.rank) {
        case B_STD_MIN_CARD_RANK ... 10:
                sprintf(buffer, "|%2d\\%2c|", card.rank, card.suit[0]);
                break;
        case 11:
                sprintf(buffer, "|%2c\\%2c|", 'J', card.suit[0]);
                break;
        case 12:
                sprintf(buffer, "|%2c\\%2c|", 'Q', card.suit[0]);
                break;
        case 13:
                sprintf(buffer, "|%2c\\%2c|", 'K', card.suit[0]);
                break;
        case B_STD_MAX_CARD_RANK:
        default:
                return "";
        }

        return buffer;
}

      
