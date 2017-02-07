#include "Neural.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Perform an entire calculation on the Neural Network
double* Neural::Perform(double* inArray) {
	// hidden node values
	double* hidden = new double[hiddenNodes];
	
	// get input to hidden nodes
	for (int i = 0; i < hiddenNodes; i++) {
		double val = 0;
		for (int in = 0; in < inNodes; in++) {
			val += inArray[in] * network[in][inNodes + i];
		}
		hidden[i] = Sigmoid(val, inNodes);
	}
	
	// perform hidden nodes operation `iteration` times
	for (int i = 0; i < iterations; i++) {
		double* newHidden = new double[hiddenNodes];
		for (int i = 0; i < hiddenNodes; i++) {
			double val = 0;
			for (int old = 0; old < hiddenNodes; old++) {
				val += hidden[old] * network[inNodes + old][inNodes + i];
			}
			newHidden[i] = Sigmoid(val, hiddenNodes);
		}
		delete [] hidden;
		hidden = newHidden;
	}
	
	// copy hidden nodes to output using sigmoid
	double* result = new double[outNodes];
	for (int i = 0; i < outNodes; i++) {
		double val = 0;
		for (int h = 0; h < hiddenNodes; h++) {
			val += hidden[h] * network[inNodes + h][inNodes + i];
		}
		result[i] = Sigmoid(val, hiddenNodes);
	}
	
	// cleanup hidden node values
	delete [] hidden;
	
	return result;
}

// update the network
void Neural::UpdateNetwork(double** deviations) {
	for (int i = 0; i < Size(); i++) {
		for (int j = 0; j < Size(); j++) {
			network[i][j] += deviations[i][j];	
		}
	}
}

// computes the sigmoidal output
double Neural::Sigmoid(double value, int nodes) {
	double result = 1 / (1 + exp(-value / alpha));
	return result;
}

// Make the Neural Network
double** Neural::MakeNeural(int in, int hidden, int out, int its) {
	// seed random
	srand(time(NULL));
		
	hiddenNodes = hidden;
	inNodes = in;
	outNodes = out;
	iterations = its;
	
	// make the network
	double** result = new double*[Size()];
	for (int i = 0; i < Size(); i++) {
		result[i] = new double[Size()];
	}
	
	// set random variables on the edges
	double totalRand = 0;
	int granularity = 100; // how fine-grained random is
	for (int i = 0; i < Size(); i++)
		for (int j = 0; j < Size(); j++)
			if (i != j) {
				double r = ((rand() % granularity) / ((double)granularity * 0.5)) - 1; // [-1..1]
				totalRand += r;
				result[i][j] = r;
			}
	//for (int i = 0; i < inNodes; i++)
	//	for (int j = inNodes; j < inNodes + hiddenNodes; j++)
	//		result[i][j] = 1; 
			
	PrintNetwork(result);
	if (debugging) cerr << "Total random: " << totalRand << ", div by N^2-N: " << totalRand / (pow(Size(), 2) - Size()) << endl;
	return result;
}

int Neural::Size() {
	return inNodes + hiddenNodes + outNodes;
}

// Constructors
Neural::Neural(bool debug) {
	debugging = debug;
	network = MakeNeural(4, 20, 4, 25);
}

Neural::Neural(int in, int hidden, int out, int iterations, bool debug) {
	debugging = debug;
	network = MakeNeural(in, hidden, out, iterations);
}

// Destructor
Neural::~Neural() {
	DeleteNetwork();
}

// Deletes the network for destructor and SetNetwork
void Neural::DeleteNetwork() {
	for (int i = 0; i < Size(); i++) {
		delete [] network[i];
		network[i] = NULL;
	}
	delete [] network;
	network = NULL;
}

// GET/SET
double** Neural::GetNetwork() {
	return network;
}

void Neural::SetNetwork(double** aNetwork) {
	/*for (int i = 0; i < Size(); i++) {
		for (int j = 0; j < Size(); j++) {
			network[i][j] = aNetwork[i][j];
		}
	}*/
	DeleteNetwork();
	network = aNetwork;
}

// DEBUG
void Neural::PrintNetwork(double** aNetwork) {
	if (debugging) {
		cerr << endl << "Printing Weights Network: " << endl;
		for (int i = 0; i < Size(); i++) {
			bool first = true;
			for (int j = 0; j < Size(); j++) {
				if (!first) cerr << " || ";
				else first = false;
				cerr << aNetwork[i][j];
			}
			cerr << endl;
		}
		cerr << endl;
	}
}
