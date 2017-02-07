#include <iostream>
#include <cstdlib>
#include "../../../Include/Box2D.h"
#include "background.h"
using namespace std;

int main(int argc, char* argv[]) {
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	BackgroundProcess* bgp = new BackgroundProcess(false); // debug=false
	double result = bgp->Fitness();
	delete bgp;
	cout << "Moved to the right by: " << result << endl;
	
	return EXIT_SUCCESS;
}
