//
// Created by awbrenn on 3/2/16.
//

#ifndef SPHSOLVER_H
#define SPHSOLVER_H

#include "SPHParticle.h"
#include "SPHForce.h"
#include "math.h"
#include <vector>
#include <cstdlib>
#include <iostream>

enum UPDATE_FUNCTION {LEAP_FROG, SIXTH};

class SPHSolver {
  private:
    void enforceBoundary(SPHParticle *p);
    void leapFrog(float dt);
    void sixth(float dt);

  public:
    float upper_bound;
    float lower_bound;
    float dampening;
    std::vector<SPHParticle> particles;
    SPHForce force;

    SPHSolver(unsigned int number_of_particles, const float upper_bound, const float lower_bound);
    void update(const float dt, UPDATE_FUNCTION function);
};

#endif //SPHSOLVER_H
