#pragma once

#include <list>

#include "check.h"

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