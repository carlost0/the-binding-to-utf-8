// main.c
// cc -std=c99 -lm -lpthread -D_POSIX_C_SOURCE=200809L src/main.c aschii/lib/utils.c aschii/lib/keyboard.c aschii/include/cbmp.c -o game
#include "../aschii/include/cbmp.h"
#include "../aschii/lib/utils.h"
#include "../aschii/lib/keyboard.h"
#include "player.h"
#include "enemies.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FPS 30
#define SCREEN_HEIGHT 36
#define SCREEN_WIDTH  74
#define ENEMY_COUNT   3

int main(void) {
	scene_t scene = {
		.size = {SCREEN_WIDTH, SCREEN_HEIGHT},
		.screen = {}
	};

    player_t player;
    //enemy_t enemies[ENEMY_COUNT] = {0};  
    enemy_t * enemies = (enemy_t *) malloc(ENEMY_COUNT * sizeof(enemy_t));
    memset(enemies, 0, sizeof(enemy_t) * ENEMY_COUNT);

    init_player(&player);

    for (int i = 0; i < ENEMY_COUNT; i++){
        init_enemy(scene, &enemies[i], time(0) + i);
    }

	init_scene(&scene);
	INIT_INPUT	

	while (input != 'q') {
		GET_INPUT

        for (int i = 0; i < ENEMY_COUNT; i++){
            if (enemies[i].is_alive) handle_enemy(&scene, &enemies[i], &player, time(0) + i);
        }

        draw_screen_borders(&scene);

        handle_player(&scene, &player, input);

        print_scene(&scene);
        clear_scene(&scene);
		delay(1000000 / FPS);
	}

	END_INPUT
	free(scene.screen);
    free(enemies);
}
