/*
CharTable
=========
The CharTable class is used by the boyer-moore algorithm to pre-process the pattern string.
*/

// Includes
// ========
#include "CharTable.h"

// Consturctor
// ===========
CharTable::CharTable(string pattern)
{
    // Save the pattern in the CharTable
    tablePattern = pattern;

    // Save pattern length
    patternLength = tablePattern.length();

    // Populate the skiptable with the default value of patternLength
    for (int i = 0; i < 256; i++)
    {
        skipValues[i] = patternLength;
    }

    // Process string an populate the skipValues table
    for (int i = 0; i < patternLength; i++)
    {
        // For each of the skip values save the position of each of the characters
        skipValues[int(tablePattern[i])] = (patternLength - 1) - i;
    }
}

// Public Functions
// ================
// Check if the character is in the pattern, if it is return the position for skipping
int CharTable::In(char character)
{
    return skipValues[int(character)];
}

//Return the pattern length
int CharTable::Length()
{
    return patternLength;
}
