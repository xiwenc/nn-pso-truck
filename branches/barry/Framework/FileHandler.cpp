#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

FileHandler::FileHandler() {
	defaultFilenameIn = "weightsIn.nnw";
	defaultFilenameOut = "weightsOut.nnw";
}

void FileHandler::SaveWeights(double** weights, int size) {
	SaveWeights(weights, size, defaultFilenameOut);
}

void FileHandler::SaveWeights(double** weights, int size, string filename) {
	ofstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		// save the weights to file
		file << size << endl; // save 'size'
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				file << weights[i][j] << " "; // save every weight
			}
			file << endl; // per row
		}
		file.close();
	}
}

double** FileHandler::LoadWeights(void) {
	return LoadWeights(defaultFilenameIn);
}

double** FileHandler::LoadWeights(string filename) {
	ifstream file;
	file.open(filename.c_str());
	double** result = NULL;
	if (file.is_open()) {
		// get size
		int size = 0;
		string line;
		if (!file.eof()) {
			getline(file, line);
			size = atoi(line.c_str());
		}
		if (size > 0) {
			// make array
			result = new double*[size];
			for (int i = 0; i < size; i++) {
				result[i] = new double[size];
			}
			char cline[2056];
			int i = 0;
			while (!file.eof()) {
				getline(file, line);
				// make sure line is not empy
				if (line.length() > 0) {
					// make c-style string
					strcpy(cline, line.c_str());
					// tokenize
					char* w;
					w = strtok(cline, " ");
					// for every element in row
					int j = 0;
					while (w != NULL) {
						double weight = atof(w);
						result[i][j] = weight;
						w = strtok(NULL, " ");
						j++;
					}
				}
				i++;
			}
		}
	}
	return result;	
}

