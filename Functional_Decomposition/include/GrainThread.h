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

	// Grain height in inches
	double height_tmp;

	// Calculate the new height of the grain
	void compute_tmp_variables();

	void update_world_state();

	const static double GRAIN_GROWS_PER_MONTH;
	const static double ONE_DeerThread_EATS_PER_MONTH;
	const static double MIDTEMP;
	const static double MIDPRECIP;
};

#endif