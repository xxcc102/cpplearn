#ifndef _TIMER
#define _TIMER
#include <chrono>
#include "common.h"

using namespace std::chrono;
using namespace std;
using trace_index = unsigned int;
using duration_mesc = unsigned long;


class TimeTrack
{
public:
	TimeTrack()
	{ 
		timestamp_.reserve(10);
		timestamp_.push_back(high_resolution_clock::now());
	}

	~TimeTrack()
	{
		timestamp_.clear();
	}

	trace_index Track();

	int ClearStamp();
	int GetStampSize()const;

	duration_mesc DurationTime(const int start, const int finish) const;

private:
	vector<high_resolution_clock::time_point> timestamp_;
};




#endif 