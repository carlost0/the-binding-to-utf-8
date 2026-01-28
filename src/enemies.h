#ifndef ENEMIES_H_
#define ENEMIES_H_

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "player.h"
#include "../aschii/lib/utils.h"

#define ATTACK_FRAMES_MAX 10

typedef enum {
    SQUARE,
    CROSS,
    CIRC
} attack_form;

typedef struct {
    attack_form  type;
    uint8_t      strength;
    uint16_t     distance;
    uint8_t      probabillity;
    uint8_t      time;
    char         sprite;
    bool         is_active;
} attack_t;

typedef struct {
    point_t velocity;
    point_t speed;
    uint8_t probabillity;
} movement_t;

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    attack_t    attack;
    movement_t  movement;
    int8_t      hp;
    uint16_t    gold;
    bool        is_alive;
} enemy_t;

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player, int64_t seed);
void move_enemy(scene_t scene, enemy_t * enemy, player_t player);
void init_enemy(scene_t scene, enemy_t * enemy, int64_t seed);
void draw_enemy(scene_t * scene, enemy_t enemy);

#endif //ENEMIES_H_
