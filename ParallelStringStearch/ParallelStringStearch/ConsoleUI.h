/*
ConsoleUI
=========
This class provides some set functions for the console UI, simplifying message printing and graphics etc.
*/
#pragma once

// Includes
// ========
#include <iostream>
#include <string>
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <unordered_map>
#include <mutex>

// Imports
// =======
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::mutex;
using std::unique_lock;

// Class
// =====
class ConsoleUI
{
	// Public
	// ------
	public:
		// Constructor
		ConsoleUI();

		// Print the main welcome screen for the program
		void PrintWelcome();

		// Print a generic message to the console
		void PrintMessage(string message);

		// Print a messasge that a specific file is loading
		void PrintFileLoadingMessage(string filePath);

		// Print a message that a specific file is loading
		void PrintFileLoadMessage(string filePath);

		// Print a success message
		void PrintSuccess(string successMessage);

		// Print an error message
		void PrintError(string errorMessage);

		// Print press key message
		void PrintPressKeyMessage(string keyName, string toDo);

		// Print search start message
		void PrintSearchStartMessage(string searchName);

		// Print search stop message
		void PrintSearchCompleteMessage(string searchName);

		// Print search timing infromation
		void PrintSearchTiming(string searchName, long long duration_ms);

		// Wait For Key Press
		void WaitForKeyPress();

		// Clear the console
		void Clear();

		// Print the pattern hit results
		void PrintResults(string searchName, vector<int>* results, vector<string>* patternList);

		void PrintResults(string searchName, unordered_map<string, int>* results, vector<string>* patternList);

	// Private
	// -------
	private:
		// Console Handle
		HANDLE hConsole;

		// Console Mutex
		mutex consoleMutex;

		// Console colors
		enum consoleColor
		{
			CYAN = 11,
			DEFAULT = 7,
			RED = 12,
			GREEN = 10,
			MAGENTA = 13,
			YELLOW = 14
		};

		// Set the console text color
		void setTextColor(int colorCode);

		// Set the console text to default color
		void setTextDefault();

		// Print a title block with the title
		void printTitle(string title);
};

