/*
CsvWriter
=========
Class to take in the results for the BenchmarkTimer and write these out to a .csv file
to allow to external potting etc.
*/

#pragma once
// Includes
// ========
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Imports
// =======
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

// Class
// =====
class CsvWriter
{
	// Public
	// ------
	public:
		// Write the resuts from BenchmarkTimer to the output file as .csv
		void WriteToFile(vector<long long>& results, string outputFilePath);

		// Write 3 searches results to file
		void WriteToFile(long long& seqResult, vector<long long>& taskResults, string outputFilePath);

	// Private
	// -------
	private:
};

