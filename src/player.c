#include "player.h"

void draw_player_stats(scene_t * scene, player_t player) {
    text_t hp = {
        .pos = {1, 1},
        .str = ""
    };

    text_t gold = {
        .pos = {1, 2},
        .str = ""
    };

    char gold_tmp[50];
    char hp_tmp[50];

    sprintf(hp_tmp, "HP:   %d", player.hp);
    sprintf(gold_tmp, "GOLD: %d", player.gold);
    gold.str = gold_tmp;
    hp.str = hp_tmp;
    
    draw_text_horizontal(scene, hp);
    draw_text_horizontal(scene, gold);
}

void draw_player(scene_t * scene, player_t player) {
    draw_rectangle(scene, player.hitbox);
    draw_rectangle(scene, player.atr);
}

void init_player(scene_t scene, player_t * player) {
    player->atr.pos.x = round(scene.size.w / 2);
    player->atr.pos.y = round(scene.size.h / 2);
    player->atr.sprite = '@';
    player->atr.size.w = PLAYER_WIDTH;
    player->atr.size.h = PLAYER_HEIGHT;

    player->hitbox.pos.x = 64;
    player->hitbox.pos.y = 18;
    player->hitbox.sprite = ' ';
    player->hitbox.size.w = PLAYER_WIDTH;
    player->hitbox.size.h = PLAYER_HEIGHT;

    player->velocity.x = 0;
    player->velocity.y = 0;
    player->speed.x = 3;
    player->speed.y = 2;
    
    player->hp = 100;
    player->gold = 0;

    player->invincible = false;
}

void move_player(scene_t scene, char input, player_t * player) {
    switch (input) {
        case 'w':
            player->velocity.y = -player->speed.y;
            player->velocity.x = 0;
            break;
        case 's':
            player->velocity.y = player->speed.y;
            player->velocity.x = 0;
            break;
        case 'a':
            player->velocity.x = -player->speed.x;
            player->velocity.y = 0;
            break;
        case 'd':
            player->velocity.x = player->speed.x;
            player->velocity.y = 0;
            break;
        default:
            player->velocity.x = 0;
            player->velocity.y = 0;
            break;
    }
    
    point_t next_pos = add_points(player->atr.pos, player->velocity);

    if (!(next_pos.x <= 0 || next_pos.x + player->hitbox.size.w >= scene.size.w))
        player->atr.pos.x += player->velocity.x;
    if (!(next_pos.y <= 0 || next_pos.y + player->hitbox.size.h >= scene.size.h))
        player->atr.pos.y += player->velocity.y;

    player->hitbox.pos = player->atr.pos;
}

void handle_i_frames(player_t * player) {
    if (player->invincible) player->attack_timer++;
    if (player->attack_timer > PLAYER_I_FRAMES) {
        player->invincible = false;
        player->attack_timer = 0;
    } 
}
void handle_player(scene_t * scene, player_t * player, char input) {
    handle_i_frames(player);
    move_player(*scene, input, player);
    draw_player(scene, *player);
    draw_player_stats(scene, *player);
}
