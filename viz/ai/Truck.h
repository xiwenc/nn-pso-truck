// $Id: Truck.h 59 2010-11-23 11:42:14Z xcheng $
/*!
 @file
 @author xcheng, bvveen
 @class Truck
 @brief This class defines a special Truck :P
 @detail This very special truck was ported from flash[1] to C++.
 1. http://www.emanueleferonato.com/2009/04/06/two-ways-to-make-box2d-cars/
 */
/*
* Copyright (c) 2008 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef TRUCK_H
#define TRUCK_H

#include "../Framework/Test.h"
#include "definitions.h"

class Truck : public Test
{
    public:
        Truck();
        void Step(Settings* settings);
        void Keyboard(unsigned char key);
        static Test* Create();
        b2Vec2 getBodyOffset();
        void getEnvironment(double* env);
        void simulate(float tstep, int iter);
        void setParameters(double* params);
        b2Vec2 getPosition();

    private:
        b2Body* m_leftWheel;
        b2Body* m_rightWheel;
        b2Body* m_vehicle;
        b2RevoluteJoint* m_leftJoint;
        b2RevoluteJoint* m_rightJoint;
        b2PrismaticJoint* m_leftSpring;
        b2PrismaticJoint* m_rightSpring;
        b2Body* m_leftAxle;
        b2Body* m_rightAxle;
        b2Vec2 o_bodyOffset;
};

#endif
