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
			cout << s.performance() << endl;
	}
	auto end_set = high_resolution_clock::now();
	auto durtion_set = duration_cast<chrono::seconds>(end_set - start_set).count();
	cout << "performance set : " << count / durtion_set << " per/sec" << endl;

	// Computing get performance
	auto start_get = high_resolution_clock::now();
	for (int i = 0 ; i < count ; i++)
	{
		s.get(to_string(i));
//		if(i == 49999)
//			cout << s.performance() << endl;
	}
	auto end_get = high_resolution_clock::now();
	auto durtion_get = duration_cast<chrono::seconds>(end_get - start_get).count();
	cout << "performance get : " << count / durtion_get << " per/sec" << endl;
}
