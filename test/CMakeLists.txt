

add_executable(server server.cpp)
add_executable(client client.cpp)

#add custom lib flags
add_definitions(-std=c++11 -O3)

