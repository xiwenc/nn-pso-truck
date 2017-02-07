Made available on Github (not tested)
Video of a trained system at https://www.youtube.com/watch?v=J_QZrTARB8A

Introduction
==

This project was a product of an assignment build during the Swarm Intelligence Class at Leiden Institute of Advanced Computer Science (LIACS), Leiden University. This master class was given by Prof. T. Baeck and Rui Li of the Natural Computing Group (http://natcomp.liacs.nl).

Officially this project was and still hosted at https://i.cinaq.com/redmine/swi2010

This is published with the intent to be useful to others interested in Neural Networks and Particle Swarm Optimizer. The target was to train a Recurrent NN using PSO where the NN controls a truck in a one dimensional world written in C++ with the Box2D framework.

There are 3 versions:
trunk - simple world without visualization
hard - same as trunk but with more difficult world
viz - same as hard but with visualization (how the training improves over time)

Included in the .tar.gz you'll find refman.pdf which is the doxygen generated documentation of the classes. The HTML version is also available online on the official project site.

Parameters
==
```
Usage: ./dist/Debug/GNU-Linux-x86/trunk
    Options:
    -d INTEGER  Debug level, 0-4
    -i INTEGER  Input nodes, 1-10
    -o INTEGER  Output nodes, 1-2
    -l INTEGER  Hidden layers, 1 or more
    -n INTEGER  Nodes per hidden layer, 1 or more
    -t INTEGER  Number of Swarm iterations, 1 or more
    -p INTEGER  Number particles per Swarm, 1 or more
    -a INTEGER  Show global best after every iteration, 1 or 0
    -x FLOAT    Target x-value
```

License
==
GPL v2 - We would appreciate if credits could be given back to us and we're eager to know how this project is used in future projects.
Please also note that part of this project was taken from a previous project which we don't know who the original authors were. If you are, please let us know to give you credit. The parts in question are the PSO implementation and the smaller classes like vector and particle.


Instructions
==

```
# there shouldn't be any exotic libraries you need to solve manually

# First you need to build Box2D:
cd Box2D
make
cd ../

# second build the trunk:
cd trunk
make

# to run the app:
./run.sh

# optionally generate doxygen documentation for this project:
doxygen doxy.cfg
cd docs/latex
make && make
cp refman.pdf ../../docs/
```
