#pragma once
#ifndef WORLDSTATE_H

class WorldState
{

public:
	WorldState();
	~WorldState();

	int num_deer;
	int num_month; // 0 - 11
	int now_year;  // 2014 - 2019

	double now_height; // Grain height in inches
	double now_precip; // inches of rain per month
	double now_temp;   // temperature this month

};

#endif