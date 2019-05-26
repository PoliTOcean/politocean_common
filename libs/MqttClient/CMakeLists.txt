cmake_minimum_required(VERSION 3.5)
project(MqttClient VERSION 1.0.0 LANGUAGES CXX)

add_library(MqttClient SHARED
        MqttClient.cpp)

add_library(PolitoceanCommon::MqttClient ALIAS MqttClient)

target_include_directories(MqttClient
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MqttClient mosquittopp PolitoceanCommon::logger)

target_compile_features(MqttClient PRIVATE cxx_auto_type)
target_compile_options(MqttClient PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS MqttClient
        EXPORT PolitoceanCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
