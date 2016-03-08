/*
 * Author:         Austin Brennan
 * University:     Clemson University
 * Course:         2D Fluid Simulation
 * Professor:      Dr. Jerry Tessendorf
 * Due Date:       3/8/2016
 */

#include "SPHParticle.h"

SPHParticle::SPHParticle(const vector2 _position, const vector2 _velocity) {
  position = _position;
  velocity = _velocity;
  color = {0.0, 1.0, 0.0};
}
