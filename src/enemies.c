#include "enemies.h"

int square(int n) { return n * n; }

int random_range(int min, int max) { return rand() % (max - min + 1) + min; }

int enemy_sizes[3] = {2, 3, 3};

bool check_attack_inbounds(scene_t scene, enemy_t enemy) {
    return
        ((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) + enemy.attack.distance < scene.size.w) && 
        ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) + enemy.attack.distance < scene.size.h) &&
        ((enemy.atr.pos.x + round(enemy.atr.size.w / 2)) - enemy.attack.distance > 0) &&
        ((enemy.atr.pos.y + round(enemy.atr.size.h / 2)) - enemy.attack.distance > 0);
}

bool check_enemy_inbounds(scene_t scene, enemy_t enemy) {
    point_t next = add_points(enemy.hitbox.pos, enemy.movement.velocity);

    return 
        (next.x + enemy.hitbox.size.w < scene.size.w) &&
        (next.x > 0) &&
        (next.y + enemy.hitbox.size.h < scene.size.h) &&
        (next.y > 0);
            
}

void move_enemy(scene_t scene, enemy_t * enemy, player_t player) {
    if (enemy->atr.pos.x < player.atr.pos.x) enemy->movement.velocity.x = enemy->movement.speed.x;
    if (enemy->atr.pos.x > player.atr.pos.x) enemy->movement.velocity.x = -enemy->movement.speed.x;

    if (enemy->atr.pos.y < player.atr.pos.y) enemy->movement.velocity.y = enemy->movement.speed.y;
    if (enemy->atr.pos.y > player.atr.pos.y) enemy->movement.velocity.y = -enemy->movement.speed.y;

    if (check_enemy_inbounds(scene, *enemy)) enemy->atr.pos = add_points(enemy->movement.velocity, enemy->atr.pos);
    enemy->hitbox.pos = enemy->atr.pos;
}

void attack_circ(scene_t * scene, enemy_t enemy, player_t * player) {
    // euclidian distance
    int distance = round(
        sqrt(
            square(enemy.atr.pos.x - player->atr.pos.x) +
            square(enemy.atr.pos.y - player->atr.pos.y)
        )
    );

    circle_t attack_circ = {
        .radius = enemy.attack.distance,
        .sprite = enemy.attack.sprite,
        .pos = {
            .x = enemy.atr.pos.x + round(enemy.atr.size.w / 2),
            .y = enemy.atr.pos.y + round(enemy.atr.size.h / 2),
        }
    };
    draw_circle(scene, attack_circ);

    if (distance < enemy.attack.distance && !player->invincible) {
         player->hp -= enemy.attack.strength;
         player->invincible = true;
    }
}

void attack_square(scene_t * scene, enemy_t enemy, player_t * player) {
    rectangle_t attack_box = {
        .sprite = enemy.attack.sprite,
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

    if (check_collision(attack_box, player->hitbox) && !player->invincible) {
        player->hp -= enemy.attack.strength;
        player->invincible = true;
    } 
}

void attack_cross(scene_t * scene, enemy_t enemy, player_t * player) {
    rectangle_t top_box =  {
        .sprite = enemy.attack.sprite,
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
        .sprite = enemy.attack.sprite,
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
        .sprite = enemy.attack.sprite,
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
        .sprite = enemy.attack.sprite,
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

    if ((check_collision(top_box, player->hitbox) || check_collision(right_box, player->hitbox) ||
        check_collision(bottom_box, player->hitbox) || check_collision(left_box, player->hitbox)) &&
        !player->invincible) {
        player->hp -= enemy.attack.strength;
        player->invincible = true;
    }
}

void init_enemy(scene_t scene, enemy_t * enemy, int64_t seed) {
    srand(seed);
    enemy->is_alive                = true;

    enemy->atr.size.w              = enemy_sizes[rand() % 3];
    enemy->atr.size.h              = enemy->atr.size.w;
    enemy->atr.pos.x               = random_range(enemy->atr.size.w, scene.size.w - enemy->atr.size.w);
    enemy->atr.pos.y               = random_range(enemy->atr.size.h, scene.size.h - enemy->atr.size.h);
    enemy->atr.sprite              = '#';

    enemy->hitbox.size.w           = enemy->atr.size.w;
    enemy->hitbox.size.h           = enemy->atr.size.w;
    enemy->hitbox.pos.x            = enemy->atr.pos.x;
    enemy->hitbox.pos.y            = enemy->atr.pos.y;
    enemy->hitbox.sprite           = ' ';
    
    enemy->movement.speed.x        = 1;
    enemy->movement.speed.y        = 1;
    enemy->movement.probabillity   = 100;

    enemy->hp                      = ceil(3 * enemy->atr.size.w);
    enemy->gold                    = ceil(enemy->hp / 2);

    enemy->attack.strength         = ceil(enemy->hp / 2);
    enemy->attack.distance         = ceil(enemy->attack.strength);
    enemy->attack.probabillity     = 40;//enemy->atr.size.w * (100 / 3);
    enemy->attack.type             = enemy->atr.size.w % 2 == 0 ? rand() % 2 : (rand() % 2) + 1;
    enemy->attack.sprite           = '.';
}

void handle_enemy(scene_t * scene, enemy_t * enemy, player_t * player, int64_t seed) {
    srand(seed);
    
    // handle enemy attacks
    if (check_collision(enemy->hitbox, player->hitbox) && !player->invincible) {
        player->hp -= 3;
        player->invincible = true;
    }

    if (rand() % 101 <= enemy->attack.probabillity && !enemy->attack.is_active) enemy->attack.is_active = true;

    if (enemy->attack.is_active && check_attack_inbounds(*scene, *enemy) &&
        enemy->movement.velocity.x != 0 && enemy->movement.velocity.y != 0) {
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

    // handle movement
    enemy->movement.velocity.x = 0;
    enemy->movement.velocity.y = 0;

    if (rand() % 101 <= enemy->movement.probabillity) move_enemy(*scene, enemy, *player);
    draw_enemy(scene, *enemy);
}

void draw_enemy(scene_t * scene, enemy_t enemy) {
    draw_rectangle(scene, enemy.hitbox);
    draw_rectangle(scene, enemy.atr);
}
