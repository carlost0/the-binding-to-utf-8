#ifndef PLAYER_H_
#define PLAYER_H_
#include "../aschii/lib/utils.h"
#include <stdbool.h>

#define PLAYER_HEIGHT 2
#define PLAYER_WIDTH  2

#define PLAYER_I_FRAMES 15

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    point_t velocity;
    point_t speed;
    int attack_timer;
    int hp;
    int gold;
    bool invincible;
} player_t;

void draw_player(scene_t * scene, player_t player);
void init_player(player_t * player);
void handle_player(scene_t * scene, player_t * player, char input);
void move_player(scene_t scene, char input, player_t * player);

#endif //PLAYER_H_
