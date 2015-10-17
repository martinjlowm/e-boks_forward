########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(libeboks CXX C)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")

option(test "Build all tests." OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(curl)
find_package(pugixml)

########################################################################
# Setup the include and linker paths
########################################################################
include_directories(
    src
    ${libcurl_INCLUDE_DIRS}
    ${pugixml_INCLUDE_DIRS}
    ${CPPUNIT_INCLUDE_DIRS}
)

link_directories(
  ${libcurl_LIBRARY_DIRS}
  ${pugixml_LIBRARY_DIRS}
  ${CPPUNIT_LIBRARY_DIRS}
)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(eboks ${SRC_FILES})
target_link_libraries(eboks ${libcurl_LIBRARIES} pugixml)

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
  file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
  foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(EXEC_TEST_FILE ${TEST_FILE} NAME_WE)
    add_executable(${EXEC_TEST_FILE} ${TEST_FILE})

    # Extra linking for the project.
    target_link_libraries(${EXEC_TEST_FILE} eboks)

    # Standard linking to gtest stuff.
    target_link_libraries(${EXEC_TEST_FILE} gtest gmock gtest_main)

    add_test(${EXEC_TEST_FILE} ${EXEC_TEST_FILE})
  endforeach(TEST_FILE)
endif()
