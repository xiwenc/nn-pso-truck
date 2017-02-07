
/*!
 @file
 @class Particle
 @brief A particle used in Particle Swarm Optimzer
 @detail Each particle has a position in a predefined dimension d. The current location can be requested, new velocity can be calculated based on PSO
*/
#ifndef _PARTICLE_CLASS_
#define _PARTICLE_CLASS_

#include <vector>
#include "math.h"
#include "vec.h"
using namespace std;

/**
 * Particle class
 */
class Particle {
	
	public:
        /*!
         Constructs a particle
         @param[in] dimensions the dimensionality of this particle
        */
		Particle(int dimensions);          //constructor
		~Particle(void);        //destructor
		void update(Vec);       //step to next iteration
		Vec getLocation(void);  //return _location
		float GetPBestValue();	// return personal best fitness
		Vec GetPBest();		// return personal best
                float getFitness();     
		
	private:
	
		//---------
		//functions
		//---------
		void _init(int);        //initialization
                void updatePBest();     //update personal best
		float evaluate();       //compute fitness of particle
		
		//---------
		//variables
		//---------
		Math _M;                //math object
		Vec _velocity,          //particle velocity
		    _location,          //particle location
		    _pbest;             //personal best
		float _pbestValue,      //personal best evaluation value
                      _fitness;         //fitness value
		
};//particle class

#endif
