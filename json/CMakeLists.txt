cmake_minimum_required(VERSION 3.5)
project(json VERSION 1.0.0 LANGUAGES CXX)

add_library(json
                json.cpp)

add_library(PolitoceanCommon::json ALIAS json)

target_include_directories(json
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(json PRIVATE cxx_auto_type)
target_compile_options(json PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS json
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
