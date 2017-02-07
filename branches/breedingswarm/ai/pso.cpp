// $Id: pso.cpp 74 2010-12-21 18:23:55Z xcheng $

#include "pso.h"
#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include <iostream>
#include <vector>
using namespace std;

PSO::PSO() {
    _M.seed();
}

void PSO::setPopulation(vector<Particle*> p) {
    _particles = p;
}

void PSO::updateVelocity(Vec gbest, float inertia) {
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        _particles[i]->updateVelocity(gbest, inertia);
    }
}
vector<Particle*> PSO::updateLocation(Vec gbest) {
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        _particles[i]->updateLocation(gbest);
    }
    return _particles;
}

