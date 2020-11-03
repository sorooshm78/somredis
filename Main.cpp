#include <string>
#include <iostream>

#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;

void f(somredis s)
{
	s.clear();
}

int main()
{
	/*somredis ss("127.0.0.1", 6379);
	f(ss);

	// FIXME: WHY?!
	string my_str = "salam";
	f(my_str);*/
	somredis s("127.0.0.1", 6379);
	s.insert("name", "ali");
	somredis a("127.0.0.1", 6379);
	cout << a.get("name") << endl;
}

