cmake_minimum_required(VERSION 3.1...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(sutf_lib
        VERSION 0.3.1
        DESCRIPTION "sutf as a library"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(sutf_lib INTERFACE)

target_include_directories(sutf_lib INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(sutf_lib INTERFACE cxx_std_17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -Wextra")