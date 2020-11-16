#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;
using namespace std::chrono;

void man_page()
{
	cout << "this is man page:" <<endl;
	cout << "-h  help " << endl;
	cout << "-k  size byte key default: 30 " << endl; 
	cout << "-v  size byte value default: 100 " << endl;
	cout << "-f  type of performance set or get or sg(set and get) default: set " << endl;
	cout << "-c  ip or unix default: ip " << endl;
	cout << "-n  count set or get to redis default: 100 " << endl;
	cout << "-t  count thread default: 5 " << endl;
}

// Create random string
string str_rand(int byte)
{
	vector <char> str;
	for(int i = 0 ; i < byte ; i++)
	{
		str.push_back(rand() % 256);
	}
	return string(str.begin(), str.end());
}

void set_performance(somredis* &s, vector <string> key, vector <string> val)
{
	for (int i = 0 ; i < key.size() ; i++)
		s->insert(key[i], val[i]);
}

void get_performance(somredis* &s, vector <string> key)
{
	for (int i = 0 ; i < key.size() ; i++)
		s->get(key[i]);	
}

void initialize_data(vector <string> &k, int count, int key_byte)
{
	for(int i = 0 ; i < count ; i++)
		k.push_back(str_rand(key_byte));
}

void initialize_connection(vector<somredis*> &c, string type, int count)
{
	if(type == "ip")
	{
		for(int i = 0; i < count ; i++)
			c.push_back(new somredis("127.0.0.1", 6379));
	}
	
	if(type == "unix")
	{
		for(int i = 0; i < count ; i++)
			c.push_back(new somredis("/var/run/redis/redis.sock"));
	}
}

void deletion_connection(vector <somredis*> &v, int count)
{		
	for(int i = 0; i < count ; i++)
		delete v[i];
}

void join_threads(vector <thread> &t)
{
	for(int i = 0 ; i < t.size() ; i++)
		t[i].join();
}

void clear_deta_from_redis()
{
	somredis s("127.0.0.1", 6379);
	s.clear();
}

int computing_time(high_resolution_clock::time_point &start, high_resolution_clock::time_point &end, int count)
{
	auto durtion = duration_cast<chrono::microseconds>(end - start).count();
	double time = (double)durtion / (double) 1000000;
	return (int)(count / time);
}

int main(int argc, char *argv[])
{	
	// Configure default
	int opt;
	int count = 100;
	int key_byte = 30;
	int val_byte = 100;
	int count_thread = 7;
	string type = "set";
	string connect = "ip";
	
	// Srand for random function
	srand(time(0));
	
	// Getopt for send argument
    while((opt = getopt(argc, argv, ":t:c:f:n:k:v:h")) != -1)
	{
		switch(opt)
		{			
			// HELP
			case 'h':
			man_page();
			return 0;
	
			// SIZE KEY
			case 'k':
			key_byte = stoi(optarg);
			break;
			
			// SIZE VALUE
			case 'v':
			val_byte = stoi(optarg);	
			break;

			// COUNT DATA 
			case 'n':
			count = stoi(optarg); 
			break;

			// TYPE OF WORK BY REDIS
			case 'f':
			type = optarg;
			break;

			// COUNT THREAD
			case 't':
			count_thread = stoi(optarg);
			break;		

			// TYPE CONNECTION
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
	
	// Configure 
	vector <string> keys;
	vector <string> vals;
	vector <somredis*> connections;
	
	// Initialize random keys and values
	initialize_data(keys, count, key_byte);
	initialize_data(vals, count, val_byte);

	// Check connection
	if(connect == "ip")
		initialize_connection(connections, "ip", count_thread);

	if(connect == "unix")
		initialize_connection(connections, "unix", count_thread);
	
	// Count insert or get each thread
	int add = count / count_thread;

	if(type == "set" or type == "sg")
	{
		// Create threads 
 		vector <thread> threads;
		
		// Pointer to begin an end keys and vals vector
		auto bk = keys.begin();
		auto bv = vals.begin();
		auto ek = keys.end();
		auto ev = vals.end();

		// START TIME
		auto start_set = high_resolution_clock::now();
		
		//  Create threads for set keys in redis
		for(int i = 0 ; i < count_thread ; i++)
		{
			if(i == count_thread - 1)
				threads.push_back(thread(set_performance, ref(connections[i]), vector<string>(bk, ek), vector<string>(bv, ev)));
			else
			{
				threads.push_back(thread(set_performance, ref(connections[i]), vector<string>(bk, bk + add), vector<string>(bv, bv + add)));
				bk += add;
				bv += add;
			}
		}

		//	Join threads
		join_threads(threads);		

		// END TIME
		auto end_set = high_resolution_clock::now();

		// Computing time
		cout << "performance set : " << computing_time(start_set, end_set, count)  << " per/sec" << endl;
	}		

	if(type == "sg")
	{
		// CREAT THREAD
		vector <thread> threads;
		
		// Pointer to begin and end of key vector
		auto bk = keys.begin();
		auto ek = keys.end();

		// START TIME
		auto start_get = high_resolution_clock::now();
		
		// Create threads for get keys in redis
		for(int i = 0 ; i < count_thread ; i++)
		{
			if(i == count_thread - 1)
				threads.push_back(thread(get_performance, ref(connections[i]), vector<string>(bk, ek)));
			else
			{
				threads.push_back(thread(get_performance, ref(connections[i]), vector<string>(bk, bk + add)));
				bk += add;
			}	
		}

		//	Join threads
		join_threads(threads);

		// END TIME
		auto end_get = high_resolution_clock::now();

		// Computing time
		cout << "performance get : " << computing_time(start_get, end_get, count)  << " per/sec" << endl;
	}
	
	// Free connections to redis
	deletion_connection(connections, count_thread);

	// Clear keys and value from redis
	clear_deta_from_redis();
}
