#include "../include/HunterThread.h"
#include <iostream>
const double HunterThread::HUNTER_KILL_CHANCE = 0.3333;
const int	 HunterThread::HUNTER_KILL_LIMIT = 4;
const int    HunterThread::HUNTER_MIN_RAND = 0;
const int    HunterThread::HUNTER_MAX_RAND = 1000;

HunterThread::HunterThread(pthread_barrier_t& computing_barrier_in,
	pthread_barrier_t& assignment_barrier_in,
	pthread_barrier_t& printing_barrier_in,
	WorldState& state_in)
	: EntityThread(computing_barrier_in, assignment_barrier_in, printing_barrier_in, state_in)
	, num_hunters_temp(-1)
{
}

HunterThread::~HunterThread()
{
}

void HunterThread::compute_tmp_variables()
{
	int num_deer = current_state.num_deer;
	num_hunters_temp = current_state.num_hunters;

	// Hunters must maintain a 2:1 hunter/deer ratio
	if ((num_deer / 2) > num_hunters_temp)
	{
		num_hunters_temp++;
	}
	else
	{
		num_hunters_temp--;
	}

	if (num_hunters_temp < 1)
	{
		num_hunters_temp = 1;
	}
}

void HunterThread::update_world_state()
{
	current_state.num_hunters = num_hunters_temp;
	num_hunters_temp = -1;
}

