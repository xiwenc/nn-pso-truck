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
Particle::Particle(int d) {
	if (debugging && DEBUGLEVEL >= 2) cout << "creating particle" << endl;
	_init(d);
}//constructor

//----------
//destructor
//----------
Particle::~Particle(void) {
	if (debugging && DEBUGLEVEL >= 2) cout << "destroying particle" << endl;
}//destructor

//------
//update
//------
void Particle::update(Vec gbest) {

        if (debugging && DEBUGLEVEL >= 2) {
            cout << "updating particle" << endl;
	}

        //update velocity
        _velocity = _velocity * inertia
                    + (_pbest - _location) * memory * _M.uniformRandom()
                    + (gbest - _location) * social * _M.uniformRandom();
        //TODO consider vMax

        //update location
	_location = _location + _velocity;
        //TODO consider xMax

        //update fitness
        evaluate();

        //update pBest
        updatePBest();
        
}//update

//------------------------
//process evaluation value
//------------------------
void Particle::updatePBest() {

        if (debugging && DEBUGLEVEL >= 2) cout << "updating personal best" << endl;

        //compare pBest with current fitness
        if (_fitness < _pbestValue) {
		_pbestValue = _fitness;
		_pbest = _location;
	}//if

}//process evaluation value

//---------------
//return location
//---------------
Vec Particle::getLocation(void) {
	return _location;
}//return location

//
float Particle::GetPBestValue() {
	return _pbestValue;
}

//
Vec Particle::GetPBest() {
	return _pbest;
}

//--------------
//initialization
//--------------
void Particle::_init(int d) {
	if (debugging && DEBUGLEVEL >= 2) {
            cout << "initializing particle" << endl;
        }
	vector<float> v, l;
	for (int i = 0; i < d; ++i) {
		v.push_back(_M.uniformRandom(-Vmax, Vmax));
		l.push_back(_M.uniformRandom(-Xmax, Xmax));
	}//for
	_velocity = v;
	_location = l;
	_pbest = _location;
        _pbestValue = evaluate();
}//initialization

//----------
//evaluation Spheres function
//----------
/*float Particle::evaluate() {
    
	float fitness = 0.0;
        vector<float> thisWeights = _location.GetWeights();

        //compute sphere functin fitness
        for (unsigned int i = 0; i < thisWeights.size(); i++) {
          //cout << thisWeights[i] << endl;
          fitness += (thisWeights[i]*thisWeights[i]);
        }

        if (debugging && DEBUGLEVEL >= 2) {
            cout << "PSO::_evaluate(Particle* p)" << endl;
            cout << "\tweight 0: " << thisWeights[0] << endl;
            cout << "\tweight 1: " << thisWeights[1] << endl;
            cout << "\tfitness: " << fitness << endl;
        }
        
        //update fitness and return
        _fitness = fitness;
	return fitness;
        
}*/

//----------
//evaluation Ackley function
//----------
float Particle::evaluate() {

        //variables for ackley function
        float c1 = 20.0;
        float c2 = 0.2;
        float c3 = 2*M_PI;

        //other vars
	float fitness = 0.0;
        vector<float> thisWeights = _location.GetWeights();
        int n = thisWeights.size();

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
        fitness = -c1 * exp( -c2 * sqrt( 1/n * part1 ) )
                      - exp( 1/n * part2 )
                      + c1
                      + M_E;

        cout << DEBUGLEVEL << endl;
        if (debugging && DEBUGLEVEL >= 2) {
            cout << "PSO::_evaluate(Particle* p)" << endl;
            cout << "\tweight 0: " << thisWeights[0] << endl;
            cout << "\tweight 1: " << thisWeights[1] << endl;
            cout << "\tfitness: " << fitness << endl;
        }

        //update fitness and return
        _fitness = fitness;
	return fitness;

}//evaluate particle

float Particle::getFitness() {
    return _fitness;
}