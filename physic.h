#ifndef PHYSIC_H
#define PHYSIC_H

#include "headers.h"

typedef struct 
{
    float __VELOCITY_X;
    float __VELOCITY_Y;
    float __WEIGHT;
    float __GRAVITY;
    float __KINETIC_ENERGY;
    float __DAMPING;
} _Physic;

int calculateVelocity(_Physic *physic);
float calculate_kinetic_energy(_Physic *physic);

#endif // PHYSIC_H