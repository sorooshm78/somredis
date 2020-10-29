#include "api.h"
#include <iostream>
#include <string>
#include <hiredis/hiredis.h>

using namespace std;

somredis::somredis(std::string ip_connect, int port_connect)
:ip(ip_connect), port(port_connect)
{
	context = redisConnect(ip.c_str(),port);
	if (context == NULL || context->err) 
	{
   		 if (context) 
	     {
        	cout << "Error: " << context->errstr << endl;
 	     }
	     else
         {
        	cout << "Can't allocate redis context" << endl;
         }
 	}
}

somredis::somredis(std::string unix_socket)
{
	context = redisConnectUnix(unix_socket.c_str());
    if (context == NULL || context->err)
    {
      	if (context)
      	{
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
	exit();
	freeReplyObject(reply);
	redisFree(context);
}

void somredis::insert(std::string key, std::string value)
{
	redisCommand(context, "SET %s %s", key.c_str(), value.c_str());
}

void somredis::exit()
{
	redisCommand(context,"SHUTDOWN NOSAVE");
	redisCommand(context,"QUIT");
}

std::string somredis::get(std::string key)
{
	reply = (redisReply *) redisCommand(context,"GET %s",key.c_str());
	if(reply->type == REDIS_REPLY_NIL)	
		return string();
	return reply->str ;
}

int somredis::size()
{
	reply = (redisReply *) redisCommand(context,"DBSIZE");
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
	redisCommand(context,"FLUSHALL");
}
