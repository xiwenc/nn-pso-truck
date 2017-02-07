// $Id: particle.cpp 74 2010-12-21 18:23:55Z xcheng $

#include "particle.h"

Particle::Particle(int d) {
#if DEBUGLEVEL > 2
    printf("Particle::Particle(%d)\n", d);
#endif
    _init(d);
}

Particle::Particle(Vec location, Vec velocity, Vec pbest, float pbestValue) {
    _init(location.getVector().size());
    _location = location;
    _velocity = velocity;
    _pbest = pbest;
    _pbestValue = pbestValue;

}

Particle::~Particle(void) {
#if DEBUGLEVEL > 2
    printf("Particle::~Particle()\n");
#endif
}

//update
void Particle::updateVelocity(Vec gbest, float inertia) {
#if DEBUGLEVEL > 2
    printf("Particle::updateVelocity(..., %.5f)\n", inertia);
#endif
    // generate random vectors
    vector<float> memory;
    vector<float> social;
    unsigned int d = gbest.getVector().size();
    for (unsigned int i = 0; i < d; i++) {
        memory.push_back(_M.uniformRandom() * config[CONFIG_MEMORY]);
        social.push_back(_M.uniformRandom() * config[CONFIG_SOCIAL]);
    }
    
#if DEBUGLEVEL > 3
    vector<float> t = _velocity.getVector();
    printf("\t PRE velocity: %.5f %.5f\n", t[0], t[1]);
    printf("\t memory: %.5f\n", f1);
    printf("\t social: %.5f\n", f2);
#endif
    //update velocity
    _velocity = _velocity * inertia
            + (_pbest - _location) * Vec(memory)
            + (gbest - _location) * Vec(social);
    //keep velocity within <-Vmax, Vmax>
    _velocity.enforceVMax();
    //_velocity = _velocity.normalized() * config[CONFIG_VMAX];
#if DEBUGLEVEL > 3
    t = _velocity.getVector();
    printf("\t POST velocity: %.5f %.5f\n", t[0], t[1]);
#endif
}

void Particle::updateLocation(Vec gbest) {
#if DEBUGLEVEL > 2
    printf("Particle::updateLocation(...)\n");
#endif
    //update location
    _location = _location + _velocity;
    //keep location withing <-Xmax, Xmax>
    _location.enforceXMax();
}

//process evaluation value
void Particle::updatePersonalBest() {
#if DEBUGLEVEL > 2
    printf("Particle::updatePersonalBest(...)\n");
#endif
    //compare pBest with current fitness
    if (_fitness <= _pbestValue) {
        _pbestValue = _fitness;
        _pbest = _location;
    }//if

}

//return location
Vec Particle::getLocation(void) {
    return _location;
}

float Particle::getPersonalBestFitness() {
    return _pbestValue;
}

Vec Particle::getPersonalBest() {
    return _pbest;
}

//initialization
void Particle::_init(int d) {
#if DEBUGLEVEL > 2
    printf("Particle::_init()\n");
#endif
    vector<float> v, l;
    for (int i = 0; i < d; ++i) {
        v.push_back(_M.uniformRandom(-1 * config[CONFIG_VMAX], config[CONFIG_VMAX]));
        l.push_back(_M.uniformRandom(-1 * config[CONFIG_XMAX], config[CONFIG_XMAX]));
#if DEBUGLEVEL > 4
        printf("\tlocation: %d %.5f\n", i, l.back());
#endif
    }//for
    _velocity = v;
    _location = l;
    _pbest = _location;
    _pbestValue = evaluate();
}

#ifndef PULSE
//evaluation Ackley function
float Particle::evaluate() {
#if DEBUGLEVEL > 2
    printf("Particle::evaluate()\n");
#endif
    //variables for ackley function
    float c1 = 20.0;
    float c2 = 0.2;
    float c3 = 2*M_PI;

    //other vars
    float fitness = 0.0;
    vector<float> thisWeights = _location.getVector();
    float n = (float)thisWeights.size();

    //first sommation of the ackley function
    float part1 = 0.0;
    for (unsigned int i = 0; i < thisWeights.size(); i++) {
      part1 += (thisWeights[i]*thisWeights[i]);
    }

    //second sommation of the ackley function
    float part2 = 0.0;
    for (unsigned int i = 0; i < thisWeights.size(); i++) {
      part2 += cos(c3*thisWeights[i]);
    }

    //ackley function
    fitness = -1*c1 * exp( -1*c2 * sqrt( 1/n * part1 ) )
                  - exp( 1/n * part2 )
                  + c1
                  + M_E;
/*
    fitness = 0;
    for (unsigned int i = 0; i < thisWeights.size(); i++)
        fitness += sqrt(thisWeights[i]*thisWeights[i]);
*/
#if DEBUGLEVEL > 4
    for (unsigned int i = 0; i < thisWeights.size(); i++)
        printf("\t%d\t %.5f\n", i, thisWeights[i]);
#endif
#if DEBUGLEVEL > 3
    printf("\tfitness: %.5f\n", fitness);
#endif

    //update fitness and return
    _fitness = fitness;
    return fitness;

}//evaluate particle

#else

//evaluation: pulsed output
float Particle::evaluate() {
#if DEBUGLEVEL > 2
    printf("Particle::evaluate()\n");
#endif

    vector<float> thisWeights = _location.getVector();
    float error, t1, t2, t3, ti, oi, tsi, osi, ti1, oi1;
    double in[2], out[2];
    Neural neural(IN_NODES, OUT_NODES, HIDDEN_LAYERS, NODES_PER_LAYER);

    // weights
    double myWeights[thisWeights.size()];

    // map particle dimensions to weights
    for (unsigned int i = 0; i < thisWeights.size(); i++) {
        myWeights[i] = thisWeights[i];
    }
    neural.setWeights(myWeights);
    neural.resetMemory();

    error = 0;
    oi1 = ti1 = 0;
    for (int i = 1; i <= 100; i++) {
        ti = pulse(i);
        in[0] = (float) i;
        neural.perform(in, out);
        oi = out[0];
        tsi = ti - ti1;
        osi = oi - oi1;
        t1 = ti - oi;
        t2 = tsi - osi;
        t3 = t1*t1 + 2*t2*t2;
        error += t3;
        ti1 = ti;
        oi1 = oi;
    }

    _fitness = error;
    return _fitness;
}//evaluate particle
#endif


float Particle::getFitness() {
    return _fitness;
}

Vec Particle::getVelocity() {
    return _velocity;
}

void Particle::mutate(float rate) {
    _location.mutate(rate);
    _velocity.mutate(rate);
}

// objective function, defined for [10:90]
float Particle::pulse(int x) {
    if (x < 10 || x > 90) return 0;
    int temp = x%20-10;
    return temp * temp * 0.01;
}
