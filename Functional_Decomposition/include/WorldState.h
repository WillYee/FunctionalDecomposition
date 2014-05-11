#pragma once
#ifndef WORLDSTATE_H

class WorldState
{

public:
	WorldState();
	~WorldState();

	int num_deer;
	int num_hunters;
	int num_month; // 0 - 11
	int now_year;  // 2014 - 2019

	double now_height; // Grain height in inches
	double now_precip; // inches of rain per month
	double now_temp;   // temperature this month

	enum months
	{
		JANUARY   = 0,
		FEBRUARY  = 1,
		MARCH     = 2,
		APRIL	  = 3,
		MAY		  = 4,
		JUNE	  = 5,
		JULY	  = 6,
		AUGUST    = 7,
		SEPTEMBER = 8,
		OCTOBER   = 9,
		NOVEMBER  = 10,
		DECEMBER  = 11
	};

};

#endif