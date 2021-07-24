cmake_minimum_required(VERSION 3.10)

project(10-armed-testbed)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")

# 设定头文件与源文件的路径
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 画图库
include_directories(/usr/local/include/gnuplot)
find_package(Boost REQUIRED COMPONENTS iostreams system thread)
include_directories(${Boost_INCLUDE_DIRS})


# 包含自定义的头文件
include_directories(${INCROOT})

set(SOURCE_FILES main.cpp)

# 所有的自定义头文件集
set(FILES_HEADER
    ${INCROOT}/KarmedBandit.h
    ${INCROOT}/EstimateMethods.hpp
    ${INCROOT}/SimpleGnuplot.hpp
    )

# 所有的自定义源文件集
set(FILES_SRC
    ${SRCROOT}/main.cpp
    ${SRCROOT}/KarmedBandit.cpp
    ${SRCROOT}/EstimateMethods.cpp
    ${SRCROOT}/SimpleGnuplot.cpp
    )

# 生成可执行文件
add_executable(run ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(run ${Boost_LIBRARIES})

