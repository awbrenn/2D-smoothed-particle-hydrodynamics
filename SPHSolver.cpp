//
// Created by awbrenn on 3/2/16.
//

#include "SPHSolver.h"

SPHSolver::SPHSolver(unsigned int number_of_particles, const float upper_bound, const float lower_bound) {
  // initialize particles
  for (int i = 0; i < number_of_particles; ++i) {
    vector2 position;
    position.x = lower_bound + static_cast <float> (rand()) / ((RAND_MAX / (upper_bound - lower_bound)));
    position.y = lower_bound + static_cast <float> (rand()) / ((RAND_MAX / (upper_bound - lower_bound)));
    vector2 velocity = {0.0f, 0.0f};
    particles.push_back(SPHParticle(position, velocity));
  }
}

void SPHSolver::update(const float dt) {
  std::vector<SPHParticle>::iterator pi = particles.begin();
  while(pi != particles.end()) {
    pi->acceleration = force.evaluateForce(&particles, &(*pi), dt);
    ++pi;
  }
}
