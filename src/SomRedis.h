#ifndef SOMREDIS_H_
#define SOMREDIS_H_

#include <hiredis/hiredis.h> 
#include <string>
   
class somredis
{
public:
	somredis(std::string ip_connect, int port_connect);
	somredis(std::string unix_socket);
	~somredis();
	void insert(std::string key, std::string value);
	std::string get(std::string key);
	int del(std::string key);
	int size();
	bool empty();
	void clear();

private:
    std::string ip;
	int port;
	redisContext *context;
	redisReply *reply;
};

#endif
