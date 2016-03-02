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

class SPHSolver {
  private:
    void enforceBoundary(SPHParticle *p);

  public:
    float upper_bound;
    float lower_bound;
    float dampening;
    std::vector<SPHParticle> particles;
    SPHForce force;

    SPHSolver(unsigned int number_of_particles, const float upper_bound, const float lower_bound);
    void update(const float dt);
};

#endif //SPHSOLVER_H
