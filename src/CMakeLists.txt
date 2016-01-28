

add_library(network SHARED Buffer.cpp IODispatcher.cpp Client.cpp Server.cpp)

#add custom lib flags
add_definitions(-std=c++11 -O3)

