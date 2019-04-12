cmake_minimum_required(VERSION 3.13)
project(Subscriber VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)


add_library(Subscriber SHARED
        src/Subscriber.cpp)

target_link_directories(Subscriber
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Subscriber -lpaho-mqttpp3)

include(GNUInstallDirs)

install(TARGETS Subscriber
        EXPORT subscriber-export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT subscriber-export
        FILE SubscriberTargets.cmake
        NAMESPACE Subscriber::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Subscriber
)

