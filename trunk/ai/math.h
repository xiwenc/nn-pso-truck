// $Id: math.h 66 2010-11-24 10:22:04Z xcheng $
/*!
 @file
 @author unknown
 @class
 @brief Defines some math functions used by in particular Particle class

 This class was taken from SBI_DEMO
 */
#ifndef _MATH_CLASS_
#define _MATH_CLASS_

/**
 * Math class
 */
class Math {

    public:
        //! @return A uniform random value between 0 and 1
        float uniformRandom(void);
        /*!
         @param[in] lower the lower bound
         @param[in] upper the upper bound
         @return A uniform random value between lower and upper
        */
        float uniformRandom(float lower, float upper);

        //! Seeds the random generator
        void seed(void);

        /*!
         Swaps two values with each other
         @param[out] f1 value one
         @param[out] f2 value two
        */
        void swap(float &f1, float &f2);

        //! Calculate the approximation of the Euclidian distance
        float approxEuclidean(float, float);

};//Math class

#endif

