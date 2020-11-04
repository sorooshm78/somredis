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

TEST_F(Tests, 2_connecting_in_redis_and_set_get)
{
	somredis a("127.0.0.1", 6379);
	s.insert("name", "mr.mehran");
	EXPECT_EQ("mr.mehran", a.get("name"));
}

TEST_F(Tests, connecting_s_and_p_to_redis_and_set_s_get_p_and_conversely)
{
	// Defulte define somredis s
	somredis p("127.0.0.1", 6379);
	s.insert("name", "soroush");
	p.insert("age", "21");
	EXPECT_EQ("soroush", p.get("name"));
	EXPECT_EQ("21", s.get("age"));
}

TEST_F(Tests, empty_string_should_not_cause_trouble)
{
	string str;
	s.insert(str, str);
}

TEST_F(Tests, empty_string_key)
{
	string str;
	s.insert(str, "sian");
}

TEST_F(Tests, empty_string_value)
{
	string str;
	s.insert("name", str);
}

TEST_F(Tests, bad_characters_should_not_cause_trouble)
{
	string str = "a\0a\0a@!@#\0";
	s.insert("key", str);
	EXPECT_EQ(str.size(), s.get("key").size());
}

TEST_F(Tests, bad_characters_insert_and_get)
{
	string key = "!wxq#@$&($)(&#$)&$^#$^@^$*@";
	string value = "!@56253)(*&^%$$/***sda+-)";
	s.insert(key, value); 
	EXPECT_EQ(value , s.get(key));
}

TEST_F(Tests, inserted_simple_key_should_be_existed)
{
	s.insert("name", "ali");
    EXPECT_EQ("ali", s.get("name"));
}

TEST_F(Tests, inserted_key_by_space_should_be_existed)
{	
	s.insert("first name","sina");
	EXPECT_EQ("sina",s.get("first name"));	
}

TEST_F(Tests, inserted_value_by_space_should_be_existed)
{
	s.insert("name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("name"));
}

TEST_F(Tests, inserted_key_and_value_by_space_should_be_existed)
{
	s.insert("last name","allah gholi");
	EXPECT_EQ("allah gholi",s.get("last name"));
}

TEST_F(Tests, inserted_key_by_Capital_letters_should_be_existed)
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

TEST_F(Tests, get_key_when_Does_not_exist)
{
	EXPECT_EQ("",s.get("name"));
}	

TEST_F(Tests, delete_key_when_does_not_exist)
{
	EXPECT_EQ(-1, s.del("P"));
}

TEST_F(Tests, delete_key_exist)
{
	s.insert("first name", "sina");
    EXPECT_EQ(0, s.del("first name"));
}

TEST_F(Tests, empty_size)
{
    EXPECT_EQ(0, s.size());
}

TEST_F(Tests, size)
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
