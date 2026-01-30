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

    room_t not_found = { .id = -1 };

    return not_found;
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

room_t init_room(box_t size, int32_t id, int8_t enemy_amount) {
    box_t door_size_h = {
        .w = round(size.w / 4),
        .h = 2
    };

    box_t door_size_v = {
        .w = 2,
        .h = round(size.h / 4)
    };

    room_t room = {
        .scene = {
            .size = size
        },
        .enemies = {0},
        .enemy_amount = enemy_amount,
        .id = id
    };

    init_scene(&room.scene);

    for (int i = 0; i < room.enemy_amount; i++) {
        init_enemy(room.scene, &room.enemies[i], clock() + i);
    }

    return room;
}

int32_t handle_door(room_t * room, player_t * player) {
    for (int i = 0; i < 4; i++) {
        draw_rectangle(&room->scene, room->doors[i].box);

        if (!check_collision(player->hitbox, room->doors[i].box)) return room->id;

        if (room->doors[i].anchor == LEFT)      player->atr.pos.x = room->scene.size.w - 3;
        if (room->doors[i].anchor == RIGHT)     player->atr.pos.x = 3;
        if (room->doors[i].anchor == BOTTOM)    player->atr.pos.x = room->scene.size.h - 3;
        if (room->doors[i].anchor == TOP)       player->atr.pos.y = 3;

        int32_t ret = room->doors[i].out_id;
        return ret;
    }
}

int32_t handle_room(room_t * room, player_t * player, int64_t seed) {
    int32_t id;

    for (int i = 0; i < room->enemy_amount; i++) {
        handle_enemy(&room->scene, &room->enemies[i], player, seed + i);
    }

    for (int i = 0; i < 4; i++) {
        id = handle_door(room, player);
    }

    return id;
}

void draw_room_id(room_t * room, int32_t id) {
    char buf[10];
    sprintf(buf, "ROOM: %d", id);
    text_t text = {
        .str = buf,
        .pos = {1, 3}
    };
    draw_text_horizontal(&room->scene, text);
}
