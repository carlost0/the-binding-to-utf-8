#include "rooms.h"
#include <stdlib.h>
#include <strings.h>
#include <time.h>

room_t init_room(box_t size) {
    room_t room = {
        .scene = {
            .size = size
        },
        .enemies = {
            .size = 2
        },
        .doors = {
            .size = 1
        }
    };

    init_scene(&room.scene);

    room.enemies.content = (enemy_t *) malloc(sizeof(enemy_t) * room.enemies.size);
    for (int i = 0; i < room.enemies.size; i++) {
        init_enemy(room.scene, &room.enemies.content[i], time(0) + i);
    }

    return room;
}
