// $Id$

#include "ga.h"
#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include <iostream>
#include <vector>
using namespace std;

GA::GA() {
    _M.seed();
}

// sets population
void GA::setPopulation(vector<Particle*> p, int parents) {
    _numParents = parents;
    _population = p;
}

// tournament selection
void GA::selection() {
    int c1, c2; // candidates
    _parents.clear();
    for (int i = 0; i < _numParents; i++) {
        c1 = (int) (_M.uniformRandom()*_numParents);
        c2 = c1;
        // Post condition: c1 != c2
        while (c1 == c2)
            c2 = (int) (_M.uniformRandom()*_numParents);
        // fight! :p
        if (_population[c1]->getFitness() > _population[c2]->getFitness()) 
            _parents.push_back(_population[c1]);
        else
            _parents.push_back(_population[c2]);
    }

}

// VPAC crossover
void GA::crossover() {
    Particle* c1;
    Particle* c2; // offsprings
    Vec v1, v2, o1, o2;

    // clear old population
//    for (int i = 0; i < _population.size(); i++) {
//        delete _population[i];
//    }
    _population.clear();

    for (int i = 0; i < _parents.size(); i += 2) {
        v1 = _parents[i]->getLocation();
        v2 = _parents[i+1]->getLocation();
        o1 = (v1 + v2)/2 - _parents[i]->getVelocity() * _M.uniformRandom();
        o2 = (v1 + v2)/2 - _parents[i+1]->getVelocity() * _M.uniformRandom();
        c1 = new Particle(o1, _parents[i]->getVelocity(), _parents[i]->GetPBest(), _parents[i]->GetPBestValue());
        c2 = new Particle(o2, _parents[i+1]->getVelocity(), _parents[i+1]->GetPBest(), _parents[i+1]->GetPBestValue());
        _population.push_back(c1);
        _population.push_back(c2);
    }
}

// mutation
void GA::mutation(float rate) {
    for (int i = 0; i < _population.size(); i++) {
            _population[i]->mutate(rate);
    }
}

vector<Particle*> GA::update(float mrate) {
    selection();
    crossover();
    mutation(mrate);
    return _population;
}
