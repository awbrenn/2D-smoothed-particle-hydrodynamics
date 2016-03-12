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
#include <math.h>
#include <vector>

class SPHForce {
  private:
    float getPressure(SPHParticle *p);

  public:
    vector2 gravity = vector2(0.0f, -9.8f);
    float density_base = 0.5f;
    float gamma = 0.1f;
    float beta = 2.0;


    vector2 evaluateForce(std::vector<SPHParticle> *particles, SPHParticle *b);
};

#endif //SPHFORCE_H
