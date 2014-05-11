#include "../include/WorldState.h"

WorldState::WorldState()
	: num_deer(1)
	, num_hunters(1)
	, num_month(11)
	, now_year(2013)
	, now_height(1.0)
	, now_precip(-1) // Invalid values to start, must compute valid values
	, now_temp(-1)   // Invalid values to start, must compute valid values
{

}


WorldState::~WorldState()
{

}
