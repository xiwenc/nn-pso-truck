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
    delete truck;
}

void Background::Init(bool debug) {
    this->debug = debug;

    truck = new Truck();
    // set other parameters
    neural = new Neural(IN_NODES, OUT_NODES, HIDDEN_LAYERS, NODES_PER_LAYER);
}

double Background::Fitness() {
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 iterations = 10;
    double params[OUT_NODES];
    double env[IN_NODES];

    // This is our little game loop.
    for (int32 i = 0; i < 1800; ++i)
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

    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.
    return (truck->getPosition() - truck->getBodyOffset()).x;
}
