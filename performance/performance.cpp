#include <string>
#include <chrono>
#include <iostream>
#include <vector>

#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;
using namespace std::chrono;

string str_rand(int byte)
{
	int count_byte = byte;
	char k[count_byte];
	for(int i = 0 ; i < count_byte ; i++)
	{
		k[i] = rand() % 256;
	}
	return string(k);
}

int main()
{	
	// Configure
	int count = 5000;
	int key_byte = 30;
	int val_byte = 100;
	vector <string> keys;
	srand(time(0));
	somredis s("127.0.0.1", 6379);

	// Computing set performance
	auto start_set = high_resolution_clock::now();
	for (int i = 0 ; i < count ; i++)
	{
		keys.push_back(str_rand(key_byte));
		s.insert(keys[i], str_rand(val_byte));
	}
	auto end_set = high_resolution_clock::now();
	auto durtion_set = duration_cast<chrono::microseconds>(end_set - start_set).count();
	double time_s = (double)durtion_set / (double) 1000000;
	cout << "performance set : " << (int)(count / time_s)  << " per/sec" << endl;

	// Computing get performance
	auto start_get = high_resolution_clock::now();
	for (int i = 0 ; i < count ; i++)
		s.get(keys[i]);
		
	auto end_get = high_resolution_clock::now();
	auto durtion_get = duration_cast<chrono::microseconds>(end_get - start_get).count();
	double time_g = (double)durtion_get / (double) 1000000;
	cout << "performance get : " << (int)(count / time_g)  << " per/sec" << endl;
}
