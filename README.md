# sutf
## simple unit test framework created for the sake of some C++ practice; currently in developemt, thus stable work is not guaranteed.

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

| Fatal assertion                | Nonfatal assertion             | Verifies                                                 |
| --------------------------     | ------------------------------ | -------------------------------------------------------- |
| `ASSERT_STREQ(str1,str2);`     | `EXPECT_STREQ(str1,str2);`     | the two C strings have the same content   		     |
| `ASSERT_STRNE(str1,str2);`     | `EXPECT_STRNE(str1,str2);`     | the two C strings have different contents 		     |

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
TEST(TestSuiteName, TestName) {
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

#include "single_include/sutf.hpp"

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

    ASSERT_EQ(value_entries,2u);
    ASSERT_EQ(value_entries,3u);
}

int main()
{
    RUN_ALL_TESTS();
    return 0;
}
```
