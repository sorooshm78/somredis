#include <iostream>
#include <string>
#include <chrono>

#include <hiredis/hiredis.h>
#include "SomRedis.h"

using namespace std;
using namespace std::chrono;

int main()
{	
	// Config
	int count = 50000;
	somredis s("127.0.0.1", 6379);

	// Computing set performance
	auto start_set = high_resolution_clock::now();
	for (int i = 0 ; i < count ; i++)
	{
		s.insert(to_string(i), to_string(i+1));
		if(i == 49999)
			// Show info stats when i = 49999
			cout << s.performance() << endl;
	}
	auto end_set = high_resolution_clock::now();
	auto durtion_set = duration_cast<chrono::microseconds>(end_set - start_set).count();
	double time_s = (double)durtion_set / (double) 1000000;
	cout << "performance set : " << (int)(count / time_s)  << " per/sec" << endl;

	// Computing get performance
	auto start_get = high_resolution_clock::now();
	for (int i = 0 ; i < count ; i++)
	{
		s.get(to_string(i));
//		if(i == 49999)
			// Show info stats when i = 49999
//			cout << s.performance() << endl;
	}
	auto end_get = high_resolution_clock::now();
	auto durtion_get = duration_cast<chrono::microseconds>(end_get - start_get).count();
	double time_g = (double)durtion_get / (double) 1000000;
	cout << "performance get : " << (int)(count / time_g)  << " per/sec" << endl;
}
