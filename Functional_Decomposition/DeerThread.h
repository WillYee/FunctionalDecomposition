#pragma once
#ifndef DEERTHREAD_H

#include "EntityThread.h"

// This class will manage the information regarding the deer population in the world
class DeerThread : public EntityThread
{
public:

	DeerThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in);
	~DeerThread();

private:

	// Disable copy and assignment operators
	DeerThread(const DeerThread&);
	DeerThread& operator=(const DeerThread&);

	// Temporary, internal copy of the number of deers in the world. Copied in from WorldState class
	// and modified within this class to be copied back to WorldState
	int num_of_deer_tmp;

	// Calculate the new number of deer
	void compute_tmp_variables();

	void update_world_state();
};

#endif