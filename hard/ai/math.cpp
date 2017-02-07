// $Id: math.cpp 65 2010-11-24 09:51:09Z xcheng $

#include "math.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//---------------------------
//uniform random float [0, 1]
//---------------------------
float Math::uniformRandom(void) {
    return (float) rand() / (float) RAND_MAX;
}//uniformRandom()

//-----------------------------
//uniform random [lower, upper]
//-----------------------------
float Math::uniformRandom(float lower, float upper) {
    return (upper - lower) * uniformRandom() + lower;
}//uniformRandom

//----
//seed
//----
void Math::seed(void) {
    srand(time(NULL));
}//randomReset

//----
//swap
//----
void Math::swap(float &x, float &y) {
    float z = x;
    x = y;
    y = z;
}//swap

//-------------------------------------------------------------------------------
//approximate euclidean distance
//see: http://www.flipcode.com/archives/Fast_Approximate_Distance_Functions.shtml
//-------------------------------------------------------------------------------
float Math::approxEuclidean(float s, float l) {
    if (s < 0) s = -s;
    if (l < 0) l = -l;
    if (s > l) swap(s, l); //l should be the larger
    float approx = 1007 * l + 441 * s;
    if (l < 4 * s) approx -= 40 * l;
    return (approx + 512) / 1024;
}//approxEuclidean
