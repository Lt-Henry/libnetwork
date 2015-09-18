
cmake_minimum_required (VERSION 2.6)
project (libnetwork)


add_library(network SHARED Buffer.cpp IODispatcher.cpp Client.cpp Server.cpp)


#require pkg-config support
find_package(PkgConfig REQUIRED)

#required pkg-config libs
#pkg_check_modules(CAIRO REQUIRED cairo)

#add include dirs
#include_directories(${CMAKE_SOURCE_DIR}/include/lgi-1.0 ${CAIRO_INCLUDE_DIRS})

#add custom lib flags
add_definitions(-std=c++11 -O3)

