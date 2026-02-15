#include <stdio.h>
#include <stdlib.h>
#include "decls.h"
#include "cards.h"
#include "game.h"

int main() {
        game_t*         game;
        cards_t*        deck;
        player_t*       players[4];
        const char*     gi;

        printf("Hello Bridge Players!\n");
        
        deck = init_card_collection(B_STD_DECK_SIZE);
        create_deck(deck);
        for (size_t i = 0; i < B_STD_NUM_PLAYERS; ++i) {
                player_t* p;

                p = init_player("Example");
                players[i] = p;
        }

        game = init_game(players, deck);
        
        printf("Let's Begin!\n");
        play(game);

        free_game(game);
        game = NULL;

        return 0;
}
