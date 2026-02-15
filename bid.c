#include <stdlib.h>
#include "bid.h"
#include "cards.h"

bid_t init_bid(uint8_t rank, bid_suit_t suit) {
        bid_t b;

        b.rank = rank;
        b.suit = suit;

        return b;
}

const char* bid_info(bid_t bid) {
        char*           buffer;

        buffer = (char*)malloc(BID_INFO_BUFFER_SIZE);
        if (buffer == NULL) {
                return NULL;
        }

        snprintf(buffer, BID_INFO_BUFFER_SIZE, "|%d%c|\0", b.rank, suit_info(b.suit));

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
        bid_table_t     bt;
        size_t          table_size;

        table_size = sizeof(bid_t) * (suit_t)NUM_SUITS * B_STD_MAX_BID_RANK;
        bt.table = (bid_t*)malloc(table_size);

        for (size_t i = 0; i < B_STD_MAX_BID; ++i) {
                for (size_t j = 0; j < (suit_t)NUM_SUITS; ++j) {
                        bid_t   bid = init_bid(i, (suit_t)j);
                        size_t  idx = (i + 1) * (suit_t)NUM_SUITS + (suit_t)j;

                        bt.table[idx] = bid;
                }
        }

        return bt;
}

void free_bid_table(bid_table_t* bid_table) {
        free(bid_table->table);
        bid_table->table = NULL;

        return;
}

const char* bid_table_info(bid_table_t* bid_table) {
        return "\0";
}
