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

cmake_minimum_required(VERSION 3.10)
project("something_code")

#enable_testing()

#SET(SRCS
#  source/list.c
#  source/cache.c
#  source/hash.c
#)

#SET(TESTS ${CMAKE_SOURCE_DIR}/Tests)

#add_library(lclib STATIC ${SRCS})

add_executable(a.out main.cpp algorithm.cpp)
target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(a.out lclib)

#file(GLOB testfiles "Tests/*.dat")
#foreach(file ${testfiles})
#  add_test(
#    NAME ${file}
#    COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${file} ./LC.x"
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#  set_tests_properties(${file} PROPERTIES DEPENDS LC.x)
#endforeach()