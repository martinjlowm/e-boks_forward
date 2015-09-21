########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(libeboks CXX C)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")

option(test "Build all tests." OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(curl)
find_package(libxml++)

########################################################################
# Setup the include and linker paths
########################################################################
include_directories(
    src
    ${libcurl_INCLUDE_DIRS}
    ${libxml++_INCLUDE_DIRS}
    ${CPPUNIT_INCLUDE_DIRS}
)

link_directories(
  ${libcurl_LIBRARY_DIRS}
  ${libxml++_LIBRARY_DIRS}
  ${CPPUNIT_LIBRARY_DIRS}
)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_library(libeboks ${SRC_FILES})
target_link_libraries(libeboks ${libcurl_LIBRARIES} ${libxml++_LIBRARIES})

if (test)
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/gmock-1.7.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gmock_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
    ${gmock_SOURCE_DIR})

  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

  ##############
  # Unit Tests
  ##############
  file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cc)
  add_executable(runUnitTests
    ${TEST_FILES})

  # Extra linking for the project.
  target_link_libraries(runUnitTests libeboks)

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gmock gtest_main)

  add_test(GTest runUnitTests)
endif()
