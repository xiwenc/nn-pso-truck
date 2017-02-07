#include "pso.h"

/**
 * main loop
 */
int main (void) {
	PSO swarm(10, 2);
	swarm.update();
	swarm.update();
	return 0;
}//main
