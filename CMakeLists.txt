#------------------------------------------------------------------------------
#
# CMake approach
# * dependencies are all correct
# * additional library output
# * object targets and separate dir for free
#
#------------------------------------------------------------------------------
#
# This file is licensed after LGPL v3
# Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
#
#------------------------------------------------------------------------------

# rm -rf build
# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build 
# cmake --build ./build
# env CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --target test

cmake_minimum_required(VERSION 3.14)
project("triangle")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(a.out main.cpp)
target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(tests tests/test_main.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(tests)


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()