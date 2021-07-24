cmake_minimum_required(VERSION 3.10)

project(1day)

# set(CMAKE_C_COMPILER_INIT g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(GNUPLOT /usr/local/include/gnuplot)

find_package(Boost REQUIRED COMPONENTS iostreams system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(example1 ./example1.cpp)
target_link_libraries(example1 ${Boost_LIBRARIES})
