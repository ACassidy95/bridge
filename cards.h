#include <stdint.h>
#include "defs.h"

typedef struct card {
        uint8_t         rank;
        const char*     suit;
} card_t;

struct deck {
        card_t* cards;
        size_t  capacity;
        size_t  size;
} deck_default = { NULL, B_STD_DECK_SIZE, 0 };

typedef struct deck deck_t;

struct hand {
        card_t* cards;
        size_t capacity;
        size_t size;
} hand_default = { NULL, B_STD_HAND_SIZE, 0 };

typedef struct hand hand_t;

card_t          init_card(uint8_t, const char*);
const char*     card_info(card_t);

deck_t*         init_deck();
const char*     deck_info(deck_t*);
void            shuffle_deck(deck_t*);
card_t          deal_card(deck_t*);

hand_t*         init_hand();
const char*     hand_info(hand_t*);
void            add_card(hand_t*, card_t);
