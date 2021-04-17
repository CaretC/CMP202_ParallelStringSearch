/*
PatternListLoader
=================
Class to load a list of patterns to search for from a text file and store them in
a vector for use. The patterns will be loaded one pattern per line in the text file.
*/

// Includes
// ========
#include "PatternListLoader.h"

// Public Functions
// ================
// Load the pattern file and parse it to have one patter per line of the text file and save in output vector
void PatternListLoader::LoadPatternList(string patternListFilePath, vector<string>& outputVector)
{
	// Open input file
	ifstream inFile;
	inFile.open(patternListFilePath);

	// If the file opens successfully read it
	if (inFile.is_open())
	{
		// Temp line variabel
		string line;

		// Read the entire file line-by-line and save in outputVector
		while (getline(inFile, line))
		{
			// Save the line in output veector
			outputVector.push_back(line);
		}
	}
	// If the file is not opened successfully print error and exit
	else
	{
		cout << "ERROR!" << endl;
		cin;
		exit(1);
	}
}

// Private Functions
// =================
