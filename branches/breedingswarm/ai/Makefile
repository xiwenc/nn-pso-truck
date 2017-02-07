CC = g++
CFLAGS = -O2 -Wall -g
OBJECTS = neural.o pso.o particle.o vec.o math.o bs.o
TESTS = test_xor

all: $(OBJECTS)
#all: clean $(TESTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

test_xor: $(OBJECTS)
	$(CC) $(CFLAGS) -o test_xor $(OBJECTS) test_xor.cpp

clean: 
	rm -f *.o
	rm -f $(TESTS)

