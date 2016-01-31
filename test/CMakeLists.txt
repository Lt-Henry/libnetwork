

add_executable(server server.cpp)
add_executable(client client.cpp)


target_link_libraries (client LINK_PUBLIC network pthread)
target_link_libraries (server LINK_PUBLIC network pthread)

#add custom lib flags
add_definitions(-std=c++11 -O3)

