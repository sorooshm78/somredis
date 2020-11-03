#include <string>
#include <iostream>

#include <hiredis/hiredis.h>

#include "SomRedis.h"

using namespace std;

void f(somredis &s)
{
//	s.clear();
	cout<<"hi"<<endl;
}

int main()
{
	somredis ss("127.0.0.1", 6379);
	f(ss);
	ss.insert("name", "s");
	cout << ss.get("name") << endl;

	// FIXME: WHY?!
//	string my_str = "salam";
//	f(my_str);
/*	somredis s("127.0.0.1", 6379);
	s.insert("WC", "wc");
	somredis a("127.0.0.1", 6379);
	cout << a.get("WC") << endl;
	s.insert("name","alii");
	a.insert("age", "21");
	cout << a.get("name") << endl;
	cout << s.get("age") << endl;
*/
}

