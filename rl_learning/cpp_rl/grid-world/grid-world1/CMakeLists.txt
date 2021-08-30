cmake_minimum_required(VERSION 3.10)

project(grid-world)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")

# 设定头文件与源文件的路径
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 画图库
# include_directories(/usr/local/include/gnuplot)


# 包含自定义的头文件
include_directories(${INCROOT})

set(SOURCE_FILES main.cpp)

# 所有的自定义头文件集
set(FILES_HEADER
    ${INCROOT}/constants.h
    ${INCROOT}/gridWorld.h
    ${INCROOT}/world.h
    ${INCROOT}/agent.h
    )

# 所有的自定义源文件集
set(FILES_SRC
    ${SRCROOT}/main.cpp
    ${SRCROOT}/gridWorld.cpp
    ${SRCROOT}/world.cpp
    ${SRCROOT}/agent.cpp
    # ${SRCROOT}/SimpleGnuplot.cpp
    )

# 生成可执行文件
add_executable(run ${FILES_HEADER} ${FILES_SRC})

# boost库
# find_package(Boost REQUIRED COMPONENTS iostreams system thread)
# include_directories(${Boost_INCLUDE_DIRS})
# target_link_libraries(run ${Boost_LIBRARIES})

# Eigen3 线性代数库
find_package(Eigen3 3.3.9 REQUIRED)
if (Eigen3_FOUND)
    message(STATUS "Found Eigen3 in: ${EIGEN3_INCLUDE_DIRS}")
    include_directories(${EIGEN3_INCLUDE_DIRS})
endif()

# SFML库
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()
