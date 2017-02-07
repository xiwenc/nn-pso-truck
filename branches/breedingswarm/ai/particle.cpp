// $Id: particle.cpp 74 2010-12-21 18:23:55Z xcheng $

#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "neural.h"
#include "background.h"

using namespace std;

//constructor
Particle::Particle(int d, Test* test) {
    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2)
        cout << "creating particle" << endl;
    _init(d, test);
}//constructor

Particle::Particle(Vec location, Vec velocity, Vec pbest, float pbestValue) {
    _location = location;
    _velocity = velocity;
    _pbest = pbest;
    _pbestValue = pbestValue;

}

//destructor
Particle::~Particle(void) {
    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2)
        cout << "destroying particle" << endl;
}//destructor

//update
void Particle::updateVelocity(Vec gbest, float inertia) {
    //update velocity
    _velocity = _velocity * inertia
                + (_pbest - _location) * config[CONFIG_MEMORY] * _M.uniformRandom()
                + (gbest - _location) * config[CONFIG_SOCIAL] * _M.uniformRandom();
    //keep velocity withing <-Vmax, Vmax>
    _velocity.enforceVMax();
}

void Particle::updateLocation(Vec gbest) {
    //update location
    _location = _location + _velocity;
    //keep location withing <-Xmax, Xmax>
    _location.enforceXMax();
}//update

//process evaluation value
void Particle::updatePBest() {

    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2)
        cout << "updating personal best" << endl;

    //compare pBest with current fitness
    if (_fitness > _pbestValue) {
    _pbestValue = _fitness;
    _pbest = _location;
    }//if

}//process evaluation value

//return location
Vec Particle::getLocation(void) {
    return _location;
}

float Particle::GetPBestValue() {
    return _pbestValue;
}

Vec Particle::GetPBest() {
    return _pbest;
}

//initialization
void Particle::_init(int d) {
    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2) {
            cout << "initializing particle" << endl;
        }
    vector<float> v, l;
    for (int i = 0; i < d; ++i) {
        v.push_back(_M.uniformRandom(-1 * config[CONFIG_VMAX], config[CONFIG_VMAX]));
        l.push_back(_M.uniformRandom(-1 * config[CONFIG_XMAX], config[CONFIG_XMAX]));
    }//for
    _velocity = v;
    _location = l;
    _pbest = _location;
    _pbestValue = evaluate(test);
    _neural = new Neural(config[CONFIG_IN_NODES], config[CONFIG_OUT_NODES],
             config[CONFIG_HIDDEN_LAYERS], config[CONFIG_NODES_PER_LAYER]);
}

//evaluation: pulsed output
float Particle::evaluate() {

    vector<float> thisWeights = _location.GetWeights();

    // weights
    double myWeights[thisWeights.size()];

    // map particle dimensions to weights
    for (unsigned int i = 0; i < thisWeights.size(); i++) {
        myWeights[i] = thisWeights[i];
    }
    _neural->setWeights(myWeights);
    _fitness = 0;
    return _fitness;
}//evaluate particle

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
