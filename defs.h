#ifndef DEFS_H_
#define DEFS_H_

// Define some standard bridge constants
#define B_STD_NUM_PLAYERS       4
#define B_STD_DECK_SIZE         52
#define B_STD_HAND_SIZE         13
#define B_STD_MIN_CARD_RANK     2
#define B_STD_MAX_CARD_RANK     14

// Standad Bridge suits in order of value increasing
static const char* B_STD_CARD_SUITS[4] = {
        "CLUBS",
        "DIAMONDS",
        "HEARTS",
        "SPADES"
};

// Standard Bride bids in order of value increasing
static const char* B_STD_BID_SUITS[5] = {
        "CLUBS",
        "DIAMONDS",
        "HEARTS",
        "SPADES",
        "NO TRUMP"
};

// Declare basic structures
enum    suit;
struct  card;
struct  cards;
struct  player;
struct  game;

#endif
