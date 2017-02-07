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
		Vec GetGBest();               // Get Global Best
                float GetGBestValue();      //get global best fitness
		
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
                Vec _gbest;                    //global best
                float _gbestValue;             //global best fitness
		
};//PSO class

#endif
