#include <iostream>
#include <vector>
#include <pthread.h>

#include "include/DeerThread.h"
#include "include/WatcherThread.h"
#include "include/GrainThread.h"
#include "include/HunterThread.h"
#include "include/WorldState.h"

static const int NUM_THREADS = 4;
static const int NUM_COMPUTE_THREADS = 3;

// Bare function to call base class run function
void* entity_start_thread(void *ptr)
{
	// Not using a smart ptr since this object cannot be freed when scoped out
	EntityThread* argument  = reinterpret_cast<EntityThread*>(ptr);
	argument->run();
	
	pthread_exit(NULL);

	// Visual Studio complains unless I provide this return statement
	return 0;
}

bool check_status(int status)
{
	bool return_val = true;

	switch (status)
	{
	case 0:
		return_val = false;
		break;

	case EAGAIN:
		std::cerr << "Thread creation failed because of insufficient resources" << std::endl;
		return_val = true;
		break;

	case EINVAL:
		std::cerr << "Thread creation failed because of invalid argument" << std::endl;
		return_val = true;
		break;

	default:
		std::cerr << "Thread creation failed because of some unknown error" << std::endl;
		return_val = true;
	}

	return return_val;
}

int main(int argc, char* argv[])
{
	// Declare our threads
	pthread_t deer_thread;
	pthread_t grain_thread;
	pthread_t watcher_thread;
	pthread_t hunter_thread;

	// Declare our barriers
	pthread_barrier_t assign_barrier;
	pthread_barrier_t computing_barrier;
	pthread_barrier_t print_barrier;

	// Initialize all our barriers
	pthread_barrier_init(&assign_barrier, NULL, NUM_THREADS);
	pthread_barrier_init(&computing_barrier, NULL, NUM_COMPUTE_THREADS);
	pthread_barrier_init(&print_barrier, NULL, NUM_THREADS);

	// Set up the state of the world and initialize values
	WorldState current_state;

	// Declare our three entity threads
	DeerThread deer(computing_barrier, assign_barrier, print_barrier, current_state);
	WatcherThread watcher(computing_barrier, assign_barrier, print_barrier, current_state);
	GrainThread grain(computing_barrier, assign_barrier, print_barrier, current_state);
	HunterThread hunter(computing_barrier, assign_barrier, print_barrier, current_state);
	
	std::cout << "temperature, precipatation, number of deer, height of grain, number of hunters" << std::endl;

	// Begin spinning off threads
	int status = pthread_create(&deer_thread, NULL, entity_start_thread, &deer);

	if (check_status(status) == false)
	{
		status = pthread_create(&grain_thread, NULL, entity_start_thread, &grain);

		if (check_status(status) == false)
		{
			status = pthread_create(&hunter_thread, NULL, entity_start_thread, &hunter);

			if (check_status(status) == false)
			{
				status = pthread_create(&watcher_thread, NULL, entity_start_thread, &watcher);

				if (check_status(status) == false)
				{
					// Join the watcher thread, kill all others
					pthread_join(watcher_thread, NULL);

					pthread_cancel(deer_thread);
					pthread_cancel(grain_thread);
				}
			}
		}
	}

	getchar();
}