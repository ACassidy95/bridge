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
        char            suit;
};

static struct card card_default = { 0, '0' };

typedef struct card card_t;

struct cards {
        card_t*         cards;
        size_t          capacity;
        size_t          size;
};

static struct cards cards_default = { NULL, 0, 0 };

typedef struct cards cards_t;

enum remove_order {
        FIRST,
        LAST
};

// Function signatures
// Card functions
card_t          init_card(uint8_t, char);
const char*     card_info(card_t);

// Card collection functions
// Providing interfaces for all deck and hand functions
cards_t*        init_card_collection(size_t);
void            free_card_collection(cards_t*);
const char*     card_collection_info(cards_t*);
void            create_deck(cards_t*);
void            add_card(cards_t*, card_t);
card_t          remove_card(cards_t*, enum remove_order);
void            shuffle(cards_t*);

#endif

