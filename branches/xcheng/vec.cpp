// $Id: vec.cpp 74 2010-12-21 18:23:55Z xcheng $

#include "vec.h"
#include "definitions.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Vec::Vec(void) {
}

Vec::Vec(vector<float> dimensions) {
    _dimensions = dimensions;
}

Vec::~Vec(void) {
}

Vec Vec::operator=(vector<float> dimensions) {
    _dimensions = dimensions;
    return Vec(_dimensions);
}

Vec Vec::operator=(Vec other) {
    vector<float> op = other.getVector();
    _dimensions = op;
    return Vec(_dimensions);
}

Vec Vec::operator*(float scalar) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] *= scalar;
    }
    return Vec(temp);
}

Vec Vec::operator*(Vec other) {
    vector<float> temp = _dimensions;
    vector<float> op = other.getVector();
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] *= op[i];
    }
    return Vec(temp);
}

Vec Vec::operator/(float scalar) {
    vector<float> temp = _dimensions;
    // no division by zero
    if (scalar == 0) return Vec(temp);
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] /= scalar;
    }
    return Vec(temp);
}

Vec Vec::operator+(vector<float> other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] += other[i];
    }
    return Vec(temp);
}

Vec Vec::operator+(Vec other) {
    vector<float> temp = _dimensions;
    vector<float> op = other.getVector();
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] += op[i];
    }
    return Vec(temp);
}

Vec Vec::operator-(vector<float> other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] -= other[i];
    }
    return Vec(temp);
}

Vec Vec::operator-(Vec other) {
    vector<float> temp = _dimensions;
    vector<float> op = other.getVector();
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] -= op[i];
    }
    return Vec(temp);
}

Vec Vec::operator-(float other) {
    vector<float> temp = _dimensions;
    for (unsigned int i = 0; i < temp.size(); ++i) {
        temp[i] -= other;
    }
    return Vec(temp);
}

float Vec::magnitude(void) {
    float temp = 0;
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        temp = sqrt(temp * temp + _dimensions[i] * _dimensions[i]);
    }
    return temp;
}

Vec Vec::normalized(void) {
    return Vec(_dimensions) / magnitude();
}


//enforce vMax, keep _velocity withing bounds
Vec Vec::enforceVMax(void) {
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        if (_dimensions[i] < (-1 * config[CONFIG_VMAX])) {
            _dimensions[i] = -1 * config[CONFIG_VMAX];
        } else if (_dimensions[i] > config[CONFIG_VMAX]) {
            _dimensions[i] = config[CONFIG_VMAX];
        }
    }
    return Vec(_dimensions);
}


//enforce xMax
Vec Vec::enforceXMax(void) {
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        if (_dimensions[i] < (-1 * config[CONFIG_XMAX])) {
            _dimensions[i] = -1 * config[CONFIG_XMAX];
        } else if (_dimensions[i] > config[CONFIG_XMAX]) {
            _dimensions[i] = config[CONFIG_XMAX];
        }
    }
    return Vec(_dimensions);
}

void Vec::print(string msg) {
    cout << msg << ": ";
    print();
}

void Vec::print(void) {
    cout << "<";
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        cout << _dimensions[i];
        if ( i + 1 < _dimensions.size()) cout << ", ";
    }
    cout << ">" << endl;
}

//print magnitude
void Vec::printMagnitude(string msg) {
    cout << msg << ": ";
    printMagnitude();
}

//print magnitude
void Vec::printMagnitude(void) {
    cout << magnitude() << endl;
}

vector<float> Vec::getVector() {
    return _dimensions;
}

void Vec::mutate(float rate) {
    for (unsigned int i = 0; i < _dimensions.size(); ++i) {
        if (rate > _M.uniformRandom())
            _dimensions[i] = _dimensions[i] * _M.uniformRandom();
    }
}
