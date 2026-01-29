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

void test() {
    box_t size = {10, 10};
    room_t * rooms = (room_t *) malloc(3 * sizeof(room_t));
    for (int i = 0; i < 3; i++) {
        rooms[i] = init_room(size, i);
        printf("id at index %d: %d\n", i, rooms[i].id);
    }

    room_t t_room = get_room_by_id(2, rooms, 3);
    printf("found room id: %d\nexpected room id: 2", t_room.id);
}

int main(void) {
	box_t size = {SCREEN_WIDTH, SCREEN_HEIGHT};
    //test();
    int32_t room_id = 0;
    int32_t room_amount = 1;

    room_t * rooms = (room_t *) malloc(sizeof(room_t) * room_amount);

    for (int i = 0; i < room_amount; i++) {
        rooms[i] = init_room(size, i);
    }

    room_t room;


    player_t player;


    room = get_room_by_id(room_id, rooms, room_amount);
    init_player(room.scene, &player);

	INIT_INPUT	

	while (input != 'q') {
		GET_INPUT
        draw_screen_borders(&room.scene);

        handle_room(&room, &player, time(0), &room_id);
        handle_player(&room.scene, &player, input);

        print_scene(&room.scene);
        clear_scene(&room.scene);
		delay(1000000 / FPS);
	}

	END_INPUT
	free(room.scene.screen);
}
