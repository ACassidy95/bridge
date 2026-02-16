#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bid.h"

bid_t init_bid(uint8_t over, bid_suit_t suit)
{
        bid_t b;

        b.over = over;
        b.suit = suit;

        return b;
}

const char* bid_info(bid_t bid)
{
        char*           buffer;

        buffer = (char*)malloc(BID_INFO_BUFFER_SIZE);
        if (buffer == NULL)
                return NULL;

        snprintf(buffer, BID_INFO_BUFFER_SIZE, \
		 "|%d%c|\0", bid.over, bid_suit_info(bid.suit));

        return buffer;
}

const char bid_suit_info(bid_suit_t suit)
{
        switch (suit) {
        case B_CLUBS:
		return 'C';
        case B_DIAMONDS:
		return 'D';
        case B_HEARTS:
		return 'H';
        case B_SPADES:
		return 'S';
        case B_NO_TRUMP:
		return 'N';
        default:
		return '\\';
        }
}

player_bid_t init_player_bid(uint8_t over, bid_suit_t suit, bool pass)
{
        bid_t           b;
        player_bid_t    p;

        p.bid.over = over;
        p.bid.suit = suit;
        p.pass = pass;

        return p;
}

const char* player_bid_info(player_bid_t bid)
{
        return "\0";
}

bid_table_t init_bid_table()
{
        bid_table_t     bt;
        size_t          bt_size;

        bt_size = sizeof(bid_t) * \
		(bid_suit_t)NUM_BID_SUITS * B_STD_MAX_BID_OVER;
        bt.table = (bid_t*)malloc(bt_size);
        bt.table_size = 0;

        for (size_t i = 0; i < B_STD_MAX_BID_OVER; ++i) {
                for (size_t j = 0; j < (bid_suit_t)NUM_BID_SUITS; ++j) {
                        bid_t   bid = init_bid(i, (bid_suit_t)j);
                        size_t  idx = (i + 1) * (bid_suit_t)NUM_BID_SUITS \
				      + (bid_suit_t)j;

                        bt.table[idx] = bid;
                        bt.table_size++;
                }
        }

        return bt;
}

void free_bid_table(bid_table_t* bid_table)
{
        free(bid_table->table);
        bid_table->table = NULL;

        return;
}

const char* bid_table_info(bid_table_t* bid_table)
{
        char*   buffer;
        size_t  buff_len;

        buff_len = bid_table->table_size * BID_INFO_BUFFER_SIZE + 1;
        buffer = (char*)malloc(buff_len);
        if (buffer == NULL)
                return NULL;

        for (size_t i = 0; i < bid_table->table_size; ++i) {
                const char* bi = bid_info(bid_table->table[i]);
                if (bi == NULL)
                        return NULL;

                strncat(buffer, bi, BID_INFO_BUFFER_SIZE);
                free((char*)bi);
        }
        buffer[buff_len - 1] = '\0';

        return buffer;
}

