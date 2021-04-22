/*
ConsoleUI
=========
This class provides some set functions for the console UI, simplifying message printing and graphics etc.
*/

// Includes
// ========
#include "ConsoleUI.h"

// Constructor
// ===========
ConsoleUI::ConsoleUI()
{
	// Get the current Std ouput console handle
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Disable the console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Public Functions
// ================
// Print the main welcome screen for the program
void ConsoleUI::PrintWelcome()
{
	printTitle("String Searcher");

	string asciiArt = R"(
         ______       
       .-'      `-.           Welcome the String Searcher, this tool uses the Boyer Moor Horspool
     .'            `.         algorithm to search through a text file for a list of patterns.
    /                \         
   ;                 ;`       There are several modes to this programme that conduct this search in 
   |                 |;       different ways. These are:
   ;                 ;|			
   '\               / ;          * A sequential search of the pattern list in text
    \`.           .' /           * A simple CPU parallel search with a thread per pattern
     `.`-._____.-' .'            * A busy waiting task based parallel search
      / /`_____.-'               * GPU?
     / / /                       * Accelerated by split text?
    / / /
   / / /
  / / /
 / / /
 \/_/

	)";

	cout << asciiArt << endl;
}

// Print a generic message to the console
void ConsoleUI::PrintMessage(string message)
{
	cout << " " << message << endl;
}

// Print a messasge that a specific file is loading
void ConsoleUI::PrintFileLoadingMessage(string filePath)
{
	cout << " Loading ";

	setTextColor(consoleColor::MAGENTA);

	cout << filePath;

	setTextDefault();

	cout << " ..." << endl;
}

// Print a message that a specific file is loading
void ConsoleUI::PrintFileLoadMessage(string filePath)
{
	setTextColor(consoleColor::MAGENTA);

	cout << " " << filePath;

	setTextDefault();

	cout << " loaded ";

	setTextColor(consoleColor::GREEN);

	cout << "successfully";

	setTextDefault();

	cout << "!" << endl;
}

// Print a success message
void ConsoleUI::PrintSuccess(string successMessage)
{
}

// Print an error message
void ConsoleUI::PrintError(string errorMessage)
{
}

// Print press key message
void ConsoleUI::PrintPressKeyMessage(string keyName, string toDo)
{
	cout << " Press [";

	setTextColor(consoleColor::CYAN);

	cout << keyName;

	setTextDefault();

	cout << "] to " << toDo << "..."<< endl;
}

// Print search start message
void ConsoleUI::PrintSearchStartMessage(string searchName)
{
	cout << " ";

	setTextColor(consoleColor::CYAN);

	cout << searchName;

	setTextDefault();

	cout << " started..." << endl;
}

// Print search stop message
void ConsoleUI::PrintSearchCompleteMessage(string searchName)
{
	cout << " ";

	setTextColor(consoleColor::CYAN);

	cout << searchName;

	setTextColor(consoleColor::GREEN);

	cout << " complete";

	setTextDefault();

	cout << "!" << endl;
}

// Print search timing infromation
void ConsoleUI::PrintSearchTiming(string searchName, long long duration_ms)
{
	cout << " ";

	setTextColor(consoleColor::CYAN);

	cout << searchName;

	setTextDefault();

	cout << " took a total of ";

	setTextColor(consoleColor::MAGENTA);

	cout << duration_ms;

	setTextDefault();

	cout << " ms to complete." << endl;

}

// Wait For Key Press
void ConsoleUI::WaitForKeyPress()
{
	PrintPressKeyMessage("ENTER", "continue");
	cin.get();
}

// Clear the console
void ConsoleUI::Clear()
{
	system("cls");
	printTitle("String Searcher");
	cout << endl;
}

// Print the pattern hit results
void ConsoleUI::PrintResults(string searchName, vector<int>* results, vector<string>* patternList)
{
	string line = " ";

	for (int i = 0; i < (searchName.size() + 8); i++)
	{
		line += "=";
	}

	cout << endl;
	cout << line << endl;

	setTextColor(consoleColor::CYAN);
	cout << " " << searchName;

	setTextDefault();
	cout << " Results" << endl;

	cout << line << endl;

	cout << " Pattern\t" << "Matches" << endl;
	cout << " -------\t" << "-------" << endl;

	for (int i = 0; i < results->size(); i++)
	{
		setTextColor(consoleColor::MAGENTA);
		cout << " " << (*patternList)[i];
		
		setTextDefault();
		cout << "\t--\t";
		
		setTextColor(consoleColor::CYAN);
		cout << (*results)[i] << endl;

		setTextDefault();
	}

	cout << line << endl;
	cout << endl;
}


// Private Functions
// =================
// Set the console text color
void ConsoleUI::setTextColor(int colorCode)
{
	// Check that the colorCode is within a valid range
	assert(colorCode > 0 && colorCode < 25 && "Invalid Console Color Code! Code Out of Range! ");

	SetConsoleTextAttribute(hConsole, colorCode);
}

// Set the console text to default color
void ConsoleUI::setTextDefault()
{
	SetConsoleTextAttribute(hConsole, consoleColor::DEFAULT);
}

// Print a title block with the title
void ConsoleUI::printTitle(string title)
{
	string offset = " ";
	int titleLength = title.length();

	setTextColor(consoleColor::DEFAULT);

	cout << offset;

	for (int i = 0; i < titleLength + 4; i++)
	{
		cout << '#';
	}

	cout << endl;

	cout << offset;
	cout << "# ";

	setTextColor(consoleColor::CYAN);

	cout << title;

	setTextColor(consoleColor::DEFAULT);

	cout << " #" << endl;

	cout << offset;

	for (int i = 0; i < titleLength + 4; i++)
	{
		cout << '#';
	}

	cout << endl;
	
	setTextDefault();
}


