#include <iostream>
#include "background.h"
#include "../PSO/definitions.h"
using namespace std;

BackgroundProcess::BackgroundProcess(bool debug) {
	Init(debug);
}

BackgroundProcess::BackgroundProcess(double** networkWeights, bool debug) {
	Init(debug);
	neural->SetNetwork(networkWeights);
}

BackgroundProcess::~BackgroundProcess() {
	delete neural;
	delete world;
	delete robotFactory;
}

void BackgroundProcess::Init(bool debug) {
	this->debug = debug;
	robotFactory = new SbiRobotFactory();
	
	// world & ground
	DefineWorld();
	robotFactory->DefineGround(world);
	
	// robot
	MakeFigure();
	
	// set other parameters
	neural = robotFactory->CreateNeuralNetwork(this->debug);
}

double BackgroundProcess::Fitness() {
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;

	// This is our little game loop.
	for (int32 i = 0; i < 1800; ++i)
	{
		//UpdateWorld();
		robotFactory->PerformNeuralNetwork(body, jointLeft, jointRight, neural);
		// Instruct the world to perform a single step of simulation. It is
		// generally best to keep the time step and iterations fixed.
		world->Step(timeStep, iterations);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.
	return (body->GetPosition() - robotFactory->GetBodyOffset()).x;
}

void BackgroundProcess::MakeFigure() {	
	body = robotFactory->CreateBody(world);
	wheelLeft = robotFactory->CreateWheel(world, 1);
	jointLeft = robotFactory->CreateJoint(world, body, wheelLeft, 1);
	wheelRight = robotFactory->CreateWheel(world, 2);
	jointRight = robotFactory->CreateJoint(world, body, wheelRight, 2);
}

void BackgroundProcess::DefineWorld() {
	// Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, gravity, doSleep);
}


