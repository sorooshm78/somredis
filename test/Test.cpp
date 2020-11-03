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

TEST_F(Tests, doing_nothing_should_not_casue_anything)
{
	somredis ss("127.0.0.1", 6379);
}

TEST_F(Tests, more_connect_and_set_get)
{
	somredis a("127.0.0.1", 6379);
	s.insert("name", "mr.mehran");
	EXPECT_EQ("mr.mehran", a.get("name"));
}

TEST_F(Tests, empty_string_should_not_cause_trouble)
{
	string str;
	s.insert(str, str);
}

TEST_F(Tests, bad_characters_should_not_cause_trouble)
{
	string str = "a\0a\0a@!@#";
	s.insert("key", str);
	EXPECT_EQ(str.size(), s.get("key").size());
}

TEST_F(Tests, inserted_simple_key_should_be_existed)
{
	s.insert("name", "ali");
    EXPECT_EQ("ali", s.get("name"));
}

TEST_F(Tests, key_by_space)
{	
	s.insert("first name","sina");
	EXPECT_EQ("sina",s.get("first name"));	
}

TEST_F(Tests, value_by_space)
{
	s.insert("name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("name"));
}

TEST_F(Tests, key_and_value_by_space)
{
	s.insert("last name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("last name"));
}

TEST_F(Tests, key_by_big_word)
{
	s.insert("PERSON","ASGAR");
	EXPECT_EQ("ASGAR",s.get("PERSON"));
	EXPECT_EQ("",s.get("person"));
}

TEST_F(Tests, not_find_key)
{
	s.insert("age","21");
	EXPECT_EQ("",s.get("ag"));
}

TEST_F(Tests, get_key)
{
	EXPECT_EQ("",s.get("name"));
}	

TEST_F(Tests, delete_not_find_key)
{
	EXPECT_EQ(-1, s.del("P"));
}

TEST_F(Tests, delete_fn)
{
	s.insert("first name", "sina");
    EXPECT_EQ(0,s.del("first name"));
}

TEST_F(Tests, size)
{
    EXPECT_EQ(0, s.size());
}

TEST_F(Tests, size_is_two)
{
	s.insert("name", "ali");
	s.insert("age", "21");
	EXPECT_EQ(2, s.size());
}

TEST_F(Tests, empty_and_clear)
{
	s.clear();
    EXPECT_TRUE(s.empty());
}
