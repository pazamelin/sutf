#pragma once

#include <cstdint>
#include <iostream>

///////////////////////////////////////
//    BINARY COMPARISON OPERATORS    //
///////////////////////////////////////

namespace sutf::_internal
{
    enum class eOperators : std::uint8_t
    {
        EQ, NE, LT, LE, GT, GE
    };

    std::string to_string(const eOperators& obj)
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

    template<class T, class U>
    constexpr bool apply_operator(const T& t, const U& u,
                                  const eOperators& op) noexcept
    {
        switch (op)
        {
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
        }
    }

} // namespace sutf::_internal