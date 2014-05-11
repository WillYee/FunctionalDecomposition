#pragma once
#ifndef WATCHER_H

#include "EntityThread.h"

class WatcherThread : EntityThread
{
public:
	WatcherThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in);

	~WatcherThread();

	void run();

private:

	void print();
	void compute_tmp_variables();
	void update_world_state();

	double ranf(double a, double b);

	const double AVG_PRECIP_PER_MONTH = 6.0;
	const double AMP_PRECIP_PER_MONTH = 6.0;
	const double RANDOM_PRECIP = 2.0;

	const double AVG_TEMP = 50.0;
	const double AMP_TEMP = 20.0;
	const double RANDOM_TEMP = 10.0;

};

#endif