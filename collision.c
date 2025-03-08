#include "collision.h"

_Rectangle *__ARRAY_RECTANGLES = NULL;
int __RECTANGLES_COUNT = 0;
int __RECTANGLES_CAPACITY = 0;

void bouncingCube(_Rectangle *rectangle, SDL_Window *window, int speed) {
    if (rectangle->__RIGHT == 1 && (rectangle->rect.x + rectangle->rect.w) >= SDL_GetWindowSurface(window)->w) {
        rectangle->__RIGHT = 0;
        rectangle->__LEFT = 1;
    } else if (rectangle->__LEFT == 1 && rectangle->rect.x <= 0) {
        rectangle->__LEFT = 0;
        rectangle->__RIGHT = 1;
    }

    // Move on X axis
    if (rectangle->__RIGHT == 1) {
        rectangle->rect.x += speed;
    } else if (rectangle->__LEFT == 1) {
        rectangle->rect.x -= speed;
    }

    // Check for bouncing on Y axis
    if (rectangle->__DOWN == 1 && (rectangle->rect.y + rectangle->rect.h) >= SDL_GetWindowSurface(window)->h) {
        rectangle->__DOWN = 0;
        rectangle->__UP = 1;
    } else if (rectangle->__UP == 1 && rectangle->rect.y <= 0) {
        rectangle->__UP = 0;
        rectangle->__DOWN = 1;
    }

    // Move on Y axis
    if (rectangle->__DOWN == 1) {
        rectangle->rect.y += speed;
    } else if (rectangle->__UP == 1) {
        rectangle->rect.y -= speed;
    }
}

void checkOverlapse(_Rectangle **rectangle_array) {
    for (int i = 0; i < __RECTANGLES_COUNT; i++) {
        for (int j = i + 1; j < __RECTANGLES_COUNT; j++) {
            if ((*rectangle_array)[i].rect.x < ((*rectangle_array)[j].rect.x + (*rectangle_array)[j].rect.w) &&
                ((*rectangle_array)[i].rect.x + (*rectangle_array)[i].rect.w) > (*rectangle_array)[j].rect.x &&
                (*rectangle_array)[i].rect.y < ((*rectangle_array)[j].rect.y + (*rectangle_array)[j].rect.h) &&
                ((*rectangle_array)[i].rect.y + (*rectangle_array)[i].rect.h) > (*rectangle_array)[j].rect.y) {
                (*rectangle_array)[i].__DOWN = !(*rectangle_array)[i].__DOWN;
                (*rectangle_array)[i].__UP = !(*rectangle_array)[i].__UP;
                (*rectangle_array)[i].__LEFT = !(*rectangle_array)[i].__LEFT;
                (*rectangle_array)[i].__RIGHT = !(*rectangle_array)[i].__RIGHT;

                (*rectangle_array)[j].__DOWN = !(*rectangle_array)[j].__DOWN;
                (*rectangle_array)[j].__UP = !(*rectangle_array)[j].__UP;
                (*rectangle_array)[j].__LEFT = !(*rectangle_array)[j].__LEFT;
                (*rectangle_array)[j].__RIGHT = !(*rectangle_array)[j].__RIGHT;
            }
        }
    }
}



void addRectangle(_Rectangle **rectangle_array, SDL_Window *window) {
    if (__RECTANGLES_CAPACITY == 0) {
        *rectangle_array = (_Rectangle*) malloc(1 * sizeof(_Rectangle));
        __RECTANGLES_CAPACITY = 1;
    } else if (__RECTANGLES_COUNT == __RECTANGLES_CAPACITY) {
        __RECTANGLES_CAPACITY *= 2;
        *rectangle_array = (_Rectangle*) realloc(*rectangle_array, __RECTANGLES_CAPACITY * sizeof(_Rectangle));
    }

    (*rectangle_array)[__RECTANGLES_COUNT].rect.h = 40;
    (*rectangle_array)[__RECTANGLES_COUNT].rect.w = 40;
    (*rectangle_array)[__RECTANGLES_COUNT].rect.x = SDL_GetWindowSurface(window)->w / 2;
    (*rectangle_array)[__RECTANGLES_COUNT].rect.y = SDL_GetWindowSurface(window)->h / 2;

    (*rectangle_array)[__RECTANGLES_COUNT].__UP = 0;
    (*rectangle_array)[__RECTANGLES_COUNT].__DOWN = 1;
    (*rectangle_array)[__RECTANGLES_COUNT].__LEFT = 0;
    (*rectangle_array)[__RECTANGLES_COUNT].__RIGHT = 1;

    (*rectangle_array)[__RECTANGLES_COUNT].speed = 1;

    __RECTANGLES_COUNT += 1;
}