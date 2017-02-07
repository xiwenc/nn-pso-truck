// $Id: pso.h 74 2010-12-21 18:23:55Z xcheng $
/*!
 @file
 @author bvveen, xcheng, unknown
 @class PSO
 @brief This is a standard Particle Swarm Optimizer that minimizes the fitness.

 This class was taken from SBI_DEMO and modified.
 */
#ifndef _PSO_CLASS_
#define _PSO_CLASS_

#include "particle.h"
#include "math.h"
#include "../Framework/Test.h"
#include<vector>
using namespace std;

/**
 * PSO class
 */
class PSO {

    public:
        PSO();
        void setPopulation(vector<Particle*> p);
        void updateVelocity(Vec gbest, float inertia);
        vector<Particle*> updateLocation(Vec gbest);

    private:
        Math _M;
        vector<Particle*> _particles;

};//PSO class

#endif
