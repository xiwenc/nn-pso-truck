// $Id: vec.h 59 2010-11-23 11:42:14Z xcheng $
/*!
 @file
 @author xcheng, unknown
 @class Vec
 @brief Implements a special type of vector, one with operators that can be applied to each individual element
 @detail This class was taken from SBI_DEMO and modified
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

        //---------
        //functions
        //---------
        Vec(void);                    //constructor
        Vec(vector<float>);           //constructor
        ~Vec(void);                   //destructor
        Vec operator=(vector<float>); //assignment of dimensions
        Vec operator=(Vec);           //assignment of dimensions
        Vec operator*(float);         //scale vector
        Vec operator/(float);         //scale vector
        Vec operator+(vector<float>); //combined vector
        Vec operator+(Vec);           //combined vector
        Vec operator-(vector<float>); //difference vector
        Vec operator-(Vec);           //difference vector
        Vec normalized(void);         //normalized
        float magnitude(void);        //magnitude
        void print(void);             //print
        void print(string);           //print
        void printMagnitude(void);    //print magnitude
        void printMagnitude(string);  //print magnitude
        Vec enforceVMax(void);        //keep velocity within bounds
        Vec enforceXMax(void);        //keep location withing bounds

        // GET
        vector<float> GetWeights();        // get the values of the dimensions

    private:

        //---------
        //variables
        //---------
        vector<float> _dimensions;              //vector dimensions
        Math _M;                                //math object

};//Vec class

#endif
