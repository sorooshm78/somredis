#ifndef SOMREDIS_H_
#define SOMREDIS_H_

#include <hiredis/hiredis.h> 
#include <string>
   
class somredis
{
public:
	// Constructor
	explicit somredis(const std::string &ip_connect,const int &port_connect);
	somredis(const std::string &unix_socket);
	// Distructor
	~somredis();
	// Copy constructor
	somredis(somredis &obj);
	// Set in redis
	void insert(const std::string &key, const std::string &value);
	// Get key in redis
	std::string get(const std::string &key);
	// Delete key
	int del(const std::string &key);
	// Return count key
	int size();
	// Check database empty or no 
	bool empty();
	// Clear all keys
	void clear();
	// Return ip connecting the redis 
	std::string get_ip();
	// Return port connecting the redis
	int get_port();
	// Show info stats
	std::string performance();

private:
    std::string ip;
	int port;
	redisContext *context = nullptr;
	redisReply *reply = nullptr;
};

#endif

