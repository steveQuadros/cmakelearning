cmake_minimum_required(VERSION 3.20)
project(Hello)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

# Google Test from: https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# START so comment copypasta
# found in SO comment: 
# https://stackoverflow.com/questions/56511716/cmake-file-for-a-folly-project
find_package(Boost REQUIRED)
find_package(folly REQUIRED)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# NO IDEA WHY THESE ARE COMMENTED OUT 
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${folly_INCLUDE_DIRS})

set_and_check(FOLLY_INCLUDE_DIR /opt/homebrew/include/folly)
set_and_check(FOLLY_CMAKE_DIR /opt/homebrew/lib/cmake/folly)
if (NOT TARGET Folly::folly)
  include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif()

set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
  message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif()

add_executable(Hello Hello.cpp)
target_link_libraries(Hello  ${Boost_LIBRARIES} ${FOLLY_LIBRARIES})
#END SO Comment copypasta

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)