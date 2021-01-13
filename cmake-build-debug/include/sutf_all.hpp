#ifndef SUTF_HPP
#define SUTF_HPP

#define SUTF_HPP_VERSION_MAJOR 0
#define SUTF_HPP_VERSION_MINOR 3
#define SUTF_HPP_VERSION_PATCH 1
#define SUTF_HPP_VERSION_TWEAK 
#define SUTF_HPP_VERSION "0.3.1"

#if defined(_WIN32) || defined(_WIN64)
    #define SUTF_OS_WINDOWS
#elif defined(__APPLE__)
    #define SUTF_OS_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define SUTF_OS_LINUX
#else
    #error unsupported platform
#endif

#include "../third_party/termcolor/termcolor.hpp"

#include "public_api.h"

#include "fail_info.h"
#include "binary_operatrs.h"
#include "printing.h"
#include "check.h"
#include "test"
#include "linker_sections.h"
#include "test_runner.h"

#undef SUTF_OS_WINDOWS
#undef SUTF_OS_MACOS
#undef SUTF_OS_LINUX

#endif // SUTF_HPP_