#ifndef GAME_H_
#define GAME_H_

#include "defs.h"

// Structure implementations

struct player{
        const char*     name;
        card_t*         hand      
};

static struct player player_default = { NULL, NULL };

typedef struct player player_t;

struct game{
        player_t*       players;
        deck_t*         deck;      
};

static struct game game_default = { NULL, NULL };

typedef struct game game_t;

// Player function declarations
player_t*       init_player(const char*);
void            free_player(player_t*);
const char*     player_info(player_t*);

// Game function declarations
game_t*         init_game();
void            free_game(game_t*);
const char*     game_info(game_t*);

#endif
