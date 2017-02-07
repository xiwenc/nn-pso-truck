// $Id$

#include "bs.h"
#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include <iostream>
#include <vector>
using namespace std;

//-----------
//constructor
//-----------
BS::BS(int n, int d, Test* test) {
    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2)
        cout << "particle swarm being created" << endl;
    _M.seed(); //seed math object
    _n = n; //number of particles
    _d = d; //dimensionality of search space
    _init(test); //initialise particles
}//constructor

//----------
//destructor
//----------
BS::~BS(void) {
    if (debugging && config[CONFIG_DEBUGLEVEL] >= 2)
        cout << "particle swarm being destroyed" << endl;
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        delete _particles[i]; //delete particle
    }//for
}//destructor

// sorts population by fitness, _particles[0] being the largest
void BS::rank() {
    vector<Particle*> sorted;
    bool used[_particles.size()];
    float best = 0, current;
    int ibest = 0;

    for (unsigned int i = 0; i < _particles.size(); i++)
        used[i] = false;
    while (sorted.size() != _particles.size()) {
        for (unsigned int i = 0; i < _particles.size(); i++) {
            // grab largest 
            current = _particles[i]->getFitness();
            if (current > best && !used[i]) {
                ibest = i;
                best = current;
            }
        }

        // ibest contains index of particle with largest fitness
        sorted.push_back(_particles[ibest]);
        // mark it as used
        used[ibest] = true;
    }

    // replace old population with the new one, sorted
    _particles.clear();
    while (!sorted.empty()) {
        _particles.push_back(sorted.back());
        sorted.pop_back();
    }
}

void BS::update(float inertia, float mrate, Test* test) {
    int k = config[CONFIG_SURVIVORS];
    int kp = _n - k;

    vector<Particle*> pop_pso;
    vector<Particle*> pop_ga;

    rank();

    // pick the best k
    for (int i = 0; i < k; ++i) {
        pop_ga.push_back(_particles[i]);
        pop_pso.push_back(_particles[i]);
    }
    // discard the rest
    for (int i = k; i < _n; i++) {
        //delete _particles[i];
    }

    _ga.setPopulation(pop_ga, kp);
    _pso.setPopulation(pop_pso);
    _pso.updateVelocity(_gbest, inertia);
    pop_ga = _ga.update(mrate);
    pop_pso = _pso.updateLocation(_gbest);

    // merge the populations
    _particles.clear();
    for (unsigned int i = 0; i < pop_ga.size(); i++)
        _particles.push_back(pop_ga[i]);
    for (unsigned int i = 0; i < pop_pso.size(); i++)
        _particles.push_back(pop_pso[i]);

    // evaluate them
    for (unsigned int i = 0; i < _particles.size(); i++) {
        _particles[i]->evaluate(test);
        _particles[i]->updatePBest();
    }

    //get gbest
    _gbest = GetGBest();
}

// Get the Global Best from all the Personal Bests of the Particles
Vec BS::GetGBest() {

    //set initial gbest
    _gbestValue = 0;

    //iterate over particles, find best pbest fitness value
    float newValue;
    for (unsigned int i = 0; i < _particles.size(); i++) {
        newValue = _particles[i]->GetPBestValue();
        if (newValue > _gbestValue) {
            _gbest = _particles[i]->GetPBest();
            _gbestValue = newValue;
        }
    }

    return _gbest;
        
}

// Get the Global Best from all the Personal Bests of the Particles
float BS::GetGBestValue() {
    return _gbestValue;
}

//initialization
void BS::_init(Test* test) {
    //initialize partices
    for (int i = 0; i < _n; ++i) {
        _particles.push_back(new Particle(_d, test)); //create particle
    }

    //compute gBest
    _gbest = GetGBest();
}//initialize particle swarm


