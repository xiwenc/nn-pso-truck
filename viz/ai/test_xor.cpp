// $Id: test_xor.cpp 59 2010-11-23 11:42:14Z xcheng $

#include <stdio.h>
#include "neural.h"
#include "pso.h"

int main() {
    // L*N^2 + I*L*N + O*L*N
    PSO swarm(1, 2*2*2*2+2*2*2+1*2*2);
    for (int i = 0; i < 5; i++) {
        swarm.update();
        printf("gbest: %f \n", swarm.GetGBestValue());
    }
    return 0;
}
