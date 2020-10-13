cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(MERGER VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set a variable for .cpp source files
set(SOURCES main.cpp)

# set a variable .h headers
set(HEADERS merger.hpp)

# add the executable
add_library(MERGER ${SOURCES} ${HEADERS})

set_target_properties(
        MERGER PROPERTIES
        CMAKE_CXX_STANDARD 17
        CMAKE_CXX_STANDARD_REQUIRED ON
)

# enable all warnings during compile process
# append flag to previously defined flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")