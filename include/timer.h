#ifndef _TIMER
#define _TIMER
#include <chrono>
#include "common.h"

using namespace std::chrono;
using namespace std;

class TimeTrack
{
public:
	TimeTrack() { timestamp_.reserve(10); }
	~TimeTrack() {}
	int Track();
	int ClearStamp();
	int GetStampSize()const { return timestamp_.size(); }
	unsigned long DurationTime(const int start, const int finish) const;

private:
	vector<high_resolution_clock::time_point> timestamp_;
	//const unsigned long milli = 1000;
	//list<high_resolution_clock::time_point> timestamp_;
};




#endif 