#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <chrono>

#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;
using namespace std::chrono;

string str_rand(int byte)
{
	int count_byte = byte;
	char str[count_byte];
	for(int i = 0 ; i < count_byte ; i++)
	{
		str[i] = rand() % 256;
	}
	return string(str);
}

void performance(somredis &s, string type, int count, int key_byte, int val_byte)
{
	vector <string> keys;
	if(type == "set" or type == "sg")
	{
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
	}

	if(type == "get" or type == "sg")
	{
		// Computing get performance
		auto start_get = high_resolution_clock::now();
		for (int i = 0 ; i < count ; i++)
			s.get(keys[i]);
		
		auto end_get = high_resolution_clock::now();
		auto durtion_get = duration_cast<chrono::microseconds>(end_get - start_get).count();
		double time_g = (double)durtion_get / (double) 1000000;
		cout << "performance get : " << (int)(count / time_g)  << " per/sec" << endl;
	}
}

void man_page()
{
	cout << "this is man page:" <<endl;
	cout << "-h  help " << endl;
	cout << "-k  size byte key default: 30 " << endl; 
	cout << "-v  size byte value default: 100 " << endl;
	cout << "-t  type of performance set or get or sg(set and get) default: set " << endl;
	cout << "-c  ip or unix default: ip " << endl;
	cout << "-n  count set or get to redis default: 100 " << endl;
}

int main(int argc, char *argv[])
{	
	// Configure default
	int opt;
	int count = 100;
	int key_byte = 30;
	int val_byte = 100;
	string type = "set";
	string connect = "ip";

	// Srand for random function
	srand(time(0));
	
	// Getopt for send argument
    while((opt = getopt(argc, argv, ":c:t:n:k:v:h")) != -1)
	{
		switch(opt)
		{			
			case 'h':
			man_page();
			return 0;
	
			case 'k':
			key_byte = stoi(optarg);
			break;
			
			case 'v':
			val_byte = stoi(optarg);	
			break;

			case 'n':
			count = stoi(optarg); 
			break;

			case 't':
			type = optarg;
			break;
			
			case 'c':
			connect = optarg;
			break;			

			case ':':
			cout << "option need value" << endl;
			break;

			case '?':
			cout << "unknown option: %c" << optopt << endl; 
			break;
		}
	}

	if(connect == "ip")
	{
		somredis s("127.0.0.1", 6379);
		performance(s, type, count, key_byte, val_byte);
	}

	if(connect == "unix")
	{
		somredis s("/var/run/redis/redis.sock");
		performance(s, type, count, key_byte, val_byte);
	}
}
