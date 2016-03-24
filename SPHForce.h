/*
 * Author:         Austin Brennan
 * University:     Clemson University
 * Course:         2D Fluid Simulation
 * Professor:      Dr. Jerry Tessendorf
 * Due Date:       3/8/2016
 */

#ifndef SPHFORCE_H
#define SPHFORCE_H
#include "SPHParticle.h"
#include "SPHOccupancyVolume.h"
#include <math.h>
#include <vector>
#include <omp.h>

class SPHForce {
  private:
    float calculatePressure(SPHParticle *p);
    float calculateViscocityForce(SPHParticle *b, SPHParticle *a, float h);

  public:
    vector2 gravity = vector2(0.0f, -9.8f);
    float density_base = 141.471060526f;
    float gamma = 3.0f;
    float beta = 10.0;
    float viscosity = 5.0f;
    float epsilon = 0.1f;

    vector2 evaluateForce(std::vector<SPHParticle> *particles, SPHParticle *b, SPHOccupancyVolume *occupancy_volume);
};

#endif //SPHFORCE_H
