#include <iostream>
#include <string>
#include <chrono>

#include <hiredis/hiredis.h>
#include "SomRedis.h"

using namespace std;
using namespace std::chrono;

int main()
{	
	int count = 1000000;
	somredis s("127.0.0.1", 6379);
	auto start = high_resolution_clock::now();
	for (int i = 0 ; i < count;i++)
	{
		s.insert(to_string(i), to_string(i+1));
	}
	auto end = high_resolution_clock::now();
	auto durtion = duration_cast<chrono::microseconds>(end - start).count();
	cout << "performance per/microsec : " << durtion / count << endl;
}
