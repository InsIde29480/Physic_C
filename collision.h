#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int speed;
    int __UP;
    int __DOWN;
    int __LEFT;
    int __RIGHT;
} _Rectangle;

extern _Rectangle *__ARRAY_RECTANGLES;
extern int __RECTANGLES_COUNT;
extern int __RECTANGLES_CAPACITY;

void bouncingCube(_Rectangle *rectangle, SDL_Window *window, int speed);
void checkOverlapse();
void addRectangle(_Rectangle **rectangle_array, SDL_Window *window);

#endif // COLLISION_H