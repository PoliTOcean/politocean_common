cmake_minimum_required(VERSION 3.13)
project(Publisher)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(publisher SHARED
        src/Publisher.cpp)
target_link_libraries(publisher -lpaho-mqttpp3)

install(TARGETS publisher
        LIBRARY DESTINATION /usr/local/lib
        ARCHIVE DESTINATION /usr/local/lib
        RUNTIME DESTINATION /usr/local/bin
        INCLUDES DESTINATION /usr/local/include)