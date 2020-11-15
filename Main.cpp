#include <hiredis/hiredis.h>
#include <iostream>
#include <vector>

#include "SomRedis.h"

using namespace std; 

void f(vector <int> s)
{
	for(int i=0;i<s.size();i++)
		cout << s[i] << endl;
}
int main()  
{
	int c = 10;
	int t = 3;
	int add = c / t;
	vector <int> v={1,2,3,4,5,6,7,8,9,10};
	auto b = v.begin();
	auto e = v.end();
	
	for(int i = 0 ; i < t ; i++)
	{
		if(i == v.size()-1)
		{	
			f(vector<int>(b,e));
		}
		else
		{
			f(vector <int>(b, b + add));
			b += add; 
		}
	}
	return 0; 
} 
