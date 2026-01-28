#ifndef PLAYER_H_
#define PLAYER_H_

#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../aschii/lib/utils.h"

#define PLAYER_HEIGHT 2
#define PLAYER_WIDTH  2

#define PLAYER_I_FRAMES 15

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    point_t velocity;
    point_t speed;
    uint8_t attack_timer;
    uint8_t hp;
    uint16_t gold;
    bool invincible;
} player_t;

void draw_player(scene_t * scene, player_t player);
void init_player(scene_t scene, player_t * player);
void handle_player(scene_t * scene, player_t * player, char input);
void move_player(scene_t scene, char input, player_t * player);

#endif //PLAYER_H_
