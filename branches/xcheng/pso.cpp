// $Id: pso.cpp 74 2010-12-21 18:23:55Z xcheng $

#include "pso.h"

PSO::PSO() {
}

void PSO::setPopulation(vector<Particle> p) {
    _particles = p;
}

vector<Particle> PSO::updateVelocity(Vec gbest, float inertia) {
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        _particles[i].updateVelocity(gbest, inertia);
    }
    return _particles;
}
vector<Particle> PSO::updateLocation(Vec gbest) {
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        _particles[i].updateLocation(gbest);
    }
    return _particles;
}

