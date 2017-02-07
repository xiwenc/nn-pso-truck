// $Id: test_xor.cpp 73 2010-12-21 13:19:07Z xcheng $

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
