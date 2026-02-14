#ifndef GAME_H_
#define GAME_H_

#include "defs.h"

#define PLAYER_NAME_MAX_SIZE 32

// Structure implementations

struct player{
        const char*     name;
        cards_t*        hand;      
};

static struct player player_default = { NULL, NULL };

typedef struct player player_t;

struct game{
        player_t*       players[B_STD_NUM_PLAYERS];
        cards_t*        deck;      
};

static struct game game_default = { NULL, NULL };

typedef struct game game_t;

// Player function declarations
player_t*       init_player(const char*);
void            free_player(player_t*);
const char*     player_info(player_t*);

// Game function declarations
game_t*         init_game(player_t*[B_STD_NUM_PLAYERS], cards_t*);
void            free_game(game_t*);
const char*     game_info(game_t*);
void            play(game_t*);

#endif
