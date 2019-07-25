#include "cpp11.h"
#include "gtest/gtest.h"
#include <bitset>

void print(){}

template<typename T,typename... Type>
void print(const T& firstArg, const Type&... args)
{
	cout << firstArg << endl;
	print(args...);
}

TEST(Variadic_Templates, Normal)
{
	print(7.5,"hello",bitset<16>(377),42);
}


