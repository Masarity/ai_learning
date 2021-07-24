cmake_minimum_required(VERSION 3.10)

project(mySimpleLib)

set(CMAKE_CXX_STANDARD 17)

set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(/usr/local/include/gnuplot)
find_package(Boost REQUIRED COMPONENTS iostreams system thread)
include_directories(${Boost_INCLUDE_DIRS})


include_directories(${INCROOT})

set(FILES_HERD 
    ${INCROOT}/SimpleGnuplot.hpp
    )

set(
    FILES_SRC 
    ${SRCROOT}/main.cpp 
    ${SRCROOT}/SimpleGnuplot.cpp
    )

add_executable(run ${FILES_HERD} ${FILES_SRC})
target_link_libraries(run ${Boost_LIBRARIES})

