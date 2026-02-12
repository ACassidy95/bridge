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

void free_player(player_t* player) {
        free_hand(player->hand);
        player->hand = NULL;

        free((char*)player->name);
        player->name = NULL;

        free(player);

        return
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

        buffer = (char*)malloc(bufflen);
        if (buffer == NULL) {
                return NULL;
        }

        snprintf(buffer, buff_len, "Player: %s | %s", name, hinfo)

        return buffer;
} 
