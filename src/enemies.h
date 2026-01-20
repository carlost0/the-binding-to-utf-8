#include "../aschii/lib/utils.h"
#include "player.h"
#include <stdbool.h>
#ifndef ENEMIES_H
#define ENEMIES_H

#define ATTACK_FRAMES_MAX 10
//hello!
typedef struct {
    int strength;
    int distance;
    int probabillity;
    int time;
    bool is_active;
} attack_t;

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    attack_t attack;
    point_t velocity;
    point_t speed;
    int hp;
    int gold;
} enemy_t;

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player);
void init_enemy(scene_t scene, enemy_t * enemy);
void draw_enemy(scene_t * scene, enemy_t enemy);

#endif //ENEMIES_H
