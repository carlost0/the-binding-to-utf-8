#include "enemies.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int square(int n) {return n * n;}

void attack(scene_t * scene, enemy_t enemy, player_t * player) {
    srand(time(0));
    
    if ((rand() % 101) < enemy.attack.probabillity)return;
    if (!enemy.attack.is_active) return;
    if (enemy.attack.time > ATTACK_FRAMES_MAX) return;
        enemy.attack.time++;
        // euclidian distance
        int distance = round(
            sqrt(
                square(enemy.atr.pos.x - player->atr.pos.x) +
                square(enemy.atr.pos.y - player->atr.pos.y)
            )
        );
        if (((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) + enemy.attack.distance < scene->size.w) && 
            ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) + enemy.attack.distance < scene->size.h) &&
            ((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) - enemy.attack.distance > 0) &&
            ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) - enemy.attack.distance > 0)) {

            circle_t attack_circ = {
                .radius = enemy.attack.distance,
                .sprite = 'A',
                .pos = {
                    .x = enemy.atr.pos.x + round(enemy.atr.size.w / 2),
                    .y = enemy.atr.pos.y + round(enemy.atr.size.h / 2),
                }
            };
            draw_circle(scene, attack_circ);
        } else return;
        if (distance < enemy.attack.distance) player->hp -= enemy.attack.strength;
}

void init_enemy(scene_t scene, enemy_t * enemy) {
    srand(time(0));
    enemy->atr.size.w              = rand() % (3 - 2 + 1) + 2;
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
}

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player) {
    draw_enemy(scene, *enemy);
    attack(scene, *enemy, player);
}

void draw_enemy(scene_t * scene, enemy_t enemy) {
    draw_rectangle(scene, enemy.hitbox);
    draw_rectangle(scene, enemy.atr);
}
