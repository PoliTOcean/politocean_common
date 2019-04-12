cmake_minimum_required(VERSION 3.5)
project(Subscriber VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)


add_library(Subscriber SHARED
        src/Subscriber.cpp)

add_library(Politocean::Subscriber ALIAS Subscriber)


target_include_directories(Subscriber
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Subscriber -lpaho-mqttpp3)

target_compile_features(Subscriber PRIVATE cxx_auto_type)
target_compile_options(Subscriber PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Subscriber
        EXPORT PolitoceanTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

