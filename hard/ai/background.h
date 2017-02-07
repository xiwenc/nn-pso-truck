// $Id: background.h 65 2010-11-24 09:51:09Z xcheng $
/*!
 @file
 @author xcheng, bvveen, unknown
 @class
 @brief Does background simulation, used by Particle to determine the fitness of a solution
 @detail This class was taken from SBI_DEMO and modified.
 */
#ifndef BACKGROUNDPROCESS
#define BACKGROUNDPROCESS

#include "neural.h"
#include "Truck.h"
#include "../../Box2D/Include/Box2D.h"
#include "definitions.h" // debugging, parameters

class Background {
    public:
        Background(bool debug); // constructor
        Background(double* networkWeights, bool debug);
        ~Background();
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
