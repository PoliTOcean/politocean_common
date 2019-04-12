cmake_minimum_required(VERSION 3.5)
project(Publisher VERSION 1.0.0 LANGUAGES CXX)

add_library(Publisher
        src/Publisher.cpp)

add_library(Politocean::Publisher ALIAS Publisher)

target_include_directories(Publisher
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Publisher -lpaho-mqttpp3)

target_compile_features(Publisher PRIVATE cxx_auto_type)
target_compile_options(Publisher PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Publisher
        EXPORT PolitoceanTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
