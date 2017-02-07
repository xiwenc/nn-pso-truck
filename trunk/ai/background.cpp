// $Id: background.cpp 61 2010-11-23 16:24:37Z xcheng $

#include <iostream>
#include "background.h"
using namespace std;

Background::Background(bool debug) {
    Init(debug);
}

Background::Background(double* networkWeights, bool debug) {
    Init(debug);
    neural->setWeights(networkWeights);
}

Background::~Background() {
    delete neural;
}

void Background::Init(bool debug) {
    this->debug = debug;
   
    // set other parameters
    neural = new Neural(config[CONFIG_IN_NODES], config[CONFIG_OUT_NODES],
            config[CONFIG_HIDDEN_LAYERS], config[CONFIG_NODES_PER_LAYER]);
}

double Background::Fitness(Test* test) {
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 iterations = 10;
    double params[(int)config[CONFIG_OUT_NODES]];
    double env[(int)config[CONFIG_IN_NODES]];
    double before, after;

    truck = (Truck *)test;

    before = truck->getPosition().x;

    // This is our little game loop.
    for (int32 i = 0; i < 1000; ++i)
    {
        // get environment data
        truck->getEnvironment(env);
        // ask the almighty for instructions :)
        neural->perform(env, params);
        // apply result to actuators
        truck->setParameters(params);
        // Instruct the world to perform a single step of simulation. It is
        // generally best to keep the time step and iterations fixed.
        truck->simulate(timeStep, iterations);
        
    }
    after = truck->getPosition().x;

    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.
    return after-before;

}
