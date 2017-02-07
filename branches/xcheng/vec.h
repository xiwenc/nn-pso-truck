// $Id: vec.h 74 2010-12-21 18:23:55Z xcheng $
/*!
 @file
 @author xcheng, unknown
 @class Vec
 @brief Implements a special type of vector
 
 one with operators that can be applied to each individual element

 This class was taken from SBI_DEMO and modified
 */
#ifndef _VEC_CLASS_
#define _VEC_CLASS_

#include "math.h"
#include <vector>
#include <string>
using namespace std;

/**
 * Vec class
 */
class Vec {
    public:
        Vec(void);
        Vec(vector<float>);
        ~Vec(void);
        Vec operator=(vector<float>);
        Vec operator=(Vec);
        Vec operator*(float);
        Vec operator*(Vec other);
        Vec operator/(float);
        Vec operator+(vector<float>);
        Vec operator+(Vec);
        Vec operator-(vector<float>);
        Vec operator-(Vec);
        Vec operator-(float);
        Vec normalized(void);
        float magnitude(void);
        void print(void);
        void print(string);
        void printMagnitude(void);
        void printMagnitude(string);
        Vec enforceVMax(void);
        Vec enforceXMax(void);

        // GET
        vector<float> getVector();
        void mutate(float rate);

    private:

        //---------
        //variables
        //---------
        vector<float> _dimensions;              //vector dimensions
        Math _M;                                //math object

};//Vec class

#endif
