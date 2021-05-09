/*
Channel
=======
Custom implementation of a channel class to be used in thread synchronization.
*/
#pragma once

// Includes
// ========
#include <string>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <thread>

// Imports
// =======
using std::string;
using std::unordered_map;
using std::queue;
using std::mutex;
using std::unique_lock;
using std::pair;
using std::thread;

// Class
// =====
class Channel
{
	// Public
	// ------
	public:
		// Constructor
		Channel(unordered_map<string, int>* outResults);

		// Destructor
		~Channel();

		// Open
		void Open();

		// Close
		void Close();

		// Write data to the channel
		void Write(pair<string, int> result);

		// Read data from the channel buffer
		void Read(pair<string, int>* outRes);

		// Returns if the channel is open or not
		bool IsOpen();

	// Private
	// -------
	private:
		// Data Buffer
		queue<pair<string, int>> channelBuffer;
		mutex bufferMutex;

		// Pointer to output unordered map
		unordered_map<string, int>* pOutResults;

		// Channel Open
		bool channelOpen = false;




};

