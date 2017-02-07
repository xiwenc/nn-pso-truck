all: pso

pso: main.o math.o pso.o particle.o vec.o
	g++ -Wall main.o math.o pso.o particle.o vec.o -o pso

main.o: main.cpp pso.h
	g++ -c -Wall main.cpp
	
math.o: math.cpp math.h
	g++ -c -Wall math.cpp

pso.o: pso.cpp pso.h particle.h vec.h math.h definitions.h
	g++ -c -Wall pso.cpp

particle.o: particle.cpp particle.h vec.h math.h definitions.h
	g++ -c -Wall particle.cpp
	
vec.o: vec.cpp vec.h
	g++ -c -Wall vec.cpp
	
clear:
	rm *.o pso
	
run: pso
	./pso

recomp: clear run

clean: clear
