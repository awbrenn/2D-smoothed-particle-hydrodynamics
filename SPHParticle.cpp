//
// Created by awbrenn on 3/2/16.
//

#include "SPHParticle.h"

SPHParticle::SPHParticle(const vector2 _position, const vector2 _velocity) {
  position = _position;
  velocity = _velocity;
  color = {0.0, 1.0, 0.0};
}
