cmake_minimum_required(VERSION 3.5)
project(Component VERSION 1.0.0 LANGUAGES CXX)

add_library(Component SHARED
        Component.cpp)

add_library(PolitoceanCommon::Component ALIAS Component)

target_include_directories(Component
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Component PRIVATE cxx_auto_type)
target_compile_options(Component PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Component
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)