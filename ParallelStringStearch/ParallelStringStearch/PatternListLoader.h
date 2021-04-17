/*
PatternListLoader
=================
Class to load a list of patterns to search for from a text file and store them in 
a vector for use. The patterns will be loaded one pattern per line in the text file.
*/
#pragma once

// Includes
// ========
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Imports
// =======
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::getline;
using std::string;
using std::vector;

// Class
// =====
class PatternListLoader
{
	// Public
	// ------
	public:
		// Load the pattern file and parse it to have one patter per line of the text file and save in output vector
		void LoadPatternList(string patternListFilePath, vector<string>& outputVector);

	// Private
	// -------
	private:
};

