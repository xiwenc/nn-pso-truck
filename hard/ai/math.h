// $Id: math.h 65 2010-11-24 09:51:09Z xcheng $
/*!
 @file
 @author unknown
 @class
 @brief Defines some math functions used by in particular Particle class
 @detail This class was taken from SBI_DEMO
 */
#ifndef _MATH_CLASS_
#define _MATH_CLASS_

/**
 * Math class
 */
class Math {

    public:

        //---------
        //functions
        //---------
        float uniformRandom(void);
        float uniformRandom(float, float);
        void seed(void);
        void swap(float &, float &);
        float approxEuclidean(float, float);

};//Math class

#endif

