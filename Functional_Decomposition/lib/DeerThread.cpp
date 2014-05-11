#include "../include/DeerThread.h"
#include "../include/HunterThread.h"
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

	// Determine the number of deers hunted due to hunters
	if (num_of_deer_tmp > HunterThread::HUNTER_KILL_LIMIT)
	{
		int deers_hunted = 0;
		int num_hunters = current_state.num_hunters;
		
		// Calculate the number of deers hunted based off of a randomly generated number
		// and the HunterThread::HUNTER_KILL_CHANCE
		for (int i = 0; i < num_hunters; i++)
		{
			double random_number = ranf(HunterThread::HUNTER_MIN_RAND, HunterThread::HUNTER_MAX_RAND);
			if (random_number < (HunterThread::HUNTER_MAX_RAND * HunterThread::HUNTER_KILL_CHANCE))
			{
				deers_hunted++;
			}
		}

		if (deers_hunted > HunterThread::HUNTER_KILL_LIMIT)
		{
			deers_hunted = HunterThread::HUNTER_KILL_LIMIT;
		}

		num_of_deer_tmp -= deers_hunted;

		// Cap number of deers to 0
		if (num_of_deer_tmp < 0)
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
