cmake_minimum_required(VERSION 3.5)
project(Listener VERSION 1.0.0 LANGUAGES CXX)

add_library(Listener SHARED
        Listener.cpp)

add_library(PolitoceanCommon::Listener ALIAS Listener)

target_include_directories(Listener
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Listener PRIVATE cxx_auto_type)
target_compile_options(Listener PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Listener
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
