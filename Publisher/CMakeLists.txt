cmake_minimum_required(VERSION 3.5)
project(Publisher VERSION 1.0.0 LANGUAGES CXX)

add_library(Publisher
        src/Publisher.cpp)

target_include_directories(Publisher
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Publisher -lphao-mqttpp3)

target_compile_features(Publisher PRIVATE cxx_auto_type)
target_compile_options(Publisher PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Publisher)

install(TARGETS Publisher
        EXPORT Publisher-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT Publisher-targets
        FILE PublisherTargets.cmake
        NAMESPACE Publisher::
        DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/PublisherConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/PublisherConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PublisherConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/PublisherConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/PublisherConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT Publisher-targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/PublisherTargets.cmake
        NAMESPACE Publisher::
)

export(PACKAGE Publisher)
