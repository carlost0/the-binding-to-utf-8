#include "rooms.h"
#include <stdlib.h>
#include <strings.h>
#include <time.h>

room_t get_room_by_id(int32_t id, room_t * rooms, int32_t room_amount) {
    if (rooms == NULL) {
        perror("rooms array is a null pointer");
        exit(1);
    } 

    for (int i = 0; i < room_amount; i++) { 
        if (rooms->id == id) return *rooms;
        rooms++;
    }
    perror("room not found");
    exit(1);
}

room_t init_room(box_t size, int id) {
    room_t room = {
        .scene = {
            .size = size
        },
        .doors = {0},
        .enemies = {0},
        .enemy_amount = 2,
        .id = id
    };

    init_scene(&room.scene);

    for (int i = 0; i < room.enemy_amount; i++) {
        init_enemy(room.scene, &room.enemies[i], time(0) + i);
    }

    return room;
}

door_t init_door(box_t size, anchor_t anchor, room_t room_in, room_t room_out) {
    point_t pos;
    if (anchor == TOP) {
        pos.x = round(room_in.scene.size.w / 2) - round(size.w / 2);
        pos.y = room_in.scene.size.h;
    } else if (anchor == LEFT) {
        pos.x = 0;
        pos.y = round(room_in.scene.size.h / 2) - round(size.h / 2);
    } else if (anchor == BOTTOM) {
        pos.x = round(room_in.scene.size.w / 2) - round(size.w / 2);
        pos.y = size.h;
    } else if (anchor == RIGHT) {
        pos.x = room_in.scene.size.w - size.w;
        pos.y = round(room_in.scene.size.h / 2) - round(size.h / 2);
    }

    door_t door = {
        .box = {
            .size   = size,
            .pos    = pos,
            .sprite = '['
        },
        .anchor     = anchor,
        .in_id      = room_in.id,
        .out_id     = room_out.id,
    };

    return door;
}

void handle_door(room_t * room, player_t * player, int32_t * current_room_id) {
    for (int i = 0; i < 4; i++) {
        if (check_collision(player->hitbox, room->doors[i].box)) 
            current_room_id = &room->doors[i].out_id;
        draw_rectangle(&room->scene, room->doors[i].box);
    }
}

void handle_room(room_t * room, player_t * player, int64_t seed, int32_t * current_room_id) {
    for (int i = 0; i < room->enemy_amount; i++) {
        handle_enemy(&room->scene, &room->enemies[i], player, seed + i);
        draw_enemy(&room->scene, room->enemies[i]);
    };
    for (int i = 0; i < 4; i++) {
        handle_door(room, player, current_room_id);
    }
}

