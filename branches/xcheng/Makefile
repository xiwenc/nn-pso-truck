CC = g++
CFLAGS = -O2 -Wall -g
CFLAGS = -Wall -g
OBJECTS = neural.o pso.o particle.o vec.o math.o bs.o ga.o
MAIN = main

all: $(MAIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS) main.cpp

clean: 
	rm -f *.o
	rm -f $(MAIN)

