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
void Particle::update(Vec lbest) {
	if (debugging && DEBUGLEVEL >= 2) {
		cout << "updating particle" << endl;
	}
	_velocity = (_velocity.normalized() * inertia
	          + (_location - _pbest).normalized() * memory
	          + (_location - lbest).normalized() * social).normalized() //direction
	          * _M.uniformRandom() * Vmax; //random speed in [0, Vmax]
	_location = _location + _velocity;
}//update

//------------------------
//process evaluation value
//------------------------
bool Particle::processEval(float value) {
	if (debugging && DEBUGLEVEL >= 2) cout << "updating personal best" << endl;
	if (value > _pbestValue) {
		_pbestValue = value;
		_pbest = _location;
		return true;
	}//if
	return false;
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
	if (debugging && DEBUGLEVEL >= 2) cout << "initializing particle" << endl;
	vector<float> v, l;
	for (int i = 0; i < d; ++i) {
		v.push_back(_M.uniformRandom(-Vmax, Vmax));
		l.push_back(_M.uniformRandom(-Xmax, Xmax));
	}//for
	_velocity = v;
	_location = l;
	_pbestValue = 0; //FIXME: Application specific hack
	_pbest = _location;
}//initialization
