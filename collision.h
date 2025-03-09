#ifndef COLLISION_H
#define COLLISION_H

#include "headers.h"
#include "physic.h"

typedef struct {
    SDL_Rect rect;
    int __UP;
    int __DOWN;
    int __LEFT;
    int __RIGHT;
    _Physic physic;
} _Rectangle;

extern _Rectangle *__ARRAY_RECTANGLES;
extern int __RECTANGLES_COUNT;
extern int __RECTANGLES_CAPACITY;

void addRectangle(_Rectangle **rectangle_array, SDL_Window *window);
void calculatePosition(_Rectangle *rectangle, SDL_Window *window);
void addColision(_Rectangle *rectangle, SDL_Window *window, float damping);

#endif // COLLISION_H