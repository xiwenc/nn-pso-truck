// $Id$
/*!
 @file
 @author xcheng
 @class BS
 @brief Breeding swarm as described by Settle and Soule

 */
#ifndef _BS_CLASS_
#define _BS_CLASS_

#include <iostream>
#include <vector>
#include <stdio.h>

#include "particle.h"
#include "math.h"
#include "ga.h"
#include "pso.h"
#include "vec.h"
#include "definitions.h"
using namespace std;

/**
 * BS class
 */
class BS {

    public:
        /*!
         Constructs a swarm of specified size
         @param[in] n number of particles in this population
         @param[in] d dimensionality of each particle
        */
        BS(int n, int d, int mode);                //constructor

        //! Destructs the instance
        ~BS(void);                   //destructor

        /*!
         Executes an iteration
        */
        void update(float inertia, float mrate);            //step to next iteration

        /*!
         Determine the global best of current population
         @return global best particle
        */
        Vec getGlobalBest();               // Get Global Best

        /*!
         Fitness of global best, call this after calling update()
         @return global best fitness
        */
        float getGlobalBestFitness();      //get global best fitness

    private:

        //---------
        //functions
        //---------
        void _init();             //initialize particle swarm
        void rank(); // sorts the population

        //---------
        //variables
        //---------
        int _n;                       //number of particles
        int _d;                       //dimensionality of search space
        Math _M;                      //math object
        vector<Particle> _particles; //swarm
        Vec _gbest;                    //global best
        float _gbestValue;             //global best fitness
        GA _ga;
        PSO _pso;
        int _mode;

};//BS class

#endif
