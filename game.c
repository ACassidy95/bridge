#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "game.h"

player_t* init_player(const char* name) {
        player_t*       p;
        char*           pname;
        hand_t*         phand;

        p = (player_t*)malloc(sizeof(player_t));
        if(p == NULL) {
                return NULL;
        }

        *p = player_default;

        pname = (char*)malloc(PLAYER_NAME_MAX_SIZE);
        if(pname == NULL) {
                return NULL;
        }

        phand = (hand_t*)malloc(sizeof(hand_t) * B_STD_HAND_SIZE);
        if(phand == NULL) {
                return NULL;
        }

        strncpy(pname, name, PLAYER_NAME_MAX_SIZE);
        phand = init_hand();
        
        p->name = pname;
        p->hand = phand;

        return p;
}

void free_player(player_t* player) {
        free_hand(player->hand);
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
        hinfo = hand_info(player->hand);

        // +11 for additional hardcoded string sections
        buff_len = strlen(name) + strlen(hinfo) + 1 + 11;

        buffer = (char*)malloc(buff_len);
        if (buffer == NULL) {
                return NULL;
        }

        snprintf(buffer, buff_len, "Player: %s | %s", name, hinfo);

        return buffer;
}

// Game function implementations


game_t* init_game(player_t* players[B_STD_NUM_PLAYERS], deck_t* deck) {
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
        
        free_deck(game->deck);
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
                if (pi == NULL) {
                        return NULL;
                }
                
                buff_len += strlen(pi);
                free((char*)pi);
        }
        buff_len += 1;

        buffer = (char*)malloc(buff_len);
        if (buffer == NULL) {
                return NULL;
        }

        for (size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                const char* pi = player_info(game->players[i]);
                if (pi == NULL) {
                        return NULL;
                }
                
                strncat(buffer, pi, strlen(pi));
                free((char*)pi);
        }
        buffer[buff_len] = '\0';

        return buffer;
}

