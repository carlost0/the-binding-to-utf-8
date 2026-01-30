// main.c
// cc -std=c99 -lm -lpthread -D_POSIX_C_SOURCE=200809L src/main.c aschii/lib/utils.c aschii/lib/keyboard.c aschii/include/cbmp.c -o game
#include "../aschii/include/cbmp.h"
#include "../aschii/lib/utils.h"
#include "../aschii/lib/keyboard.h"
#include "player.h"
#include "enemies.h"
#include "rooms.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define FPS           30
#define SCREEN_HEIGHT 36
#define SCREEN_WIDTH  74
#define ENEMY_COUNT   3

int32_t room_id_sum(room_t * rooms, int32_t room_amount) {
    int32_t sum = 0;

    for (int i = 0; i < room_amount; i++) sum += rooms[i].id;

    return sum;
}
int main(void) {
	box_t room_size = {SCREEN_WIDTH, SCREEN_HEIGHT};
	box_t door_vert_size = {3, round(SCREEN_HEIGHT / 3)};
	box_t door_hori_size = {round(SCREEN_WIDTH / 3), 3};
    //test();
    int32_t room_id = 0;
    int32_t old_room_id = 0;
    int32_t room_amount = 2;

    room_t * rooms = (room_t *) malloc(sizeof(room_t) * room_amount);

    for (int i = 0; i < room_amount; i++) {
        rooms[i] = init_room(room_size, i, i + 1);
    }

    rooms[0].doors[0] = init_door(door_vert_size, RIGHT, rooms[0], 1);
    rooms[1].doors[0] = init_door(door_vert_size, LEFT, rooms[1], 0);
    room_t room;

    player_t player;

    room = get_room_by_id(room_id, rooms, room_amount);
    init_player(room.scene, &player);

	INIT_INPUT	

	while (input != 'q') {
		GET_INPUT

        draw_screen_borders(&room.scene);

        old_room_id = room_id;
        room_id     = handle_room(&room, &player, time(0));
        draw_room_id(&room, room_id);

        if (room_id != old_room_id)
            room = get_room_by_id(room_id, rooms, room_amount);

        if (room.id == -1) {
            room_amount++;
            room.id = 0;
            rooms = (room_t *) malloc(sizeof(room_t) * room_amount);
            rooms[room_amount] = init_room(room_size, room_id_sum(rooms, room_amount) + 1, room_amount);
        } 

        handle_player(&room.scene, &player, input);

        print_scene(&room.scene);
        clear_scene(&room.scene);
		delay(1000000 / FPS);
	}

	END_INPUT
	free(room.scene.screen);
}
