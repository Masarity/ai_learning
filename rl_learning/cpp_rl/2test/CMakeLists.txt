cmake_minimum_required(VERSION 3.10)

# set(box2d_DIR=/usr/local/lib/cmake/box2d/)
# set(CMAKE_MODULE_PATH "/usr/local/lib/cmake/box2d")
project(test_mlpack)
set(CMAKE_BUILD_TYPE "Debug")
# find_package(box2d REQUIRED)
# find_package(MLPACK REQUIRED)
# find_package(mlpack)
FIND_PACKAGE( OpenMP REQUIRED )
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(mlpack /usr/local/include/mlpack)
# message(${CMAKE_MODULE_PATH})
# if (box2d_FIND)
    # message(${box2d_INCLUDE_DIRS})
    # include_directories(${box2d_INCLUDE_DIRS})
# endif()

add_executable(run main.cpp)
target_link_libraries(run mlpack)





