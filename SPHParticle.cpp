/*
 * Author:         Austin Brennan
 * University:     Clemson University
 * Course:         2D Fluid Simulation
 * Professor:      Dr. Jerry Tessendorf
 * Due Date:       3/8/2016
 */

#include "SPHParticle.h"

SPHParticle::SPHParticle(const vector2 _position, const vector2 _velocity, const float _radius) {
  position = _position;
  velocity = _velocity;
  radius = _radius;
  mass = 1.0f;
  color = {0.0, 0.0, 1.0};
}
