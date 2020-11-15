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

int main(int argc, char *argv[])
{	
	// Configure default
	int opt;
	int count = 100;
	int key_byte = 30;
	int val_byte = 100;
	int count_thread = 10;
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

	// STRING OF KEY
	vector <string> keys;
	vector <string> vals;

	for(int i = 0 ; i < count ; i++)
		keys.push_back(str_rand(key_byte));
	
	for(int i = 0 ; i < count ; i++)
		vals.push_back(str_rand(val_byte));
	
	auto bk = keys.begin();
	auto bv = vals.begin();
	auto ek = keys.end();
	auto ev = vals.end();
	int add = count / count_thread;

	if(connect == "ip")
	{
		if(type == "set" or type == "sg")
		{	
			// CREATE CONNECTION FOR REDIS
			vector <somredis*> c;
			for(int i = 0; i < count_thread ; i++)
				c.push_back(new somredis("127.0.0.1", 6379));

			// START TIME
			auto start_set = high_resolution_clock::now();

			// CREAT THREAD
 			vector <thread> threads;				
	
			for(int i = 0 ; i < count_thread ; i++)
			{
				if(i == count_thread - 1)
					threads.push_back(thread(set_performance, ref(c[i]), vector<string>(bk, ek), vector<string>(bv, ev)));
				else
				{
					threads.push_back(thread(set_performance, ref(c[i]), vector<string>(bk, bk + add), vector<string>(bv, bv+add)));
					bk += add;
					bv += add;
				}
			}

			//	JOIN THREAD
			for(int i = 0 ; i < count_thread ; i++)
				threads[i].join();

			// END TIME
			auto end_set = high_resolution_clock::now();

			//	FREE OF CONNECTION
			for(int i = 0; i < count_thread ; i++)
				delete c[i];
		
			// COMPUTING TIME
			auto durtion_set = duration_cast<chrono::microseconds>(end_set - start_set).count();
			double time_s = (double)durtion_set / (double) 1000000;
			cout << "performance set : " << (int)(count / time_s)  << " per/sec" << endl;
		}		

		if(type == "get" or type == "sg")
		{
	
			// CREATE CONNECTION FOR REDIS
			vector <somredis*> c;
			for(int i = 0; i < count_thread ; i++)
				c.push_back(new somredis("127.0.0.1", 6379));

			// START TIME
			auto start_get = high_resolution_clock::now();

			// CREAT THREAD
			vector <thread> threads;
			bk = keys.begin();
			for(int i = 0 ; i < count_thread ; i++)
			{
				if(i == count_thread - 1)
					threads.push_back(thread(get_performance, ref(c[i]), vector<string>(bk, ek)));
				else
				{
					threads.push_back(thread(get_performance, ref(c[i]), vector<string>(bk, bk + add)));
					bk += add;
				}	
			}

			//	JOIN THREAD
			for(int i = 0 ; i < count_thread ; i++)
				threads[i].join();

			// END TIME
			auto end_get = high_resolution_clock::now();

			//	FREE OF CONNECTION
			for(int i = 0; i < count_thread ; i++)
				delete c[i];
		

			// COMPUTING TIME
			auto durtion_get = duration_cast<chrono::microseconds>(end_get - start_get).count();
			double time_s = (double)durtion_get / (double) 1000000;
			cout << "performance get : " << (int)(count / time_s)  << " per/sec" << endl;
		}
	}

	if(connect == "unix")
	{
		if(type == "set" or type == "sg")
		{
	
			// CREATE CONNECTION FOR REDIS
			vector <somredis*> c;
			for(int i = 0; i < count_thread ; i++)
				c.push_back(new somredis("/var/run/redis/redis.sock"));

		
			// START TIME
			auto start_set = high_resolution_clock::now();

			// CREAT THREAD
 			vector <thread> threads;
			bk = keys.begin();
			bv = vals.begin();
			for(int i = 0 ; i < count_thread ; i++)
			{
				if(i == count_thread - 1)
					threads.push_back(thread(set_performance, ref(c[i]), vector<string>(bk, ek), vector<string>(bv, ev)));
				else
				{
					threads.push_back(thread(set_performance, ref(c[i]), vector<string>(bk, bk + add), vector<string>(bv, bv+add)));
					bk += add;
					bv += add;
				}
			}

			//	JOIN THREAD
			for(int i = 0 ; i < count_thread ; i++)
				threads[i].join();

			// END TIME
			auto end_set = high_resolution_clock::now();

			//	FREE OF CONNECTION
			for(int i = 0; i < count_thread ; i++)
				delete c[i];
		
			// COMPUTING TIME
			auto durtion_set = duration_cast<chrono::microseconds>(end_set - start_set).count();
			double time_s = (double)durtion_set / (double) 1000000;
			cout << "performance set : " << (int)(count / time_s)  << " per/sec" << endl;
		}		

		if(type == "get" or type == "sg")
		{
	
			// CREATE CONNECTION FOR REDIS
			vector <somredis*> c;
			for(int i = 0; i < count_thread ; i++)
				c.push_back(new somredis("/var/run/redis/redis.sock"));

			// START TIME
			auto start_get = high_resolution_clock::now();

			// CREAT THREAD
			vector <thread> threads;
			bk = keys.begin();
			for(int i = 0 ; i < count_thread ; i++)
			{
				if(i == count_thread - 1)
					threads.push_back(thread(get_performance, ref(c[i]), vector<string>(bk, ek)));
				else
				{
					threads.push_back(thread(get_performance, ref(c[i]), vector<string>(bk, bk + add)));
					bk += add;
				}	
			}

			//	JOIN THREAD
			for(int i = 0 ; i < count_thread ; i++)
				threads[i].join();

			// END TIME
			auto end_get = high_resolution_clock::now();

			//	FREE OF CONNECTION
			for(int i = 0; i < count_thread ; i++)
				delete c[i];
		
			// COMPUTING TIME
			auto durtion_get = duration_cast<chrono::microseconds>(end_get - start_get).count();
			double time_s = (double)durtion_get / (double) 1000000;
			cout << "performance get : " << (int)(count / time_s)  << " per/sec" << endl;
		}
	}

	//	CLEAR DATA FROM REDIS
	//somredis s("127.0.0.1", 6379);
	//s.clear();
}
