#define _USE_MATH_DEFINES
#include "WatcherThread.h"

#include <iostream>
#include <cmath>

WatcherThread::WatcherThread(pthread_barrier_t& computing_barrier_in,
	pthread_barrier_t& assignment_barrier_in,
	pthread_barrier_t& printing_barrier_in,
	WorldState& state_in)
	: EntityThread(computing_barrier_in, assignment_barrier_in, printing_barrier_in, state_in)
{
}

WatcherThread::~WatcherThread()
{
}

void WatcherThread::compute_tmp_variables()
{
	// Nothing to compute in temp variables
}

void WatcherThread::update_world_state()
{
	// Increment the month, and possibly the year
	if (current_state.num_month >= 11)
	{
		current_state.num_month = 0;
		current_state.now_year++;
	}
	else
	{
		current_state.num_month++;
	}

	// Calculate the new temperature and precipitation for the month

	double ang = (30.*(double) current_state.num_month + 15.) * (M_PI / 180.);
	double temp = AVG_TEMP - AMP_TEMP * cos(ang);
	double precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);

	current_state.now_temp = temp + ranf(-RANDOM_TEMP, RANDOM_TEMP);
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
	std::cout << current_state.now_temp << ", " << current_state.now_precip << ", " << current_state.num_deer << ", " << current_state.now_height << std::endl;
}

// This was taken from http://stackoverflow.com/a/5289624 
// since ranf was not provided to us on the class website
double WatcherThread::ranf(double a, double b) 
{
	double random = ((double)rand()) / (double)RAND_MAX;
	double diff = b - a;
	double r = random * diff;
	return a + r;
}