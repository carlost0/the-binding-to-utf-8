#include "enemies.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int square(int n) {return n * n;}

int enemy_sizes[3] = {2, 2, 4};

bool check_inbounds(scene_t scene, enemy_t enemy) {
    return
        ((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) + enemy.attack.distance < scene.size.w) && 
        ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) + enemy.attack.distance < scene.size.h) &&
        ((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) - enemy.attack.distance > 0) &&
        ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) - enemy.attack.distance > 0);
}
void attack_circ(scene_t * scene, enemy_t enemy, player_t * player) {
    // euclidian distance
    int distance = round(
        sqrt(
            square(enemy.atr.pos.x - player->atr.pos.x) +
            square(enemy.atr.pos.y - player->atr.pos.y)
        )
    );

    // check if attack circle is in bounds

    circle_t attack_circ = {
        .radius = enemy.attack.distance,
        .sprite = 'c',
        .pos = {
            .x = enemy.atr.pos.x + round(enemy.atr.size.w / 2),
            .y = enemy.atr.pos.y + round(enemy.atr.size.h / 2),
        }
    };
    draw_circle(scene, attack_circ);

    if (distance < enemy.attack.distance) player->hp -= enemy.attack.strength;
}

void attack_square(scene_t * scene, enemy_t enemy, player_t * player) {
    rectangle_t attack_box = {
        .sprite = 's',
        .pos = {
            .x = enemy.atr.pos.x - enemy.atr.size.w,
            .y = enemy.atr.pos.y - enemy.atr.size.h
        },
        .size = {
            .w = enemy.attack.distance * 2,
            .h = enemy.attack.distance * 2
        }
    };

    draw_rectangle(scene, attack_box);

    if (check_collision(attack_box, player->hitbox)) player->hp -= enemy.attack.strength;
}

void attack_cross(scene_t * scene, enemy_t enemy, player_t * player) {
    rectangle_t top_box =  {
        .sprite = '|',
        .pos = {
            .x = enemy.atr.pos.x,
            .y = enemy.atr.pos.y - enemy.attack.distance,
        },
        .size = {
            .w = enemy.atr.size.w,
            .h = enemy.attack.distance
        }
    };

    rectangle_t bottom_box =  {
        .sprite = '|',
        .pos = {
            .x = enemy.atr.pos.x,
            .y = enemy.atr.pos.y + enemy.atr.size.h,
        },
        .size = {
            .w = enemy.atr.size.w,
            .h = enemy.attack.distance
        }
    };

    rectangle_t left_box =  {
        .sprite = '-',
        .pos = {
            .x = enemy.atr.pos.x - enemy.attack.distance,
            .y = enemy.atr.pos.y
        },
        .size = {
            .w = enemy.attack.distance,
            .h = enemy.atr.size.h
        }
    };

    rectangle_t right_box =  {
        .sprite = '-',
        .pos = {
            .x = enemy.atr.pos.x + enemy.atr.size.w,
            .y = enemy.atr.pos.y
        },
        .size = {
            .w = enemy.attack.distance,
            .h = enemy.atr.size.h
        }
    };

    draw_rectangle(scene, top_box);
    draw_rectangle(scene, bottom_box);
    draw_rectangle(scene, right_box);
    draw_rectangle(scene, left_box);

    if (check_collision(top_box, player->hitbox) || check_collision(right_box, player->hitbox) ||
        check_collision(bottom_box, player->hitbox) || check_collision(left_box, player->hitbox))
        player->hp -= enemy.attack.strength;
}
void init_enemy(scene_t scene, enemy_t * enemy) {
    srand(time(0));
    enemy->atr.size.w              = enemy_sizes[rand() % 3];
    enemy->atr.size.h              = enemy->atr.size.w;
    enemy->atr.pos.x               = rand() % ((scene.size.w - 10) - 10 + 1) + 1;
    enemy->atr.pos.y               = rand() % ((scene.size.h - 10) - 10 + 1) + 1;
    enemy->atr.sprite              = 'e';

    enemy->hitbox.size.w           = enemy->atr.size.w;
    enemy->hitbox.size.h           = enemy->atr.size.w;
    enemy->hitbox.pos.x            = enemy->atr.pos.x;
    enemy->hitbox.pos.y            = enemy->atr.pos.y;
    enemy->hitbox.sprite           = ' ';
    
    enemy->speed.x                 = floor(5 / enemy->atr.size.w);
    enemy->speed.y                 = ceil(enemy->speed.x / 2);
    enemy->hp                      = ceil(3 * enemy->atr.size.w);
    enemy->gold                    = ceil(enemy->hp / 2);
    enemy->attack.strength         = ceil(enemy->hp / 2);
    enemy->attack.distance         = ceil(enemy->attack.strength);
    enemy->attack.probabillity     = (enemy->atr.size.w * (100 / 3));
    enemy->attack.type             = CROSS;//rand() % 4;
}

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player) {
    srand(time(NULL));
    
    // handle enemy attacks
    if (rand() % 101 <= enemy->attack.probabillity && !enemy->attack.is_active) enemy->attack.is_active = true;

    if (enemy->attack.is_active && check_inbounds(*scene, *enemy)) {
        enemy->attack.time++;
        switch (enemy->attack.type) {
            case CIRC:
                attack_circ(scene, *enemy, player);
                break;
            case SQUARE:
                attack_square(scene, *enemy, player);
                break;
            case CROSS:
                attack_cross(scene, *enemy, player);
                break;
        }
    }

    if (enemy->attack.time >= ATTACK_FRAMES_MAX) {
        enemy->attack.is_active = false;
        enemy->attack.time = 0;
    }

    draw_enemy(scene, *enemy);
}

void draw_enemy(scene_t * scene, enemy_t enemy) {
    draw_rectangle(scene, enemy.hitbox);
    draw_rectangle(scene, enemy.atr);
}
