/*
* Copyright (c) 2007 Erin Catto http://www.gphysics.com
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
/* Wrote a little Test setup for Box2D TestBed */

#ifndef SBI_H
#define SBI_H

#include <iostream> // cerr
#include <cstdlib>
#include <ctime>
#include <list>
#include "../Framework/Neural.h"
#include "../Framework/SbiRobotFactory.h"
#include "../PSO/definitions.h" // debugging, parameters
#include "../PSO/pso.h"
using namespace std;

class SBI : public Test
{
	public:
	SBI()
	{
		// set rand
		srand(time(NULL));
		
		robotFactory = new SbiRobotFactory();
		robotFactory->DefineGround(m_world);		
		MakeFigure();
		// set neural network
		network = robotFactory->CreateNeuralNetwork(debugging);
		
		// create PSO
		pso = new PSO(NPARTICLES, TOTAL_NODES * TOTAL_NODES);
		
		////////////////////////
		/// Make the weightsfile
		//static int i = 0;
		//if (i++ % 500 == 0) {
		//	ActivateNeural();
		//}
	}
	
	~SBI() {
		delete network;
	}
	
	void MakeFigure() {	
		body = robotFactory->CreateBody(m_world);
		wheelLeft = robotFactory->CreateWheel(m_world, 1);
		jointLeft = robotFactory->CreateJoint(m_world, body, wheelLeft, 1);
		wheelRight = robotFactory->CreateWheel(m_world, 2);
		jointRight = robotFactory->CreateJoint(m_world, body, wheelRight, 2);
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 0:
			break;
		}
	}
	
	void ActivateNeural() {
		static int i = 0;
		if (true) { //(i++ % 20 == 0) {
			for (int j = 0; j < 1000; j++) {
				pso->update();
			}
			Vec newGBest = pso->GetGBest();
			network->SetNetwork(robotFactory->TransformParticleResultToWeights(newGBest.GetWeights()));
			// Save weights to file
			robotFactory->SaveWeights(network->GetNetwork(), network->Size());
			
			if (debugging && DEBUGLEVEL >= 2) {
				cerr << "ms1 " << jointLeft->GetMotorSpeed() << " <> ";
				cerr << "ms2 " << jointRight->GetMotorSpeed() << " <> ";
				cerr << "bh  " << (1 / (1 + body->GetPosition().y)) << endl;
			}
		}
	}

	void Step(Settings* settings)
	{
		////////////////////////
		/// Test the weightsfile
		robotFactory->PerformNeuralNetwork(body, jointLeft, jointRight, network);
		Test::Step(settings);
		
		// give result
		static int i = 0;
		if (i++ % 1800 == 0) {
			cout << "Right: " << (body->GetPosition() - robotFactory->GetBodyOffset()).x << endl;
		}
	}

	static Test* Create()
	{
		return new SBI;
	}

	
	private:
		// particle swarm
		PSO* pso;
	
		// neural network
		Neural* network;
		
		// Box2D robot factory 
		// (also contains neural network update function)
		SbiRobotFactory* robotFactory;
		
		// geometric constructs
		b2Body* body;
		b2Body* wheelLeft;
		b2Body* wheelRight;
		b2RevoluteJoint* jointLeft;
		b2RevoluteJoint* jointRight;
};

#endif
