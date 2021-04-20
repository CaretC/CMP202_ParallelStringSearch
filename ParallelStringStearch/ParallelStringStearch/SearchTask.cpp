/*
Search Task
===========
A single string search task to be processed by the farm over multiple threads. Inherits from Task Class.
*/

// Includes
// ========
#include "SearchTask.h"

// Constructor
// ===========
SearchTask::SearchTask(string pattern, string* text)
{
	SearchTask::pattern = pattern;
	p_text = text;
}

// Public Functions
// ================
// Run this SearchTask
void SearchTask::Run()
{
	BMHSearch(pattern, p_text);
}

// Private Functions
// =================
int SearchTask::BMHSearch(string pattern, string* text)
{
	// Valid matches
	int matches = 0;

	// Pre-process the pattern into char table
	CharTable pattTable(pattern);
	//cout << "Pattern pre-processed" << endl;

	// Search the text for the string
	for (int i = 0; i < (*text).length() - pattTable.Length(); i++)
	{
		// Check if the tail character is in the pattTable
		int skipStep = pattTable.In((*text)[i + pattTable.Length() - 1]);

		if (skipStep != 0)
		{
			i += skipStep - 1;
			continue;
		}

		// Check for match
		int j;
		for (j = 0; j < pattTable.Length(); j++)
		{
			if ((*text)[i + j] != pattern[j])
			{
				// This is not a match
				break;
			}
		}

		// Check if the match loop exited after finding string or breaking
		if (j == pattTable.Length())
		{
			matches++;
			// TODO: Save this somewhere
			//cout << "Match found at position " << i << endl;
		}
		else
		{
			//cout << "No match in the text found!" << endl;
		}
	}

	return matches;
}
