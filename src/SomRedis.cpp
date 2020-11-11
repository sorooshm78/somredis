#include "SomRedis.h"

#include <string>
#include <iostream>

#include <hiredis/hiredis.h>

using namespace std;

somredis::somredis(const std::string &ip_connect, const int &port_connect)
: ip(ip_connect)
, port(port_connect)
{
	try{
		context = redisConnect(ip.c_str(), port);
		if (context == nullptr || context->err) 
		{
   		 	if (context) 
	     	{
				// FIXME throw exception
				throw context->errstr ;
 	     	}
	     	else
        	{
				// FIXME
				throw "Can't allocate redis context" ;
        	}
 		}
	}
	catch(string s){}
}

// FIXME change string to const string&
somredis::somredis(const std::string &unix_socket)
{
	try{
		context = redisConnectUnix(unix_socket.c_str());
    	if (context == nullptr || context->err)
    	{
      		if (context)
      		{
				// FIXME
				throw context->errstr ;
      		}
        	else
        	{
				throw "allocate_redis_context" ;
        	}
    	}
	}
	catch(string s){} 
}

somredis::~somredis()
{	
	clear();
	redisCommand(context,"QUIT");
	freeReplyObject(reply);
	redisFree(context);
}

somredis::somredis(somredis &obj)
{
	ip = obj.get_ip() ;
	port = obj.get_port() ;
	context = redisConnect(ip.c_str(), port);
}

void somredis::insert(const std::string &key, const std::string &value)
{	
	if(key.size() == 0 or value.size() == 0)
		return;
	redisCommand(context, "SET %b %b", key.c_str(), (size_t)key.size(), value.c_str(), (size_t)value.size());
}

bool somredis::del(const std::string &key)
{
	reply = (redisReply *) redisCommand(context,"DEL %b",key.c_str(), (size_t)key.size());
	if (reply->integer == 0)
		return false;
	else
		return true;  
}

std::string somredis::get(const std::string & key)
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

std::string somredis::get_ip()
{
	return ip;
}

int somredis::get_port()
{
	return port;
}

std::string somredis::performance()
{
	reply = (redisReply *) redisCommand(context,"INFO STATS");
	if(reply->type == REDIS_REPLY_NIL)	
		return string();
	return reply->str; 
}
