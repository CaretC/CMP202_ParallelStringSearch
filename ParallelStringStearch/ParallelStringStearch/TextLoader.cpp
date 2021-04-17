/*
TextLoader
==========
Loads a .txt file into memory for use with other algorithms.
*/

// Includes
// ========
#include "TextLoader.h"

// Public Functions
// ================
// Load the specified text file into the specifed output
void TextLoader::LoadFile(string inputFilePath, string& outputVariable)
{
	// Open input file
	ifstream inFile;
	inFile.open(inputFilePath);

	// If the file opens successfully load it
	if (inFile.is_open())
	{
		// Read the file to a string stream
		stringstream inFileStrStream;
		inFileStrStream << inFile.rdbuf();

		// Write read buffer to the outputVariable
		outputVariable = inFileStrStream.str();

		// Close the inFile
		inFile.close();
	}
	// If the file fails to open print error and exit
	else
	{
		cout << "ERROR!" << endl;
		cin;
		exit(1);
	}
}

// Private Functions
// =================

