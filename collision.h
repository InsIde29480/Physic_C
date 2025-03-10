#ifndef COLLISION_H
#define COLLISION_H

#include "headers.h"
#include "physic.h"

typedef struct {
    SDL_Rect rect;
    _Physic physic;
} _Rectangle;

extern _Rectangle *__ARRAY_RECTANGLES;
extern int __RECTANGLES_COUNT;
extern int __RECTANGLES_CAPACITY;

void addRectangle(SDL_Window *window);
void calculatePosition(_Rectangle *rectangle, SDL_Window *window);
void addCollision(_Rectangle *rectangle, SDL_Window *window);
void resolveCollision(_Rectangle *a, _Rectangle *b);

#endif // COLLISION_H