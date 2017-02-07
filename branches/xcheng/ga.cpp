// $Id$

#include "ga.h"

GA::GA() {
#if DEBUGLEVEL > 2
    printf("GA::GA()\n");
#endif
}

// sets population
void GA::setPopulation(vector<Particle> p, int parents) {
#if DEBUGLEVEL > 2
    printf("GA::setPopulation(..., %d)\n", parents);
#endif
    _numParents = parents;
    _population = p;
}

// tournament selection
void GA::selection() {
#if DEBUGLEVEL > 2
    printf("GA::selection()\n");
#endif
    int c1, c2; // candidates
    Particle p1(0); //temp
    Particle p2(0); // selected
    unsigned int max = _population.size();
    for (int i = 0; i < _numParents; i++) {
        c1 = (int) (_M.uniformRandom()*max);
        c2 = c1;
        // Post condition: c1 != c2
        while (c1 == c2)
            c2 = (int) (_M.uniformRandom()*max);
        // fight! :p
        if (_population[c1].getFitness() > _population[c2].getFitness()) 
            p1 = _population[c1];
        else
            p1 = _population[c2];
        
        p2 = Particle(p1.getLocation(),
            p1.getVelocity(),
            p1.getPersonalBest(),
            p1.getPersonalBestFitness());
        _parents.push_back(p2);
    }

}

// VPAC crossover
void GA::crossover() {
#if DEBUGLEVEL > 2
    printf("GA::crossover()\n");
#endif
    Particle c1(0);
    Particle c2(0); // offsprings
    Vec v1, v2, o1, o2;
    unsigned int s = _parents.size();

    _population.clear();
    for (unsigned int i = 0; i < s; i += 2) {
        if (i+1 == s) i--;
        v1 = _parents[i].getLocation();
        v2 = _parents[i+1].getLocation();
        o1 = (v1 + v2)/2 - _parents[i].getVelocity() * _M.uniformRandom();
        o2 = (v1 + v2)/2 - _parents[i+1].getVelocity() * _M.uniformRandom();
        c1 = Particle(o1, _parents[i].getVelocity(), 
            _parents[i].getPersonalBest(), 
            _parents[i].getPersonalBestFitness());
        c2 = Particle(o2, _parents[i+1].getVelocity(), 
            _parents[i+1].getPersonalBest(), 
            _parents[i+1].getPersonalBestFitness());
        _population.push_back(c2);
        if (i+1 != s) _population.push_back(c1);
        else break;
    }
    _parents.clear(); // they are dead :p
}

// mutation
void GA::mutation(float rate) {
#if DEBUGLEVEL > 2
    printf("GA::mutation(%.5f)\n", rate);
#endif
    for (unsigned int i = 0; i < _population.size(); i++) {
            _population[i].mutate(rate);
    }
}

vector<Particle> GA::update(float mrate) {
#if DEBUGLEVEL > 2
    printf("GA::update(%.5f)\n", mrate);
#endif
    selection();
    crossover();
    mutation(mrate);
    return _population;
}

