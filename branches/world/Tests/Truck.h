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

#ifndef CAR_H
#define CAR_H

// Adapted from SpiritWalkers by darkzerox
class Truck : public Test
{
public:
	Truck()
	{
		{	// car body
                        // cart
                        b2BodyDef bd;
                        b2PolygonDef boxDef;

                        bd.position.Set(0, 3.5);
                        m_vehicle = m_world->CreateBody(&bd);

                        boxDef.density = 2;
                        boxDef.friction = 0.5;
                        boxDef.restitution = 0.2;
                        boxDef.filter.groupIndex = -1;

                        boxDef.SetAsBox(1.5, 0.3);
                        m_vehicle->CreateShape(&boxDef);
                        boxDef.SetAsBox(0.4, 0.15, b2Vec2(-1, -0.3), b2_pi/3);
                        m_vehicle->CreateShape(&boxDef);
                        boxDef.SetAsBox(0.4, 0.15, b2Vec2(1, -0.3), b2_pi/-3);
                        m_vehicle->CreateShape(&boxDef);
                        m_vehicle->SetMassFromShapes();
		}

                {
                        // axle with springs
			b2BodyDef bd;
                        b2PolygonDef boxDef;
                        boxDef.density = 1;
                        b2PrismaticJointDef pjDef;
                        boxDef.friction = 0.5;
                        boxDef.restitution = 0.2;
                        boxDef.filter.groupIndex = -1;

                        // left axle
			bd.position.Set(0.0f, 3.5f);
                        boxDef.SetAsBox(0.4, 0.1, b2Vec2(-1 - 0.6*cos(b2_pi/3), -0.3 - 0.6*sin(b2_pi/3)), b2_pi/3);
                        m_leftAxle = m_world->CreateBody(&bd);
                        m_leftAxle->CreateShape(&boxDef);
                        m_leftAxle->SetMassFromShapes();

                        // left spring
                        pjDef.Initialize(m_vehicle, m_leftAxle, m_leftAxle->GetWorldCenter(), b2Vec2(cos(b2_pi/3), sin(b2_pi/3)));
                        pjDef.lowerTranslation = -0.3;
                        pjDef.upperTranslation = 0.5;
                        pjDef.enableLimit = true;
                        pjDef.enableMotor = true;
                        m_leftSpring = (b2PrismaticJoint *)m_world->CreateJoint(&pjDef);

                        // right axle
                        m_rightAxle = m_world->CreateBody(&bd);
                        boxDef.SetAsBox(0.4, 0.1, b2Vec2(0.5 + 0.6*cos(b2_pi/-3), -0.3 + 0.6*sin(b2_pi/-3)), b2_pi/-3);
                        m_rightAxle->CreateShape(&boxDef);
                        m_rightAxle->SetMassFromShapes();

                        // right spring
                        pjDef.Initialize(m_vehicle, m_rightAxle, m_rightAxle->GetWorldCenter(), b2Vec2(cos(b2_pi/-3), sin(b2_pi/3)));
                        m_rightSpring = (b2PrismaticJoint *)m_world->CreateJoint(&pjDef);


                }


		{	// vehicle wheels
			b2CircleDef	circ;
			circ.density = 0.1f;
			circ.radius = 0.7f;
			circ.friction = 5.0f;
                        circ.restitution = 0.2f;
			circ.filter.groupIndex = -1;

			b2BodyDef bd;
			bd.allowSleep = false;
			bd.position.Set(m_rightAxle->GetWorldCenter().x + 0.3*cos(b2_pi/-3), m_rightAxle->GetWorldCenter().y + 0.3 * sin(b2_pi/-3));

			m_rightWheel = m_world->CreateBody(&bd);
			m_rightWheel->CreateShape(&circ);
			m_rightWheel->SetMassFromShapes();

			bd.position.Set(m_leftAxle->GetWorldCenter().x - 0.3*cos(b2_pi/3), m_leftAxle->GetWorldCenter().y - 0.3 * sin(b2_pi/3));
			m_leftWheel = m_world->CreateBody(&bd);
			m_leftWheel->CreateShape(&circ);
			m_leftWheel->SetMassFromShapes();
		}

		{	// join wheels to chassis
			b2Vec2 anchor;
			b2RevoluteJointDef jd;

			jd.Initialize(m_leftAxle, m_leftWheel, m_leftWheel->GetWorldCenter());
			//jd.collideConnected = false;
			jd.enableMotor = true;
			//jd.maxMotorTorque = 10.0f;
			//jd.motorSpeed = 0.0f;
			m_leftJoint = (b2RevoluteJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_rightAxle, m_rightWheel, m_rightWheel->GetWorldCenter());
			//jd.collideConnected = false;
			m_rightJoint = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
		}

		{	// ground
			b2PolygonDef box;
			box.SetAsBox(50.0f, 0.5f);
			box.friction = 1.0f;
                        box.density = 0.0f;

			b2BodyDef bd;
			bd.position.Set(0.0f, 0.5f);

			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&box);

                        //obstacles
                        box.SetAsBox(1, 2, b2Vec2(-50, 0.5), 0);
                        ground->CreateShape(&box);
                        box.SetAsBox(1, 2, b2Vec2(50, 0.5), 0);
                        ground->CreateShape(&box);
                        box.SetAsBox(3, 0.5, b2Vec2(5, 1.5), b2_pi/4);
                        ground->CreateShape(&box);
                        box.SetAsBox(3, 0.5, b2Vec2(3.5, 1), b2_pi/8);
                        ground->CreateShape(&box);
                        box.SetAsBox(3, 0.5, b2Vec2(9, 1.5), b2_pi/-4);
                        ground->CreateShape(&box);
                        box.SetAsBox(3, 0.5, b2Vec2(10.5, 1), b2_pi/-8);
                        ground->CreateShape(&box);

                        ground->SetMassFromShapes();

		}
	}

	void Step(Settings* settings)
	{
		DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d");
		m_textLine += 15;
                DrawString(5, m_textLine, "Position = (%f, %f)", m_vehicle->GetPosition().x, m_vehicle->GetPosition().y);
		m_textLine += 15;
                DrawString(5, m_textLine, "Velocity = %f", m_vehicle->GetLinearVelocity().Length());
		m_textLine += 15;

		Test::Step(settings);
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'a':
			m_leftJoint->SetMaxMotorTorque(400.0f);
			m_leftJoint->SetMotorSpeed(6.0f);
			break;

		case 's':
			m_leftJoint->SetMaxMotorTorque(100.0f);
			m_leftJoint->SetMotorSpeed(0.0f);
			break;

		case 'd':
			m_leftJoint->SetMaxMotorTorque(600.0f);
			m_leftJoint->SetMotorSpeed(-18.0f);
			break;
		}
	}

	static Test* Create()
	{
		return new Truck;
	}

	b2Body* m_leftWheel;
	b2Body* m_rightWheel;
	b2Body* m_vehicle;
	b2RevoluteJoint* m_leftJoint;
	b2RevoluteJoint* m_rightJoint;
        b2PrismaticJoint* m_leftSpring;
        b2PrismaticJoint* m_rightSpring;
	b2Body* m_leftAxle;
	b2Body* m_rightAxle;
};

#endif
