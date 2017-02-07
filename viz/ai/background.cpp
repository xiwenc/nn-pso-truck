// $Id: background.cpp 62 2010-11-23 16:34:56Z xcheng $

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
    return Fitness(test, NULL);

}
double Background::Fitness(Test* test, Settings* settings) {
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 iterations = 10;
    int bmax = 3, bstate = 0;
    double params[(int)config[CONFIG_OUT_NODES]];
    double env[(int)config[CONFIG_IN_NODES]];
    double before, after;
    double previous = -99999;

    truck = (Truck *)test;

    before = truck->getPosition().x;

    // This is our little game loop.
    for (int32 i = 0; i < 1000; ++i)
    {
        if (settings != NULL) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }
        // get environment data
        truck->getEnvironment(env);
        // ask the almighty for instructions :)
        neural->perform(env, params);
        // apply result to actuators
        truck->setParameters(params);
        // Instruct the world to perform a single step of simulation. It is
        // generally best to keep the time step and iterations fixed.

        if (settings != NULL) {
            truck->Step(settings);
            glutSwapBuffers();
        } else {
            truck->simulate(timeStep, iterations);
        }
        // break out when we don't move forward anymore
        if (bstate >= bmax) break;
        if (truck->getPosition().x == previous) {
            bstate++;
        } else {
            bstate = 0;
        }
        previous = truck->getPosition().x;
    }
    after = truck->getPosition().x;

    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.
    return after-before;

}
