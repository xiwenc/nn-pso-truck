// $Id: neural.cpp 73 2010-12-21 13:19:07Z xcheng $
#include "neural.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Constructors
Neural::Neural() {
    makeNetwork(1, 1, 2, 2);
}

Neural::Neural(int inputs, int outputs, int hiddenLayers, int nodesPerLayer) {
#if DEBUGLEVEL > 2
    printf("Neural::Neural(%d, %d, %d, %d)\n", inputs, outputs, hiddenLayers, nodesPerLayer);
#endif
    makeNetwork(inputs, outputs, hiddenLayers, nodesPerLayer);
}

// Destructor
Neural::~Neural() {
    // Inputs to Hidden
    for (int i = 0; i < _inputs; i++)
        delete [] _weightsInputs[i];
    delete [] _weightsInputs;
    // Hidden to Outputs
    for (int i = 0; i < _outputs; i++)
        delete [] _weightsOutputs[i];
    delete [] _weightsOutputs;
    // Hidden nodes
    for (int i = 0; i < _hiddenLayers*_nodesPerLayer; i++)
        delete [] _weightsHidden[i];
    delete [] _weightsHidden;

    // memory
    for (int i = 0; i < _hiddenLayers; i++)
        delete [] _aH[i];
    delete [] _aH;
}

void Neural::resetMemory() {
    // all activations in hidden nodes default to zero, thus no activity;
    for (int i = 0; i < _hiddenLayers; i++)
        for (int j = 0; j < _nodesPerLayer; j++)
            _aH[i][j] = 0;
}

// Perform an entire calculation on the Neural Network
// Activations for each layer is calculated sequentially
void Neural::perform(double* inputValues, double* outputValues) {

    // helper vars
    double dSum;

    // activation tables
    double *aI = inputValues;

    // hidden layers
    // foreach hidden layer h
    for (int h = 0; h < _hiddenLayers; h++) {
           for (int y = 0; y < _nodesPerLayer; y++) {
               dSum = 0;
               // inputs to hidden
               for (int x = 0; x < _inputs; x++) {
                   dSum += aI[x] * _weightsInputs[x][h * _nodesPerLayer + y];
               }

               // hidden to hidden
               for (int x = 0; x < _hiddenLayers; x++) {
                   for (int n = 0; n < _nodesPerLayer; n++) {
                       dSum += _aH[h][y] * _weightsHidden[y * _hiddenLayers + n][h * _nodesPerLayer +x];
                   }
               }
               _aH[h][y] = sigmoid(dSum);
           }
    }

    // finally the output layer :p
    for (int i = 0; i < _outputs; i++) {
        dSum = 0;
        for (int h = 0; h < _hiddenLayers; h++) {
            for (int y = 0; y < _nodesPerLayer; y++) {
                dSum += _aH[h][y] * _weightsOutputs[i][h * _nodesPerLayer + y];
            }
        }
        outputValues[i] = sigmoid(dSum);
    }
}

// computes the sigmoidal output
double Neural::sigmoid(double value) {
    double result = 1 / (1 + exp(-1 * value / alpha));
    return result;
}

// computes the sigmoidal differential output
double Neural::sigmoid_dif(double value) {
    return sigmoid(value) * (1.0 - sigmoid(value));
}

// Make the Neural Network
void Neural::makeNetwork(int inputs, int outputs, int hiddenLayers, int nodesPerLayer) {
#if DEBUGLEVEL > 2
    printf("Neural::makeNetwork(%d, %d, %d, %d)\n", inputs, outputs, hiddenLayers, nodesPerLayer);
#endif

    _inputs = inputs;
    _outputs = outputs;
    _hiddenLayers = hiddenLayers;
    _nodesPerLayer = nodesPerLayer;

    // Inputs to Hidden
    _weightsInputs = new double*[_inputs];
    for (int i = 0; i < inputs; i++)
        _weightsInputs[i] = new double[_hiddenLayers * _nodesPerLayer];
    // Hidden to Outputs
    _weightsOutputs = new double*[_outputs];
    for (int i = 0; i < _outputs; i++)
        _weightsOutputs[i] = new double[_hiddenLayers * _nodesPerLayer];
    // Hidden nodes
    _weightsHidden = new double*[_hiddenLayers * _nodesPerLayer];
    for (int i = 0; i < _hiddenLayers * _nodesPerLayer; i++)
        _weightsHidden[i] = new double[_hiddenLayers * _nodesPerLayer];
    
    // activations (memory)
    _aH = new double*[_hiddenLayers];
    for (int i = 0; i < _hiddenLayers; i++)
        _aH[i] = new double[_nodesPerLayer];
}

int Neural::size() {
    int I = _inputs;
    int O = _outputs;
    int L = _hiddenLayers;
    int N = _nodesPerLayer;
    return I*L*N + O*L*N + L*N*L*N;
}

void Neural::setWeights(double* weights) {
    int h, y;
    h = y = 0;
    int phase = 0;

    for (int i = 0; i < size(); i++) {
        switch(phase) {
            case 0:
                _weightsInputs[h][y] = weights[i];
                y++;
                if (y % (_hiddenLayers * _nodesPerLayer) == 0) {
                    h++;
                    y = 0;
                    if (h % _inputs == 0) {
                        h = 0;
                        phase++;
                    }
                }
                break;
            case 1:
                _weightsOutputs[h][y] = weights[i];
                y++;
                if (y % (_hiddenLayers * _nodesPerLayer) == 0) {
                    h++;
                    y = 0;
                    if (h % (_outputs) == 0) {
                        h = 0;
                        phase++;
                    }
                }
                break;
            case 2:
                _weightsHidden[h][y] = weights[i];
                y++;
                if (y % (_hiddenLayers * _nodesPerLayer) == 0) {
                    h++;
                    y = 0;
                    if (h % (_hiddenLayers * _nodesPerLayer) == 0) {
                        h = 0;
                        phase++;
                    }
                }
                break;
            default:
                break;
        }
    }
}
void Neural::setWeights(double** inputs, double** outputs, double** hidden) {
    // Inputs to Hidden
    for (int i = 0; i < _inputs; i++)
        for (int j = 0; j < _hiddenLayers * _nodesPerLayer; j++)
            _weightsInputs[i][j] = inputs[i][j];
    // Hidden to Outputs
    for (int i = 0; i < _outputs; i++)
        for (int j = 0; j < _hiddenLayers * _nodesPerLayer; j++)
            _weightsOutputs[i][j] = outputs[i][j];
    // Hidden nodes
    for (int i = 0; i < _hiddenLayers * _nodesPerLayer; i++)
        for (int j = 0; j < _hiddenLayers * _nodesPerLayer; j++)
            _weightsHidden[i][j] = hidden[i][j];
}

void Neural::print() {
    cout << endl << "Printing Weights Network: " << endl;
    cout << endl << "From inputs to all hidden nodes: " << endl;
    for (int i = 0; i < _inputs; i++) {
        for (int j = 0; j < _hiddenLayers*_nodesPerLayer; j++)
            cout << _weightsInputs[i][j] << " ";
        cout << endl;
    }
    cout << endl << "From all hidden nodes to outputs: " << endl;
    for (int i = 0; i < _outputs; i++) {
        for (int j = 0; j < _hiddenLayers*_nodesPerLayer; j++)
            cout << _weightsOutputs[i][j] << " ";
        cout << endl;
    }
    cout << endl << "From all hidden nodes to all hidden nodes: " << endl;
    for (int i = 0; i < _hiddenLayers*_nodesPerLayer; i++) {
        for (int j = 0; j < _hiddenLayers*_nodesPerLayer; j++)
            cout << _weightsHidden[i][j] << " ";
        cout << endl;
    }
}

