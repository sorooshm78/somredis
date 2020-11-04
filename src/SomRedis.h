#ifndef SOMREDIS_H_
#define SOMREDIS_H_

#include <hiredis/hiredis.h> 
#include <string>
   
class somredis
{
public:
	explicit somredis(const std::string &ip_connect,const int &port_connect);
	somredis(const std::string &unix_socket);
	~somredis();
	somredis(somredis &obj);
	void insert(const std::string &key, const std::string &value);
	std::string get(const std::string &key);
	int del(const std::string &key);
	int size();
	bool empty();
	void clear();
	std::string get_ip();
	int get_port();
	std::string performance();

private:
    std::string ip;
	int port;
	redisContext *context = nullptr;
	redisReply *reply = nullptr;
};

#endif

