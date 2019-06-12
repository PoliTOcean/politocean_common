cmake_minimum_required(VERSION 3.5)
project(QueuedListener VERSION 1.0.0 LANGUAGES CXX)

add_library(QueuedListener SHARED
        QueuedListener.cpp)

add_library(PolitoceanCommon::QueuedListener ALIAS QueuedListener)

target_link_libraries(QueuedListener PolitoceanCommon::Listener)

target_include_directories(QueuedListener
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(QueuedListener PRIVATE cxx_auto_type)
target_compile_options(QueuedListener PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS QueuedListener
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
