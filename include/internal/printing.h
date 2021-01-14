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