cmake_minimum_required(VERSION 3.5)
project(PolitoceanCommon)

include_directories(include)

# Add here all libraries' directories
#add_subdirectory(name_of_directory)
add_subdirectory(libs/Logger)
add_subdirectory(libs/mqttLogger)
add_subdirectory(libs/Publisher)
add_subdirectory(libs/Subscriber)
add_subdirectory(libs/Sensor)
add_subdirectory(libs/MqttClient)


# Install and export (do not touch this part)
install(
  EXPORT PolitoceanCommonTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanCommon
  NAMESPACE PolitoceanCommon::
  FILE PolitoceanCommonTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "PolitoceanCommonConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanCommon
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PolitoceanCommonConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanCommonConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanCommonConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanCommon"
  )
