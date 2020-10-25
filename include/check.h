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

    check_result check_cstr(
            const char *const cstr1,
            const char *const cstr2,
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

    ////////////////////////////////////
    //   CHECK MACRO IMPLEMENTATION   //
    ////////////////////////////////////

    #define CHECK_IMPLEMENTATION(x, y, type, op, iop, is_assert) \
        __rs.add(sutf::_internal::check(x, y,                    \
                 sutf::_internal::eOperators::op,                \
                 is_assert,                                      \
                 CHECK_FAIL_INFO(x, y, type, op, iop)))

    #define CHECK_CSTR_IMPLEMENTATION(cstr1, cstr2, type, op, iop, is_assert) \
        __rs.add(sutf::_internal::check_cstr(cstr1, cstr2,                    \
                 sutf::_internal::eOperators::op,                             \
                 is_assert,                                                   \
                 CHECK_FAIL_INFO(cstr1, cstr2, type, op, iop)))

} // namespace sutf::_internal
