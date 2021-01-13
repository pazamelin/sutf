#pragma once

#include "test.h"

///////////////////////////////////////////////
//   CUSTOM LINKER SECTION ADDRESS VARIABLES //
///////////////////////////////////////////////

// section "tests" address variables:
extern sutf::_internal::test_t __start_tests;
extern sutf::_internal::test_t __stop_tests;

// section "test_names" address variables:
extern sutf::_internal::test_name_t __start_test_names;
extern sutf::_internal::test_name_t __stop_test_names;

