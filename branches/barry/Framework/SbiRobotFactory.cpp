#include <iostream>
#include <cmath>
#include <vector>
#include "SbiRobotFactory.h"
#include "../PSO/definitions.h"
using namespace std;

SbiRobotFactory::SbiRobotFactory() {
	// body
	halfBodyHeight.Set(0.0f, 0.8f);
	halfBodyWidth.Set(1.5f, 0.0f);
	// starting height
	bodyStartHeight.Set(0.0f, 8.0f);
	// body offset
	bodyOffset.Set(-30.0f, 0.0f);
	// FileHandler
	fileHandler = new FileHandler();
}

b2Body* SbiRobotFactory::CreateBody(b2World* world) {
	// shape definition
	b2PolygonDef sd;
	sd.density = 1.0f;
	sd.SetAsBox(bodyWidth, bodyHeight);
	sd.filter.groupIndex = -1;
	// body definition
	b2BodyDef bd;
	bd.position = bodyStartHeight + bodyOffset;
	b2Body* body = world->CreateBody(&bd);
	body->CreateShape(&sd);
	body->SetMassFromShapes();
	return body;
}

b2Body* SbiRobotFactory::CreateWheel(b2World* world, int index) {
	b2CircleDef sd;
	sd.density = 1.0f;
	sd.radius = 0.5f;
	sd.filter.groupIndex = -1;
	b2BodyDef bd;
	
	b2Vec2 offset(pow(-1, index) * bodyWidth, 0.0f);
	bd.position = offset + bodyOffset; // original position of wheel
	b2Body* wheel = world->CreateBody(&bd);
	wheel->CreateShape(&sd);
	wheel->SetMassFromShapes();
	return wheel;
}

b2RevoluteJoint* SbiRobotFactory::CreateJoint(b2World* world, b2Body* body, b2Body* wheel, int index) {
	b2Vec2 offset(pow(-1, index) * bodyWidth, 0.0f);
	b2Vec2 pos = offset + bodyStartHeight + bodyOffset; // position of joint
	
	b2RevoluteJointDef jd;
	jd.Initialize(wheel, body, pos);
	jd.collideConnected = false;
	// speed
	jd.motorSpeed = ((rand() % 100) / 100.0) * maxMotorSpeed;
	jd.maxMotorTorque = 400.0f;
	jd.enableMotor = true;
	return (b2RevoluteJoint*)world->CreateJoint(&jd);
}

b2Body* SbiRobotFactory::DefineGround(b2World* world) {
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonDef groundShapeDef;

	// The extents are the half-widths of the box.
	groundShapeDef.SetAsBox(75.0f, 10.0f);

	// Add the ground shape to the ground body.
	groundBody->CreateShape(&groundShapeDef);
	
	return groundBody;
}

///
///
///
Neural* SbiRobotFactory::CreateNeuralNetwork(bool debug){
	Neural* result = new Neural(IN_NODES, HIDDEN_NODES, OUT_NODES, ITERATIONS, debug);
	// Get weights from file and load
	double** weights = fileHandler->LoadWeights();
	if (weights != NULL) {
		result->SetNetwork(weights);
	}
	return result;
}

// Transform the vector<float> from a particle to double**
double** SbiRobotFactory::TransformParticleResultToWeights(vector<float> best) {
	double** result = new double*[TOTAL_NODES];
	for (int i = 0; i < TOTAL_NODES; i++) {
		result[i] = new double[TOTAL_NODES];
	}
	if (best.size() == (TOTAL_NODES * TOTAL_NODES)) {
		int count = 0;
		for (int i = 0; i < TOTAL_NODES; i++) {
			for (int j = 0; j < TOTAL_NODES; j++) {
				result[i][j] = best[count];
				count++;
			}
		}
	}
	else {
		return NULL;
	}
	return result;
}

/// Save the weights to default file
void SbiRobotFactory::SaveWeights(double** weights, int size) {
	fileHandler->SaveWeights(weights, size);
}

void SbiRobotFactory::PerformNeuralNetwork(b2Body* body, b2RevoluteJoint* left, b2RevoluteJoint* right, Neural* network) {
	double* in = new double[IN_NODES];
	in[0] = abs(left->GetMotorSpeed() / maxMotorSpeed);	// to normalize to [0..1]
	in[1] = left->GetMotorSpeed() < 0 ? 0 : 1;		// 0: clockwise, 1: ccw
	in[2] = left->GetJointAngle() / (2 * M_PI);		// defined in radius
	in[3] = abs(right->GetMotorSpeed() / maxMotorSpeed);	// to normalize to [0..1]
	in[4] = right->GetMotorSpeed() < 0 ? 0 : 1;		// 0: clockwise, 1: ccw
	in[5] = -right->GetJointAngle() / (2 * M_PI);	// defined in radius
	in[6] = (1 / (1 + body->GetPosition().y));		// to normalize to [0..1]
	in[7] = body->GetAngle() / (2 * M_PI);			// defined in radius
	// Execute Neural Network
	double* newSpeed = network->Perform(in);
	// Get new output
	left->SetMotorSpeed(NewMotorSpeed(newSpeed[0]));
	right->SetMotorSpeed(NewMotorSpeed(newSpeed[1]));
	delete [] in;
	delete [] newSpeed;
}

double SbiRobotFactory::NewMotorSpeed(double speed) {
	return (speed - 0.5) * 2 * maxMotorSpeed;
}

// GET
b2Vec2 SbiRobotFactory::GetBodyOffset() {
	return bodyOffset;
}


