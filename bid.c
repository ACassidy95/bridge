#include "bid.h"

bid_t init_bid(uint8_t rank, bid_suit_t suit) {
        bid_t b;

        b.rank = rank;
        b.suit = suit;

        return b;
}

const char* bid_info(bid_t bid) {
        return "\0";
}

player_bid_t init_player_bid(uint8_t rank, bid_suit_t suit, bool pass) {
        bid_t           b;
        player_bid_t    p;

        p.bid.rank = rank;
        p.bid.suit = suit;
        p.pass = pass;

        return p;
}

const char* player_bid_info(player_bid_t bid) {
        return "\0";
}

bid_table init_bid_table() {
        bid_table_t bt;
        return bt;
}

const char* bid_table_info(bid_table_t bid_table) {
        return "\0";
}
