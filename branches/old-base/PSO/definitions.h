#ifndef _DEFINITIONS_
#define _DEFINITIONS_

// Debugging
#define debugging true
#define DEBUGLEVEL 1 // > 1 is more details

// Neural Network
#define IN_NODES 8
#define HIDDEN_NODES 20
#define OUT_NODES 2
#define TOTAL_NODES (IN_NODES + HIDDEN_NODES + OUT_NODES)
#define ITERATIONS 1

// Particles
#define NPARTICLES 20

#define Vmax 1.0
#define Xmax 1.0

#define inertia 0.8 //how much is the particle influenced by it's current velocity
#define memory 0.7  //how much is the particle influenced by it's personal best
#define social 0.7  //how much is the particle influenced by the local/global best

#endif
