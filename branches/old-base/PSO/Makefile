all: pso

pso: main.o math.o pso.o particle.o vec.o
	g++ -Wall main.o math.o pso.o particle.o vec.o -o pso

main.o: main.cc pso.h
	g++ -c -Wall main.cc
	
math.o: math.cc math.h
	g++ -c -Wall math.cc

pso.o: pso.cc pso.h particle.h vec.h math.h definitions.h
	g++ -c -Wall pso.cc

particle.o: particle.cc particle.h vec.h math.h definitions.h
	g++ -c -Wall particle.cc
	
vec.o: vec.cc vec.h
	g++ -c -Wall vec.cc
	
clear:
	rm *.o pso
	
run: pso
	./pso

recomp: clear run

clean: clear
