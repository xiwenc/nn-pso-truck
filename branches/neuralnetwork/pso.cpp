#include "pso.h"
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
PSO::PSO(int n, int d) {
	if (debugging && DEBUGLEVEL >= 2) cout << "particle swarm being created" << endl;
	_M.seed(); //seed math object
	_n = n; //number of particles
	_d = d; //dimensionality of search space
	_init(); //initialise particles
}//constructor

//----------
//destructor
//----------
PSO::~PSO(void) {
	if (debugging && DEBUGLEVEL >= 2) cout << "particle swarm being destroyed" << endl;
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		delete _particles[i]; //delete particle
	}//for
}//destructor

//------
//update
//------
void PSO::update(void) {

	//update partices
        for (unsigned int i = 0; i < _particles.size(); ++i) {
            _particles[i]->update(_gbest);
	}

        //get gbest
        _gbest = GetGBest();
        
}

//
// Get the Global Best from all the Personal Bests of the Particles
//
Vec PSO::GetGBest() {

        //set initial gbest
	_gbestValue = NULL;

        //iterate over particles, find best pbest fitness value
        float newValue;
	for (unsigned int i = 0; i < _particles.size(); i++) {
		newValue = _particles[i]->GetPBestValue();
		if (newValue < _gbestValue || _gbestValue == NULL) {
                    _gbest = _particles[i]->GetPBest();
                    _gbestValue = newValue;
		}
	}

        return _gbest;
        
}

//
// Get the Global Best from all the Personal Bests of the Particles
//
float PSO::GetGBestValue() {
    return _gbestValue;
}

//--------------
//initialization
//--------------
void PSO::_init(void) {

        //initialise partices
	for (int i = 0; i < _n; ++i) {
		_particles.push_back(new Particle(_d)); //create particle
	}

        //compute gBest
        _gbest = GetGBest();

}//initialize particle swarm


