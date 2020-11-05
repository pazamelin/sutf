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