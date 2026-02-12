#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cards.h"

// Card function implementations

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
                sprintf(buffer, "|ERROR|");
                break;
        }

        return buffer;
}

// Deck function implmentations

deck_t* init_deck() {
        deck_t* d;

        d = (deck_t*)malloc(sizeof(deck_t));
        if(d == NULL) {
                return NULL;
        }

        *d = deck_default;

        d->capacity = B_STD_DECK_SIZE;
        d->cards = (card_t*)malloc(sizeof(card_t) * d->capacity);
        if(d->cards == NULL) {
                return NULL;
        }

        for(size_t i = 0; i <= B_STD_MAX_CARD_RANK - B_STD_MIN_CARD_RANK; ++i) {
                for(size_t j = 0; j < sizeof(B_STD_CARD_SUITS) / sizeof(B_STD_CARD_SUITS[0]); ++j) {
                        card_t c = init_card(i + B_STD_MIN_CARD_RANK, B_STD_CARD_SUITS[j][0]);
                        size_t idx = i * (sizeof(B_STD_CARD_SUITS) / sizeof(B_STD_CARD_SUITS[0])) + j;
                        
                        d->cards[idx] = c;
                        d->size++;
                }
        }

        return d;
}

void free_deck(deck_t* deck) {
        free(deck->cards);
        deck->cards = NULL;

        free(deck);
        return;
}

const char* deck_info(deck_t* deck) {
        char* buffer;

        buffer = (char*)malloc(deck->size * CARD_INFO_BUFFER_SIZE);
        if(buffer == NULL) {
                return NULL;
        }

        for(size_t i = 0; i < deck->size; ++i) {
                const char* ci = card_info(deck->cards[i]);
                if (ci == NULL) {
                        return NULL;
                }

                strncat(buffer, ci, CARD_INFO_BUFFER_SIZE);
                free((char*)ci);
        }

        return buffer;
}

void shuffle_deck(deck_t* deck) {
        int c1, c2;
        card_t tmp;
        
        srand(time(NULL));

        for (size_t i = 0; i < deck->size; ++i) {
                c1 = rand() % deck->size;
                c2 = rand() % deck->size;

                tmp = deck->cards[c1];
                deck->cards[c1] = deck->cards[c2];
                deck->cards[c2] = tmp;
        }

        return;
}

card_t deal_card(deck_t* deck) {
        card_t card;

        card = card_default;
        if (deck->size > 0) {
                card = deck->cards[deck->size];
                deck->size--;
        }

        return card;
}

// Hand function imeplementation

hand_t init_hand() {
        hand_t*         h;
        cards_t*        c;
        
        h = (hand_t*)malloc(sizeof(hand_t));
        if (h == NULL) {
                return NULL;
        }

        c = (card_t*)malloc(sizoef(card_t) * B_STD_HAND_SIZE);
        if (c == NULL) {
                return NULL;
        }

        h->cards = c;
        h->capacity = B_STD_HAND_SIZE;
        h->size = 0;

        return h; 
}

void free_hand(hand_t* hand) {
        free(hand->cards);
        hand->cards = NULL;

        free(hand);

        return;
}

const char* hand_info(hand_t* hand) {
        char* buffer;

        buffer = (char*)malloc(hand->size * CARD_INFO_BUFFER_SIZE);
        if (buffer == NULL) {
                return NULL;
        }

        for (size_t i = 0; i < B_STD_HAND_SIZE; ++i) {
                const char* ci = card_info(hand->cards[i]);
                if (ci == NULL) {
                        return NULL;
                }

                strncat(buffer, ci, CARD_INFO_BUFFER_SIZE);
                free((char*)ci);
        }

        return buffer;        
}
