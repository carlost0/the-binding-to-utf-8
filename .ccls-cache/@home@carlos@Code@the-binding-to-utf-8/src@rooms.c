#include "rooms.h"

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

door_t init_door(box_t size, anchor_t anchor, room_t room, int64_t out_id) {
    point_t pos;
    if (anchor == TOP) {
        pos.x = round(room.scene.size.w / 2) - round(size.w / 2);
        pos.y = room.scene.size.h;
    } else if (anchor == LEFT) {
        pos.x = 0;
        pos.y = round(room.scene.size.h / 2) - round(size.h / 2);
    } else if (anchor == BOTTOM) {
        pos.x = round(room.scene.size.w / 2) - round(size.w / 2);
        pos.y = size.h;
    } else if (anchor == RIGHT) {
        pos.x = room.scene.size.w - size.w;
        pos.y = round(room.scene.size.h / 2) - round(size.h / 2);
    }

    door_t door = {
        .box = {
            .size   = size,
            .pos    = pos,
            .sprite = 'D'
        },
        .anchor     = anchor,
        .in_id      = room.id,
        .out_id     = out_id,
    };

    return door;
}

room_t init_room(box_t size, int id) {
    box_t door_size_h = {
        .w = round(size.w / 3),
        .h = 2
    };

    box_t door_size_v = {
        .w = 2,
        .h = round(size.h / 3)
    };

    room_t room = {
        .scene = {
            .size = size
        },
        .enemies = {0},
        .enemy_amount = 1,
        .id = id
    };

    init_scene(&room.scene);

    for (int i = 0; i < room.enemy_amount; i++) {
        init_enemy(room.scene, &room.enemies[i], time(0) + i);
    }

    return room;
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
    }
    for (int i = 0; i < 4; i++) {
        handle_door(room, player, current_room_id);
    }
}

