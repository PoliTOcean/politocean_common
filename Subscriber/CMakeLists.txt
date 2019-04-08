cmake_minimum_required(VERSION 3.13)
project(Subscriber)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(subscriber SHARED
        src/Subscriber.cpp)
target_link_libraries(subscriber -lpaho-mqttpp3)

install(TARGETS publisher
        LIBRARY DESTINATION /usr/local/lib
        ARCHIVE DESTINATION /usr/local/lib
        RUNTIME DESTINATION /usr/local/bin
        INCLUDES DESTINATION /usr/local/include)
