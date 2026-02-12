#ifndef CARDS_H_
#define CARDS_H_

#include <stdint.h>
#include "defs.h"

// Card related constants

// Cards will be printed as "|%2d\\%2c|\0"
#define CARD_INFO_BUFFER_SIZE 8

// Structure implementations with default initialisations where necessary
struct card {
        uint8_t         rank;
        const char*     suit;
        const char*     str;
};

static struct card card_default = { 0, NULL, NULL };

typedef struct card card_t;

struct deck {
        card_t*         cards;
        size_t          capacity;
        size_t          size;
        const char*     str;
};

static struct deck deck_default = { NULL, B_STD_DECK_SIZE, 0, NULL };

typedef struct deck deck_t;

struct hand {
        card_t*         cards;
        size_t          capacity;
        size_t          size;
        const char*     str;
};

static struct hand hand_default = { NULL, B_STD_HAND_SIZE, 0, NULL };

typedef struct hand hand_t;

// Function signatures
// Card functions
card_t*         init_card(uint8_t, const char*);
void            free_card(card_t*);
const char*     card_info(card_t);

// Deck functions
deck_t*         init_deck();
void            free_deck(deck_t*);
const char*     deck_info(deck_t*);
void            shuffle_deck(deck_t*);
card_t          deal_card(deck_t*);

// Hand functions
hand_t*         init_hand();
void            free_hand(hand_t*);
const char*     hand_info(hand_t*);
void            add_card(hand_t*, card_t);

#endif

