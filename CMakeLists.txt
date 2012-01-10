cmake_minimum_required(VERSION 2.8)
project(CPPLOT)
find_package(GLUT)
find_package(OpenGL)

add_subdirectory(lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/gl2ps)

find_package( Boost COMPONENTS thread )
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )

include_directories(${PROJECT_SOURCE_DIR}/include)

option(CPPLOT_BUILD_EXAMPLES "Build examples" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-ggdb -Wall -Wextra")

add_subdirectory(src)


###
### Examples
###
if(CPPLOT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
