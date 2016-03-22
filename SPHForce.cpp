//
// Created by awbrenn on 3/2/16.
//

#include "SPHForce.h"

vector2 calculateGradW(SPHParticle *b, SPHParticle *a, float h) {
  float q, one_minus_q, magnitude;
  vector2 result;

  magnitude = ((b->position - a->position).length());
  q = magnitude / b->radius;
  if (q >= 1.0f or q == 0.0) { result = vector2(0.0f, 0.0f); }
  else {
    one_minus_q = 1.0f - q;

    result = (b->position - a->position).scale(1.0f / magnitude)
        .scale((float) ((-30.0f / (M_PI * (h * h * h))) * (one_minus_q * one_minus_q)));
  }

  return result;
}

float SPHForce::calculatePressure(SPHParticle *p) {
  float result;
  result = beta*powf((p->density/density_base), gamma);
  return result;
}

float SPHForce::calculateViscocityForce(SPHParticle *b, SPHParticle *a, float h) {
  float viscosity_force;

  vector2 x_ba = (b->position - a->position);
  float x_ba_magnitude = x_ba.length();

  viscosity_force = -1.0f * viscosity * (b->velocity - a->velocity).scale(h).dot(x_ba) /
                                        ((x_ba_magnitude*x_ba_magnitude) + (epsilon * h * h)) *
                                        (1.0f / (b->density + a->density));

  return viscosity_force;
}

vector2 SPHForce::evaluateForce(std::vector<SPHParticle> *particles, SPHParticle *b) {
  vector2 force;
  vector2 grad_w;
  float pressure_a, pressure_b, viscosity_force;

  force = vector2(0.0f, 0.0f);
  std::vector<SPHParticle>::iterator pi = particles->begin();
  while(pi != particles->end()) {
    pressure_a = calculatePressure(&(*pi));
    pressure_b = calculatePressure(b);
    grad_w = calculateGradW(b, &(*pi), b->radius);
    viscosity_force = calculateViscocityForce(b, &(*pi), b->radius);
    force += grad_w.scale((pi->mass) * ((pressure_a / (pi->density * pi->density)) +
                                        (pressure_b / ( b->density *  b->density)) +
                                         viscosity_force));
    ++pi;
  }
  force = force.scale(-1.0f/b->mass);

  force += gravity;
  return force;
}
