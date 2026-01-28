#ifndef ROOMS_H_
#define ROOMS_H_

#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "enemies.h"
#include "player.h"
#include "../aschii/lib/utils.h"

typedef enum {
    TOP,
    LEFT,
    BOTTOM,
    RIGHT
} anchor_t;

typedef struct {
    rectangle_t box;
    int32_t     in_id;
    int32_t     out_id;
    anchor_t    anchor;
} door_t;

typedef struct {
    scene_t     scene;
    enemy_t     enemies[20];
    door_t      doors[4];
    int8_t      enemy_amount;
    int32_t     id;
} room_t;

room_t init_room(box_t size, int id);
door_t init_door(box_t size, anchor_t anchor, room_t room_in, room_t room_out);
void   handle_room(room_t * room, player_t * player, int64_t seed, int32_t * current_room_id);
void   handle_door(room_t * room, player_t * player, int32_t * current_room_id);
room_t get_room_by_id(int32_t id, room_t * rooms, int32_t room_amount);

#endif //ROOMS_H_
