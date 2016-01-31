

add_library(network SHARED Buffer.cpp IODispatcher.cpp Client.cpp Server.cpp)

target_include_directories (network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add custom lib flags
add_definitions(-std=c++11 -O3)

