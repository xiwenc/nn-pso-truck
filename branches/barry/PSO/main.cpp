#include "pso.h"
#include <iostream>

/**
 * main loop
 */
int main (void) {
	PSO swarm(20, 2);
        swarm.update();
        for (int i=0; i<100; i++) {
            swarm.update();
            cout << swarm.GetGBestValue() << endl;
        }
        //cout << swarm.GetGBestValue() << endl;
	return 0;
}//main
