#pragma once
#ifndef GRAINTHREAD_H

#include "EntityThread.h"

class GrainThread : public EntityThread
{
public:
	GrainThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in);
	~GrainThread();

private:

	// Disable copy and assignment operator
	GrainThread(const GrainThread&);
	GrainThread& operator=(const GrainThread&);

	double height_tmp; // Grain height in inches

	const double GRAIN_GROWS_PER_MONTH		   = 8.0;
	const double ONE_DeerThread_EATS_PER_MONTH = 0.5;
	const double MIDTEMP					   = 40.0;
	const double MIDPRECIP					   = 10.0;

	// Calculate the new height of the grain
	void compute_tmp_variables();

	void update_world_state();
};

#endif