#ifndef DEFS_H_
#define DEFS_H_

// Define some standard bridge constants
#define B_STD_NUM_PLAYERS       4
#define B_STD_DECK_SIZE         52
#define B_STD_HAND_SIZE         13
#define B_STD_MIN_CARD_RANK     2
#define B_STD_MAX_CARD_RANK     14

static const char* B_STD_CARD_SUITS[4] = {
        "CLUBS",
        "DIAMONDS",
        "HEARTS",
        "SPADES"
}

static const char* B_STD_BID_SUITS[5] = {
        "CLUBS",
        "DIAMONDS",
        "HEARTS",
        "SPADES",
        "NO TRUMP"
}

// Declare basic structures required for a bridge game
struct  card;
struct  deck;
struct  hand;
struct  player;
struct  game;

#endif
