#ifndef _PSO_CLASS_
#define _PSO_CLASS_

#include "particle.h"
#include "math.h"
#include<vector>
using namespace std;

/**
 * PSO class
 */
class PSO {
	
	public:
	
		//---------
		//functions
		//---------
		PSO(int, int);                //constructor
		~PSO(void);                   //destructor
		void update(void);            //step to next iteration
		Vec GetGBest();				// Get Global Best
		
	private:
	
		//---------
		//functions
		//---------
		void _init(void);             //initialize particle swarm
		float _evaluate(Particle*);    //evaluate particle
	
		//---------
		//variables
		//---------
		int _n;                       //number of particles
		int _d;                       //dimensionality of search space
		Math _M;                      //math object
		vector<Particle*> _particles; //swarm
		SbiRobotFactory* robotFactory;	// factory containing several useful functions
		
};//PSO class

#endif
