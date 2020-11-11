#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;

string random(int byte)
{
	int count_byte = byte;
	char k[count_byte];
	srand(time(0));
	for(int i = 0 ; i < count_byte ; i++)
	{
		k[i] = rand() % 256;
	}
	return string(k);
}

int main()
{
	somredis s("127.0.0.1", 6379);
	string key = random(30);
	cout << key.size() << endl;
	s.insert(key, "sina");
}

