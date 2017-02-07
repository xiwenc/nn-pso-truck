// $Id: pso.h 65 2010-11-24 09:51:09Z xcheng $
/*!
 @file
 @author bvveen, xcheng, unknown
 @class PSO
 @brief This is a standard Particle Swarm Optimizer that minimizes the fitness.
 @detail This class was taken from SBI_DEMO and modified.
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

        //---------
        //functions
        //---------
        PSO(int, int, Test* test);                //constructor
        ~PSO(void);                   //destructor
        void update(Test* test);            //step to next iteration
        Vec GetGBest();               // Get Global Best
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
