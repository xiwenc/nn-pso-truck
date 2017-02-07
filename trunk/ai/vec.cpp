// $Id: vec.cpp 54 2010-11-22 15:49:27Z xcheng $

#include "vec.h"
#include "definitions.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//-----------
//constructor
//-----------
Vec::Vec(void) {
}//constructor

//-----------
//constructor
//-----------
Vec::Vec(vector<float> dimensions) {
    _dimensions = dimensions;
}//constructor

//----------
//destructor
//----------
Vec::~Vec(void) {
}//destructor

//---------
//operator=
//---------
Vec Vec::operator=(vector<float> dimensions) {
    _dimensions = dimensions;
    return Vec(_dimensions);
}//operator=

//---------
//operator=
//---------
Vec Vec::operator=(Vec other) {
    _dimensions = other._dimensions;
    return Vec(_dimensions);
}//operator=

//---------
//operator*
//---------
Vec Vec::operator*(float scalar) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] *= scalar;
    }//for
    return Vec(temp);
}//operator*

//---------
//operator/
//---------
Vec Vec::operator/(float scalar) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] /= scalar;
    }//for
    return Vec(temp);
}//operator/

//---------
//operator+
//---------
Vec Vec::operator+(vector<float> other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] += other[i];
    }//for
    return Vec(temp);
}//operator+

//---------
//operator+
//---------
Vec Vec::operator+(Vec other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] += other._dimensions[i];
    }//for
    return Vec(temp);
}//operator+

//---------
//operator-
//---------
Vec Vec::operator-(vector<float> other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] -= other[i];
        // xcheng: HACK
        if (temp[i] == 0) temp[i] = 1;
    }//for
    return Vec(temp);
}//operator-

//---------
//operator-
//---------
Vec Vec::operator-(Vec other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] -= other._dimensions[i];
        // xcheng: HACK
        if (temp[i] == 0) temp[i] = 1;
    }//for
    return Vec(temp);
}//operator-

//---------
//magnitude
//---------
float Vec::magnitude(void) {
    float temp = 0;
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        temp = sqrt(temp * temp + _dimensions[i] * _dimensions[i]);
    }//for
    return temp;
}//magnitude

//---------
//normalized
//---------
Vec Vec::normalized(void) {
    return Vec(_dimensions) / magnitude();
}//normalized


//---------
//enforce vMax, keep _velocity withing bounds
//---------
Vec Vec::enforceVMax(void) {
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        if (_dimensions[i] < (-1 * config[CONFIG_VMAX])) {
                    _dimensions[i] = -1 * config[CONFIG_VMAX];
                } else if (_dimensions[i] > config[CONFIG_VMAX]) {
                    _dimensions[i] = config[CONFIG_VMAX];
                }
    }//for
        return Vec(_dimensions);
}//normalized


//---------
//enforce xMax
//---------
Vec Vec::enforceXMax(void) {
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        if (_dimensions[i] < (-1 * config[CONFIG_XMAX])) {
                    _dimensions[i] = -1 * config[CONFIG_XMAX];
                } else if (_dimensions[i] > config[CONFIG_XMAX]) {
                    _dimensions[i] = config[CONFIG_XMAX];
                }
    }//for
        return Vec(_dimensions);
}//normalized

//-----
//print
//-----
void Vec::print(string msg) {
    cout << msg << ": ";
    print();
}//print

//-----
//print
//-----
void Vec::print(void) {
    cout << "<";
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        cout << _dimensions[i];
        if ( i + 1 < _dimensions.size()) cout << ", ";
    }//for
    cout << ">" << endl;
}//print

//---------------
//print magnitude
//---------------
void Vec::printMagnitude(string msg) {
    cout << msg << ": ";
    printMagnitude();
}//printMagnitude

//---------------
//print magnitude
//---------------
void Vec::printMagnitude(void) {
    cout << magnitude() << endl;
}//printMagnitude

//
//
//
vector<float> Vec::GetWeights() {
    return _dimensions;
}


