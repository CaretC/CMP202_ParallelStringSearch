/*
Channel
=======
Custom implementation of a channel class to be used in thread synchronization.
*/

// Includes
// ========
#include "Channel.h"

// Constructor
// ===========
Channel::Channel(unordered_map<string, int>* outResults)
{
	pOutResults = outResults;
}

// Destructor
// ==========
Channel::~Channel()
{
}

// Public Functions
// ================
// Open
void Channel::Open()
{
	channelOpen = true;
}

// Close
void Channel::Close()
{
	while (!channelBuffer.empty())
	{
		// Wait until the channel buffer is empty
	}

	channelOpen = false;
}

// Write data to the channel
void Channel::Write(pair<string, int> results)
{
	bufferMutex.lock();
	channelBuffer.push(results);
	bufferMutex.unlock();
}

// Read data from the channel buffer
void Channel::Read(pair<string, int>* outRes)
{
	pair<string, int> res;
	unique_lock<mutex> lock(bufferMutex);

	if (!channelBuffer.empty())
	{
		res = channelBuffer.front();
		channelBuffer.pop();

		*outRes = res;
	}
}

// Returns if the channel is open or not
bool Channel::IsOpen()
{
	return channelOpen;
}

// Private Functions
// =================



