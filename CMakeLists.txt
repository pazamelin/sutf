cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(SUTF VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(merger ../merger/cmake-build-debug)

# set a variable for .cpp source files
set(SOURCES
        main.cpp
)

# set a variable .h headers
set(HEADERS
        # third party:
        third_party/termcolor/termcolor.hpp

        # local includes:
        include/public_api.h
        include/fail_info.h include/binary_operators.h
        include/check.h
        include/test.h
        include/test_runner.h
        include/linker_sections.h
        include/printing.h

        # single header result:
        single_header/sutf.hpp
)

# add the executable
add_executable(SUTF ${SOURCES} ${HEADERS})

set_target_properties(
        SUTF PROPERTIES
        CMAKE_CXX_STANDARD 17
        CMAKE_CXX_STANDARD_REQUIRED ON
)

# enable all warnings during compile process
# append flag to previously defined flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -Wextra")
