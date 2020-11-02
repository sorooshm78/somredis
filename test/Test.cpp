#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "SomRedis.h"

using namespace std;

class Tests : public ::testing::Test
{
public:
	Tests()
	: s("127.0.0.1", 6379)
	{
	}

	void SetUp() override
	{
		s.clear();
	}

	somredis s; 
};

TEST_F(Tests, DISABLED_doing_nothing_should_not_casue_anything)
{
	somredis ss("127.0.0.1", 6379);
}

TEST_F(Tests, DISABLED_empty_string_should_not_cause_trouble)
{
	string str;
	s.insert(str, str);
}

TEST_F(Tests, DISABLED_bad_characters_should_not_cause_trouble)
{
	string str = "a";
	str += '\0';
	str += 'a';
	str += '\0';
	str += 'a';
	str += '\0';
	str += 'a';

	cout << "str size: " << str.size() << endl;
	s.insert("key", str);
	EXPECT_EQ(str.size(), s.get("key").size());
}

TEST_F(Tests, inserted_simple_key_should_be_existed)
{
	s.insert("name", "ali");
    EXPECT_EQ("ali", s.get("name"));
}

TEST_F(Tests, insert_and_get)
{	
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

TEST_F(Tests, del)
{
	//s.del("name");
	EXPECT_EQ("",s.get("name"));
	
	s.del("P");
	
	s.del("first name");
    EXPECT_EQ("",s.get("first name"));
}

TEST_F(Tests, size)
{
    EXPECT_EQ(0, s.size());
}

TEST_F(Tests, empty_and_clear)
{
	s.clear();
    EXPECT_TRUE(s.empty());
}
