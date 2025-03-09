#include "headers.h"

_Rectangle *__ARRAY_RECTANGLES = NULL;
int __RECTANGLES_COUNT = 0;
int __RECTANGLES_CAPACITY = 0;

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

    (*rectangle_array)[__RECTANGLES_COUNT].physic.__GRAVITY = 0.98;
    (*rectangle_array)[__RECTANGLES_COUNT].physic.__WEIGHT = 1;
    (*rectangle_array)[__RECTANGLES_COUNT].physic.__VELOCITY_X = 0;
    (*rectangle_array)[__RECTANGLES_COUNT].physic.__VELOCITY_Y = 0;
    (*rectangle_array)[__RECTANGLES_COUNT].physic.__KINETIC_ENERGY = 0;
    (*rectangle_array)[__RECTANGLES_COUNT].physic.__DAMPING = 0.5;

    __RECTANGLES_COUNT += 1;
}

void calculatePosition(_Rectangle *rectangle, SDL_Window *window) {
    calculateVelocity(&rectangle->physic);
    rectangle->rect.y += rectangle->physic.__VELOCITY_Y * rectangle->physic.__DAMPING;
    rectangle->rect.x += rectangle->physic.__VELOCITY_X * rectangle->physic.__DAMPING;
    addColision(rectangle, window, rectangle->physic.__DAMPING);
}

void addColision(_Rectangle *rectangle, SDL_Window *window, float damping) {
    float minVelocity = 1;
    int window_width = SDL_GetWindowSurface(window)->w;
    int window_height = SDL_GetWindowSurface(window)->h;

    if ((rectangle->rect.y + rectangle->rect.h) >= window_height) {
        rectangle->rect.y = window_height - rectangle->rect.h;
        rectangle->physic.__VELOCITY_Y = -rectangle->physic.__VELOCITY_Y * damping;
    }
    if (rectangle->rect.y <= 0) {
        rectangle->rect.y = 0;
        rectangle->physic.__VELOCITY_Y = -rectangle->physic.__VELOCITY_Y * damping;
    }
    if ((rectangle->rect.x + rectangle->rect.w) >= window_width) {
        rectangle->rect.x = window_width - rectangle->rect.w;
        rectangle->physic.__VELOCITY_X = -rectangle->physic.__VELOCITY_X * damping;
    }
    if (rectangle->rect.x <= 0) {
        rectangle->rect.x = 0;
        rectangle->physic.__VELOCITY_X = -rectangle->physic.__VELOCITY_X * damping;
    }

    // Set velocity to zero if it falls below the minimum threshold
    if (fabs(rectangle->physic.__VELOCITY_X) < minVelocity) {
        rectangle->physic.__VELOCITY_X = 0;
    }
    if (fabs(rectangle->physic.__VELOCITY_Y) < minVelocity) {
        rectangle->physic.__VELOCITY_Y = 0;
    }
}