# simple unit test framework

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/954f686578db42a49f614bc4eea033f0)](https://app.codacy.com/gh/pazamelin/sutf?utm_source=github.com&utm_medium=referral&utm_content=pazamelin/sutf&utm_campaign=Badge_Grade)

## Assertions:

### Basic Assertions

These assertions do basic true/false condition testing.

Fatal assertion            | Nonfatal assertion         | Verifies
-------------------------- | -------------------------- | --------------------
`ASSERT_TRUE(condition);`  | `EXPECT_TRUE(condition);`  | `condition` is true
`ASSERT_FALSE(condition);` | `EXPECT_FALSE(condition);` | `condition` is false

### Binary Comparison

This section describes assertions that compare two values.

Fatal assertion          | Nonfatal assertion       | Verifies
------------------------ | ------------------------ | --------------
`ASSERT_EQ(val1, val2);` | `EXPECT_EQ(val1, val2);` | `val1 == val2`
`ASSERT_NE(val1, val2);` | `EXPECT_NE(val1, val2);` | `val1 != val2`
`ASSERT_LT(val1, val2);` | `EXPECT_LT(val1, val2);` | `val1 < val2`
`ASSERT_LE(val1, val2);` | `EXPECT_LE(val1, val2);` | `val1 <= val2`
`ASSERT_GT(val1, val2);` | `EXPECT_GT(val1, val2);` | `val1 > val2`
`ASSERT_GE(val1, val2);` | `EXPECT_GE(val1, val2);` | `val1 >= val2`

### String Comparison

The assertions in this group compare two **C strings**. If you want to compare
two `string` objects, use `EXPECT_EQ`, `EXPECT_NE`, and etc instead.

<!-- mdformat off(github rendering does not support multiline tables) -->

| Fatal assertion                  | Nonfatal assertion               | Verifies                                                 |
| --------------------------       | ------------------------------   | -------------------------------------------------------- |
| `ASSERT_CSTR_EQ(str1,str2);`     | `EXPECT_CSTR_EQ(str1,str2);`     | the two C strings have the same content   		     |
| `ASSERT_CSTR_NE(str1,str2);`     | `EXPECT_CSTR_NE(str1,str2);`     | the two C strings have different contents 		     |

<!-- mdformat on-->

## Simple Tests

To create a test:

1.  Use the `TEST()` macro to define and name a test function. 
2.  In this function, along with any valid C++ statements you want to include,
    use the various assertions to check values.
3.  The test's result is determined by the assertions. 
    If any `ASSERT_*` in the test fails or if the test crashes, the entire test fails.
    If any `EXPECT_*` in the test fails, an error message is produced, but the entire test won't fail.

```c++
TEST(TestName) {
  ... test body ...
}
```
To run all created tests use the `RUN_ALL_TESTS()` macro.

## Usage Example:

```c++
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>

#include "single_header/sutf.hpp"

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

int main()
{
     RUN_ALL_TESTS();
     return 0;
}
```

## Test output:
If an assertion fails, an according failure message is printed to std::cerr in to provide information about failed comparison.
The failure message, inter alia, contains `actual` and `expected` values according to the failed assertion. There are, however, three different cases for test output:
1. If type T used in the failed assertion has no standard stream inserter operator, then values of the type will still be printed by default test output function.
2. If the type T has standard stream inserter operator, then the operator is used for printing the failure message.
3. If the type T has standard stream inserter operator, but also has user-defined function for test output, than the function is to be used.
The function would provide different output for testing than the “normal” output. For example, you may want to print some hidden flags or data in the type that normally wouldn’t be exposed while printing.
Function format:
```c++
std::ostream& user_defined_sutf_printer_function(std::ostream &os, T value)
{
  ...
}
```
### Examples for the three cases:
```c++
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

TEST(test_output_print)
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


```
