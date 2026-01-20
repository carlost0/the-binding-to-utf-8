#include "../aschii/lib/utils.h"
#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_HEIGHT 2
#define PLAYER_WIDTH  2

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    point_t velocity;
    point_t speed;
    int hp;
    int gold;
} player_t;

void draw_player(scene_t * scene, player_t player);
void draw_player_stats(scene_t * scene, player_t player);
void init_player(player_t * player);
void handle_player(char input);
void move_player(scene_t scene, char input, player_t * player);

#endif //PLAYER_H
