#pragma once

#include <string>
#include <utility>
#include <chrono>
#include <iostream>

#include "test.h"
#include "linker_sections.h"

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
