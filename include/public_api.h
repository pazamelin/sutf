#pragma once

///////////////////////////
//   PUBLIC INTERFACE:   //
///////////////////////////

namespace sutf
{
    /////////////////////////////
    //   TEST CREATION MACRO   //
    /////////////////////////////

    #define TEST(name) \
        REGISTER_TEST(name)

    ///////////////////////////////
    //   TEST EXECUTION MACROS   //
    ///////////////////////////////

    // run a single test:
    #define RUN_TEST(name) \
        RUN_TEST_IMPLEMENTATION(name)

    // run all created tests:
    #define RUN_ALL_TESTS() \
        RUN_ALL_TESTS_IMPLEMENTATION()

    ////////////////////////////////
    //   ASSERT OPERATOR MACROS   //
    ////////////////////////////////

    // asserts: x == y
    #define ASSERT_EQ(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, EQ, !=, true)

    // asserts: x != y
    #define ASSERT_NE(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, NE, ==, true)

    // asserts: x < y
    #define ASSERT_LT(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, LT, >=, true)

    // asserts: x <= y
    #define ASSERT_LE(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, LE, >, true)

    // asserts: x > y
    #define ASSERT_GT(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, GT, <=, true)

    // asserts: x >= y
    #define ASSERT_GE(x, y) \
        CHECK_IMPLEMENTATION(x, y, ASSERT, GE, <, true)

    ////////////////////////////////
    //   EXPECT OPERATOR MACROS   //
    ////////////////////////////////

    // expects: x == y
    #define EXPECT_EQ(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, EQ, !=, false)

    // expects: x != y
    #define EXPECT_NE(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, NE, ==, false)

    // expects: x < y
    #define EXPECT_LT(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, LT, >=, false)

    // expects: x <= y
    #define EXPECT_LE(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, LE, >, false)

    // expects: x > y
    #define EXPECT_GT(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, GT, <, false)

    // expects: x >= y
    #define EXPECT_GE(x, y) \
        CHECK_IMPLEMENTATION(x, y, EXPECT, GE, <=, false)

    /////////////////////////////////////
    //   ASSERT_CSTR OPERATOR MACROS   //
    /////////////////////////////////////

    // assert operator macros for C strings

    // asserts: cstr1 == cstr2
    #define ASSERT_CSTR_EQ(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, EQ, !=, true)

    // asserts: cstr1 != cstr2
    #define ASSERT_CSTR_NE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, NE, ==, true)

    // asserts: cstr1 < cstr2
    #define ASSERT_CSTR_LT(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, LT, >=, true)

    // asserts: cstr1 <= cstr2
    #define ASSERT_CSTR_LE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, LE, >, true)

    // asserts: cstr1 > cstr2
    #define ASSERT_CSTR_GT(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, GT, <=, true)

    // asserts: cstr1 >= cstr2
    #define ASSERT_CSTR_GE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, ASSERT_CSTR, GE, <, true)

    /////////////////////////////////////
    //   EXPECT_CSTR OPERATOR MACROS   //
    /////////////////////////////////////

    // expect operator macros for C strings

    // expects: cstr1 == cstr2
    #define EXPECT_CSTR_EQ_(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, EQ, !=, false)

    // expects: cstr1 != cstr2
    #define EXPECT_CSTR_NE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, NE, ==, false)

    // expects: cstr1 < cstr2
    #define EXPECT_CSTR_LT(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, LT, >=, false)

    // expects: cstr1 <= cstr2
    #define EXPECT_CSTR_LE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, LE, >, false)

    // expects: cstr1 > cstr2
    #define EXPECT_CSTR_GT(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, GT, <=, false)

    // expects: cstr1 >= cstr2
    #define EXPECT_CSTR_GE(cstr1, cstr2) \
        CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, EXPECT_CSTR, GE, <, false)

    //////////////////////////////////
    //   ASSERT TRUE/FALSE MACROS   //
    //////////////////////////////////

    // asserts: condition == true
    #define ASSERT_TRUE(condition) \
        ASSERT_EQ(condition, true)

    // asserts: condition == false
    #define ASSERT_FALSE(condition) \
        ASSERT_EQ(condition, false)

    //////////////////////////////////
    //   EXPECT TRUE/FALSE MACROS   //
    //////////////////////////////////

    // expects: condition == true
    #define EXPECT_TRUE(condition) \
        EXPECT_EQ(condition, true)

    // expects: condition == true
    #define EXPECT_FALSE(condition) \
        EXPECT_EQ(condition, false)

    //////////////////////////
    //   ASSERT PTR MACRO   //
    //////////////////////////

    // asserts: ptr != nullptr
    #define ASSERT_PTR(ptr) \
        ASSERT_NE(ptr, nullptr)

    //////////////////////////
    //   EXPECT PTR MACRO   //
    //////////////////////////

    #define EXPECT_PTR(ptr) \
        EXPECT_NE(ptr, nullptr)

} // namespace sutf
