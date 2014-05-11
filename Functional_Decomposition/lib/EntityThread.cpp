#define _USE_MATH_DEFINES
#include "../include/EntityThread.h"
#include <cmath>
#include <cstdlib>

EntityThread::EntityThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in)
	: computing_barrier(computing_barrier_in)
	, assignment_barrier(assignment_barrier_in)
	, printing_barrier(printing_barrier_in)
	, current_state(state_in)
{
}


EntityThread::~EntityThread()
{
}

void EntityThread::run()
{
	while (true)
	{
		pthread_barrier_wait(&printing_barrier);
		compute_tmp_variables();
		pthread_barrier_wait(&computing_barrier);
		update_world_state();
		pthread_barrier_wait(&assignment_barrier);
	}
}

double EntityThread::ranf(double low, double high)
{
	double r = (double)rand(); // 0 - RAND_MAX
	return(low + r * (high - low) / (double)RAND_MAX);
}