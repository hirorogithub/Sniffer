cmake_minimum_required(VERSION 2.8)

project(sniffer)
add_executable(${PROJECT_NAME} "main.c" "network_capture.c"
                                "usage.c" "protocol_parse.c"
                                "debug.c" packet-sniffer.h  BasicData.cpp BasicData.h ICMPData.cpp ICMPData.h Manager.cpp Manager.h TCPData.cpp TCPData.h UDPData.cpp UDPData.h main.cpp Utility.h)

set_target_properties(sniffer PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        )