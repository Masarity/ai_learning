cmake_minimum_required(VERSION 3.10)

# set(box2d_DIR=/usr/local/lib/cmake/box2d/)
# set(CMAKE_MODULE_PATH "/usr/local/lib/cmake/box2d")
project(test_box2d)
set(CMAKE_BUILD_TYPE "Debug")
# find_package(box2d REQUIRED)
include_directories(box2d /usr/local/include/box2d)
# message(${CMAKE_MODULE_PATH})
# if (box2d_FIND)
    # message(${box2d_INCLUDE_DIRS})
    # include_directories(${box2d_INCLUDE_DIRS})
# endif()

add_executable(run main2.cpp)

target_link_libraries(run box2d)




