#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

#include "binary_operators.h"
#include "printing.h"

namespace sutf::_internal
{

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

    ///////////////////
    //    CHECKER    //
    ///////////////////

    template<class T, class U>
    class checker
    {
    public:

        template<eOperators op>
        static check_result check(const T& t,
                           const U& u,
                           bool isAssert,
                           const std::string& hint = { })
        {
            if (!(operator_applier<T, U>::template apply<op>(t, u)))
            {
                std::ostringstream os;
                if (!hint.empty())
                {
                    os << "     " << hint << std::endl;
                }

                if (op == eOperators::EQ)
                {
                    os << "         actual: ";
                    sutf_printer_function(os, t);
                    os << ", expected: ";
                    sutf_printer_function(os, u);
                    os << "; ";
                }
                else
                {
                    os << "         ";
                }
                sutf_printer_function(os, t);
                os << " " << sutf::_internal::to_string(!op) << " ";
                sutf_printer_function(os, u);
                os << std::endl;

                return {isAssert, os.str()};
            }
            return {isAssert, ""};
        }
    };

    class checker_cstr
    {
    public:

        template<eOperators op>
        static check_result check(const char* const cstr1,
                           const char* const cstr2,
                           bool isAssert,
                           const std::string& hint = { })
        {
            int cstr_cmp_value{std::strcmp(cstr1, cstr2)};
            if (!(operator_applier<int, int>::template apply<op>(cstr_cmp_value, 0)))
            {
                std::ostringstream os;
                if (!hint.empty())
                {
                    os << "     " << hint << std::endl;
                }

                if (op == eOperators::EQ)
                {
                    os << "         actual: \"" << cstr1 << "\n";
                    os << ", expected: \"" << cstr2 << "\"; ";
                }
                else
                {
                    os << "         ";
                }
                os << "\"" << cstr1 << "\" " << sutf::_internal::to_string(!op)
                   << " \"" << cstr2 << "\"" << std::endl;

                return {isAssert, os.str()};
            }
            return {isAssert, ""};
        }
    };

    ////////////////////////////////////
    //   CHECK MACRO IMPLEMENTATION   //
    ////////////////////////////////////

    #define CHECK_IMPLEMENTATION(x, y, type, op, iop, is_assert)      \
        __rs.add(sutf::_internal::checker<decltype(x), decltype(y)>:: \
                    check<sutf::_internal::eOperators::op>(x, y,      \
                        is_assert,                                    \
                        CHECK_FAIL_INFO(x, y, type, op, iop)))

    #define CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, type, op, iop, is_assert)      \
        __rs.add(sutf::_internal::checker_cstr::                                   \
                    check<sutf::_internal::eOperators::op>(cstr1, cstr2,           \
                        is_assert,                                                 \
                        CHECK_FAIL_INFO(cstr1, cstr2, type, op, iop)))

} // namespace sutf::_internal
