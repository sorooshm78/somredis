#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "api.h"


TEST(test_somredis, insert_and_get)
{
	somredis s("127.0.0.1",6379);
	
	//key and value no space
	s.insert("name","ali");
    EXPECT_EQ("ali",s.get("name"));

	//key space and value no space
	s.insert("first name","sina");
	EXPECT_EQ("sina",s.get("first name"));	

	//key no space and value space
	s.insert("name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("name"));

	//key and value space
	s.insert("last name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("last name"));

	//not find key
	s.insert("age","21");
	EXPECT_EQ("",s.get("ag"));
}





