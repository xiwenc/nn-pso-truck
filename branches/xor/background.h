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
        double Fitness();

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
