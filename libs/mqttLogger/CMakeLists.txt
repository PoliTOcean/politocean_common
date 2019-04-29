cmake_minimum_required(VERSION 3.5)
project(mqttLogger VERSION 1.0.0 LANGUAGES CXX)

add_library(mqttLogger
        mqttLogger.cpp)

add_library(PolitoceanCommon::mqttLogger ALIAS mqttLogger)

target_include_directories(mqttLogger
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mqttLogger PolitoceanCommon::logger PolitoceanCommon::Publisher)

target_compile_features(mqttLogger PRIVATE cxx_auto_type)
target_compile_options(mqttLogger PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS mqttLogger
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
