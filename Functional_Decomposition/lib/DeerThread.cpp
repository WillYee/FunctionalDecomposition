#include "../include/DeerThread.h"
#include <iostream>

DeerThread::DeerThread(pthread_barrier_t& computing_barrier_in,
	pthread_barrier_t& assignment_barrier_in,
	pthread_barrier_t& printing_barrier_in,
	WorldState& state_in)
	: EntityThread(computing_barrier_in, assignment_barrier_in, printing_barrier_in, state_in)
	, num_of_deer_tmp(-1)
{
}


DeerThread::~DeerThread()
{

}

void DeerThread::compute_tmp_variables()
{
	double num_deer = (double)current_state.num_deer;
	double grain_height = current_state.now_height;

	if (num_deer < grain_height)
	{
		num_of_deer_tmp = (int)num_deer + 1;
	}
	else
	{
		num_of_deer_tmp = (int)num_deer - 1;

		if (num_of_deer_tmp < 1)
		{
			num_of_deer_tmp = 0;
		}
	}
}

void DeerThread::update_world_state()
{
	current_state.num_deer = num_of_deer_tmp;
	num_of_deer_tmp = -1;
}
