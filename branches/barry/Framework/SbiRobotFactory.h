#ifndef SBIROBOTFACTORY
#define SBIROBOTFACTORY

#include <vector>
#include "../../Box2D/Include/Box2D.h"
#include "Neural.h"
#include "../PSO/definitions.h"
#include "FileHandler.h"
using namespace std;

class SbiRobotFactory {
	public:
		SbiRobotFactory();
		
		// Create Ground & Robot
		b2Body* DefineGround(b2World* world);
		b2Body* CreateBody(b2World* world);
		b2Body* CreateWheel(b2World* world, int index);
		b2RevoluteJoint* CreateJoint(b2World* world, b2Body* body, b2Body* wheel, int index);
		
		// Make the neural network
		Neural* CreateNeuralNetwork(bool debug);
		// Transform the vector<float> from a particle to double**
		double** TransformParticleResultToWeights(vector<float> best);
		
		// FileHandler
		void SaveWeights(double** weights, int size);
		
		// Perform a step of the neural network using given parameters, 
		// and make sure to update the results within the given bodies.
		void PerformNeuralNetwork(b2Body* body, b2RevoluteJoint* left, b2RevoluteJoint* right, Neural* network);
		
		// GET Parameters
		b2Vec2 GetBodyOffset();		
		
	private:
		// FileHandler
		FileHandler* fileHandler;
	
		// figure parameters
		static const float32 bodyHeight = 0.5f;
		b2Vec2 halfBodyHeight;
		static const float32 bodyWidth = 3.0f;
		b2Vec2 halfBodyWidth;
		
		// body starting point
		b2Vec2 bodyStartHeight;
		b2Vec2 bodyOffset;
		
		// parameters
		static const float32 maxMotorSpeed = 5.0f;
		double NewMotorSpeed(double speed);
};

#endif
