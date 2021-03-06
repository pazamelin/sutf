#ifndef SUTF_HPP
#define SUTF_HPP

#define SUTF_HPP_VERSION_MAJOR 0
#define SUTF_HPP_VERSION_MINOR 3
#define SUTF_HPP_VERSION_PATCH 2
#define SUTF_HPP_VERSION_TWEAK 1

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

#include <public/public_api.h>

#include <internal/fail_info.h>
#include <internal/binary_operators.h>
#include <internal/printing.h>
#include <internal/check.h>
#include <internal/test.h>
#include <internal/linker_sections.h>
#include <internal/test_runner.h>

#undef SUTF_OS_WINDOWS
#undef SUTF_OS_MACOS
#undef SUTF_OS_LINUX

#endif // SUTF_HPP