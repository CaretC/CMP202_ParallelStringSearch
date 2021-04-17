/*
TextLoader
==========
Loads a .txt file into memory for use with other algorithms.
*/

// Includes
// ========
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Imports
// =======
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ifstream;
using std::stringstream;

// Class
// =====
#pragma once
class TextLoader
{
	// Public
	// ------
	public:
		// Load the specified text file into the specifed output
		void LoadFile(string inputFilePath, string& outputVariable);

	// Private
	// -------
	private:
};

