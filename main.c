#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "cards.h"
#include "game.h"

int main() {
        game_t*         game;
        deck_t*         deck;
        player_t*       players[4];

        printf("Hello Bridge Players!\n");
        
        deck = init_deck();
        shuffle_deck(deck);
        for(size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                player_t* p;

                p = init_player("Example");
                players[i] = p;
        }

        game = init_game(players, deck);
        
        free_deck(deck);
        for(size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                free(players[i]);
                players[i] = NULL;
        }
        deck = NULL;

        return 0;
}
