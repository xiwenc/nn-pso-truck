// $Id: definitions.h 74 2010-12-21 18:23:55Z xcheng $

#ifndef _DEFINITIONS_
#define _DEFINITIONS_

// Debugging
#define DEBUGLEVEL 0 // > 1 is more details

// Neural Network
#define IN_NODES 1 // max 10
#define HIDDEN_LAYERS 5
//#define NODES_PER_LAYER 5
#define NODES_PER_LAYER 5
#define OUT_NODES 1 // max 4

// program
#define MODE 0 // 0 = BS, 1 = PSO, 2 = GA with VPAC
//#define PULSE // pulsed eval

// PSO
#define ITERATIONS 10
#define NPARTICLES 10
#define DIMENSIONS 675
//#define DIMENSIONS 35
#define SURVIVORS 5

#define VMAX 1.0
#define XMAX 1.0

#define INERTIA 0.7 //how much is the particle influenced by it's current velocity
#define MEMORY 2.0  //how much is the particle influenced by it's personal best
#define SOCIAL 2.0  //how much is the particle influenced by the local/global best

// Test/Truck
#define MAXSPEED 50
#define MAXTORC 100 // default torc is MAXTORC/2
#define TARGET_X 55 // target x value of the truck

typedef enum ConfigT {
    CONFIG_DEBUGLEVEL,
    CONFIG_IN_NODES,
    CONFIG_HIDDEN_LAYERS,
    CONFIG_NODES_PER_LAYER,
    CONFIG_OUT_NODES,
    CONFIG_ITERATIONS,
    CONFIG_NUM_PARTICLES,
    CONFIG_VMAX,
    CONFIG_XMAX,
    CONFIG_INERTIA,
    CONFIG_SOCIAL,
    CONFIG_MEMORY,
    CONFIG_MAXSPEED,
    CONFIG_MAXTORC,
    CONFIG_DIMENSIONS,
    CONFIG_SHOW_ITERATIONS,
    CONFIG_TARGET_X,
    CONFIG_SURVIVORS,
    CONFIG_MODE,
    CONFIG_SIZE
} ConfigT;

extern double config[CONFIG_SIZE];

#endif
