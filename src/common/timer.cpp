#include "timer.h"

int TimeTrack::Track()
{
	try
	{
		timestamp_.push_back(std::chrono::high_resolution_clock::now());
		return timestamp_.size() - 1;
	}
	catch (const std::exception&)
	{
		throw "InsertStamp time stamp error";
		return -1;
	}
}

int TimeTrack::ClearStamp()
{
	try
	{
		timestamp_.clear();
		return 0;
	}
	catch (const std::exception&)
	{
		throw "Clear time stamp error";
		return -1;
	}
}


unsigned long TimeTrack::DurationTime(const int track_start,const int track_finish) const
{
	try
	{
		if (track_start < 0 || track_finish > timestamp_.size())
		{
			throw "track_start and track_finish is outoff range";
		}
		auto time = duration_cast<milliseconds>(timestamp_.at(track_finish) - timestamp_.at(track_start)).count();
		
		return time;
	}
	catch (const std::exception&)
	{
		throw "Get duration time error";
		return 0;
	}
}

