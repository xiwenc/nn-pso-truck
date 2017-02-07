// $Id$

#include "bs.h"

BS::BS(int n, int d, int mode) {
#if DEBUGLEVEL > 2
    printf("BS::BS(%d, %d)\n", n, d);
#endif
    _M.seed();
    _n = n;
    _d = d;
    _mode = mode;
    _init();
}

BS::~BS(void) {
#if DEBUGLEVEL > 2
    printf("BS::~BS()\n");
#endif
    for (unsigned int i = 0; i < _particles.size(); ++i) {
        //delete _particles[i];
    }
}

// sorts population by fitness, _particles[0] being the largest
void BS::rank() {
#if DEBUGLEVEL > 2
    printf("BS::rank()\n");
#endif
    vector<Particle> sorted;
    bool used[_particles.size()];
    float best, current;
    int ibest = 0;

#if DEBUGLEVEL > 3
    printf("\tPRE-back: %.5f\n", _particles.back().getFitness());
    printf("\tPRE-front: %.5f\n", _particles.front().getFitness());
#endif

    for (unsigned int i = 0; i < _particles.size(); i++)
        used[i] = false;
    while (sorted.size() != _particles.size()) {
        best = 99999;
        for (unsigned int i = 0; i < _particles.size(); i++) {
            // grab largest 
            current = _particles[i].getFitness();
            if (current <= best && !used[i]) {
                ibest = i;
                best = current;
            }
        }

        // ibest contains index of particle with largest fitness
        sorted.push_back(_particles[ibest]);
        // mark it as used
        used[ibest] = true;
    }

    // replace old population with the new one, sorted
    _particles.clear();
    while (!sorted.empty()) {
        _particles.push_back(sorted.back());
        sorted.pop_back();
    }
#if DEBUGLEVEL > 3
    printf("\tPOST-back: %.5f\n", _particles.back().getFitness());
    printf("\tPOST-front: %.5f\n", _particles.front().getFitness());
#endif
}

void BS::update(float inertia, float mrate) {
#if DEBUGLEVEL > 2
    printf("BS::update(%.5f, %.5f)\n", inertia, mrate);
#endif
    int k = config[CONFIG_SURVIVORS];
    int kp = _n - k;

    vector<Particle> pop_pso;
    vector<Particle> pop_ga;



    switch (_mode) {
        case 0:
            rank();
            // pick the best k
            for (int i = 0; i < k; i++) {
                pop_pso.push_back(_particles.back());
                _particles.pop_back();
            }
            // discard the rest
            while(!_particles.empty()){
                _particles.pop_back();
            }
            _pso.setPopulation(pop_pso);
            pop_ga = _pso.updateVelocity(_gbest, inertia);
            _ga.setPopulation(pop_ga, kp);

            pop_ga = _ga.update(mrate);
            pop_pso = _pso.updateLocation(_gbest);
        break;
        case 1:
            inertia = 0.8;
            _pso.setPopulation(_particles);
            _pso.updateVelocity(_gbest, inertia);
            pop_pso = _pso.updateLocation(_gbest);
        break;
        case 2:
            _pso.setPopulation(_particles);
            pop_ga = _pso.updateVelocity(_gbest, inertia);
            _ga.setPopulation(pop_ga, pop_ga.size());
            pop_ga = _ga.update(mrate);
        break;
        default:
            // don't do anything
            pop_pso = _particles;
        break;
    }


    // merge the populations
    _particles.clear();
    for (unsigned int i = 0; i < pop_ga.size(); i++)
        _particles.push_back(pop_ga[i]);
    for (unsigned int i = 0; i < pop_pso.size(); i++)
        _particles.push_back(pop_pso[i]);

    // evaluate them
    for (unsigned int i = 0; i < _particles.size(); i++) {
        _particles[i].evaluate();
        _particles[i].updatePersonalBest();
    }

    //get gbest
    _gbest = getGlobalBest();
}

// Get the Global Best from all the Personal Bests of the Particles
Vec BS::getGlobalBest() {
#if DEBUGLEVEL > 2
    printf("BS::getGlobalBest()\n");
#endif

    //iterate over particles, find best pbest fitness value
    float newValue;
    for (unsigned int i = 0; i < _particles.size(); i++) {
        newValue = _particles[i].getPersonalBestFitness();
        if (newValue <= _gbestValue) {
            _gbest = _particles[i].getPersonalBest();
            _gbestValue = newValue;
        }
    }

    return _gbest;
        
}

// Get the Global Best from all the Personal Bests of the Particles
float BS::getGlobalBestFitness() {
#if DEBUGLEVEL > 2
    printf("BS::getGlobalBestFitness()\n");
#endif
    return _gbestValue;
}

//initialization
void BS::_init() {
    //initialize partices
    for (int i = 0; i < _n; ++i) {
        _particles.push_back(Particle(_d)); //create particle
    }

    //set initial gbest value
    _gbestValue = 999999;

    //compute gBest
    _gbest = getGlobalBest();
}//initialize particle swarm


