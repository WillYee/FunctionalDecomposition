#pragma once
#ifndef ENTITYTHREAD_H

#include <pthread.h>
#include "../WorldState.h"

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

	virtual void compute_tmp_variables() = 0;
	virtual void update_world_state() = 0;

	pthread_barrier_t& computing_barrier; // WatcherThread will never use this!!!
	pthread_barrier_t& assignment_barrier;
	pthread_barrier_t& printing_barrier;
	WorldState&			   current_state;

private:

	// Disable copy and assignment operator
	EntityThread(const EntityThread&);
	EntityThread& operator=(const EntityThread&);
};

#endif