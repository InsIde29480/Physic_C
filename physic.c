#include "headers.h"

int calculateVelocity(_Physic *physic) {
    // Apply gravity
    physic->__VELOCITY_Y += physic->__GRAVITY * physic->__WEIGHT;

    return 0;
}

float calculate_kinetic_energy(_Physic *physic) {
    return 0.5 * physic->__WEIGHT * 
           (physic->__VELOCITY_X * physic->__VELOCITY_X + 
            physic->__VELOCITY_Y * physic->__VELOCITY_Y);
}