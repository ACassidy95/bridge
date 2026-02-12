#include <stdio.h>
#include "cards.h"
#include "game.h"

player_t init_player(const char* name) {
        player_t*       p;
        char*           pname;
        card_t*         phand;

        p = (player_t*)malloc(sizeof(player_t));
        if(p == NULL) {
                return NULL;
        }

        *p = player_default;

        pname = (char*)malloc(PLAYER_NAME_MAX_SIZE);
        if(pname == NULL) {
                return NULL;
        }

        phand = (card_t*)malloc(sizeof(card_t) * B_STD_HAND_SIZE);
        if(phand == NULL) {
                return NULL;
        }

        strncpy(pname, name, PLAYER_NAME_MAX_SIZE);
        phand = init_hand();
        
        p->name = pname;
        p->hand = phand;

        return p;
}
