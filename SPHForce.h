/*
 * Author:         Austin Brennan
 * University:     Clemson University
 * Course:         2D Fluid Simulation
 * Professor:      Dr. Jerry Tessendorf
 * Due Date:       3/8/2016
 */

#ifndef SPHFORCE_H
#define SPHFORCE_H
#include "SPHParticle.h"
#include <vector>

class SPHForce {
  public:
    vector2 gravity = {0.0f, -9.8f};
    vector2 evaluateForce(const std::vector<SPHParticle> *particles, const SPHParticle *a, const float dt);
};


#endif //SPHFORCE_H
