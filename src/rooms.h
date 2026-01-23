#ifndef ROOMS_H_
#define ROOMS_H_

#include "enemies.h"
#include "../aschii/lib/utils.h"

typedef enum {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} anchor_t;

typedef struct {
    void * content;
    int size;
} vector_t;

typedef struct {
    rectangle_t box;
    void * in;
    void * out;
} door_t;

typedef struct {
    scene_t scene;
    vector_t enemies;
    vector_t doors;
} room_t;

room_t init_room(box_t size);
door_t init_door(box_t size, anchor_t anchor);
void   draw_room(room_t * room);

#endif //ROOMS_H_
