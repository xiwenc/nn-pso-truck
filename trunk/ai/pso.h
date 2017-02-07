// $Id: pso.h 66 2010-11-24 10:22:04Z xcheng $
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
        /*!
         Constructs a swarm of specified size
         @param[in] n number of particles in this population
         @param[in] d dimensionality of each particle
         @param[in] test the environment
        */
        PSO(int n, int d, Test* test);                //constructor

        //! Destructs the instance
        ~PSO(void);                   //destructor

        /*!
         Executes an iteration
         @param[in] test the environment
        */
        void update(Test* test);            //step to next iteration

        /*!
         Determine the global best of current population
         @return global best particle
        */
        Vec GetGBest();               // Get Global Best

        /*!
         Fitness of global best, call this after calling update()
         @return global best fitness
        */
        float GetGBestValue();      //get global best fitness

    private:

        //---------
        //functions
        //---------
        void _init(Test* test);             //initialize particle swarm
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
