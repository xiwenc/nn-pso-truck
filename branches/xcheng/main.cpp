// $Id$

#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

#include "bs.h"
#include "definitions.h"

using namespace std;

double config[CONFIG_SIZE];

namespace
{
    BS* swarm;
    Vec solution;
}

int main(int argc, char** argv)
{
    // default values
    config[CONFIG_DEBUGLEVEL] = DEBUGLEVEL;
    config[CONFIG_ITERATIONS] = ITERATIONS;
    config[CONFIG_NUM_PARTICLES] = NPARTICLES;
    config[CONFIG_VMAX] = VMAX;
    config[CONFIG_XMAX] = XMAX;
    config[CONFIG_INERTIA] = INERTIA;
    config[CONFIG_SOCIAL] = SOCIAL;
    config[CONFIG_MEMORY] = MEMORY;
    config[CONFIG_DIMENSIONS] = DIMENSIONS; // calculate this!
    config[CONFIG_SHOW_ITERATIONS] = 0;
    config[CONFIG_MAXSPEED] = MAXSPEED;
    config[CONFIG_SURVIVORS] = SURVIVORS;
    config[CONFIG_MODE] = MODE;

    // parse arguments and override above parameters where necessary
    int c, errflg = 0;
    extern char* optarg;
    extern int optopt;
    while ((c = getopt(argc, argv, "v:d:i:p:a:s:m:")) != -1) {
        switch (c) {
            case 'v':
                config[CONFIG_DEBUGLEVEL] = atoi(optarg);
                break;
            case 'd':
                config[CONFIG_DIMENSIONS] = atoi(optarg);
                break;
            case 'i':
                config[CONFIG_ITERATIONS] = atoi(optarg);
                break;
            case 'p':
                config[CONFIG_NUM_PARTICLES] = atoi(optarg);
                break;
            case 'a':
                config[CONFIG_SHOW_ITERATIONS] = atoi(optarg);
                break;
            case 's':
                config[CONFIG_SURVIVORS] = atoi(optarg);
                break;
            case 'm':
                config[CONFIG_MODE] = atoi(optarg);
                break;
            case ':':
                fprintf(stderr, "\nERROR: Option -%c requires an operand\n", optopt);
                errflg++;
                break;
            case '?':
                errflg++;
                break;
            default:
                break;
        }
    }

    if (errflg) {
        fprintf(stderr, "\nUsage: %s\n\tOptions:\n", argv[0]);
        fprintf(stderr, "\t-v INTEGER\tDebug level, 0-4 [deprecated] \n");
        fprintf(stderr, "\t-d INTEGER\tDimensionality, 1-%d\n", IN_NODES);
        fprintf(stderr, "\t-i INTEGER\tNumber of Swarm iterations, 1 or more\n");
        fprintf(stderr, "\t-p INTEGER\tNumber particles per Swarm, 1 or more\n");
        fprintf(stderr, "\t-a INTEGER\tShow global best after every iteration, 1 or 0\n");
        fprintf(stderr, "\t-s INTEGER\tNumber survivors, 1 or more, must be less than number of particles\n");
        fprintf(stderr, "\t-m INTEGER\tMode\n\t\t0 = BS, \n\t\t1 = PSO, \n\t\t2 = GA with VPAC");
        exit(2);
    }


    // initialize a BS
    swarm = new BS(config[CONFIG_NUM_PARTICLES], config[CONFIG_DIMENSIONS], config[CONFIG_MODE]);

    double f1, f2 = 0;
    float inertia = 0.7;
    float mrate = 1;

    for (int i = 0; i < config[CONFIG_ITERATIONS]; i++) {
        float inertia2 = inertia - (i/config[CONFIG_ITERATIONS])*inertia;
        if (inertia2 < 0.4) inertia2 = 0.4;
        float mrate2 = mrate - (i/config[CONFIG_ITERATIONS])*mrate;

        swarm->update(inertia2, mrate2);
        f1 = swarm->getGlobalBestFitness();
        if (f1 != f2 || config[CONFIG_SHOW_ITERATIONS]) {
            f2 = f1;
            printf("%d\t%e\n", i, f1);
        }
    }

#ifdef PULSE
    solution = swarm->getGlobalBest();
    vector<float> fl = solution.getVector();
    Neural neural(IN_NODES, OUT_NODES, HIDDEN_LAYERS, NODES_PER_LAYER);
    double myWeights[fl.size()];
    double in[2], out[2];
    for (unsigned int i = 0; i < fl.size(); i++) {
        myWeights[i] = fl[i];
    }
    neural.setWeights(myWeights);
    neural.resetMemory();
    for (int i = 1; i <= 100; i++) {
        in[0] = (float) i;
        neural.perform(in, out);
        printf ("%d\t%e\n", i, out[0]);
    }

#endif

    delete swarm;

    return 0;
}
