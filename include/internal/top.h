#ifndef SUTF_HPP
#define SUTF_HPP

#define SUTF_HPP_VERSION_MAJOR 0
#define SUTF_HPP_VERSION_MINOR 3
#define SUTF_HPP_VERSION_PATCH 1

#if defined(_WIN32) || defined(_WIN64)
    #define SUTF_OS_WINDOWS
#elif defined(__APPLE__)
    #define SUTF_OS_MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define SUTF_OS_LINUX
#else
    #error unsupported platform
#endif

    // is not to be ignored during merging:
    #include "../third_party/termcolor/termcolor.hpp"