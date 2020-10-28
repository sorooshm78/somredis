#include <string>
#include <iostream>
#include "api.h"
#include <hiredis/hiredis.h>

using namespace std;

int main()
{
	cout << "-----------" << endl;
	somredis s("127.0.0.1", 6379);
	s.insert("fname","mehran");
	cout << "SET fname mehran" << endl;
	cout << "get fname: " << s.get("fname") << endl;
    cout << "-----------" << endl;
	cout << "size befor clear: " << s.size() << endl;
	cout << "empty: " << s.empty() << endl;
	cout << "-----------" << endl;
	s.clear();
	cout << "clear database" << endl;
	cout << "-----------" << endl;
	cout << "size after clear: " << s.size() << endl;
	cout << "empty: " << s.empty() << endl;
	cout << "-----------" << endl;
}

