#include "cpp11.h"

class MyFunctor
{
public:
	MyFunctor(int tmp) :round(tmp) {}
	int operator()(int tmp) { return tmp + round; }
private:
	int round;
};

