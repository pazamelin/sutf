#include <type_traits> // for enable_if
#include <iostream>
#include <vector>
#include <string>
#include <utility>

//////////////////////////////////////
//   META TYPE CHECK: OPERATOR <<   //
//////////////////////////////////////

namespace sutf::_internal
{
    template<typename T>
    class has_output_operator
    {
    private:

        template<typename U, typename = decltype(std::cout << std::declval<U>())>
        static constexpr bool
        check(nullptr_t) noexcept
        {
            return true;
        }

        template<typename ...>
        static constexpr bool check(...) noexcept
        {
            return false;
        }

    public:
        static constexpr bool value{check<T>(nullptr)};
    };

    template<typename T>
    class is_iteratable
    {
    private:

        template<typename U>
        static constexpr decltype(std::begin(std::declval<U>()),
                std::end(std::declval<U>()),
                bool())
        check(nullptr_t) noexcept
        {
            return true;
        }

        template<typename ...>
        static constexpr bool check(...) noexcept
        {
            return false;
        }

    public:
        static constexpr bool value{check<T>(nullptr)};
    };

    template<typename T>
    void print_meta_info(std::ostream &os = std::cout)
    {
        os << "is iteratable: " << is_iteratable<T>::value << std::endl;
        os << "has output operator: " << has_output_operator<T>::value << std::endl;
        os << std::endl;

        // TODO: check type deduction
    }
} // namespace sutf::internal

//////////////////////////////////
//   DEFAULT OUTPUT ITERATORS   //
//////////////////////////////////

namespace sutf::_internal
{
    template <typename T>
    typename std::enable_if<is_iteratable<T>::value &&
                            !has_output_operator<T>::value,
            std::ostream&>::type
    operator << (std::ostream& os, const T& obj)
    {
        bool flag{false};

        os << "{";
        for(const auto& unit : obj)
        {
            if(flag)
            {
                os << ", ";
            }
            flag = true;
            os << unit;
        }
        os << "}";

        return os;
    }

    template <typename LHS, typename RHS>
    typename std::enable_if<!has_output_operator<std::pair<LHS, RHS>>::value, std::ostream&>::type
    operator << (std::ostream& os, const std::pair<LHS, RHS>& obj)
    {
        return os << "{" << obj.first << ", " << obj.second << "}";
    }

    template <typename T>
    typename std::enable_if<!is_iteratable<T>::value &&
                            !has_output_operator<T>::value,
            std::ostream&>::type
    operator << (std::ostream& os, const T& value)
    {
        // cannot be printed
        // reflection?
        exit(123);
    }

} // namespace sutf::internal