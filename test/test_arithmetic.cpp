#include <gtest.h>
    #include "arithmetic.h"





    TEST(work, correct_answer0)
    {
        std::string s = "-11+11";
        EXPECT_EQ(0, work(s));
    }
    TEST(work, correct_answer1)
    {
        std::string s = "(((1+1)*1+1)*1+1)+1";
        EXPECT_EQ(5, work(s));
    }
    TEST(work, correct_answer2)
    {
        std::string s = "12-(-12)";
        EXPECT_EQ(24, work(s));
    }





    TEST(work, correct_answer3)
    {
        std::string s = "10-(-(-10))";
        EXPECT_EQ(0, work(s));
    }
    TEST(work, correct_answer4)
    {
        std::string s = "1/(-5)";
        EXPECT_EQ(-0.2, work(s));
    }
    TEST(work, correct_answer5)
    {
        std::string s = "-(-5)";
        EXPECT_EQ(5, work(s));
    }
    TEST(work, correct_answer6)
    {
        std::string s = "-11.3";
        EXPECT_EQ(-11.3, work(s));
    }
    TEST(work, correct_answer7)
    {
        std::string s = "(12/2)+((56/8)-11)";
        EXPECT_EQ(2, work(s));
    }
    TEST(work, correct_answer8)
    {
        std::string s = "12/2*5";
        EXPECT_EQ(30, work(s));
    }
    TEST(work, throws_if_not_correct0)
    {
        std::string s = "(12/2*7";
        ASSERT_ANY_THROW(work(s));
    }
    TEST(work, throws_if_not_correct1)
    {
        std::string s = "ros";
        ASSERT_ANY_THROW(work(s));
    }

    TEST(work, throws_if_not_correct2)
    {
        std::string s = "1*/8";
        ASSERT_ANY_THROW(work(s));
    }

