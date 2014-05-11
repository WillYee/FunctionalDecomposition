#pragma once
#ifndef WATCHER_H

#include "EntityThread.h"

class WatcherThread : public EntityThread
{
public:
	WatcherThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in);

	~WatcherThread();

	void run();

private:

	// Print out the current WorldState, using CSV
	void print();

	// Update the month/year and the temperature and precipitation
	void update_world_state();

	// inherited, but unused, must be declared here becuase it's a pure virtual
	void compute_tmp_variables();

	const static double AVG_PRECIP_PER_MONTH;
	const static double AMP_PRECIP_PER_MONTH;
	const static double RANDOM_PRECIP;

	const static double AVG_TEMP;
	const static double AMP_TEMP;
	const static double RANDOM_TEMP;

};

#endif