project(TCPCLIENTSYNC)

#
#
add_executable(TcpClientSync TcpClientSync.cpp)

find_package(Boost COMPONENTS thread system date_time REQUIRED)
target_link_libraries(TcpClientSync pthread ${Boost_LIBRARIES})

