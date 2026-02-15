#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cards.h"

// Card function implementations

card_t init_card(uint8_t rank, suit_t suit) {
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
                sprintf(buffer, "|%2d\\%2c|", card.rank, suit_info(card.suit));
                break;
        case 11:
                sprintf(buffer, "|%2c\\%2c|", 'J', suit_info(card.suit));
                break;
        case 12:
                sprintf(buffer, "|%2c\\%2c|", 'Q', suit_info(card.suit));
                break;
        case 13:
                sprintf(buffer, "|%2c\\%2c|", 'K', suit_info(card.suit));
                break;
        case B_STD_MAX_CARD_RANK:
                sprintf(buffer, "|%2c\\%2c|", 'A', suit_info(card.suit));
                break;
        default:
                sprintf(buffer, "|ERROR|");
                break;
        }

        return buffer;
}

const char suit_info(suit_t suit) {
        switch(suit) {
        case CLUBS:     return 'C';
        case DIAMONDS:  return 'D';
        case HEARTS:    return 'H';
        case SPADES:    return 'S';
        default:        return '\\';
        }
}

// Cards are compared on rank and suit
// c1.suit > c2.suit                      => c1 > c2
// c1.suit = c2.suit && c1.rank > c2.rank => c1 > c2
//                   && c1.rank < c2.rank => c1 < c2
// c1.suit < c2.suit                      => c2 > c1    
static int cmp_cards(const void* c1, const void* c2) {
        int cmp;

        card_t cd1 = *(card_t*)c1;
        card_t cd2 = *(card_t*)c2;

        if (cd1.suit > cd2.suit) {
                cmp = 1;
        } else if (cd1.suit == cd2.suit) { 
                if (cd1.rank > cd2.rank) {
                        cmp = 1;
                } else if (cd1.rank < cd2.rank) {
                        cmp = -1;
                } else {
                        // This shouldn't ever occur but needed to shut the static analyser up
                        cmp = 0;
                }
        } else {
                cmp = -1;
        }

        return cmp; 
}

// Card collection function implementations
cards_t* init_card_collection(size_t capacity) {
        cards_t* c;

        c = (cards_t*)malloc(sizeof(cards_t));
        if (c == NULL) {
                return NULL;
        }        
        c->capacity = capacity;
        c->size = 0;
        
        c->cards = (card_t*)malloc(sizeof(card_t) * capacity);
        if (c->cards == NULL) {
                return NULL;
        }

        return c;
}

void free_card_collection(cards_t* cards) {
        free(cards->cards);
        cards->cards = NULL;

        free(cards);
        return;
}

const char* card_collection_info(cards_t* cards) {
        char*   buffer;
        size_t  buff_len;

        buff_len = cards->size * CARD_INFO_BUFFER_SIZE + 1; 
        buffer = (char*)malloc(buff_len);
        if(buffer == NULL) {
                return NULL;
        }

        for(size_t i = 0; i < cards->size; ++i) {
                const char* ci = card_info(cards->cards[i]);
                if (ci == NULL) {
                        return NULL;
                }

                strncat(buffer, ci, CARD_INFO_BUFFER_SIZE);
                free((char*)ci);
        }
        buffer[buff_len - 1] = '\0';

        return buffer;
}

void create_deck(cards_t* cards) {
        if (cards->capacity < B_STD_DECK_SIZE) {
                printf("Not enough space to create a deck. Have %zu, need %d", cards->capacity, B_STD_DECK_SIZE);
                return;
        }

        suit_t ns = NUM_SUITS;
        for(size_t i = 0; i <= B_STD_MAX_CARD_RANK - B_STD_MIN_CARD_RANK; ++i) {
                for(size_t j = 0; j < ns; ++j) {
                        card_t c = init_card(i + B_STD_MIN_CARD_RANK, (suit_t)j);
                        size_t idx = i * ns  + j;
                        
                        cards->cards[idx] = c;
                        cards->size++;
                }
        }

        return;
}

void shuffle(cards_t* cards) {
        int c1, c2;
        card_t tmp;
        
        srand(time(NULL));

        for (size_t i = 0; i < cards->size; ++i) {
                c1 = rand() % cards->size;
                c2 = rand() % cards->size;

                tmp = cards->cards[c1];
                cards->cards[c1] = cards->cards[c2];
                cards->cards[c2] = tmp;
        }

        return;
}

void sort(cards_t* cards) {
        qsort(cards->cards, cards->size, sizeof(card_t), cmp_cards);
}

card_t deal(cards_t* cards) {
        card_t card;

        card = card_default;
        if (cards->size > 0) {
                card = cards->cards[cards->size];
                cards->size--;
        }

        return card;
}

void add_card(cards_t* cards, card_t card) {
        cards->cards[cards->size] = card;
        cards->size++;
        
        return; 
}

card_t remove_card(cards_t* cards, enum remove_order order) {
        card_t card;
        size_t idx;
 
        idx = 0;
        if (order == FIRST) {
                idx = 0;
        } else if (order == LAST) {
                idx = cards->size - 1;
        }

        card = cards->cards[idx];
        cards->cards[idx] = card_default;
        cards->size--;

        return card;
}

