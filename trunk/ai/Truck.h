// $Id: Truck.h 66 2010-11-24 10:22:04Z xcheng $
/*!
 @file
 @author xcheng, bvveen
 @class Truck
 @brief This class defines a special Truck :P

 This very special truck was ported from flash[1] to C++. "Sensors" and actuators are configurable using the global config[] variable. 

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
        //! Constructs a Truck
        Truck();

        /*!
         Executes a step in the world
         @param[in] settings using settings
        */
        void Step(Settings* settings);

        /*!
         React to some keystrokes.
         @note There's delay in registering the strokes when being used in visualization mode
         @param[key] the keystroke value
        */
        void Keyboard(unsigned char key);

        //! Creates an instance of Truck
        static Test* Create();

        /*!
         The initial position of the vehicle
         @return initial position
        */
        b2Vec2 getBodyOffset();
        
        /*!
         Reads sensor data. The number of variables depend on config[CONFIG_IN_NODES]
         @param[out] env values are read into env
        */
        void getEnvironment(double* env);

        /*!
         Simulates a step, not really used by the algorithm
         @param[in] tstep time step
         @param[in] iter iterations
        */
        void simulate(float tstep, int iter);

        /*!
         Sets the actuator values
         @param[in] params set of actuator values
        */
        void setParameters(double* params);

        //! @return current position of the vehicle
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
