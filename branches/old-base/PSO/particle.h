#ifndef _PARTICLE_CLASS_
#define _PARTICLE_CLASS_

#include <vector>
#include "math.h"
#include "vec.h"
#include "../Framework/SbiRobotFactory.h"
using namespace std;

/**
 * Particle class
 */
class Particle {
	
	public:
		
		//--------
		//fuctions
		//--------
		Particle(int);           //constructor
		~Particle(void);         //destructor
		void update(Vec);        //step to next iteration
		bool processEval(float); //update personal best
		Vec getLocation(void);   //return _location
		float GetPBestValue();	// return personal best fitness
		Vec GetPBest();			// return personal best
		
	private:
	
		//---------
		//functions
		//---------
		void _init(int);         //initialization
		
		//---------
		//variables
		//---------
		Math _M;                 //math object
		Vec _velocity,           //particle velocity
		    _location,           //particle location
		    _pbest;              //personal best
		float _pbestValue;       //personal best evaluation value
		
};//particle class

#endif
