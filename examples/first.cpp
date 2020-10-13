#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>

#include "single_header/sutf.hpp"
// #include "merger.hpp"

TEST(strings)
{
    std::string str1{"first string"};
    std::string str2{"second string"};

    ASSERT_EQ(str1, "first string");
    ASSERT_NE(str1, str2);
}

TEST(cstrings)
{
    char cstr1[] = "first string";
    char cstr2[] = "second string";

    ASSERT_CSTR_EQ(cstr1, "first string");
    ASSERT_CSTR_LT(cstr1, cstr2);
}

TEST(expect_failure)
{
    std::string str1;

    EXPECT_FALSE(str1.empty());
}

TEST(assert_failure)
{
    std::set<int> some_data{0, 1, 2, 4, 5};
    auto value_entries{some_data.count(3)};

    ASSERT_EQ(value_entries, 2u);
    ASSERT_EQ(value_entries, 3u);
}

TEST(test_sfinae_print)
{
    {
        std::map<int, int> data1{{0, 1}, {2, 4}};
        std::map<int, int> data2{{0, 1}, {2, 6}};
        ASSERT_EQ(data1,data2);
    }

    {

        std::vector<std::pair<int,int>> data1{{0, 1}, {2, 4}};
        std::vector<std::pair<int,int>> data2{{0, 1}, {2, 1}};
        ASSERT_EQ(data1,data2);
    }
}

int main()
{
     RUN_ALL_TESTS();
     return 0;
}

