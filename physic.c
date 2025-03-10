#include "headers.h"

void calculateVelocity(_Physic *physic) {
    // Apply gravity
    physic->__VELOCITY_Y += physic->__GRAVITY * physic->__WEIGHT;

    physic->__KINETIC_ENERGY = calculate_kinetic_energy(physic);
}

float calculate_kinetic_energy(_Physic *physic) {
    return 0.5 * physic->__WEIGHT * 
           (physic->__VELOCITY_X * physic->__VELOCITY_X + 
            physic->__VELOCITY_Y * physic->__VELOCITY_Y);
}