#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

#include "binary_operators.h"
#include "printing.h"

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
