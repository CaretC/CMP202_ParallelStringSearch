/*
CsvWriter
=========
Class to take in the results for the BenchmarkTimer and write these out to a .csv file
to allow to external potting etc.
*/

// Includes
// ========
#include "CsvWriter.h"

// Public Functions
// ================
// Write the resuts from BenchmarkTimer to the output file as .csv
void CsvWriter::WriteToFile(vector<long long>& results, string outputFilePath)
{
	// Set ouput file stream
	ofstream outFile;
	outFile.open(outputFilePath);

	// Check if the outFile is open
	if (outFile.is_open())
	{
		// Write results content to file
		for (auto& duration : results)
		{
			outFile << duration << "," << endl;
		}

		// Close the outfile
		outFile.close();
	}
	// If the files dosn't open print error
	else
	{
		// TODO: Print Error
		cout << "ERROR!" << endl;
		cin;
		exit(1);
	}
}
// Write 3 searches results to file
void CsvWriter::WriteToFile(long long& seqResult, vector<long long>& taskResults, string outputFilePath)
{
	// Set ouput file stream
	ofstream outFile;
	outFile.open(outputFilePath);

	// Check if the outFile is open
	if (outFile.is_open())
	{
		// Write results content to file
		for (int i = 0; i < taskResults.size(); i++)
		{
			outFile << (i + 1) << ",";
			outFile << seqResult << ",";
			outFile << taskResults[i] << "," << endl;

		}

		// Close the outfile
		outFile.close();
	}
	// If the files dosn't open print error
	else
	{
		// TODO: Print Error
		cout << "ERROR!" << endl;
		cin;
		exit(1);
	}

}

// Private Functions
// =================


