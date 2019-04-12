cmake_minimum_required(VERSION 3.10)
project(Politocean)

add_subdirectory(Publisher)
add_subdirectory(Subscriber)
add_subdirectory(Sensor)



install(
  EXPORT PolitoceanTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Politocean
  NAMESPACE Politocean::
  FILE PolitoceanTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "PolitoceanConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Politocean
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PolitoceanConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Politocean"
  )