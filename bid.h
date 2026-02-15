#ifndef BID_H_
#define BID_H_

#include <stdbool.h>

// Bid info will be formatted in x chars as |%d%c|\0
#define BID_INFO_BUFFER_SIZE 5

// Define basic bid types
enum bid_suit {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES,
        NO_TRUMP,
        NUM_BID_SUITS
};

typedef enum bid_suit bid_suit_t;

struct bid {
        uint8_t         over;
        bid_suit_t      suit;
};

typedef struct bid bid_t;

struct player_bid {
        bid_t   bid;
        bool    pass;
};

typedef struct player_bid player_bid_t;

struct bid_table {
        bid_t*  table;
        bid_t   current_bid;
};

typedef struct bid_table bid_table_t;

// Define bidding functions
bid_t           init_bid(uint8_t, bid_suit_t);
const char*     bid_info(bid_t);

player_bid_t    init_player_bid(uint8_t, bid_suit_t, bool);
const char*     player_bid_info(player_bid_t);

bid_table_t     init_bid_table();
void            free_bid_table(bid_table_t*)
const char*     bid_table_info(bid_table_t*);

#endif

