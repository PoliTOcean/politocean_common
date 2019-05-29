cmake_minimum_required(VERSION 3.5)
project(Subscriber VERSION 1.0.0 LANGUAGES CXX)

add_library(Subscriber SHARED
        Subscriber.cpp)

add_library(PolitoceanCommon::Subscriber ALIAS Subscriber)

target_include_directories(Subscriber
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Subscriber -lpaho-mqttpp3 -lpaho-mqtt3a PolitoceanCommon::logger)

target_compile_features(Subscriber PRIVATE cxx_auto_type)
target_compile_options(Subscriber PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Subscriber
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
