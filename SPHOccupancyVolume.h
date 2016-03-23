//
// Created by awbrenn on 3/22/16.
//

#ifndef SPH_PARTICLE_SPHOCCUPANCYVOLUME_H
#define SPH_PARTICLE_SPHOCCUPANCYVOLUME_H

#include <vector>
#include <stdlib.h>
#include "vector2.h"

class SPHOccupancyVolume {
    vector2 ovllc;
    vector2 ovurc;
    float ovnx;
    float ovny;
    float ovdx;
    float ovdy;
    std::vector<std::vector<size_t>> occupancy_volume;
};

#endif //SPH_PARTICLE_SPHOCCUPANCYVOLUME_H
