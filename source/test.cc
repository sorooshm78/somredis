#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "api.h"

namespace {

TEST(testMath, myCubeTest)
{
	somredis s("127.0.0.1",6379);
	s.insert("name","ali");
    EXPECT_EQ("ali",s.get("name"));	
}



}

