cmake_minimum_required(VERSION 3.1...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(sutf_example
        VERSION 0.1
        DESCRIPTION "sutf usage demonstration"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES_LIST main.cpp)
set(HEADERS_LIST)

add_executable(sutf_example_1 ${SOURCES_LIST} ${HEADERS_LIST})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(include/)
    target_link_libraries(sutf_example_1 sutf_lib)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -Wextra -pthread")