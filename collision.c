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
    
    rect->physic = (_Physic){ .__GRAVITY = 0.98, .__WEIGHT = 1, .__VELOCITY_X = 0.0, 
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

int checkCollision(_Rectangle *a, _Rectangle *b) {
    return (a->rect.x < b->rect.x + b->rect.w) &&
           (a->rect.x + a->rect.w > b->rect.x) &&
           (a->rect.y < b->rect.y + b->rect.h) &&
           (a->rect.y + a->rect.h > b->rect.y);
}


void resolveCollision(_Rectangle *a, _Rectangle *b) {
    if (!checkCollision(a, b)) return;

    // Swap velocities using a basic momentum exchange
    float massA = a->physic.__WEIGHT;
    float massB = b->physic.__WEIGHT;

    float newVelX_A = ((massA - massB) / (massA + massB)) * a->physic.__VELOCITY_X +
                      ((2 * massB) / (massA + massB)) * b->physic.__VELOCITY_X;

    float newVelX_B = ((massB - massA) / (massA + massB)) * b->physic.__VELOCITY_X +
                      ((2 * massA) / (massA + massB)) * a->physic.__VELOCITY_X;

    float newVelY_A = ((massA - massB) / (massA + massB)) * a->physic.__VELOCITY_Y +
                      ((2 * massB) / (massA + massB)) * b->physic.__VELOCITY_Y;

    float newVelY_B = ((massB - massA) / (massA + massB)) * b->physic.__VELOCITY_Y +
                      ((2 * massA) / (massA + massB)) * a->physic.__VELOCITY_Y;

    a->physic.__VELOCITY_X = newVelX_A * a->physic.__DAMPING;
    b->physic.__VELOCITY_X = newVelX_B * b->physic.__DAMPING;

    a->physic.__VELOCITY_Y = newVelY_A * a->physic.__DAMPING;
    b->physic.__VELOCITY_Y = newVelY_B * b->physic.__DAMPING;

    // Separate the rectangles slightly to avoid sticking
    if (a->rect.x < b->rect.x) {
        a->rect.x -= 1;
        b->rect.x += 1;
    } else {
        a->rect.x += 1;
        b->rect.x -= 1;
    }

    if (a->rect.y < b->rect.y) {
        a->rect.y -= 1;
        b->rect.y += 1;
    } else {
        a->rect.y += 1;
        b->rect.y -= 1;
    }
}

