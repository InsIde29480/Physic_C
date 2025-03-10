#include "headers.h"

_Rectangle *__ARRAY_RECTANGLES = NULL;
int __RECTANGLES_COUNT = 0;
int __RECTANGLES_CAPACITY = 0;

void addRectangle(SDL_Window *window) {
    if (__RECTANGLES_CAPACITY == 0) {
        __RECTANGLES_CAPACITY = 1;
        __ARRAY_RECTANGLES = (_Rectangle*) malloc(__RECTANGLES_CAPACITY * sizeof(_Rectangle));
    } else if (__RECTANGLES_COUNT == __RECTANGLES_CAPACITY) {
        __RECTANGLES_CAPACITY *= 2;
        _Rectangle *temp = realloc(__ARRAY_RECTANGLES, __RECTANGLES_CAPACITY * sizeof(_Rectangle));
        if (!temp) {
            return; // Handle memory allocation failure
        }
        __ARRAY_RECTANGLES = temp;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    _Rectangle *rect = &__ARRAY_RECTANGLES[__RECTANGLES_COUNT];
    rect->rect = (SDL_Rect){ surface->w / 2, surface->h / 2, 40, 40 };
    
    rect->physic = (_Physic){ .__GRAVITY = 0.98, .__WEIGHT = 2, .__VELOCITY_X = 0.0, 
                              .__VELOCITY_Y = 0.0, .__KINETIC_ENERGY = 0.0, .__DAMPING = 0.8, 
                              .__FRICTION = 0.01 };

    __RECTANGLES_COUNT++;
}

void addCollision(_Rectangle *rectangle, SDL_Window *window)
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    int max_x = surface->w - rectangle->rect.w;
    int max_y = surface->h - rectangle->rect.h;

    // Handle collision on X-axis
    if (rectangle->rect.x < 0)
    {
        rectangle->rect.x = 0;
        rectangle->physic.__VELOCITY_X *= -rectangle->physic.__DAMPING;
    }
    else if (rectangle->rect.x > max_x)
    {
        rectangle->rect.x = max_x;
        rectangle->physic.__VELOCITY_X *= -rectangle->physic.__DAMPING;
    }

    // Handle collision on Y-axis
    if (rectangle->rect.y < 0)
    {
        rectangle->rect.y = 0;
        rectangle->physic.__VELOCITY_Y *= -rectangle->physic.__DAMPING;
    }
    else if (rectangle->rect.y > max_y)
    {
        rectangle->rect.y = max_y;
        rectangle->physic.__VELOCITY_Y *= -rectangle->physic.__DAMPING;
    }
}

void calculatePosition(_Rectangle *rectangle, SDL_Window *window) {
    calculateVelocity(&rectangle->physic);
    rectangle->rect.x += (int)rectangle->physic.__VELOCITY_X;
    rectangle->rect.y += (int)rectangle->physic.__VELOCITY_Y;
    addCollision(rectangle, window);
}