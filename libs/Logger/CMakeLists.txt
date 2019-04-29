cmake_minimum_required(VERSION 3.5)
project(logger VERSION 1.0.0 LANGUAGES CXX)

add_library(logger
        logger.cpp)

add_library(PolitoceanCommon::logger ALIAS logger)

target_include_directories(logger
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(logger -lstdc++fs)

target_compile_features(logger PRIVATE cxx_auto_type)
target_compile_options(logger PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS logger
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
