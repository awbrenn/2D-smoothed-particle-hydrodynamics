//
// Created by awbrenn on 3/2/16.
//

#include "SPHSolver.h"

void handleError(const char *error_message, bool kill) {
  std::cerr << error_message << std::endl;
  if (kill) exit(-1);
}


float getRandomFloatBetweenValues (float lower_bound, float upper_bound) {
  return lower_bound + static_cast <float> (rand()) / ((RAND_MAX / (upper_bound - lower_bound)));
}


SPHSolver::SPHSolver(unsigned int number_of_particles, const float _lower_bound, const float _upper_bound) {
  lower_bound = _lower_bound;
  upper_bound = _upper_bound;
  dampening = 1.0f;
  party_mode = false;
  // initialize particles
  for (int i = 0; i < number_of_particles; ++i) {
    vector2 position;
    position.x = getRandomFloatBetweenValues(lower_bound, upper_bound);
    position.y = getRandomFloatBetweenValues(lower_bound, upper_bound);
    vector2 velocity = {0.0f, 0.0f};
    particles.push_back(SPHParticle(position, velocity));
  }
}


void SPHSolver::randomizeColor(SPHParticle *p) {
  p->color.x = getRandomFloatBetweenValues(0.1, 0.9);
  p->color.y = getRandomFloatBetweenValues(0.1, 0.9);
  p->color.z = getRandomFloatBetweenValues(0.1, 0.9);
}


void SPHSolver::enforceBoundary(SPHParticle *p) {
  bool collision = false;

  // enforce top and bottom bounds
  if (p->position.y < lower_bound) {
    p->position.y = lower_bound - p->position.y;
    p->velocity.y = (-1.0f)*p->velocity.y*dampening;
    collision = true;
  }
  else if (p->position.y > upper_bound) {
    p->position.y = upper_bound - (p->position.y - upper_bound);
    p->velocity.y = (-1.0f)*p->velocity.y*dampening;
    collision = true;
  }

  // enforce left to right bounds
  if (p->position.x < lower_bound) {
    p->position.x = lower_bound - p->position.x;
    p->velocity.x = (-1.0f)*p->velocity.x*dampening;
    collision = true;
  }
  else if (p->position.x > upper_bound) {
    p->position.x = upper_bound - (p->position.x - upper_bound);
    p->velocity.x = (-1.0f)*p->velocity.x*dampening;
    collision = true;
  }
  if (collision && party_mode) { randomizeColor(p); }
  else if (!party_mode) { p->color = {0.0f, 1.0f, 0.0f}; }
}


void SPHSolver::leapFrog(float dt) {
  dt /= 2.0f;
  std::vector<SPHParticle>::iterator pi = particles.begin();
  while(pi != particles.end()) {
    pi->position.x += pi->velocity.x*dt;
    pi->position.y += pi->velocity.y*dt;
    enforceBoundary(&(*pi));

    pi->acceleration = force.evaluateForce(&particles, &(*pi), dt);
    pi->velocity.x += pi->acceleration.x*dt;
    pi->velocity.y += pi->acceleration.y*dt;
    pi->position.x += pi->velocity.x*dt;
    pi->position.y += pi->velocity.y*dt;

    enforceBoundary(&(*pi));
    ++pi;
  }
}


void SPHSolver::sixth(float dt) {
  float a, b;
  a = 1.0f / (4.0f - powf(4.0f, 1.0f/3.0f));
  b = 1.0f - 4.0f*a;

  leapFrog(a);
  leapFrog(a);
  leapFrog(b);
  leapFrog(a);
  leapFrog(a);
}


void SPHSolver::update(const float dt, UPDATE_FUNCTION function) {
  switch (function) {
    case LEAP_FROG:
      leapFrog(dt);
      break;
    case SIXTH:
      sixth(dt);
      break;
    default:
      handleError("Error in SPHSolver::update(const float dt, UPDATE_FUNCTION function): Invalid UPDATE_FUNCTION. "
                        "Use LEAP_FROG or SIXTH", true);
      break;
  }
}
