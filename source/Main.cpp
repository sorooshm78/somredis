#include <string.h>
#include <hiredis/hiredis.h>
#include <iostream>
using namespace std;

int main()
{
cout<<"hi soroosh"<<endl;
redisReply *reply;
redisContext *c = redisConnect("127.0.0.1", 6379);
if (c == NULL or c->err) {
    if (c) {
        cout<<"Error";
        
    } else {
        cout<<"Can't allocate redis context\n";
    }
    
}
redisCommand(c, "SET num 12");
redisCommand(c, "SET age 21");
//reply = redisCommand(c,"GET age"); 
//cout <<"GET :"<<reply->str<<endl;
cout <<"bye soroosh"<<endl;
}

