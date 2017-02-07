#ifndef __FILEHANDLER__
#define __FILEHANDLER__

#include <string>
using namespace std;

class FileHandler {
	public:
		FileHandler();
	
		void SaveWeights(double** weights, int size);
		void SaveWeights(double** weights, int size, string filename);
		double** LoadWeights();
		double** LoadWeights(string filename);
	private:
		string defaultFilenameIn;
		string defaultFilenameOut;
};

#endif
