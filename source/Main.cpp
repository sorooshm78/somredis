#include <string>
#include <iostream>
#include "api.h"
#include <hiredis/hiredis.h>

using namespace std;

int main()
{
/*	redisReply *reply;
	redisContext *c = redisConnect("127.0.0.1", 6379);
	//check connect or not
	if (c == NULL or c->err) {
    	if (c) {
        	cout<<"Error";
        
   		 } else {
        	cout<<"Can't allocate redis context\n";
    	}
    
	}
	//send redis command and set name and age
	redisCommand(c, "SET name soroosh");
	redisCommand(c, "SET age 21");
	//get name from redis
	reply = (redisReply *) redisCommand(c,"GET name"); 
	cout <<"name :"<<reply->str<<endl;
	//get age from redis
	reply = (redisReply *) redisCommand(c,"GET age");
	cout <<"age :"<<reply->str<<endl;
	//shutdown and nosave from redis
    redisCommand(c, "SHUTDOWN NOSAVE");
    //quit from redis
    redisCommand(c, "QUIT");
	//free reply
	freeReplyObject(reply);
	//disconnect
	redisFree(c);*/

	somredis s("127.0.0.1", 6379);
	s.insert("age","MMM");
	cout << s.get("age") << endl; 
}

