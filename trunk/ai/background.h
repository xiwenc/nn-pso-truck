// $Id: background.h 66 2010-11-24 10:22:04Z xcheng $
/*!
 @file
 @author xcheng, bvveen, unknown
 @class
 @brief Calculates the fitness using simulation.

 Does background simulation, used by Particle to determine the fitness of a solution.
 @note This class was taken from SBI_DEMO and modified.
 */
#ifndef BACKGROUNDPROCESS
#define BACKGROUNDPROCESS

#include "neural.h"
#include "Truck.h"
#include "../../Box2D/Include/Box2D.h"
#include "definitions.h"

class Background {
    public:
        /*!
         Constructs a new background
         @param[in] debug turn on debugging or not
        */
        Background(bool debug);
        /*!
         Constructs a background and set network weights
         @param[in] networkWeights Weights used to set the network with
         @param[in] debug Turn on debugging or not
        */
        Background(double* networkWeights, bool debug);

        //! Destructs the instance
        ~Background();

        /*!
         Calculates the fitness of the solution (networkWeights) by simulating it
         @param[in] test The environment to simulate in
         @return The travelled distance 
        */
        double Fitness(Test* test);

    private:
        void Init(bool debug);

        // Truck
        Truck* truck;

        // Neural Network
        Neural* neural;

        // debug
        bool debug;
};

#endif
