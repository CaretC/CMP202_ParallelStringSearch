/*
CharTable
=========
The CharTable class is used by the boyer-moore algorithm to pre-process the pattern string.
*/
#pragma once

// Includes
// ========
#include <string>

// Imports
// =======
using std::string;

// Class
// ======
class CharTable
{
	public:
		// Constructor
		CharTable(string pattern);

		// Check if the character is in the pattern, if it is return the position for skipping
		int In(char character);

		// Return the pattern length
		int Length();

	private:
		// Store the pattern that the CharTable is pre-processed for
		string tablePattern;

		// Pattern length
		int patternLength;

		// Store if the required character is in the pattern and if so what position
		int skipValues[256];
};

