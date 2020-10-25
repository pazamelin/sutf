#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>

std::ostream& operator << (std::ostream& os, const std::set<int>& obj)
{
    return os << " user-defined stream inserter for set<int>";
}

std::ostream& operator << (std::ostream& os, const std::map<int,int>& obj)
{
    return os << " user-defined stream inserter for map<int, int>";
}

// user-defined stream inserter
std::ostream& operator << (std::ostream &os,
                           const std::vector<std::pair<int, std::string>>& value)
{
    return os << "user-defined stream inserter std::vector<std::pair<int, std::string>>";
}

// user-defined function for test output
std::ostream& user_defined_sutf_printer_function(std::ostream &os,
                                                 const std::vector<std::pair<int, std::string>>& value)
{
    return os << "user-defined test output for std::vector<std::pair<int, std::string>>";
}

#include "single_header/sutf.hpp"

TEST(test_sfinae_print)
{
    {
        std::vector<std::pair<int,int>> data1{{0, 1}, {2, 4}};
        std::vector<std::pair<int,int>> data2{{0, 1}, {2, 1}};

        // std::vector<std::pair<int,int>> has no stream inserter operator
        // values of data1 and data2 will still be printed by
        // SUTF's default test output function
        ASSERT_EQ(data1, data2);
    }

    {
        std::map<int, int> data1{{0, 1}, {2, 4}};
        std::map<int, int> data2{{0, 1}, {2, 6}};


        // std::map<int,int> has defined stream inserter operator
        // values of data1 and data2 will be thus printed by the operator
        ASSERT_EQ(data1,data2);
    }

    {
        std::set<int> data1{1,2,3};
        std::set<int> data2{1,2,4};

        // std::set<int> has defined stream inserter operator
        // values of data1 and data2 will be thus printed by the operator
        ASSERT_EQ(data1,data2);
    }

    {
        std::vector<std::pair<int,std::string>> data1{{0, "abc"}, {2, "def"}};
        std::vector<std::pair<int,std::string>> data2{{0, "abc"}, {2, "efg"}};

        // std::vector<std::pair<int,int>> has stream inserter operator
        // the type also has user_defined_sutf_printer_function, meaning that it shall be
        // used for the output:
        ASSERT_EQ(data1,data2);
    }
}

int main()
{
    // default ("non-test") output for std::vector<std::pair<int,std::string>> uses user-defined
    // stream inserter operator (while for tests' output user_defined_sutf_printer_function is employed)
    std::vector<std::pair<int,std::string>> data1{{0, "abc"}, {2, "def"}};
    std::cout << data1 << std::endl;

    RUN_ALL_TESTS();
    return 0;
}
