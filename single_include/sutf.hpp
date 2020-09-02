#ifndef SUTF_HPP_
#define SUTF_HPP_

#define SUTF_HPP_VERSION_MAJOR 0
#define SUTF_HPP_VERSION_MINOR 1
#define SUTF_HPP_VERSION_PATCH 1

#if defined(_WIN32) || defined(_WIN64)
    #define SUTF_OS_WINDOWS
#elif defined(__APPLE__)
    #define SUTF_OS_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define SUTF_OS_LINUX
#else
    #error unsupported platform
#endif

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <utility>
#include <string>
#include <list>
#include <chrono>
#include <cstdint>
#include <cstring>

#include "../third_party/termcolor/termcolor.hpp"

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

}

// #ifdef SUTF_HPP_IMPLEMENTATION_H

//////////////////////////////////////////
//   INTERNAL IMPLEMENTATION:: MACROS   //
//////////////////////////////////////////

namespace sutf::_internal
{
    ////////////////////////////////////////////
    //   ASSERT/EXPECT FAIL INFO GENERATION   //
    ////////////////////////////////////////////

    #ifndef __FUNCTION_NAME__
        #ifdef SUTF_OS_WINDOWS
            #define __FUNCTION_NAME__   __FUNCTION__
        #else
            #define __FUNCTION_NAME__   __func__
        #endif
    #endif

    /*
    * STRINGIZE converts its argument into a string constant
    * see:
    * https://gcc.gnu.org/onlinedocs/gcc-7.5.0/cpp/Stringizing.html
    * https://stackoverflow.com/a/4368983
    */

    #define STRINGIZE_IMPLEMENTATION(arg) #arg
    #define STRINGIZE(arg) STRINGIZE_IMPLEMENTATION(arg)

    /*
    * CONCAT merges its arguments into one token
    * see:
    * https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html
    * https://stackoverflow.com/a/4368983
    */

    #define CONCAT_IMPLEMENTATION(arg1, arg2) arg1 ## arg2
    #define CONCAT(arg1, arg2) CONCAT_IMPLEMENTATION(arg1, arg2)

    // fail info generator
    // is used in various assert and expect macros
    #define FAIL_INFO(failed_macro_name, x, op, y)              \
        #failed_macro_name " failed: " #x " " #op " " #y ", "   \
        __FILE__ ":" STRINGIZE(__LINE__)

    #define CHECK_FAIL_INFO(x, y, type, op, iop)                \
        STRINGIZE(type ## _ ## op) " failed: " #x " " #iop " " #y ", "      \
        __FILE__ ":" STRINGIZE(__LINE__)


    //////////////////////////////
    //   ASSERT/EXPECT RESULT   //
    //////////////////////////////

    // result of a single ASSERT or EXPECT macro

    struct check_result
    {
        bool failure;
        bool is_assert;
        const std::string fail_msg;

        check_result(bool _is_assert, std::string &&_fail_msg)
                : is_assert{_is_assert},
                  fail_msg{std::move(_fail_msg)}
        {
            failure = !fail_msg.empty();
        };
    };

    /////////////////////
    //   TEST RESULT   //
    /////////////////////

#include <list>

    // result of a single TEST
    // contains results of all ASSERT and EXPECT macros used in the test

    class test_result
    {
    public:
        test_result() = default;

        void add(check_result &&new_result)
        {
            data.push_back(new_result);
        }

        [[nodiscard]] auto begin()
        {
            return data.begin();
        }

        [[nodiscard]] auto cbegin() const
        {
            return data.cbegin();
        }

        [[nodiscard]] auto end()
        {
            return data.end();
        }

        [[nodiscard]] auto cend() const
        {
            return data.cbegin();
        }

    private:
        ::std::list<check_result> data;
    };

    ////////////////////////////////
    //    TEST FAIL EXCEPTIONS    //
    ////////////////////////////////

    // [[maybe_unused]]

    class fatal_test_error : protected std::runtime_error
    {
    public:
        explicit fatal_test_error(const std::string &__arg)
                : runtime_error(__arg)
        {};

        [[nodiscard]] const char *what() const noexcept override
        {
            return std::runtime_error::what();
        }
    };

    class nonfatal_test_error : protected std::runtime_error
    {
    public:
        explicit nonfatal_test_error(const std::string &__arg)
                : runtime_error(__arg)
        {};

        [[nodiscard]] const char *what() const noexcept override
        {
            return std::runtime_error::what();
        }
    };

    ///////////////////////////////////////
    //    BINARY COMPARISON OPERATORS    //
    ///////////////////////////////////////

    enum class eOperators : std::uint8_t
    {
        EQ, NE, LT, LE, GT, GE
    };

    std::ostream &operator<<(std::ostream &os, const eOperators &obj)
    {
        switch (obj) {
            case eOperators::EQ:
                return os << "==";
            case eOperators::NE:
                return os << "!=";
            case eOperators::LT:
                return os << "<";
            case eOperators::LE:
                return os << "<=";
            case eOperators::GT:
                return os << ">";
            case eOperators::GE:
                return os << ">=";
            default:
                throw std::runtime_error("unknown operator");
        }
    }

    constexpr inline eOperators operator!(const eOperators &obj)
    {
        switch (obj) {
            case eOperators::EQ:
                return eOperators::NE;
            case eOperators::NE:
                return eOperators::EQ;
            case eOperators::LT:
                return eOperators::GE;
            case eOperators::LE:
                return eOperators::GT;
            case eOperators::GT:
                return eOperators::LE;
            case eOperators::GE:
                return eOperators::LT;
            default:
                throw std::runtime_error("unknown operator");
        }
    }

    template<class T, class U>
    bool apply_operator(const T &t, const U &u, const eOperators &op)
    {
        switch (op) {
            case eOperators::EQ:
                return t == u;
            case eOperators::NE:
                return t != u;
            case eOperators::LT:
                return t < u;
            case eOperators::LE:
                return t <= u;
            case eOperators::GT:
                return t > u;
            case eOperators::GE:
                return t >= u;
            default:
                throw std::runtime_error("unknown operator");
        }
    }

    //////////////////////////
    //    CHECK FUNCTION    //
    //////////////////////////

    template<class T, class U>
    check_result check(
            const T &t,
            const U &u,
            eOperators op,
            bool isAssert,
            const std::string &hint = {})
    {
        if (!(apply_operator(t, u, op)))
        {
            std::ostringstream os;
            if (!hint.empty())
            {
                os << "     " << hint << std::endl;
            }

            if (op == eOperators::EQ)
            {
                os << "         actual: " << t;
                os << ", expected: " << u << ", ";
            }
            else
            {
                os << "         ";
            }
            os << t << " " << !op << " " << u << std::endl;

            return {isAssert, os.str()};
        }
        return {isAssert, ""};
    }

    check_result check_cstr(
            const char* const cstr1,
            const char* const cstr2,
            eOperators op,
            bool isAssert,
            const std::string &hint = {})
    {
        if (!(apply_operator(std::strcmp(cstr1, cstr2), 0, op)))
        {
            std::ostringstream os;
            if (!hint.empty())
            {
                os << "     " << hint << std::endl;
            }

            if (op == eOperators::EQ)
            {
                os << "         actual: \"" << cstr1 << "\n";
                os << ", expected: \"" << cstr2 << "\", ";
            }
            else
            {
                os << "         ";
            }
            os << "\"" << cstr1 << "\" " << !op << " \"" << cstr2 << "\"" << std::endl;

            return {isAssert, os.str()};
        }
        return {isAssert, ""};
    }

    ////////////////////////////////////
    //   CHECK MACRO IMPLEMENTATION   //
    ////////////////////////////////////

    #define CHECK_IMPLEMENTATION(x, y, type, op, iop, is_assert)  \
        __rs.add(sutf::_internal::check(x, y,                     \
                 sutf::_internal::eOperators::op,                 \
                 is_assert,                                       \
                 CHECK_FAIL_INFO(x, y, type, op, iop)))

    #define CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, type, op, iop, is_assert)  \
        __rs.add(sutf::_internal::check_cstr(cstr1, cstr2,                     \
                 sutf::_internal::eOperators::op,                              \
                 is_assert,                                                    \
                 CHECK_FAIL_INFO(cstr1, cstr2, type, op, iop)))

    /////////////////////////
    //   TEST TYPE ALIAS   //
    /////////////////////////

    using test_t = void (*)(sutf::_internal::test_result &__rs);
    using test_name_return_t = const char *;
    using test_name_t = test_name_return_t (*)();

    ///////////////////////////////////////////
    //   REGISTER TEST MACRO IMPLEMENTATION  //
    ///////////////////////////////////////////

    // using custom ELF sections:
    // see:
    // https://www.bottomupcs.com/elf.xhtml
    // https://mgalgs.github.io/2013/05/10/hacking-your-ELF-for-fun-and-profit.html
    // https://stackoverflow.com/questions/16552710/how-do-you-get-the-start-and-end-addresses-of-a-custom-elf-section

    // "tests" section accumulates pointers to test functions
    // "test_names" section accumulates test names

    #define REGISTER_TEST(name)                                          \
        void name([[maybe_unused]] sutf::_internal::test_result& __rs);  \
        inline sutf::_internal::test_name_return_t name ## _name();      \
                                                                         \
            sutf::_internal::test_t __test_ ## name                      \
            __attribute__((__section__("tests")))                        \
            __attribute__((__used__))                                    \
            = name;                                                      \
                                                                         \
            sutf::_internal::test_name_t test_name_ ## name              \
            __attribute__((__section__("test_names")))                   \
            __attribute__((__used__))                                    \
            = name ## _name;                                             \
                                                                         \
        inline sutf::_internal::test_name_return_t name ## _name()       \
            { return #name; };                                           \
        void name([[maybe_unused]] sutf::_internal::test_result& __rs)

}

///////////////////////////////////////////////
//   CUSTOM LINKER SECTION ADDRESS VARIABLES //
///////////////////////////////////////////////

// section "tests" address variables:
extern sutf::_internal::test_t __start_tests;
extern sutf::_internal::test_t __stop_tests;

// section "test_names" address variables:
extern sutf::_internal::test_name_t __start_test_names;
extern sutf::_internal::test_name_t __stop_test_names;

///////////////////////////////////////////////
//   INTERNAL IMPLEMENTATION:: TEST RUNNER   //
///////////////////////////////////////////////

namespace sutf::_internal
{
    //////////////////
    //   PROFILER   //
    //////////////////

    #define UNIQUE_ID_IMPLEMENTATION(type, line) __ ## type ## _ ## line
    #define UNIQUE_ID(type, line) UNIQUE_ID_IMPLEMENTATION(type, line)
    #define LOG_DURATION(msg) LogDuration UNIQUE_ID(log_duration_, __LINE__){msg}

    class LogDuration
    {
    public:
        explicit LogDuration(std::string _msg = "")
                 : msg{std::move(_msg)},
                   start{std::chrono::steady_clock::now()}
                   {};

        ~LogDuration()
        {
            auto finish{std::chrono::steady_clock::now()};
            auto duration{finish - start};
            std::cerr << msg << ": " << std::chrono::duration_cast<std::chrono::milliseconds>
                (duration).count() << " ms " << std::endl;
        }

    private:
        const std::string msg;
        const std::chrono::steady_clock::time_point start;
    };

    ////////////////
    //   LABELS   //
    ////////////////

    #define LABEL_RUN     " [ RUN      ] "
    #define LABEL_OK      " [       OK ] "
    #define LABEL_FAIL    " [  FAILED  ] "
    #define LABEL_PASS    " [  PASSED  ] "
    #define LABEL_LINE    " [----------] "
    #define LABEL_LINES   " [==========] "
    #define LABEL_EMPTY   " [          ] "

    /////////////////////
    //   TEST RUNNER   //
    /////////////////////

    class TestRunner
    {
    public:
        template<class TestFunction>
        void runTest(TestFunction test, const std::string &test_name)
        {
            test_result result;
            int __asserts_failed{0};
            int __expects_failed{0};

            std::cerr << termcolor::green << LABEL_RUN << test_name << std::endl;

            auto start{std::chrono::steady_clock::now()};

            test(result);

            auto finish{std::chrono::steady_clock::now()};
            auto duration{finish - start};

            for (const auto &res : result)
            {
                if (res.failure)
                {
                    auto msg_color{res.is_assert ? termcolor::red : termcolor::yellow};
                    std::cerr << msg_color << res.fail_msg;
                    __asserts_failed += res.is_assert;
                    __expects_failed += 1 - res.is_assert;
                }
            }
            if (__asserts_failed == 0)
            {
                std::cerr << termcolor::green << LABEL_OK;
                std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>
                        (duration).count() << " ms " << std::endl;

                tests_passed++;
            }
            else
            {
                std::cerr << termcolor::red << LABEL_FAIL << test_name;
                std::cerr << ", " << std::chrono::duration_cast<std::chrono::milliseconds>
                        (duration).count() << " ms " << std::endl;
                std::cerr << std::endl;

                tests_failed++;
            }

            asserts_failed += __asserts_failed;
            expects_failed += __expects_failed;
        }

        void run_all_tests()
        {
            // using custom ELF sections

            // see:
            // https://www.bottomupcs.com/elf.xhtml
            // https://mgalgs.github.io/2013/05/10/hacking-your-ELF-for-fun-and-profit.html
            // https://stackoverflow.com/questions/16552710/how-do-you-get-the-start-and-end-addresses-of-a-custom-elf-section

            // iterating over sections' accumulated data
            test_t *test_ptr = &__start_tests;
            test_name_t *test_name_ptr = &__start_test_names;
            while (test_ptr != &__stop_tests && test_name_ptr != &__stop_test_names)
            {
                runTest(*test_ptr, (*test_name_ptr)());
                test_name_ptr++;
                test_ptr++;
            }
        }

        ~TestRunner()
        {
            std::cerr << termcolor::green << LABEL_LINES << std::endl;
            std::cerr << termcolor::green << LABEL_PASS  << tests_passed << " tests." << std::endl;
            std::cerr << termcolor::red   << LABEL_FAIL  << tests_failed << " tests." << std::endl;

            if (tests_failed > 0)
            {
                std::cerr << termcolor::red << LABEL_FAIL << "terminate!" << std::endl;
                exit(1);
            }

            std::cerr << termcolor::red << LABEL_PASS << std::endl;
        }

    private:
        int asserts_failed = 0;
        int expects_failed = 0;
        int tests_passed = 0;
        int tests_failed = 0;
    };

    void run_all_tests()
    {
        TestRunner tr;
        tr.run_all_tests();
    }

    #define RUN_ALL_TESTS_IMPLEMENTATION()   \
        sutf::_internal::run_all_tests();
}

// #endif /* SUTF_HPP_IMPLEMENTATION_H */

#undef SUTF_OS_WINDOWS
#undef SUTF_OS_MACOS
#undef SUTF_OS_LINUX

#endif /* SUTF_HPP_ */
