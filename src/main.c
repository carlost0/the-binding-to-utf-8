// main.c
// cc -std=c99 -lm -lpthread -D_POSIX_C_SOURCE=200809L src/main.c aschii/lib/utils.c aschii/lib/keyboard.c aschii/include/cbmp.c -o game
#include "../aschii/include/cbmp.h"
#include "../aschii/lib/utils.h"
#include "../aschii/lib/keyboard.h"
#include "player.h"
#include "enemies.h"
#include <pthread.h>
#include <stdlib.h>

#define FPS 30
#define SCREEN_HEIGHT 36
#define SCREEN_WIDTH  74

int main(void) {
	scene_t scene = {
		.size = {SCREEN_WIDTH, SCREEN_HEIGHT},
		.screen = {}
	};

    player_t player;
    enemy_t enemy;

    init_player(&player);
    init_enemy(scene, &enemy);
	init_scene(&scene);
	INIT_INPUT	

	while (input != 'q') {
		GET_INPUT
        draw_player_stats(&scene, player);

        handle_enemy(&scene, &enemy, &player);
        draw_player(&scene, player);
        draw_screen_borders(&scene);
        move_player(scene, input, &player);

        print_scene(&scene);
        clear_scene(&scene);
		delay(1000000 / FPS);
	}

	END_INPUT
	free(scene.screen);
}
