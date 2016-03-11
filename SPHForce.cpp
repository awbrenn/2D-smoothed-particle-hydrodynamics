//
// Created by awbrenn on 3/2/16.
//

#include "SPHForce.h"

vector2 SPHForce::evaluateForce(const std::vector<SPHParticle> *particles, const SPHParticle *a, const float dt) {
  vector2 force;
  
  force.x = gravity.x;
  force.y = gravity.y;
  return force;
}
