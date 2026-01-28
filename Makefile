default:
	cc -std=c99 -lm -lpthread -D_POSIX_C_SOURCE=200809L src/main.c src/player.c src/enemies.c src/rooms.c aschii/lib/utils.c aschii/lib/keyboard.c aschii/include/cbmp.c -o game
asm:
	cc -std=c99 -lm -lpthread -D_POSIX_C_SOURCE=200809L -O2 -S -fverbose-asm src/main.c src/player.c src/enemies.c src/rooms.c aschii/lib/utils.c aschii/lib/keyboard.c aschii/include/cbmp.c
