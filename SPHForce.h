//
// Created by awbrenn on 3/2/16.
//

#ifndef SPHFORCE_H
#define SPHFORCE_H
#include "SPHParticle.h"
#include <vector>

class SPHForce {
  public:
    vector2 gravity = {0.0f, -0.0000098f};
    vector2 evaluateForce(const std::vector<SPHParticle> *particles, const SPHParticle *a, const float dt);
};


#endif //SPHFORCE_H
