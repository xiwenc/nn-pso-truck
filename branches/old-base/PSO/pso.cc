#include "pso.h"
#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include<iostream>
#include<vector>
using namespace std;

//-----------
//constructor
//-----------
PSO::PSO(int n, int d) {
	if (debugging) cout << "particle swarm being created" << endl;
	_M.seed(); //seed math object
	_n = n; //number of particles
	_d = d; //dimensionality of search space
	_init(); //initialise particles
}//constructor

//----------
//destructor
//----------
PSO::~PSO(void) {
	if (debugging) cout << "particle swarm being destroyed" << endl;
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		delete _particles[i]; //delete particle
	}//for
}//destructor

//------
//update
//------
void PSO::update(void) {
	float lbestValue = 0;
	Vec lbest;
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		float value = _evaluate(*(_particles[i])); //evaluate fitness
		if (_particles[i]->processEval(value)) { //process evaluation value
			if (value > lbestValue) { //update local (global) best
				lbestValue = value;
				lbest = _particles[i]->getLocation();
			}//if
		}//if
	}//for
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		_particles[i]->update(lbest); //update particle velocities and locations
	}//for
}//iterate particle swarm

//
// Get the Global Best from all the Personal Bests of the Particles
//
Vec PSO::GetGBest() {
	float gbestValue = 0;
	float newValue;
	Vec gbest;
	for (unsigned int i = 0; i < _particles.size(); i++) {
		newValue = _particles[i]->GetPBestValue();
		if (newValue > gbestValue) {
			gbest = _particles[i]->GetPBest();
		}
	}
	return gbest;
}

//--------------
//initialization
//--------------
void PSO::_init(void) {
	for (int i = 0; i < _n; ++i) {
		_particles.push_back(new Particle(_d)); //create particle
	}//for
}//initialize particle swarm

//----------
//evaluation
//----------
float PSO::_evaluate(Particle p) {
	float temp = 0;
	//FIXME: Evaluate particle here
	return temp;
}//evaluate particle
