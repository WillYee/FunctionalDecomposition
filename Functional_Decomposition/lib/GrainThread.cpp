#include "../include/GrainThread.h"
#include <cmath>

GrainThread::GrainThread(pthread_barrier_t& computing_barrier_in,
	pthread_barrier_t& assignment_barrier_in,
	pthread_barrier_t& printing_barrier_in,
	WorldState& state_in)
	: EntityThread(computing_barrier_in, assignment_barrier_in, printing_barrier_in, state_in)
	, height_tmp(-1)
{
}


GrainThread::~GrainThread()
{
}

void GrainThread::compute_tmp_variables()
{
	double num_deer = (double)current_state.num_deer;
	double temp_factor = exp(-pow(((current_state.now_temp - MIDTEMP) / 10), 2));
	double precip_factor = exp(-pow(((current_state.now_precip - MIDPRECIP) / 10), 2));

	height_tmp = current_state.now_height;
	height_tmp += temp_factor * precip_factor * GRAIN_GROWS_PER_MONTH;
	height_tmp -= (double)num_deer * ONE_DeerThread_EATS_PER_MONTH;

	if (height_tmp < 0.)
	{
		height_tmp = 0;
	}
}

void GrainThread::update_world_state()
{
	current_state.now_height = height_tmp;
	height_tmp = -1;
}
