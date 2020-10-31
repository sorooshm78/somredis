#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "api.h"

somredis s("127.0.0.1",6379); 

TEST(test_somredis, insert_and_get)
{	
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

	s.insert("PERSON","ASGAR");
	EXPECT_EQ("ASGAR",s.get("PERSON"));
	EXPECT_EQ("",s.get("person"));

	//not find key
	s.insert("age","21");
	EXPECT_EQ("",s.get("ag"));
}

TEST(test_somredis , del)
{
	s.del("name");
	EXPECT_EQ("",s.get("name"));
	
	s.del("P");
	
	s.del("first name");
    EXPECT_EQ("",s.get("first name"));
}

TEST(test_somredis , size)
{
    EXPECT_EQ(3,s.size());
    s.del("name");
    EXPECT_EQ(3,s.size());
	s.del("age");
	EXPECT_EQ(2,s.size());
}

TEST(test_somredis , empty_and_clear)
{
    EXPECT_FALSE(s.empty());
	s.clear();
    EXPECT_TRUE(s.empty());
}

