#include "../aschii/lib/utils.h"
#include "player.h"
#include <stdbool.h>
#ifndef ENEMIES_H_
#define ENEMIES_H_

#define ATTACK_FRAMES_MAX 10

typedef enum {
    SQUARE,
    CROSS,
    CIRC
} attack_form;

typedef struct {
    attack_form type;
    int strength;
    int distance;
    int probabillity;
    int time;
    char sprite;
    bool is_active;
} attack_t;

typedef struct {
    point_t velocity;
    point_t speed;
    int probabillity;
} movement_t;

typedef struct {
    rectangle_t atr;
    rectangle_t hitbox;
    attack_t attack;
    movement_t movement;
    int hp;
    int gold;
    bool is_alive;
} enemy_t;

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player, int seed);
void move_enemy(scene_t scene, enemy_t * enemy, player_t player);
void init_enemy(scene_t scene, enemy_t * enemy, int seed);
void draw_enemy(scene_t * scene, enemy_t enemy);

#endif //ENEMIES_H_
