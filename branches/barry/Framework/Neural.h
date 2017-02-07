#ifndef NEURAL
#define NEURAL

// (Almost) fully connected Hopfield neural network
// with input nodes and output nodes.
// Where n incl. input and output nodes
class Neural {
	public:
		// Construct Neural with standard parameters
		Neural(bool debug);
		// Construct Neural with given parameters
		// int in: amount of input nodes
		// int hidden: amount of hidden nodes
		// int out: amount of output nodes
		// int iterations: amount of iterations of the `hidden` network
		Neural(int in, int hidden, int out, int iterations, bool debug);
		// Destructor
		~Neural();
		
		// Get output after performing an operation of the 
		// neural network
		// double* in: array of inputs of size inNodes
		// double* result: array of outputs of size outNodes
		double* Perform(double* in);
		// Updates the network with the velocity of a particle
		// double** deviations: 2D array of deviations of size hiddenNodes
		void UpdateNetwork(double** deviations);
		
		// Useful functionality
		// Gets the size of the dynamic array
		int Size();
		
		// get/set
		double**	GetNetwork();
		void		SetNetwork(double** network);
		
	private:
		// Makes a neural network with given parameters
		double** MakeNeural(int n, int in, int out, int iterations);
		// Deletes the dynamically created double** network
		void DeleteNetwork();
		
		// Important
		// 1 / 1*e^(-value/alpha)
		double Sigmoid(double value, int nodes);
		const static double alpha = 1;
		
		
		double** network;
		int inNodes;
		int hiddenNodes;
		int outNodes;
		int iterations;
		
		// debug
		bool debugging;
		void PrintNetwork(double** aNetwork);
};

#endif
