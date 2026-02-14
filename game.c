#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "game.h"

// Game-specific helper function delcarations
void    deal_cards(cards_t*, player_t*[B_STD_NUM_PLAYERS]);

// Player functions
player_t* init_player(const char* name) {
        player_t*       p;
        char*           pname;
        cards_t*        phand;

        p = (player_t*)malloc(sizeof(player_t));
        if(p == NULL) {
                return NULL;
        }

        *p = player_default;

        pname = (char*)malloc(PLAYER_NAME_MAX_SIZE);
        if(pname == NULL) {
                return NULL;
        }
        strncpy(pname, name, PLAYER_NAME_MAX_SIZE);
        
        phand = init_card_collection(B_STD_HAND_SIZE);
        if(phand == NULL) {
                return NULL;
        }

        p->name = pname;
        p->hand = phand;

        return p;
}

void free_player(player_t* player) {
        free_card_collection(player->hand);
        player->hand = NULL;

        free((char*)player->name);
        player->name = NULL;

        free(player);

        return;
}

const char* player_info(player_t* player) {
        char*           buffer;
        const char*     hinfo;
        const char*     name;
        size_t          buff_len;

        name = player->name;
        hinfo = card_collection_info(player->hand);

        // +4 for additional hardcoded string separator and +1 for null terminator
        buff_len = strlen(name) + strlen(hinfo) + 4 + 1;

        buffer = (char*)malloc(buff_len);
        if (buffer == NULL) {
                return "\0";
        }

        snprintf(buffer, buff_len, "%s | %s\n", name, hinfo);

        return buffer;
}

// Game function implementations
game_t* init_game(player_t* players[B_STD_NUM_PLAYERS], cards_t* deck) {
        game_t* g;

        g = (game_t*)malloc(sizeof(game_t));
        if (g == NULL) {
                return NULL;
        } 
        *g = game_default;
        
        for(size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                g->players[i] = players[i];
        }
        g->deck = deck;

        return g;
}

void free_game(game_t* game) {
        for(size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                free_player(game->players[i]);
                game->players[i] = NULL;
        }
        
        free_card_collection(game->deck);
        game->deck = NULL;

        free(game);

        return;
}

const char* game_info(game_t* game) {
        char*   buffer;
        size_t  buff_len;

        buff_len = 0;
        for (size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                const char* pi = player_info(game->players[i]);
                if (strncmp(pi, "\0", 1) == 0) {
                        return "\0";
                }
 
                buff_len += strlen(pi);
                free((char*)pi);
                pi=NULL;
        }
        buff_len += 1;

        buffer = (char*)malloc(buff_len);
        if (buffer == NULL) {
                return "\0";
        }

        for (size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                const char* pi = player_info(game->players[i]);
                if (strncmp(pi, "\0", 1) == 0) {
                        free(buffer);
                        return "\0";
                }
 
                strncat(buffer, pi, strlen(pi)); 
                free((char*)pi);
                pi=NULL;
        }
        buffer[buff_len] = '\0';

        return buffer;
}

void play(game_t* game) {
        shuffle(game->deck);
        deal_cards(game->deck, game->players);

        const char* ci = game_info(game);
        printf("%s\n", ci);

        return;
}

void deal_cards(cards_t* deck, player_t* players[B_STD_NUM_PLAYERS]) {
        enum remove_order order = LAST;

        if (deck->size != B_STD_DECK_SIZE) {
                printf("I can't deal, cards are missing!\n");
                return;
        }

        for (size_t i = 0; i < B_STD_DECK_SIZE; ++i) {
                card_t c = remove_card(deck, order);
                add_card(players[i % B_STD_NUM_PLAYERS]->hand, c);
        }
}

