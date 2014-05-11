#pragma once
#ifndef HUNTERTHREAD_H

#include "EntityThread.h"

class HunterThread : public EntityThread
{
public:
	HunterThread(pthread_barrier_t& computing_barrier_in,
		pthread_barrier_t& assignment_barrier_in,
		pthread_barrier_t& printing_barrier_in,
		WorldState& state_in);

	~HunterThread();

	const static double HUNTER_KILL_CHANCE;
	const static int    HUNTER_KILL_LIMIT;
	const static int    HUNTER_MIN_RAND;
	const static int    HUNTER_MAX_RAND;

private:

	void compute_tmp_variables();
	void update_world_state();

	int num_hunters_temp;

	const int HUNTING_SEASON_START = current_state.SEPTEMBER;
	const int HUNTING_SEASON_END = current_state.DECEMBER;
};

#endif