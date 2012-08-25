project(TCPSERVERSYNC)

#
#
add_executable(TcpServerSync TcpServerSync.cpp)

find_package(Boost COMPONENTS thread system date_time REQUIRED)
target_link_libraries(TcpServerSync pthread ${Boost_LIBRARIES})

