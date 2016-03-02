//
// Created by awbrenn on 3/2/16.
//

#ifndef SPHPARTICLE_H
#define SPHPARTICLE_H

typedef struct vector2 {
  float x, y;
} vector2;

class SPHParticle {
  public:
    vector2 position;
    vector2 velocity;
    vector2 acceleration;

    SPHParticle(const vector2 _position, const vector2 _velocity);
};


#endif //SPHPARTICLE_H
