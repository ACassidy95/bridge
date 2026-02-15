#ifndef DEFS_H_
#define DEFS_H_

// Define some standard bridge constants
#define B_STD_NUM_PLAYERS       4
#define B_STD_DECK_SIZE         52
#define B_STD_HAND_SIZE         13
#define B_STD_MIN_CARD_RANK     2
#define B_STD_MAX_CARD_RANK     14
#define B_STD_MAX_BID_OVER      7

// Declare basic structures
enum    suit;
enum    bid_suit;

struct  bid;
struct  bid_table;
struct  player_bid;
struct  card;
struct  cards;
struct  game;
struct  player;

#endif

