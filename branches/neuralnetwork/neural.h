// $Id: neural.h 36 2010-11-18 14:29:03Z xcheng $
/*!
 @file
 @author xcheng
 @class Neural
 @brief Strongly connected recurrent neural network with mutiple input and outputs
 @detail This RNN has the form: I -> H1 ... Hn -> O where I is a input layer and O the output. The hidden layer H's are strongly connected. Meaning all the nodes in the the layer has a connection to all other nodes. N nodes per layer are constant.
 The implementation idea is as follow:
 Take a network with 2 inputs, 2 outputs, 2 hidden layers and 2 nodes per layer. It is represented as:
 For the nodes:
 I = [i1, i2]
 O = [o1, o2]
 H = [n11, n12, n21, n22]

 Their respective weights:
 wI = [
    i1 n11, i1 n12, i1 n21, i1 n22;
    i2 n11, i2 n12, i2 n21, i2 n22;
    ]
 wO = [
    o1 n11, o1 n12, o1 n21, o1 n22;
    o2 n11, o2 n12, o2 n21, o2 n22;
    ]
 wH = [
    n11 n11, n11 n12, n11 n21, n11 n22;
    n12 n11, n12 n12, ... ;
    ... ;
    n22 n11, ..., n22 n22;
    ]
 The hidden layers activations are processed one after another.
 for H1, the first hidden layer:
 aH(y, x) = sum(Ii*wI(i, n1x)) + sum(aH(y,x) * wH(y, nyx))
 aO(y, x) = sum(i*wI(i, n1x) + aH(1,x)
*/
#ifndef NEURAL_H
#define NEURAL_H

class Neural {
    public:
        /*!
         Construct a recurrent neural network using default parameters
        */
        Neural();

        /*!
         Construct a RNN using the following parameters
         @param[in] inputs Number of inputs
         @param[in] outputs Number of outputs
         @param[in] hiddenLayers Number of hidden layers
         @param[in] nodesPerLayer Number of nodes per hidden layer
        */
        Neural(int inputs, int outputs, int hiddenLayers, int nodesPerLayer);

        //! Destructor
        ~Neural();
        
        /*!
         Calculates the outputs given a set of inputs and the weights for each edge. Number of input elements should match with the amount used to initialize this Neural network. Same for outputs. 
         @note This method should be called after setting the weights!
         @param[in] inputs Set of input values for the network
         @param[out] outputs Array where the output values are stored in
        */
        void perform(double* inputs, double* outputs);

        /*!
         Sets the weight values for all edges. The amount should adhere to (LN)^2+ILN + OLN where L is the number of hidden layers, N nodes per layer, I number of inputs, O number of outputs. 
         @param[in] weightsHidden Set of weights for all edges in the hidden layers
         @param[in] weightsInputs Set of weights for all edges from inputs to all nodes in all hidden layers
         @param[in] weightsOutputs Set of weights for all edges from all nodes in all hidden layers to all outputs
        */
        void setWeights(double** weightsInputs, double** weightOutputs, double** weightsHidden);
        //! same as above, but this one accepts a serialized array of floats
        void setWeights(double* weights);
        
        //! Total weights count
        int size();

        //! Prints the whole network to stdout
        void print();
        
    private:
        //! Makes a neural network with given parameters
        void makeNetwork(int inputs, int outputs, int hiddenLayers, int nodesPerLayer);
        //! 1 / 1*e^(-value/alpha)
        double sigmoid(double value);
        const static double alpha = 1;

        //! sigmoid differential
        double sigmoid_dif(double value);
        
        //! Internal variables    
        double** _weightsHidden;
        double** _weightsInputs;
        double** _weightsOutputs;
        int _inputs;
        int _hiddenLayers;
        int _nodesPerLayer;
        int _outputs;
};

#endif
