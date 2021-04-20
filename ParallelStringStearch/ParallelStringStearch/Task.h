/*
Task
----
Abstract Task class for tasks to be executed.
*/
#pragma once

// Class
// =====
class Task {
	public:
		// Destructor
		// ==========
		virtual ~Task()
		{
		}

		// Run the task. This must be overridden by inheriting class
		virtual void Run() = 0;
};
