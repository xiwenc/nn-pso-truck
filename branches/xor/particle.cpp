#include "particle.h"
#include "vec.h"
#include "math.h"
#include "definitions.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "neural.h"

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
        //keep velocity withing <-Vmax, Vmax>
        _velocity.enforceVMax();

        //update location
	_location = _location + _velocity;
        //keep location withing <-Xmax, Xmax>
        _location.enforceXMax();

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

    int inputs = 2;
    int outputs = 1;
    int hiddenL = 2;
    int hiddenN = 2;

        Neural rnn(inputs, outputs, hiddenL, hiddenN);
        vector<float> thisWeights = _location.GetWeights();
        Math m;

        double in[inputs];
        in[0] = m.uniformRandom(0, 1);
        in[1] = m.uniformRandom(0, 1);
        double out[outputs];

        // weights
        double myWeights[thisWeights.size()];
        
        // map particle dimensions to weights
        for (unsigned int i = 0; i < thisWeights.size(); i++) {
            myWeights[i] = thisWeights[i];
        }
        rnn.setWeights(myWeights);

       rnn.perform(in, out);

        //xor function
        bool p = in[0] > 0.5;
        bool q = in[1] > 0.5;
        bool xx = (p && !q) || (!p && q);
        double ans = 0;
        if (xx) ans = 1;
        double fitness = ans - out[0];
        // make positive
        if (fitness < 0) fitness *= -1;

        if (debugging && DEBUGLEVEL >= 1) {
            cout << "PSO::_evaluate(Particle* p)" << endl;
            cout << "\tin[0]: " << in[0] << endl;
            cout << "\tin[1]: " << in[1] << endl;
            cout << "\tans: " << ans << endl;
            cout << "\tout: " << out[0] << endl;
            cout << "\tfitness: " << fitness << endl;
        }

        //update fitness and return
        _fitness = fitness;
	return fitness;

}//evaluate particle

float Particle::getFitness() {
    return _fitness;
}
