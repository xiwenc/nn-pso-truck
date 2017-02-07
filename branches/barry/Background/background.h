#ifndef BACKGROUNDPROCESS
#define BACKGROUNDPROCESS

#include "../Framework/SbiRobotFactory.h"
#include "../Framework/Neural.h"
#include "../../Box2D/Include/Box2D.h"
#include "../PSO/definitions.h" // debugging, parameters

class BackgroundProcess {
	public:
		BackgroundProcess(bool debug); // constructor
		BackgroundProcess(double** networkWeights, bool debug);
		~BackgroundProcess();
		double Fitness();
		
	private:
		void Init(bool debug);
		
		void DefineWorld();
		void MakeFigure();
		
		// RobotFactory (also contains neural update functions)
		SbiRobotFactory* robotFactory;
		
		// World
		b2World* world;
		// geometric constructs
		b2Body* body;
		b2Body* wheelLeft;
		b2Body* wheelRight;
		b2RevoluteJoint* jointLeft;
		b2RevoluteJoint* jointRight;
		
		// Neural Network
		Neural* neural;
		
		// debug
		bool debug;
};

#endif
