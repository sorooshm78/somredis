#include "SomRedis.h"

#include <string>
#include <iostream>

#include <hiredis/hiredis.h>

using namespace std;

somredis::somredis(std::string ip_connect, int port_connect)
: ip(ip_connect)
, port(port_connect)
{
	context = redisConnect(ip.c_str(), port);
	if (context == nullptr || context->err) 
	{
   		 if (context) 
	     {
			// FIXME throw exception
        	cout << "Error: " << context->errstr << endl;
 	     }
	     else
         {
			// FIXME
        	cout << "Can't allocate redis context" << endl;
         }
 	}
}

// FIXME change string to const string&
somredis::somredis(std::string unix_socket)
{
	context = redisConnectUnix(unix_socket.c_str());
    if (context == nullptr || context->err)
    {
      	if (context)
      	{
			// FIXME
 	    	cout << "Error: " << context->errstr << endl;
      	}
        else
        {
  	       	 cout << "Can't allocate redis context" << endl;
        }
    } 
}

somredis::~somredis()
{
	redisCommand(context,"QUIT");
	freeReplyObject(reply);
	redisFree(context);
}

void somredis::insert(std::string key, std::string value)
{
	redisCommand(context, "SET %b %b", key.c_str(), (size_t)key.size(), value.c_str(), (size_t)value.size());
}

int somredis::del(std::string key)
{
	reply = (redisReply *) redisCommand(context,"DEL %s",key.c_str());
	if (reply->integer == 0)
		return -1 ;
	else
		return 0 ;  
}

std::string somredis::get(std::string key)
{
	reply = (redisReply *) redisCommand(context,"GET %b",key.c_str(), (size_t)key.size());
	if(reply->type == REDIS_REPLY_NIL)	
		return string();
	return reply->str ;
}

int somredis::size()
{
	reply = (redisReply *) redisCommand(context, "DBSIZE");
	return reply->integer ;
}

bool somredis::empty()
{
	if(size() != 0)
		return false;
	else
		return true;
}

void somredis::clear()
{
	redisCommand(context, "FLUSHALL");
}
