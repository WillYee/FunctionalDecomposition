#pragma once
#ifndef ENTITYTHREAD_H

#include <pthread.h>
#include "WorldState.h"

class EntityThread
{
public:
	EntityThread(pthread_barrier_t& computing_barrier_in, 
		   pthread_barrier_t& assignment_barrier_in, 
		   pthread_barrier_t& printing_barrier_in,
		   WorldState& state_in);

	~EntityThread();

	// Pure virtuals, must be implemented by DeerThread and Grain classes
	virtual void run();

protected:

	// Pure virtual method that will copy certain WorldState members and calculate new values and store them
	// in their own class memeber
	virtual void compute_tmp_variables() = 0;

	// Pure virtual method that  will copy out the newly calculated value back into the 
	// WorldState
	virtual void update_world_state() = 0;

	pthread_barrier_t& computing_barrier; // WatcherThread will never use this!!!
	pthread_barrier_t& assignment_barrier;
	pthread_barrier_t& printing_barrier;
	WorldState&		   current_state;

private:

	// Disable copy and assignment operator
	EntityThread(const EntityThread&);
	EntityThread& operator=(const EntityThread&);
};

#endif