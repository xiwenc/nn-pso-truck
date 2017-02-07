// $Id: background.h 59 2010-11-23 11:42:14Z xcheng $
/*!
 @file
 @author xcheng, bvveen, unknown
 @class
 @brief Does background simulation, used by Particle to determine the fitness of a solution
 @detail This class was taken from SBI_DEMO and modified.
 */
#ifndef BACKGROUNDPROCESS
#define BACKGROUNDPROCESS

// needed by gl
#include "../../Box2D/Contrib/glui/GL/glui.h"
#include "../Framework/Render.h"
#include "../Framework/Test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "../../Box2D/Contrib/freeglut/GL/glut.h"
#endif


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
        double Fitness(Test* test, Settings* settings);

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
