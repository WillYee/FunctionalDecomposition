#define _USE_MATH_DEFINES
#include "../include/WatcherThread.h"
#include <cmath>
#include <iostream>

WatcherThread::WatcherThread(pthread_barrier_t& computing_barrier_in,
	pthread_barrier_t& assignment_barrier_in,
	pthread_barrier_t& printing_barrier_in,
	WorldState& state_in)
	: EntityThread(computing_barrier_in, assignment_barrier_in, printing_barrier_in, state_in)
{
}

WatcherThread::~WatcherThread()
{
	// Nothing needs to be freed
}

void WatcherThread::compute_tmp_variables()
{
	// Inherited but unused, nothing to compute
}

void WatcherThread::update_world_state()
{
	// Increment the month, and possibly the year
	if (current_state.num_month >= WorldState::DECEMBER)
	{
		current_state.num_month = WorldState::JANUARY;
		current_state.now_year++;
	}
	else
	{
		current_state.num_month++;
	}

	// Calculate the new temperature and precipitation for the month
	double ang    = (30.*(double) current_state.num_month + 15.) * (M_PI / 180.);

	double temp   = AVG_TEMP - AMP_TEMP * cos(ang);
	double precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);

	current_state.now_temp   = temp + ranf(-RANDOM_TEMP, RANDOM_TEMP);
	current_state.now_precip = precip + ranf(-RANDOM_PRECIP, RANDOM_PRECIP);
		
	if (current_state.now_precip < 0.)
	{
		current_state.now_precip = 0;
	}
}

void WatcherThread::run()
{
	while (current_state.now_year < 2020)
	{
		update_world_state();
		print();
		pthread_barrier_wait(&printing_barrier);
		pthread_barrier_wait(&assignment_barrier);
	}

}

void WatcherThread::print()
{
	std::cout << current_state.now_temp << ", " << current_state.now_precip << ", " << current_state.num_deer << ", " << current_state.now_height << ", " << current_state.num_hunters << std::endl;
}