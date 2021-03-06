// $Id$
/*!
 @file
 @author xcheng
 @class GA
 @brief blaat

 */
#ifndef _GA_CLASS_
#define _GA_CLASS_

#include "particle.h"
#include "math.h"
#include "../Framework/Test.h"
#include<vector>
using namespace std;

/**
 * GA class
 */
class GA {

    public:
        GA();
        void setPopulation(vector<Particle*> p, int parents);
        vector<Particle*> update(float mrate);
    private:
        void selection();
        void crossover();
        void mutation(float rate);
        vector<Particle*> _population;
        vector<Particle*> _parents;
        int _numParents;
        Math _M;

};//GA class

#endif
