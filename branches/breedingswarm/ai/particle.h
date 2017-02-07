// $Id: particle.h 74 2010-12-21 18:23:55Z xcheng $
/*!
 @file
 @author bvveen, xcheng, unknown
 @class Particle
 @brief A particle used in Particle Swarm Optimzer

 Each particle has a position in a predefined dimension d. The current location can be requested, new velocity can be calculated based on PSO
*/
#ifndef _PARTICLE_CLASS_
#define _PARTICLE_CLASS_

#include <vector>
#include "math.h"
#include "vec.h"
#include "neural.h"
#include "../Framework/Test.h"
using namespace std;

/**
 * Particle class
 */
class Particle {

    public:
        /*!
         Constructs a particle
         @param[in] dimensions the dimensionality of this particle
         @param[in] test the environment
        */
        Particle(int dimensions, Test* test);          //constructor
        Particle(Vec location, Vec velocity, Vec pbest, float pbestValue);

        //! Destructs instance
        ~Particle(void);        //destructor

        /*!
         Updates particle's velocity and position
         @param[in] gbest The global best so far
         @param[in] test the environment
        */
        void updateVelocity(Vec gbest, float inertia);
        void updateLocation(Vec gbest);

        /*!
         Current particle's location
         @return particle location
        */
        Vec getLocation(void);  //return _location

        /*!
         Personal best fitness
         @return personal best fitness
        */
        float GetPBestValue();    // return personal best fitness

        /*!
         Personal best vector
         @return personal best vector
        */
        Vec GetPBest();        // return personal best

        /*!
         Fitness of this particle. Only call this after calling update()
         @return Fitness of particle
        */
        float getFitness();     

        /*!
         Particle velocity
         @return current velocity
        */
        Vec getVelocity();

        void mutate(float rate);
        void updatePBest();     //update personal best
        float evaluate(Test* test);       //compute fitness of particle

    private:

        //---------
        //functions
        //---------
        void _init(int, Test* test);        //initialization

        //---------
        //variables
        //---------
        Math _M;                //math object
        Vec _velocity,          //particle velocity
            _location,          //particle location
            _pbest;             //personal best
        float _pbestValue,      //personal best evaluation value
              _fitness;         //fitness value
        Neural* _neural;

};//particle class

#endif
