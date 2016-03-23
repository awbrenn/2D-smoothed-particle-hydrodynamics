//
// Created by awbrenn on 3/22/16.
//

#include "SPHOccupancyVolume.h"

std::vector<size_t> *SPHOccupancyVolume::getCell(SPHParticle *p) {
    unsigned int q_i, q_j, cell_index;
    vector2 q;

    q = p->position - ovllc;
    q_i = (unsigned int) (q.x/dx);
    q_j = (unsigned int) (q.y/dy);
    cell_index = q_i + (nx * q_j);

    return &cells[cell_index];
}

void SPHOccupancyVolume::populateOccupancyVolume(std::vector<SPHParticle> *particles) {
    std::vector<SPHParticle>::iterator pi = particles->begin();
    size_t i = 0;
    while(pi != particles->end()) {
        getCell(&(*pi))->push_back(i);
        ++i;
        ++pi;
    }
}