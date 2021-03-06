#ifndef SUTF_HPP
#define SUTF_HPP

#define SUTF_HPP_VERSION_MAJOR 0
#define SUTF_HPP_VERSION_MINOR 3
#define SUTF_HPP_VERSION_PATCH 2
#define SUTF_HPP_VERSION_TWEAK 1

#if defined(_WIN32) || defined(_WIN64)
    #define SUTF_OS_WINDOWS
#elif defined(__APPLE__)
    #define SUTF_OS_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define SUTF_OS_LINUX
#else
    #error unsupported platform
#endif

#include "../third_party/termcolor/termcolor.hpp"

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

#pragma once

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

    #define CHECK_FAIL_INFO(x, y, type, op, iop)                            \
        STRINGIZE(type ## _ ## op) " failed: " #x " " #iop " " #y ", "      \
        __FILE__ ":" STRINGIZE(__LINE__)

} // namespace sutf::_internal

#pragma once

#include <cstring>
#include <iostream>

///////////////////////////////////////
//    BINARY COMPARISON OPERATORS    //
///////////////////////////////////////

namespace sutf::_internal
{
    enum class eOperators : unsigned char
    {
        EQ, NE, LT, LE, GT, GE
    };

    constexpr const char* to_string(const eOperators& obj) noexcept
    {
        switch (obj)
        {
            case eOperators::EQ:
                return "==";
            case eOperators::NE:
                return "!=";
            case eOperators::LT:
                return "<";
            case eOperators::LE:
                return "<=";
            case eOperators::GT:
                return ">";
            case eOperators::GE:
                return ">=";
        }
    }

    constexpr eOperators operator ! (const eOperators& obj) noexcept
    {
        switch (obj)
        {
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
        }
    }

    template <class T, class U>
    class operator_applier
    {
        template <eOperators, typename DUMMY = void>
        struct specialized_applier
        {
            constexpr static void apply(const T& lhs, const U& rhs);
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::EQ, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs == rhs;
            }
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::NE, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs != rhs;
            }
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::LT, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs < rhs;
            }
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::LE, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs <= rhs;
            }
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::GT, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs > rhs;
            }
        };

        template <typename DUMMY>
        struct specialized_applier<eOperators::GE, DUMMY>
        {
            constexpr static bool apply(const T& lhs, const U& rhs)
            {
                return lhs >= rhs;
            }
        };

    public:
        template <eOperators op>
        constexpr static bool apply(const T& lhs, const U& rhs)
        {
            return specialized_applier<op>::apply(lhs, rhs);
        }
    };

} // namespace sutf::_internal
#pragma once

#include <type_traits> // for enable_if, void_t, true_type, false_type
#include <iostream>
#include <string_view>
#include <utility>

//////////////////////////////////////
//   META TYPE CHECK: OPERATOR <<   //
//////////////////////////////////////

namespace sutf::_internal
{
    template <typename T, typename = void>
    struct has_output_operator : std::false_type { };

    template <typename T>
    struct has_output_operator<T, std::void_t<decltype(std::declval<std::ostream&>()
                                                       << std::declval<T>())>>
        : std::true_type { };

///////////////////////////////////
//   META TYPE CHECK: ITERABLE   //
///////////////////////////////////

    template <typename T, typename = void>
    struct is_iterable : std::false_type { };

    template <typename T>
    struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                      decltype(std::declval<T>().end())>>
        : std::true_type { };

///////////////////////////////////
//   META TYPE CHECK: ITERABLE   //
///////////////////////////////////

    template <typename T, typename = void>
    struct has_user_defined_sutf_printer_function : std::false_type { };

    template <typename T>
    struct has_user_defined_sutf_printer_function<T,
            std::void_t<decltype(user_defined_sutf_printer_function(std::declval<std::ostream&>(),
                                                                    std::declval<T>()))>>
            : std::true_type { };

//////////////////////////////
//   TYPE DEBUG META INFO   //
//////////////////////////////

    template<typename T>
    void print_meta_info(std::ostream& os = std::cout)
    {
        os << "is iteratable: " << is_iterable<T>::value << std::endl;
        os << "has output operator: " << has_output_operator<T>::value << std::endl;
        os << std::endl;
    }

} // namespace sutf::internal

///////////////////////////////////
//   DEFAULT PRINTER FUNCTIONS   //
///////////////////////////////////

/////////////////////////////////////////////////
//   FOR TYPES WITH DEFINED STREAM INSERTERS   //
/////////////////////////////////////////////////

template<typename T>
typename std::enable_if<sutf::_internal::has_output_operator<T>::value &&
                        !sutf::_internal::has_user_defined_sutf_printer_function<T>::value,
std::ostream&>::type
sutf_printer_function(std::ostream& os, const T& value)
{
    return os << value;
}

template<typename T>
typename std::enable_if<sutf::_internal::has_output_operator<T>::value &&
                        sutf::_internal::has_user_defined_sutf_printer_function<T>::value,
std::ostream&>::type
sutf_printer_function(std::ostream& os, const T& value)
{
    return user_defined_sutf_printer_function(os, value);
}

////////////////////////////////////////////////
//   TYPES WITHOUT DEFINED STREAM INSERTERS   //
////////////////////////////////////////////////

template<typename T>
typename std::enable_if<!sutf::_internal::has_output_operator<T>::value &&
                         sutf::_internal::has_user_defined_sutf_printer_function<T>::value,
std::ostream&>::type
sutf_printer_function(std::ostream& os, const T& value)
{
    return user_defined_sutf_printer_function(os, value);
}

template<typename LHS, typename RHS>
typename std::enable_if<!sutf::_internal::has_output_operator<std::pair<LHS, RHS>>::value &&
                        !sutf::_internal::has_user_defined_sutf_printer_function
                                                    <std::pair<LHS, RHS>>::value,
std::ostream&>::type
sutf_printer_function(std::ostream& os, const std::pair<LHS, RHS>& obj)
{
    os << "{";
    sutf_printer_function(os, obj.first);
    os << ", ";
    sutf_printer_function(os, obj.second);
    return os << "}";
}

template<typename T>
typename std::enable_if<!sutf::_internal::has_output_operator<T>::value &&
                        !sutf::_internal::has_user_defined_sutf_printer_function<T>::value &&
                         sutf::_internal::is_iterable<T>::value,
std::ostream& >::type
sutf_printer_function(std::ostream& os, const T& obj)
{
    bool flag{false};

    os << "{";
    for (const auto& unit : obj)
    {
        if (flag)
        {
            os << ", ";
        }
        flag = true;
        sutf_printer_function(os, unit);
    }
    os << "}";

    return os;
}

///////////////////////////
//   'UNPRINTABLE' TYPE  //
///////////////////////////

// https://stackoverflow.com/a/20170989/13589244
template <typename T>
constexpr auto type_name() noexcept
{
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void) noexcept";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

template<typename T>
typename std::enable_if<!sutf::_internal::has_output_operator<T>::value &&
                        !sutf::_internal::has_user_defined_sutf_printer_function<T>::value &&
                        !sutf::_internal::is_iterable<T>::value,
std::ostream& >::type
sutf_printer_function(std::ostream& os, const T&)
{
    // TODO: reflection  for unprintable type
    // cannot be printed
    return os << "\"" << type_name<T>() << "\"";
}
#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

// #include "binary_operators.h"
// #include "printing.h"

namespace sutf::_internal
{
    class TestRunner;

    //////////////////////////////
    //   ASSERT/EXPECT RESULT   //
    //////////////////////////////

    // result of a single ASSERT or EXPECT macro
    struct check_result
    {
    public:
        check_result() = default;

        template <class Message>
        check_result(bool _is_assert, Message&& fail_msg)
            : is_assert{_is_assert}
        {
            set_failure_msg(std::forward<Message>(fail_msg));
        };

        check_result(const check_result& other) = default;
        check_result(check_result&& other) = default;

        template <class Message>
        void set_failure_msg(Message&& msg)
        {
            this->fail_msg = std::forward<Message>(msg);
            failure = not this->fail_msg.empty();
        }

        void set_type(bool _is_assert_)
        {
            this->is_assert = _is_assert_;
        }

    private:
        bool failure   = false;
        bool is_assert = false;
        std::string fail_msg;

        friend class TestRunner;
    };

    /////////////////////////////////
    //    ASSERT/EXPECT CHECKER    //
    /////////////////////////////////

    class checker
    {
    public:

        template<class T, eOperators op, class U>
        static check_result check(const T& t,
                                  const U& u,
                                  bool isAssert,
                                  const std::string& hint = { }
        )
        {
            check_result result;
            result.set_type(isAssert);

            if (!(operator_applier<T, U>::template apply<op>(t, u)))
            {
                std::ostringstream os;
                print_fail_info<T, op, U>(os, t, u, hint);
                result.set_failure_msg(os.str());
            }

            return result;
        }

        template<eOperators op>
        static check_result check_cstr(const char* const cstr1,
                                       const char* const cstr2,
                                       bool isAssert,
                                       const std::string& hint = { }
        )
        {
            using cstr_t = const char* const;
            check_result result;
            result.set_type(isAssert);

            int cstr_cmp_value{std::strcmp(cstr1, cstr2)};
            if (!(operator_applier<int, int>::template apply<op>(cstr_cmp_value, 0)))
            {
                std::ostringstream os;
                print_fail_info<cstr_t, op, cstr_t>(os, cstr1, cstr2, hint);
                result.set_failure_msg(os.str());
            }

            return result;
        }

    private:

        template<class T, eOperators op, class U>
        static void print_fail_info(std::ostream& os,
                                    const T& t,
                                    const U& u,
                                    const std::string& hint
        )
        {
            if (!hint.empty())
            {
                os << "     " << hint << std::endl;
            }

            os << "         lhs: ";
            print_value(os, t);
            os << "\n";

            os << "         rhs: ";
            print_value(os, u);
            os << "\n";

            os << "         lhs "<< sutf::_internal::to_string(!op) << " rhs";
            os << std::endl;
        }

        template <typename T>
        static void print_value(std::ostream& os, const T& value)
        {
            os << "'";
            sutf_printer_function(os, value);
            os << "'";
        }
    };

    ////////////////////////////////////
    //   CHECK MACRO IMPLEMENTATION   //
    ////////////////////////////////////

    #define CHECK_IMPLEMENTATION(x, y, type, op, iop, is_assert)  \
        __rs.add(sutf::_internal::checker::                       \
                    check<decltype(x),                            \
                          sutf::_internal::eOperators::op,        \
                          decltype(y)>                            \
                    (                                             \
                          x,                                      \
                          y,                                      \
                          is_assert,                              \
                          CHECK_FAIL_INFO(x, y, type, op, iop)    \
                    )                                             \
        )

    #define CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, type, op, iop, is_assert)  \
        __rs.add(sutf::_internal::checker::                                    \
                    check_cstr<sutf::_internal::eOperators::op>                \
                    (                                                          \
                        cstr1,                                                 \
                        cstr2,                                                 \
                        is_assert,                                             \
                        CHECK_FAIL_INFO(cstr1, cstr2, type, op, iop)           \
                    )                                                          \
        )

} // namespace sutf::_internal

#pragma once

#include <list>

// #include "check.h"

namespace sutf::_internal
{
    class test_result;

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

    #define REGISTER_TEST(name)                                              \
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

        [[nodiscard]] auto begin() noexcept
        {
            return data.begin();
        }

        [[nodiscard]] auto end() noexcept
        {
            return data.end();
        }

        [[nodiscard]] auto cbegin() const noexcept
        {
            return data.cbegin();
        }

        [[nodiscard]] auto cend() const noexcept
        {
            return data.cbegin();
        }

    private:

        ::std::list<check_result> data;
    };

} // namespace sutf::_internal
#pragma once

// #include "test.h"

///////////////////////////////////////////////
//   CUSTOM LINKER SECTION ADDRESS VARIABLES //
///////////////////////////////////////////////

// section "tests" address variables:
extern sutf::_internal::test_t __start_tests;
extern sutf::_internal::test_t __stop_tests;

// section "test_names" address variables:
extern sutf::_internal::test_name_t __start_test_names;
extern sutf::_internal::test_name_t __stop_test_names;


#pragma once

#include <string>
#include <utility>
#include <chrono>
#include <iostream>

// #include "test.h"
// #include "linker_sections.h"

namespace sutf::_internal
{
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

} // namespace sutf::_internal

#undef SUTF_OS_WINDOWS
#undef SUTF_OS_MACOS
#undef SUTF_OS_LINUX

#endif // SUTF_HPP
